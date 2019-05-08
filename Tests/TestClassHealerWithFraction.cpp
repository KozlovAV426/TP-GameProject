#include <gtest/gtest.h>
#include "../ClassesOfUnits.h"

class TestHealerWithFraction : public ::testing::Test {
public:
    ~TestHealerWithFraction() {
        delete horde_healer;
        delete alliance_healer;
    }
protected:
    virtual void SetUp() {
        horde_healer = new HordeHealer;
        alliance_healer = new AllianceHealer;
    }

    Unit* horde_healer;
    Unit* alliance_healer;

    size_t GetHealthHHealer() {
        return horde_healer->health_points_;
    }

    size_t GetHealthAHealer() {
        return alliance_healer->health_points_;
    }

    size_t GetMFHHealer() {
        return horde_healer->melee_force;
    }

    size_t GetMFAHealer() {
        return alliance_healer->melee_force;
    }

    size_t GetPOFHHealer() {
        return horde_healer->power_of_magic_;
    }

    size_t GetPOFAHealer() {
        return alliance_healer->power_of_magic_;
    }

    std::string GetUNHHealer() {
        return horde_healer->unit_name_;
    }

    std::string GetUNAHealer() {
        return alliance_healer->unit_name_;
    }

    std::string GetFHHealer() {
        return horde_healer->fraction_;
    }

    std::string GetFAHealer() {
        return alliance_healer->fraction_;
    }

};

TEST_F(TestHealerWithFraction, GetHP_Test) {
    EXPECT_EQ(GetHealthHHealer(), horde_healer->GetHP());
    EXPECT_EQ(GetHealthAHealer(), alliance_healer->GetHP());
}

TEST_F(TestHealerWithFraction, GetMF_Test) {
    EXPECT_EQ(GetMFAHealer(), alliance_healer->GetMF());
    EXPECT_EQ(GetMFHHealer(), horde_healer->GetMF());
}

TEST_F(TestHealerWithFraction, GetPOF_Test) {
    EXPECT_EQ(GetPOFAHealer(), alliance_healer->GetPM());
    EXPECT_EQ(GetPOFHHealer(), horde_healer->GetPM());
}

TEST_F(TestHealerWithFraction, SetHealthPoints_Test) {
    size_t expected_hp = GetHealthHHealer();
    horde_healer->SetHealthPoints(GetHealthHHealer() + 10);
    expected_hp += 10;
    EXPECT_EQ(GetHealthHHealer(), expected_hp);
    horde_healer->SetHealthPoints(GetHealthHHealer() - 8);
    expected_hp -= 8;
    EXPECT_EQ(GetHealthHHealer(), expected_hp);
    expected_hp = GetHealthAHealer();
    alliance_healer->SetHealthPoints(GetHealthAHealer() + 100);
    expected_hp += 100;
    EXPECT_EQ(GetHealthAHealer(), expected_hp);
}

TEST_F(TestHealerWithFraction, SetMeleeForce_Test) {
    size_t expected_mf = GetMFHHealer();
    horde_healer->SetMeleeForce(30);
    expected_mf = 30;
    EXPECT_EQ(GetMFHHealer(), expected_mf);
    expected_mf = GetMFAHealer();
    alliance_healer->SetMeleeForce(100);
    expected_mf = 100;
    EXPECT_EQ(GetMFAHealer(), expected_mf);
}

TEST_F(TestHealerWithFraction, SetPowerOfMagic_Test) {
    size_t expected_pof = GetPOFHHealer();
    horde_healer->SetPowerOfMagic(10);
    expected_pof = 10;
    EXPECT_EQ(GetPOFHHealer(), expected_pof);
    expected_pof = GetPOFAHealer();
    alliance_healer->SetPowerOfMagic(1);
    expected_pof = 1;
    EXPECT_EQ(GetPOFAHealer(), expected_pof);
}

TEST_F(TestHealerWithFraction, SetUnitName_Test) {
    std::string expected_uname = "Unknown";
    horde_healer->SetUnitName("Unknown");
    alliance_healer->SetUnitName("Unknown");
    EXPECT_EQ(expected_uname, GetUNHHealer());
    EXPECT_EQ(GetUNAHealer(), expected_uname);
}

TEST_F(TestHealerWithFraction, SetFraction_Test) {
    std::string expected_fraction = "Students";
    horde_healer->SetFraction("Students");
    alliance_healer->SetFraction("Students");
    EXPECT_EQ(expected_fraction, GetFHHealer());
    EXPECT_EQ(GetFAHealer(), expected_fraction);
}

TEST_F(TestHealerWithFraction, FractionAction_Test) {
    size_t expected_pof = GetPOFHHealer();
    size_t expected_hp = GetHealthHHealer();
    horde_healer->FractionAction();
    EXPECT_EQ(expected_pof + 5, GetPOFHHealer());
    EXPECT_EQ(expected_hp, GetHealthHHealer());
    expected_hp = GetHealthAHealer();
    expected_pof = GetPOFAHealer();
    alliance_healer->FractionAction();
    EXPECT_EQ(expected_hp + 10, GetHealthAHealer());
    EXPECT_EQ(expected_pof, GetPOFAHealer());
}

TEST_F(TestHealerWithFraction, ToHeal_Test) {
    Unit* friend_warrior = new AllianceWarrior;
    friend_warrior->SetHealthPoints(200);
    alliance_healer->SetPowerOfMagic(10);
    alliance_healer->ToHeal(friend_warrior);
    EXPECT_EQ(friend_warrior->GetHP(), 210);
    horde_healer->SetPowerOfMagic(20);
    horde_healer->ToHeal(friend_warrior);
    EXPECT_EQ(friend_warrior->GetHP(), 230);
    delete friend_warrior;
}



