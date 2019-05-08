#include "../Builder.h"
#include <gtest/gtest.h>

class TestBuilder : public ::testing::Test {
public:
    ~TestBuilder() {
        delete horde_warrior_builder;
        delete alliance_warrior_builder;
        delete horde_healer_builder;
        delete alliance_healer_builder;
    }
protected:
    virtual void SetUp() {
        horde_warrior_builder = new HordeWarriorBuilder;
        alliance_warrior_builder = new AllianceWarriorBuilder;
        horde_healer_builder = new HordeHealerBuilder;
        alliance_healer_builder = new AllianceHealerBuilder;
        horde_warrior_builder->CreateNewUnit();
        alliance_warrior_builder->CreateNewUnit();
        horde_healer_builder->CreateNewUnit();
        alliance_healer_builder->CreateNewUnit();
    }
    CharacterBuilder* horde_warrior_builder;
    CharacterBuilder* alliance_warrior_builder;
    CharacterBuilder* horde_healer_builder;
    CharacterBuilder* alliance_healer_builder;
};

TEST_F(TestBuilder, BuildHealthPoints_Test) {
    horde_healer_builder->BuildHealthPoints();
    alliance_healer_builder->BuildHealthPoints();
    horde_warrior_builder->BuildHealthPoints();
    alliance_warrior_builder->BuildHealthPoints();
    EXPECT_EQ(10, horde_healer_builder->GetCharacter()->GetHP());
    EXPECT_EQ(10, alliance_healer_builder->GetCharacter()->GetHP());
    EXPECT_EQ(15, horde_warrior_builder->GetCharacter()->GetHP());
    EXPECT_EQ(15, alliance_warrior_builder->GetCharacter()->GetHP());
}

TEST_F(TestBuilder, BuildMeleeForce_Test) {
    horde_healer_builder->BuildMeleeForce();
    alliance_healer_builder->BuildMeleeForce();
    horde_warrior_builder->BuildMeleeForce();
    alliance_warrior_builder->BuildMeleeForce();
    EXPECT_EQ(0, horde_healer_builder->GetCharacter()->GetMF());
    EXPECT_EQ(0, alliance_healer_builder->GetCharacter()->GetMF());
    EXPECT_EQ(18, horde_warrior_builder->GetCharacter()->GetMF());
    EXPECT_EQ(18, alliance_warrior_builder->GetCharacter()->GetMF());
}

TEST_F(TestBuilder, BuildPowerOfMagic_Test) {
    horde_healer_builder->BuildPowerOfMagic();
    alliance_healer_builder->BuildPowerOfMagic();
    horde_warrior_builder->BuildPowerOfMagic();
    alliance_warrior_builder->BuildPowerOfMagic();
    EXPECT_EQ(5, horde_healer_builder->GetCharacter()->GetPM());
    EXPECT_EQ(5, alliance_healer_builder->GetCharacter()->GetPM());
    EXPECT_EQ(0, horde_warrior_builder->GetCharacter()->GetPM());
    EXPECT_EQ(0, alliance_warrior_builder->GetCharacter()->GetPM());
}

TEST_F(TestBuilder, BuildFraction_Test) {
    horde_healer_builder->BuildFraction();
    alliance_healer_builder->BuildFraction();
    horde_warrior_builder->BuildFraction();
    alliance_warrior_builder->BuildFraction();
    EXPECT_EQ("Horde", horde_healer_builder->GetCharacter()->GetFraction());
    EXPECT_EQ("Alliance", alliance_healer_builder->GetCharacter()->GetFraction());
    EXPECT_EQ("Horde", horde_warrior_builder->GetCharacter()->GetFraction());
    EXPECT_EQ("Alliance", alliance_warrior_builder->GetCharacter()->GetFraction());
}

TEST_F(TestBuilder, BuildUnitName_Test) {
    horde_healer_builder->BuildUnitName();
    alliance_healer_builder->BuildUnitName();
    horde_warrior_builder->BuildUnitName();
    alliance_warrior_builder->BuildUnitName();
    EXPECT_EQ("Healer", horde_healer_builder->GetCharacter()->GetUnitName());
    EXPECT_EQ("Healer", alliance_healer_builder->GetCharacter()->GetUnitName());
    EXPECT_EQ("Warrior", horde_warrior_builder->GetCharacter()->GetUnitName());
    EXPECT_EQ("Warrior", alliance_warrior_builder->GetCharacter()->GetUnitName());
}
