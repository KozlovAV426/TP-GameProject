#include "Relationships.h"


/////////////////////////////////////////////////////   Relationships


void Relationships::SetReciever(ManagerSystem* reciever) {
    reciever_ = reciever;
}

void Relationships::SetSender(ManagerSystem* sender) {
    sender_ = sender;
}

void Relationships::ExecuteAllComands() {
    for (auto command : reciever_->commands_list_) {
        command->Execute();
        delete command;
    }
    reciever_->commands_list_.clear();
    for (auto command : sender_->commands_list_) {
        command->Execute();
        delete command;
    }
    sender_->commands_list_.clear();
}

void OppositeFractionRelationships::SendCommands(Command* command) {
    reciever_->commands_list_.push_back(command);
}


////////////////////////////////////////   Commands

void Command::SetManagerSystem(ManagerSystem *manager) {
    manager_system_ = manager;
}

void UpdateArmy::Execute() {
    Iterator* army_iter = new UnitIterator;
    army_iter->SelectManagerSystem(manager_system_);
    std::vector<Unit*> alive_warriors;
    std::vector<Unit*> alive_healers;
    while (army_iter->Get() != nullptr) {
        Unit* unit = army_iter->Get();
        if (unit->GetHP() > 0) {
            (unit->GetUnitName() == "Warrior") ? alive_warriors.push_back(unit) : alive_healers.push_back(unit);
        }
        else {
            delete unit;
        }
        army_iter->GetNext();
    }
    manager_system_->players_squads_.clear();
    manager_system_->players_armies_.clear();
    manager_system_->players_warriors_ = std::move(alive_warriors);
    manager_system_->players_healers_  = std::move(alive_healers);
    delete army_iter;
}

void OrganizeArmy::Execute() {
    while (manager_system_->players_warriors_.size() >= 2 && manager_system_->players_healers_.size() > 0) {
        manager_system_->CreateSquad();
    }
    while (manager_system_->players_squads_.size() >= 3) {
        manager_system_->CreateArmy();
    }
}

void CreateGreaterArmyCommand::Execute() {
    manager_system_->level_ += 1;
    for (int i = 0; i < manager_system_->level_; ++i) {
        manager_system_->CreateWarriorUnit();
        manager_system_->CreateHealerUnit();
    }
    std::cout << "You've killed all opposite units. You move to next level" << std::endl;
}


////////////////////////////////////////////////    Iterator

void Iterator::SelectManagerSystem(ManagerSystem *manager_system) {
    manager_system_ = manager_system;
    for (auto army : manager_system_->players_armies_) {
        Army *r_army = static_cast<Army *>(army);
        for (auto squad : r_army->components_) {
            Squad *r_squad = static_cast<Squad *>(squad);
            for (auto unit : r_squad->units_) {
                units_.push_back(unit);
            }
        }
    }
    for (auto squad : manager_system_->players_squads_) {
        Squad *r_squad = static_cast<Squad *>(squad);
        for (auto unit : r_squad->units_) {
            units_.push_back(unit);
        }
    }
    for (auto unit : manager_system_->players_warriors_) {
        units_.push_back(unit);
    }
    for (auto unit : manager_system_->players_healers_) {
        units_.push_back(unit);
    }
    iter_ = units_.begin();
}

void UnitIterator::GetNext() {
    if (iter_ != units_.end()) {
        ++iter_;
    }
}

Unit* UnitIterator::Get() {
    if (iter_ != units_.end()) {
        Unit* unit = *iter_;
        return unit;
    }
    return nullptr;
}