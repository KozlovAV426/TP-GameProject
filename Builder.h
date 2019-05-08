#include "ClassesOfUnits.h"

class CharacterBuilder {             // Abstract Builder
    friend class CharacterGeneratorTest;
public:
    virtual ~CharacterBuilder() = default;

    Unit* GetCharacter();

    virtual Unit* CreateNewUnit() = 0;

    virtual void BuildHealthPoints() = 0;

    virtual void BuildMeleeForce() = 0;

    virtual void BuildPowerOfMagic() = 0;

    virtual void BuildFraction() = 0;

    virtual void BuildUnitName() = 0;

protected:
    Unit* character_;
};

class CharacterGenerator {                 // Director
    friend class CharacterGeneratorTest;
private:
    CharacterBuilder* builder_;

public:
    CharacterGenerator();

    void SetBuilder(CharacterBuilder* builder);

    Unit* GetUnit();

    void MakeNewUnit();

    void CreateUnitsConfiguration();
};

class HordeWarriorBuilder : public CharacterBuilder {
public:
    HordeWarriorBuilder() = default;

    virtual Unit* CreateNewUnit() override;

    virtual void BuildHealthPoints() override;

    virtual void BuildMeleeForce() override;

    virtual void BuildPowerOfMagic() override;

    virtual void BuildFraction() override;

    virtual void BuildUnitName() override;
};

class HordeHealerBuilder : public CharacterBuilder {
public:
    HordeHealerBuilder() = default;

    virtual Unit* CreateNewUnit() override;

    virtual void BuildHealthPoints() override;

    virtual void BuildMeleeForce() override;

    virtual void BuildPowerOfMagic() override;

    virtual void BuildFraction() override;

    virtual void BuildUnitName() override;
};

class AllianceWarriorBuilder : public CharacterBuilder {
public:
    AllianceWarriorBuilder() = default;

    virtual Unit* CreateNewUnit() override;

    virtual void BuildHealthPoints() override;

    virtual void BuildMeleeForce() override;

    virtual void BuildPowerOfMagic() override;

    virtual void BuildFraction() override;

    virtual void BuildUnitName() override;
};


class AllianceHealerBuilder : public CharacterBuilder {
public:
    AllianceHealerBuilder() = default;

    virtual Unit* CreateNewUnit() override;

    virtual void BuildHealthPoints() override;

    virtual void BuildMeleeForce() override;

    virtual void BuildPowerOfMagic() override;

    virtual void BuildFraction() override;

    virtual void BuildUnitName() override;

};