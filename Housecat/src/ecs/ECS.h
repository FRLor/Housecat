#pragma once

#include <set>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include <deque>

#include "../logger/Logger.h"

//REMIND
//change later (if past 32 comps.)
const unsigned int MAX_COMPONENTS = 32;


//-----------------------------------------------------//
//                    SIGNATURE                        //
//  Used bitset to track which components each entity  //
//  has and tracks which entities a system wants       //
//-----------------------------------------------------//
typedef std::bitset<MAX_COMPONENTS> Signature;





//-----------------------------------------------------//
//                    COMPONENT                        //
//           base for all compontent types             //
//-----------------------------------------------------//
struct IComponent {
protected:
	static int nextID;
};

//give unique ID to component type
template <typename T>
class Component: public IComponent {
public:
	static int GetID() {
		static auto ID = nextID++;
		return ID;
	}
};





//--------------------------------------------------//
//                    ENTITY                        //
//  each entity generates unique ID for management  //
//--------------------------------------------------//
class Entity {
private:
	int ID;

public:
	//Entity() = default;
	Entity(int ID) : ID(ID), housecat(nullptr) {}
	Entity(const Entity& entity) = default;

	int GetID() const;
	void Kill();

	bool operator==(const Entity& other) const {
		return ID == other.ID;
	}
	bool operator!=(const Entity & other) const {
		return ID != other.ID;
	}
	bool operator >(const Entity& other) const {
		return ID > other.ID; 
	}
	bool operator <(const Entity& other) const {
		return ID < other.ID; 
	}
	Entity& operator=(const Entity& other) = default;

	//REMIND
	//might not be needed?
	bool operator >=(const Entity& other) const {
		return ID >= other.ID;
	}
	bool operator <=(const Entity& other) const {
		return ID <= other.ID;
	}

	template <typename TComponent, typename ...TArgs> bool HasComponent() const;
	template <typename TComponent> TComponent& GetComponent() const;
	template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&& ...args);
	template <typename TComponent, typename ...TArgs> void RemoveComponent();

	//TODO? smart ptr
	// class std::weak_ptr<Housecat> housecat;
	class Housecat* housecat;

};




//--------------------------------------------------//
//                    SYSTEM                        //
// Process entities containing specific signature   //
//--------------------------------------------------//
class System {
private:
	Signature componentSignature;
	std::vector<Entity> entities;

public:
	System() = default;
	~System() = default;

	std::vector<Entity> GetSystemEntities() const;
	const Signature& GetComponentSignature() const;

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);

	//components type from entity before system called
	template <typename TComponent> void RequireComponent();
};





//-----------------------------------------//
//                  POOL                   //
//  Vector used for each object of type T  //
//-----------------------------------------//
class IPool {
public:
	virtual ~IPool() {}
};

template <typename T>
class Pool: public IPool {
private:
	int size;
	std::vector<T> data;

	//TODO
	//track entity IDs per index?
	//unordered_map<int, int>
public:
	//REMIND
	Pool(int size = 100) {
		//fix
		size = 0;
		data.resize(size);
	}

	virtual ~Pool() = default;

	int GetSize() const {
		return data.size();
	}

	bool IsEmpty() const {
		return data.empty();
	}

	void Resize(int n) {
		data.resize(n);
	}

	void Add(T object) {
		data.push_back(object);
	}

	void Clear() {
		data.clear();
		//reset
		size = 0;
	}

	//TODO
	//map entityID -> component
	//eror handling: if entity has component, update component index
	//else, add new component??
	void Set(int index, T object) {
		data[index] = object;
	}

	//TODO
	//void Remove(entity) 
	//s
	
	//TODO
	//error handling: entityID[entityID] ?
	T& Get(int index) {
		return static_cast<T&>(data[index]);
	}
	
	//no err
	T& operator [](unsigned int index) {
		return data[index];
	}
};



//----------------------------------------------------//
//                     HOUSECAT                       //
//               (Manager | Registry)                 //
//    Manages creation | destruction of entities      //
//  also adds systems and components to each entity   //
//         Call Housecat to manage entities           //
//----------------------------------------------------//
class Housecat {
private:
	int numOfEntities = 0;

	std::set<Entity> entitiesToAdd;
	std::set<Entity> entitiesToKill;

	//each pool has all data for certain component type
	//vector index = component type ID
	//Pool index = entity ID
	std::vector<std::shared_ptr<IPool>> componentPools;

