#include "../Relationships.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>


class TestCommands : public ::testing::Test {
public:
    ~TestCommands() {
        delete manager;
        delete update_army;
        delete organise_army;
        delete create_greater;
        delete iter;
    }
protected:
    virtual void SetUp() {
        manager = new PlayersAllianceManager;
        iter = new UnitIterator;
        update_army = new UpdateArmy;
        organise_army = new OrganizeArmy;
        create_greater = new CreateGreaterArmyCommand;
        iter->SelectManagerSystem(manager);
        update_army->SetManagerSystem(manager);
        organise_army->SetManagerSystem(manager);
        create_greater->SetManagerSystem(manager);
    }
    ManagerSystem* manager;
    Command* update_army;
    Command* organise_army;
    Command* create_greater;
    Iterator* iter;
};

TEST_F(TestCommands, TestUpdateArmy) {
    for (int i = 0; i < 10; ++i) {
        manager->CreateHealerUnit();
        manager->CreateWarriorUnit();
        manager->players_warriors_.back()->SetHealthPoints(-10);
        manager->players_healers_.back()->SetHealthPoints(-10);
    }
    update_army->Execute();
    EXPECT_EQ(manager->players_healers_.size(), 0);
    EXPECT_EQ(manager->players_warriors_.size(), 0);

}

TEST_F(TestCommands, TestOrganise) {
    for (int i = 0; i < 5; ++i) {
        manager->CreateHealerUnit();
        manager->CreateWarriorUnit();
    }
    organise_army->Execute();
    EXPECT_EQ(manager->players_warriors_.size(), 1);
    EXPECT_EQ(manager->players_healers_.size(), 3);
    EXPECT_EQ(manager->players_squads_.size(), 2);
    EXPECT_EQ(manager->players_armies_.size(), 0);
}

TEST_F(TestCommands, TestCreateGreater) {
    create_greater->Execute();
    EXPECT_EQ(manager->players_warriors_.size(), 2);
    EXPECT_EQ(manager->players_healers_.size(), 2);
}

TEST_F(TestCommands, TestIter) {
    bool succes = true;
    for (int i = 0; i < 5; ++i) {
        manager->CreateHealerUnit();
        manager->CreateWarriorUnit();
    }
    for (auto unit : manager->players_warriors_) {
        if (unit == iter->Get()) {
            iter->GetNext();
        }
        else {
            succes = false;
            break;
        }
    }
    for (auto unit : manager->players_healers_) {
        if (unit == iter->Get()) {
            iter->GetNext();
        } else {
            succes = false;
            break;
        }
    }
    EXPECT_EQ(succes, false);
}


class TestRelationships : public ::testing::Test {
public:
    ~TestRelationships() {
        delete sender;
        delete reciever;
        delete relationships;
    }
protected:
    virtual void SetUp() {
        sender = new PlayersAllianceManager;
        reciever = new PlayersHordeManager;
        relationships = new OppositeFractionRelationships;
    }
    ManagerSystem* sender;
    ManagerSystem* reciever;
    Relationships* relationships;
};

TEST_F(TestRelationships, SettersTest) {
    relationships->SetSender(sender);
    relationships->SetReciever(reciever);
    EXPECT_EQ(relationships->sender_, sender);
    EXPECT_EQ(relationships->reciever_, reciever);
}

TEST_F(TestRelationships, SendCommandTest) {
    relationships->SetSender(sender);
    relationships->SetReciever(reciever);
    EXPECT_EQ(relationships->reciever_->commands_list_.size(), 0);
    Command* update_army = new UpdateArmy;
    update_army->SetManagerSystem(relationships->reciever_);
    relationships->SendCommands(update_army);
    EXPECT_EQ(relationships->reciever_->commands_list_.size(), 1);
    delete update_army;
}

TEST_F(TestRelationships, ExecuteAllTest) {
    relationships->SetSender(sender);
    relationships->SetReciever(reciever);
    for (int i = 0; i < 5; ++i) {
        relationships->sender_->CreateWarriorUnit();
        relationships->reciever_->CreateHealerUnit();
        relationships->reciever_->players_healers_.back()->SetHealthPoints(-10);
    }
    Command* organise_army = new OrganizeArmy;
    Command* update_army = new UpdateArmy;
    organise_army->SetManagerSystem(relationships->reciever_);
    update_army->SetManagerSystem(relationships->reciever_);
    relationships->SendCommands(update_army);
    relationships->SendCommands(organise_army);
    EXPECT_EQ(relationships->reciever_->commands_list_.size(), 2);
    relationships->ExecuteAllComands();
    EXPECT_EQ(relationships->reciever_->commands_list_.size(), 0);
    EXPECT_EQ(relationships->reciever_->players_healers_.size(), 0);
    EXPECT_EQ(relationships->reciever_->players_warriors_.size(), 0);
}





