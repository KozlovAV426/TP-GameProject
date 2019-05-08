#include "../Builder.h"
#include <gtest/gtest.h>

class CharacterGeneratorTest : public testing::Test {
public:
    ~CharacterGeneratorTest() {
        delete horde_warrior_builder;
        delete alliance_healer_builder;
        delete horde_healer_builder;
        delete alliance_warrior_builder;
        delete character_generator;
    }

    CharacterBuilder* GetBuilder() {
        return character_generator->builder_;
    }

    Unit* GetHWCharacter() {
        return horde_warrior_builder->character_;
    }

    Unit* GetHHCharacter() {
        return horde_healer_builder->character_;
    }

    Unit* GetAWCharacter() {
        return alliance_warrior_builder->character_;
    }

    Unit* GetAHCharacter() {
        return alliance_healer_builder->character_;
    }
protected:
    virtual void SetUp() {
        horde_warrior_builder = new HordeWarriorBuilder;
        alliance_warrior_builder = new AllianceWarriorBuilder;
        horde_healer_builder  = new HordeHealerBuilder;
        alliance_healer_builder = new AllianceHealerBuilder;
        character_generator = new CharacterGenerator;
    }

    CharacterBuilder* horde_warrior_builder;
    CharacterBuilder* alliance_warrior_builder;
    CharacterBuilder* horde_healer_builder;
    CharacterBuilder* alliance_healer_builder;
    CharacterGenerator* character_generator;
};

TEST_F(CharacterGeneratorTest, SetBuilder_Test) {
    character_generator->SetBuilder(horde_warrior_builder);
    EXPECT_EQ(GetBuilder(), horde_warrior_builder);
    character_generator->SetBuilder(alliance_warrior_builder);
    EXPECT_EQ(GetBuilder(), alliance_warrior_builder);
    character_generator->SetBuilder(horde_healer_builder);
    EXPECT_EQ(GetBuilder(), horde_healer_builder);
    character_generator->SetBuilder(alliance_healer_builder);
    EXPECT_EQ(GetBuilder(), alliance_healer_builder);
}

TEST_F(CharacterGeneratorTest, GetUnit_Test) {
    character_generator->SetBuilder(horde_warrior_builder);
    EXPECT_EQ(GetHWCharacter(), character_generator->GetUnit());
    character_generator->SetBuilder(horde_healer_builder);
    EXPECT_EQ(GetHHCharacter(), character_generator->GetUnit());
    character_generator->SetBuilder(alliance_healer_builder);
    EXPECT_EQ(GetAHCharacter(), character_generator->GetUnit());
    character_generator->SetBuilder(alliance_warrior_builder);
    EXPECT_EQ(GetAWCharacter(), character_generator->GetUnit());
}

TEST_F(CharacterGeneratorTest, CreateUnitsConfiguration_Test) {
    character_generator->SetBuilder(horde_warrior_builder);
    character_generator->CreateUnitsConfiguration();
    EXPECT_EQ(horde_warrior_builder->GetCharacter()->GetHP(), 15);
    EXPECT_EQ(horde_warrior_builder->GetCharacter()->GetMF(), 18);
    EXPECT_EQ(horde_warrior_builder->GetCharacter()->GetPM(), 0);
    EXPECT_EQ(horde_warrior_builder->GetCharacter()->GetFraction(), "Horde");
    EXPECT_EQ(horde_warrior_builder->GetCharacter()->GetUnitName(), "Warrior");
    character_generator->SetBuilder(alliance_healer_builder);
    character_generator->CreateUnitsConfiguration();
    EXPECT_EQ(alliance_healer_builder->GetCharacter()->GetHP(), 10);
    EXPECT_EQ(alliance_healer_builder->GetCharacter()->GetMF(), 0);
    EXPECT_EQ(alliance_healer_builder->GetCharacter()->GetPM(), 5);
    EXPECT_EQ(alliance_healer_builder->GetCharacter()->GetFraction(), "Alliance");
    EXPECT_EQ(alliance_healer_builder->GetCharacter()->GetUnitName(), "Healer");
}


