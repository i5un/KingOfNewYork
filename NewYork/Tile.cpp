#include "Tile.h"

Tile::Tile(UnitP a, UnitP b)
	:building(a),army(b)
{
}

Tile::~Tile()
{
}

const UnitP Tile::getUnit() const{
	if (building->destroyed) {		
		if (army->destroyed) return nullptr;
		return building;
	}
	else {
		return building;
	}
}

void Tile::destroyUnit(Player* p,int dPoints) {
	UnitP target = getUnit();
	if (dPoints < target->getHp()) throw FailException("Insufficient Destruction points!");
	if (target != nullptr) {
		p->collectResources(target->getReward());
		target->destroyed = true;
	}
}

ostream& operator<<(ostream& os, const TileP& tile) {
	UnitP unit = tile->getUnit();
	os << "["<<unit->getName()<<"] ";
	os << "HP: " << unit->getHp();
	os << "  Reward: " << unit->getReward().first << " x" << unit->getReward().second << nl;
	return os;
}