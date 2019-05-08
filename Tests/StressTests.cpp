#include "../Interface.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>



class ManagerSystemStressTest : public ::testing::Test {
public:
    ~ManagerSystemStressTest() {
        delete manager;
        delete opposite_manager;
        delete relationships;
    }
protected:
    virtual void SetUp() {
        manager = new PlayersAllianceManager;
        opposite_manager = new PlayersHordeManager;
        relationships = new OppositeFractionRelationships;
        manager->opposite_fraction_interaction_ = relationships;
        relationships->SetReciever(opposite_manager);
        relationships->SetSender(manager);
    }
    ManagerSystem* manager;
    ManagerSystem* opposite_manager;
    Relationships* relationships;
    const size_t max = 1000000;
};


TEST_F(ManagerSystemStressTest, CreateUnitsStressTest) {
    for (size_t i = 0; i < max; ++i) {
        manager->CreateHealerUnit();
        manager->CreateWarriorUnit();
    }
    EXPECT_EQ(manager->players_warriors_.size(), max);
    EXPECT_EQ(manager->players_healers_.size(), max);

    size_t amount = 10000;
    for (size_t i = 0; i < amount; ++i) {
        manager->CreateSquad();
    }
    EXPECT_EQ(manager->players_healers_.size(), max - amount);
    EXPECT_EQ(manager->players_warriors_.size(), max - 2 * amount);
    EXPECT_EQ(manager->players_squads_.size(), amount);
}

TEST_F(ManagerSystemStressTest, GoToConquerStressTest) {
    for (size_t i = 0; i < max; ++i) {
        opposite_manager->CreateWarriorUnit();
        opposite_manager->CreateHealerUnit();
    }
    EXPECT_EQ(manager->players_warriors_.size(), 0);
    EXPECT_EQ(manager->players_healers_.size(), 0);
    manager->CreateHealerUnit();
    EXPECT_EQ(manager->players_healers_.size(), 1);
    manager->GoToConquer();
    relationships->ExecuteAllComands();
    EXPECT_EQ(manager->players_healers_.size(), 0);
    EXPECT_EQ(opposite_manager->players_warriors_.size(), 0);
    EXPECT_EQ(opposite_manager->players_healers_.size(), max / 2);

    for (size_t i = 0; i < max; ++i) {
        manager->CreateHealerUnit();
        manager->CreateWarriorUnit();
    }
    manager->GoToConquer();
    relationships->ExecuteAllComands();
    EXPECT_EQ(opposite_manager->players_warriors_.size(), 2);
    EXPECT_EQ(opposite_manager->players_healers_.size(), 2);
}

TEST_F(ManagerSystemStressTest, GetAllHealthTest) {
    EXPECT_EQ(manager->GetAllHealth(), 0);
    for (size_t i = 0; i < max; ++i) {
        manager->CreateWarriorUnit();
    }
    EXPECT_EQ(manager->GetAllHealth(), 15 * max);
    opposite_manager->CreateWarriorUnit();
    manager->GoToConquer();
    EXPECT_EQ(manager->GetAllHealth(), 15 * max - 18);
}

TEST_F(ManagerSystemStressTest, EqualFightTest) {
    for (size_t i = 0; i < max; ++i) {
        manager->CreateWarriorUnit();
        opposite_manager->CreateWarriorUnit();
    }
    manager->GoToConquer();
    relationships->ExecuteAllComands();
    EXPECT_EQ(manager->players_warriors_.size(), 0);
    EXPECT_EQ(opposite_manager->players_warriors_.size(), 2);
}

