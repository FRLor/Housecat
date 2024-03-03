#pragma once

struct DamageAreaComponent {
	bool isFriendly;
	int hitPercentDamage;

	DamageAreaComponent(bool isFriendly = false, int hitPercentDamage = 0) {
		this->isFriendly = isFriendly;
		this->hitPercentDamage = hitPercentDamage;
	}
};