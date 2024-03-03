#include <algorithm>

#include "ECS.h"



//--------------------------------------------------//
//                    COMPONENT                     //
//--------------------------------------------------//
int IComponent::nextID = 0;





//--------------------------------------------------//
//                    ENTITY                        //
//--------------------------------------------------//
int Entity::GetID() const {
	return ID;
}

void Entity::Kill() {
	housecat->KillEntity(*this);
}

//REMIND
//TODO

//freeze
//tag and? group
//Tag(), NeedsTag(), GetTag(), HasTag()





//--------------------------------------------------//
//                    SYSTEM                        //
//--------------------------------------------------//
std::vector<Entity> System::GetSystemEntities() const {
	return entities;
}

const Signature& System::GetComponentSignature() const {
	return componentSignature;
}

void System::AddEntityToSystem(Entity entity) {
	entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
	//TODO
	//HORRIBLE SYNTAX. FIX LATER
	entities.erase(std::remove_if(entities.begin(),entities.end(),[&entity](Entity other) {
		return entity == other;
	}), entities.end());
}






//--------------------------------------------------//
//                    HOUSECAT                      //
//--------------------------------------------------//
Entity Housecat::CreateEntity() {
	int entityID;

	if (freedIDs.empty()) {
		entityID = numOfEntities++;
		if (entityID >= entityComponentSignatures.size()) {
			entityComponentSignatures.resize(entityID + 1);
		}
	}
	else {
		//reuse IDs
		entityID = freedIDs.front();
		freedIDs.pop_front();
	}

	Entity entity(entityID);
	entity.housecat = this;
	entitiesToAdd.insert(entity);

	//TODO smart ptr
	//entity.housecat = std::weak_ptr<Housecat>(std::shared_ptr<Housecat>());

	if (static_cast<unsigned int>(entityID) >= entityComponentSignatures.size()) {
		entityComponentSignatures.resize(entityID + 1);
	}

	//TODO
	//try entity ID reusability design?

	//REMIND TESTING remove latr
	Logger::Log("Entity [" + std::to_string(entityID) + "] Created!");

	return entity;
}

void Housecat::KillEntity(Entity entity) {
	entitiesToKill.insert(entity);
}

void Housecat::AddEntityToSystems(Entity entity) {
	const auto entityID = entity.GetID();
	const auto& entityComponentSignature = entityComponentSignatures[entityID];

	for (auto& system : systems) {
		const auto& systemComponentSignature = system.second->GetComponentSignature();
		//bitset comparisn
		bool interestedFlag = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;
		//matched, adds entity val to system
		if (interestedFlag) {
			system.second->AddEntityToSystem(entity);
		}
	}
}

//FIXED
void Housecat::RemoveEntityFromSystems(Entity entity) {
	for (auto system : systems) {
		system.second->RemoveEntityFromSystem(entity);
	}
}

//process housecat management
void Housecat::Update() {
	//creation
	for (auto entity : entitiesToAdd) {
		AddEntityToSystems(entity);
	}
	entitiesToAdd.clear();

	//deletion
	for (auto entity : entitiesToKill) {
		RemoveEntityFromSystems(entity);
		entityComponentSignatures[entity.GetID()].reset();

		//reuse that ID
		freedIDs.push_back(entity.GetID());
	}
	entitiesToKill.clear();
}

//TODO
//adding entity Kill(), Tag()
//use housecat for management

//Housecat::KillEntity()