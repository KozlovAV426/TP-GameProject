#include <gtest/gtest.h>
#include "../ClassesOfUnits.h"

class TestWarriorWithFraction : public ::testing::Test {
public:
    ~TestWarriorWithFraction() {
        delete horde_warrior;
        delete alliance_warrior;
    }
protected:
    virtual void SetUp() {
        horde_warrior = new HordeWarrior;
        alliance_warrior = new AllianceWarrior;
    }

     Unit* horde_warrior;
     Unit* alliance_warrior;

    size_t GetHealthHWarrior() {
        return horde_warrior->health_points_;
    }

    size_t GetHealthAWarrior() {
        return alliance_warrior->health_points_;
    }

    size_t GetMFHWarrior() {
        return horde_warrior->melee_force;
    }

    size_t GetMFAWarrior() {
        return alliance_warrior->melee_force;
    }

    size_t GetPOFHWarrior() {
        return horde_warrior->power_of_magic_;
    }

    size_t GetPOFAWarrior() {
        return alliance_warrior->power_of_magic_;
    }

    std::string GetUNHWarrior() {
        return horde_warrior->unit_name_;
    }

    std::string GetUNAWarrior() {
        return alliance_warrior->unit_name_;
    }

    std::string GetFHWarrior() {
        return horde_warrior->fraction_;
    }

    std::string GetFAWarrior() {
        return alliance_warrior->fraction_;
    }

};

TEST_F(TestWarriorWithFraction, GetHP_Test) {
    EXPECT_EQ(GetHealthHWarrior(), horde_warrior->GetHP());
    EXPECT_EQ(GetHealthAWarrior(), alliance_warrior->GetHP());
}

TEST_F(TestWarriorWithFraction, GetMF_Test) {
    EXPECT_EQ(GetMFAWarrior(), alliance_warrior->GetMF());
    EXPECT_EQ(GetMFHWarrior(), horde_warrior->GetMF());
}

TEST_F(TestWarriorWithFraction, GetPOF_Test) {
    EXPECT_EQ(GetPOFAWarrior(), alliance_warrior->GetPM());
    EXPECT_EQ(GetPOFHWarrior(), horde_warrior->GetPM());
}

TEST_F(TestWarriorWithFraction, SetHealthPoints_Test) {
    size_t expected_hp = GetHealthHWarrior();
    horde_warrior->SetHealthPoints(GetHealthHWarrior() + 10);
    expected_hp += 10;
    EXPECT_EQ(GetHealthHWarrior(), expected_hp);
    horde_warrior->SetHealthPoints(GetHealthHWarrior() - 8);
    expected_hp -= 8;
    EXPECT_EQ(GetHealthHWarrior(), expected_hp);
    expected_hp = GetHealthAWarrior();
    alliance_warrior->SetHealthPoints(GetHealthAWarrior() + 100);
    expected_hp += 100;
    EXPECT_EQ(GetHealthAWarrior(), expected_hp);
}

TEST_F(TestWarriorWithFraction, SetMeleeForce_Test) {
    size_t expected_mf = GetMFHWarrior();
    horde_warrior->SetMeleeForce(30);
    expected_mf = 30;
    EXPECT_EQ(GetMFHWarrior(), expected_mf);
    expected_mf = GetMFAWarrior();
    alliance_warrior->SetMeleeForce(100);
    expected_mf = 100;
    EXPECT_EQ(GetMFAWarrior(), expected_mf);
}

TEST_F(TestWarriorWithFraction, SetPowerOfMagic_Test) {
    size_t expected_pof = GetPOFHWarrior();
    horde_warrior->SetPowerOfMagic(10);
    expected_pof = 10;
    EXPECT_EQ(GetPOFHWarrior(), expected_pof);
    expected_pof = GetPOFAWarrior();
    alliance_warrior->SetPowerOfMagic(1);
    expected_pof = 1;
    EXPECT_EQ(GetPOFAWarrior(), expected_pof);
}

TEST_F(TestWarriorWithFraction, SetUnitName_Test) {
    std::string expected_uname = "Unknown";
    horde_warrior->SetUnitName("Unknown");
    alliance_warrior->SetUnitName("Unknown");
    EXPECT_EQ(expected_uname, GetUNHWarrior());
    EXPECT_EQ(GetUNAWarrior(), expected_uname);
}

TEST_F(TestWarriorWithFraction, SetFraction_Test) {
    std::string expected_fraction = "Students";
    horde_warrior->SetFraction("Students");
    alliance_warrior->SetFraction("Students");
    EXPECT_EQ(expected_fraction, GetFHWarrior());
    EXPECT_EQ(GetFAWarrior(), expected_fraction);
}

TEST_F(TestWarriorWithFraction, FractionAction_Test) {
    size_t expected_mf = GetMFHWarrior();
    size_t expected_hp = GetHealthHWarrior();
    horde_warrior->FractionAction();
    EXPECT_EQ(expected_mf + 5, GetMFHWarrior());
    EXPECT_EQ(expected_hp, GetHealthHWarrior());
    expected_hp = GetHealthAWarrior();
    expected_mf = GetMFAWarrior();
    alliance_warrior->FractionAction();
    EXPECT_EQ(expected_hp + 10, GetHealthAWarrior());
    EXPECT_EQ(expected_mf, GetMFAWarrior());
}

TEST_F(TestWarriorWithFraction, ToDamage_Test) {
    Unit* warrior_enemy = new AllianceWarrior;
    warrior_enemy->SetHealthPoints(200);
    alliance_warrior->SetMeleeForce(10);
    alliance_warrior->ToDamage(warrior_enemy);
    EXPECT_EQ(warrior_enemy->GetHP(), 190);
    horde_warrior->SetMeleeForce(20);
    horde_warrior->ToDamage(warrior_enemy);
    EXPECT_EQ(warrior_enemy->GetHP(), 170);
    delete warrior_enemy;
}



