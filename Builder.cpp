#include "Builder.h"

Unit* CharacterBuilder::GetCharacter() {
    return character_;
}

///////////////////////////////////////////////////////////////    Character Generator (Director)

CharacterGenerator::CharacterGenerator() : builder_(nullptr) {}

void CharacterGenerator::SetBuilder(CharacterBuilder* builder) {
    builder_ = builder;
}

Unit* CharacterGenerator::GetUnit() {
    return builder_->GetCharacter();
}

void CharacterGenerator::MakeNewUnit() {
    builder_->CreateNewUnit();
}

void CharacterGenerator::CreateUnitsConfiguration() {
    builder_->BuildHealthPoints();
    builder_->BuildMeleeForce();
    builder_->BuildPowerOfMagic();
    builder_->BuildFraction();
    builder_->BuildUnitName();
}

/////////////////////////////////////////////////////////////// Builders

Unit* HordeWarriorBuilder::CreateNewUnit() {
    character_ = new HordeWarrior;
}

void HordeWarriorBuilder::BuildHealthPoints() {
    character_->SetHealthPoints(15);
}

void HordeWarriorBuilder::BuildMeleeForce() {
    character_->SetMeleeForce(18);
}

void HordeWarriorBuilder::BuildPowerOfMagic() {
    character_->SetPowerOfMagic(0);
}

void HordeWarriorBuilder::BuildFraction() {
    character_->SetFraction("Horde");
}

void HordeWarriorBuilder::BuildUnitName()  {
    character_->SetUnitName("Warrior");
}

/////////////////////////////////////////////////

Unit* AllianceHealerBuilder::CreateNewUnit() {
    character_ = new AllianceHealer;
}

void AllianceHealerBuilder::BuildHealthPoints() {
    character_->SetHealthPoints(10);
}

void AllianceHealerBuilder::BuildMeleeForce() {
    character_->SetMeleeForce(0);
}

void AllianceHealerBuilder::BuildPowerOfMagic() {
    character_->SetPowerOfMagic(5);
}

void AllianceHealerBuilder::BuildFraction() {
    character_->SetFraction("Alliance");
}

void AllianceHealerBuilder::BuildUnitName()  {
    character_->SetUnitName("Healer");
}

///////////////////////////////////////////////////////

Unit* AllianceWarriorBuilder::CreateNewUnit() {
    character_ = new AllianceWarrior;
}

void AllianceWarriorBuilder::BuildHealthPoints() {
    character_->SetHealthPoints(15);
}

void AllianceWarriorBuilder::BuildMeleeForce() {
    character_->SetMeleeForce(18);
}

void AllianceWarriorBuilder::BuildPowerOfMagic() {
    character_->SetPowerOfMagic(0);
}

void AllianceWarriorBuilder::BuildFraction() {
    character_->SetFraction("Alliance");
}

void AllianceWarriorBuilder::BuildUnitName()  {
    character_->SetUnitName("Warrior");
}

///////////////////////////////////////////////////

Unit* HordeHealerBuilder::CreateNewUnit() {
    character_ = new HordeHealer;
}

void HordeHealerBuilder::BuildHealthPoints() {
    character_->SetHealthPoints(10);
}

void HordeHealerBuilder::BuildMeleeForce() {
    character_->SetMeleeForce(0);
}

void HordeHealerBuilder::BuildPowerOfMagic() {
    character_->SetPowerOfMagic(5);
}

void HordeHealerBuilder::BuildFraction() {
    character_->SetFraction("Horde");
}

void HordeHealerBuilder::BuildUnitName()  {
    character_->SetUnitName("Healer");
}
