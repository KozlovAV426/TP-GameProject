#include "../Structure.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>


class TestComponents : public ::testing::Test {
public:
    ~TestComponents() {
        delete first_warrior;
        delete second_warrior;
        delete healer;
        delete squad;
        delete army;
    }
protected:
    virtual void SetUp() {
        first_warrior = new HordeWarrior;
        second_warrior = new AllianceWarrior;
        healer = new AllianceHealer;
        squad = new Squad(first_warrior, second_warrior, healer);
        army =  new Army;
    }
    Unit* first_warrior;
    Unit* second_warrior;
    Unit* healer;
    Squad* squad;
    Army* army;
};

TEST_F(TestComponents, TestAddComponent) {
    army->AddComponent(squad);
    EXPECT_EQ(army->components_.size(), 1);
    size_t size = squad->units_.size();
    squad->AddComponent(army);
    EXPECT_EQ(squad->units_.size(), size);
}

TEST_F(TestComponents, TestGetHP) {
    size_t health = first_warrior->GetHP() + second_warrior->GetHP() + healer->GetHP();
    EXPECT_EQ(health, squad->GetComponentsHP());
    army->AddComponent(squad);
    EXPECT_EQ(health, army->GetComponentsHP());
}

class TestManager : public ::testing::Test {
public:
    ~TestManager() {
        delete manager_system;
    }
protected:
    virtual void SetUp() {
        manager_system = new PlayersAllianceManager;
    }
    ManagerSystem* manager_system;
};

TEST_F(TestManager, CreateUnitsTest) {
    EXPECT_EQ(manager_system->players_warriors_.size(), 0);
    EXPECT_EQ(manager_system->players_healers_.size(), 0);
    manager_system->CreateHealerUnit();
    manager_system->CreateWarriorUnit();
    EXPECT_EQ(manager_system->players_warriors_.size(), 1);
    EXPECT_EQ(manager_system->players_healers_.size(), 1);
}

TEST_F(TestManager, CreateSquadTest) {
    for (int i = 0; i < 3; ++i) {
        manager_system->CreateWarriorUnit();
        manager_system->CreateHealerUnit();
    }
    EXPECT_EQ(manager_system->players_squads_.size(), 0);
    manager_system->CreateSquad();
    EXPECT_EQ(manager_system->players_squads_.size(), 1);
}

TEST_F(TestManager, SearchResourceTest) {
    EXPECT_EQ(manager_system->resources, 0);
    manager_system->SearchResources();
    EXPECT_EQ(manager_system->resources, 1);
}

TEST_F(TestManager, GetHealthTest) {
    EXPECT_EQ(manager_system->GetAllHealth(), 0);
    manager_system->CreateHealerUnit();
    manager_system->CreateHealerUnit();
    EXPECT_EQ(manager_system->GetAllHealth(), 20);
}
