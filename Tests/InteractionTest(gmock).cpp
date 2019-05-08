#include "../Interface.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class MockPlayersHordeManager : public PlayersHordeManager {
public:
    MOCK_METHOD0(CreateWarriorUnit, void());
    MOCK_METHOD0(CreateHealerUnit, void());
    MOCK_METHOD0(CreateSquad, void());
    MOCK_METHOD0(CreateArmy, void());
    MOCK_METHOD0(SearchResources, void());
    MOCK_METHOD0(GoToConquer, void());
    MOCK_METHOD0(GetAllHealth, size_t());
    //MOCK_METHOD1(SetOppositeFractionRelationship, void(Relationships* relationships));
};


class MockOppositeFractionRelationships : public OppositeFractionRelationships {
public:
    MOCK_METHOD1(SendCommands, void(Command* command));
    MOCK_METHOD0(ExecuteAllComands, void());
};

class MockUnitClass : public HordeHealer {
public:
    MOCK_METHOD1(SetHealthPoints, void(int points));
};


class TestInteraction: public ::testing::Test {
public:
    ~TestInteraction() {
        delete update_army;
        delete organise_army;
        delete create_greater;
        delete manager;
        delete opposite;
    }
protected:
    virtual void SetUp() {
        update_army = new UpdateArmy;
        organise_army = new OrganizeArmy;
        create_greater = new CreateGreaterArmyCommand;
        manager = new PlayersHordeManager;
        opposite = new PlayersAllianceManager;

    }
    Command* update_army;
    Command* organise_army;
    Command* create_greater;
    ManagerSystem* manager;
    ManagerSystem* opposite;

};


TEST_F(TestInteraction, OrganiseArmyTest) {
    MockPlayersHordeManager manager;
    manager.PlayersHordeManager::CreateWarriorUnit();
    manager.PlayersHordeManager::CreateWarriorUnit();
    manager.PlayersHordeManager::CreateHealerUnit();
    EXPECT_CALL(manager, CreateSquad()).Times(0);
    organise_army->SetManagerSystem(&manager);
}

TEST_F(TestInteraction, CreateGreaterTest) {
    MockPlayersHordeManager manager;
    create_greater->SetManagerSystem(&manager);
    EXPECT_CALL(manager, CreateWarriorUnit()).Times(::testing::AtLeast(1));
    EXPECT_CALL(manager, CreateHealerUnit()).Times(::testing::AtLeast(1));
    EXPECT_CALL(manager, CreateSquad()).Times(0);
    create_greater->Execute();
}

TEST_F(TestInteraction, ExecuteAllCommandsTest) {
    MockOppositeFractionRelationships relationships;
    manager->SetOppositeFractionRelationship(&relationships);
    relationships.OppositeFractionRelationships::SetSender(manager);
    relationships.OppositeFractionRelationships::SetReciever(manager);
    EXPECT_CALL(relationships, ExecuteAllComands()).Times(1);
    manager->GoToConquer();
    relationships.ExecuteAllComands();
}

TEST_F(TestInteraction, SettersTest) {
    MockUnitClass unit;
    Unit* healer = new AllianceHealer;
    size_t power = healer->GetPM() - 2;
    size_t heal = healer->GetPM();
    EXPECT_CALL(unit, SetHealthPoints(power)).Times(0);
    healer->ToDamage(&unit);
    healer->ToHeal(&unit);
    delete healer;
}

TEST_F(TestInteraction, SendComandsTest) {
    MockOppositeFractionRelationships relationships;
    relationships.OppositeFractionRelationships::SetSender(manager);
    relationships.OppositeFractionRelationships::SetReciever(opposite);
    manager->SetOppositeFractionRelationship(&relationships);
    Command* update_army = new UpdateArmy;
    EXPECT_CALL(relationships, SendCommands(update_army)).Times(0);
    delete update_army;
}