	//which components an entity has?
	//vector index = entityt ID
	std::vector<Signature> entityComponentSignatures;

	//what are the active systems?
	//index = system typeID
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

	//lists freed entity IDs
	std::deque<int> freedIDs;

	//TODO?
	//std::shared_ptr<Housecat> housecat;



public:
	Housecat() {
		Logger::Lifecycle("Housecat Manager Constructor Called!");
	}
	~Housecat() {
		Logger::Lifecycle("Housecat Manager Destructor Called!");
	}

	//Entity management
	Entity CreateEntity();

	void KillEntity(Entity entity);

	//TODO entity management
	//freeze?
	//tagging and? grouping

	//check component signature before adding | removing to system
	void AddEntityToSystems(Entity entity);
	void RemoveEntityFromSystems(Entity entity);

	void Update();

	//Component management
	template <typename TComponent> bool HasComponent(Entity entity) const;
	template <typename TComponent> TComponent& GetComponent(Entity entity) const;
	template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
	template <typename TComponent> void RemoveComponent(Entity entity);

	//Systems management
	template <typename TSystem> TSystem& GetSystem() const;
	template <typename TSystem> bool HasSystem() const;
	template <typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
	template <typename TSystem> void RemoveSystem();
};





//----------------------------------------//
//                TEMPLATES               //
//----------------------------------------//
template <typename TComponent, typename ...TArgs>
bool Entity::HasComponent() const {
	return housecat->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
TComponent& Entity::GetComponent() const {
	return housecat->GetComponent<TComponent>(*this);
}

template <typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs&& ...args) {
	housecat->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent, typename ...TArgs>
void Entity::RemoveComponent() {
	housecat->RemoveComponent<TComponent>(*this);
}





template <typename TComponent>
void System::RequireComponent() {
	const auto componentID = Component<TComponent>::GetID();
	componentSignature.set(componentID);
}





template <typename TSystem>
TSystem& Housecat::GetSystem() const {
	auto system = systems.find(std::type_index(typeid(TSystem)));
	return *(std::static_pointer_cast<TSystem>(system->second));
}

template <typename TSystem>
bool Housecat::HasSystem() const {
	return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem, typename ...TArgs>
void Housecat::AddSystem(TArgs&& ...args) {
	std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
	systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Housecat::RemoveSystem() {
	auto system = systems.find(std::type_index(typeid(TSystem)));
	systems.erase(system);
}

template <typename TComponent>
bool Housecat::HasComponent(Entity entity) const {
	const auto componentID = Component<TComponent>::GetID();
	const auto entityID = entity.GetID();

	return entityComponentSignatures[entityID].test(componentID);
}

template <typename TComponent>
TComponent& Housecat::GetComponent(Entity entity) const {
	const auto componentID = Component<TComponent>::GetID();
	const auto entityID = entity.GetID();
	auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentID]);
	
	return componentPool->Get(entityID);
}

template <typename TComponent, typename ...TArgs>
void Housecat::AddComponent(Entity entity, TArgs&& ...args) {
	const auto componentID = Component<TComponent>::GetID();
	const auto entityID = entity.GetID();

	//resize pool index based off num of component IDs
	if (componentID >= static_cast<int>(componentPools.size())) {
		componentPools.resize(componentID + 1, nullptr);
	}
	//using index vector, create new pool for component type
	if (!componentPools[componentID]) {
		//TODO: use smart pointers
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		componentPools[componentID] = newComponentPool;
	}

	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentID]);

	//resize pool based off num of entity IDs
	if (entityID >= componentPool->GetSize()) {
		componentPool->Resize(numOfEntities);
	}

	TComponent newComponent(std::forward<TArgs>(args)...);

	componentPool->Set(entityID, newComponent);
	//set bitset index to component ID
	entityComponentSignatures[entityID].set(componentID);

	Logger::Log("Component ID [" + std::to_string(componentID) + "] Added to Entity ID [" + std::to_string(entityID) + "]");
}

template <typename TComponent>
void Housecat::RemoveComponent(Entity entity) {
	const auto componentID = Component<TComponent>::GetID();
	const auto entityID = entity.GetID();

	entityComponentSignatures[entityID].set(componentID, false);

	Logger::Log("Component ID [" + std::to_string(componentID) + "] Removed from Component ID [" + std::to_string(entityID) + "]");
}
