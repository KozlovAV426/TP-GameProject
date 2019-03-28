#include "ClassesOfUnits.h"

void Unit::SetHealthPoints(size_t points) {
    health_points_ = points;
}

void Unit::SetMeleeForce(size_t points) {
    melee_force = points;
}

void Unit::SetPowerOfMagic(size_t points) {
    power_of_magic_ = points;
}

void Unit::SetFraction(std::string fraction) {
    fraction_ = fraction;
}

void Unit::SetUnitName(std::string unit_class) {
    unit_name_ = unit_class;
}

size_t Unit::GetHP() {
    return health_points_;
}

size_t Unit::GetPM() {
    return power_of_magic_;
}

size_t Unit::GetMF() {
    return melee_force;
}

std::string Unit::GetFraction() {
    return fraction_;
}

std::string Unit::GetUnitName() {
    return unit_name_;
}

////////////////////////////////////////////////////////  Unit Warrior

void Warrior::ToDamage(Unit &unit) {
    unit.SetHealthPoints(unit.GetHP() - melee_force);
}

void Warrior::ToHeal(Unit &unit) {}


/////////////////////////////////////////////////////// Warrior with Fraction

void HordeWarrior::FractionAction() {
    melee_force += 5;
}

void AllianceWarrior::FractionAction() {
    health_points_ += 10;
}

///////////////////////////////////////////////////////   Unit Healer

void Healer::ToDamage(Unit &unit) {}

void Healer::ToHeal(Unit &unit) {
    unit.SetHealthPoints(unit.GetHP() + power_of_magic_);
}

/////////////////////////////////////////////////////// Healer with Fraction

void HordeHealer::FractionAction() {
    power_of_magic_ += 5;
}

void AllianceHealer::FractionAction() {
    health_points_ += 10;
};