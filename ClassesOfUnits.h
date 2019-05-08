#pragma once
#include<iostream>

class Unit {
    friend class TestWarriorWithFraction;
    friend class TestHealerWithFraction;
public:
    virtual ~Unit() = default;

    virtual void ToDamage(Unit* unit) = 0;

    virtual void ToHeal(Unit* unit) = 0;

    virtual void FractionAction() = 0;

    void SetHealthPoints(int points);

    void SetMeleeForce(int points);

    void SetPowerOfMagic(int points);

    void SetFraction(const std::string& fraction);

    void SetUnitName(const std::string& unit_class);

    int GetHP();

    int GetMF();

    int GetPM();

    std::string GetFraction();

    std::string GetUnitName();

protected:
    int health_points_ = 0;
    int melee_force = 0;
    int power_of_magic_ = 0;
    std::string fraction_;
    std::string unit_name_;
};

class Warrior : public Unit {
public:
    Warrior() {}

    virtual ~Warrior() override = default;

    virtual void ToDamage(Unit* unit) override;

    virtual void ToHeal(Unit* unit) override;
};

class HordeWarrior : public Warrior {
public:
    virtual void FractionAction() override;
};

class AllianceWarrior : public Warrior {
    virtual void FractionAction() override;
};

class Healer : public Unit {
public:
    Healer() {};

    virtual ~Healer() override = default;

    virtual void ToDamage(Unit* unit) override;

    virtual void ToHeal(Unit* unit) override;
};

class HordeHealer : public Healer {
public:
    virtual void FractionAction() override;
};

class AllianceHealer : public Healer {
    virtual void FractionAction() override;
};