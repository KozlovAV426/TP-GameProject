#include "Structure.h"
#include "Relationships.h"


//////////////////////////////////////////////////////////////////////////       Squad

Squad::Squad(Unit* first_warrior, Unit* second_warrior, Unit* healer) {
    units_.push_back(first_warrior);
    units_.push_back(second_warrior);
    units_.push_back(healer);
}


void Squad::AddComponent(Component *component) {}

size_t Squad::GetComponentsHP() {
    size_t total = 0;
    for (auto unit : units_) {
        total += unit->GetHP();
    }
    return total;
}


//////////////////////////////////////        Army


void Army::AddComponent(Component *component) {
    components_.push_back(component);
}

size_t Army::GetComponentsHP() {
    size_t total = 0;
    for (auto component : components_) {
        total += component->GetComponentsHP();
    }
    return total;
}



//////////////////////////////////////////////      Manager System

void ManagerSystem::SetOppositeFractionRelationship(Relationships *relationships) {
    opposite_fraction_interaction_ = relationships;
}

size_t ManagerSystem::GetAllHealth() {
    size_t total = 0;
    for (auto unit : players_warriors_) {
        total += unit->GetHP();
    }
    for (auto unit : players_healers_) {
        total += unit->GetHP();
    }
    for (auto squad : players_squads_) {
        total += squad->GetComponentsHP();
    }
    for (auto army : players_armies_) {
        total += army->GetComponentsHP();
    }
    return total;
}

PlayersHordeManager::PlayersHordeManager() {
    warrior_builder_ = new HordeWarriorBuilder;
    healer_builder_ = new HordeHealerBuilder;
}

PlayersAllianceManager::PlayersAllianceManager() {
    warrior_builder_ = new AllianceWarriorBuilder;
    healer_builder_ = new AllianceHealerBuilder;
}

PlayersHordeManager::~PlayersHordeManager() {
    UnitIterator iter;
    iter.SelectManagerSystem(this);
    while (iter.Get() != nullptr) {
        delete iter.Get();
        iter.GetNext();
    }
    delete warrior_builder_;
    delete healer_builder_;
}

PlayersAllianceManager::~PlayersAllianceManager() {
    UnitIterator iter;
    iter.SelectManagerSystem(this);
    while (iter.Get() != nullptr) {
        delete iter.Get();
        iter.GetNext();
    }
    delete warrior_builder_;
    delete healer_builder_;
}

void PlayersManager::CreateWarriorUnit() {
    generator_.SetBuilder(warrior_builder_);
    generator_.MakeNewUnit();
    generator_.CreateUnitsConfiguration();
    players_warriors_.push_back(generator_.GetUnit());
}

void PlayersManager::CreateHealerUnit() {
    generator_.SetBuilder(healer_builder_);
    generator_.MakeNewUnit();
    generator_.CreateUnitsConfiguration();
    players_healers_.push_back(generator_.GetUnit());
}

void PlayersManager::SearchResources() {
    //sleep(1);
    resources += 1;
}

void PlayersManager::CreateSquad() {
    Unit* first_warrior = players_warriors_.back();
    players_warriors_.pop_back();
    Unit* second_warrior = players_warriors_.back();
    players_warriors_.pop_back();
    Unit* healer = players_healers_.back();
    players_healers_.pop_back();
    Component* squad = new Squad(first_warrior, second_warrior, healer);
    players_squads_.push_back(squad);
}

void PlayersManager::CreateArmy() {
    Component* army = new Army;
    for (int i = 0; i < 3; ++i) {
        army->AddComponent(players_squads_.back());
        players_squads_.pop_back();
    }
    players_armies_.push_back(army);
}

void PlayersManager::GoToConquer() {
    Iterator* my_units = new UnitIterator;
    Iterator* opposite_units = new UnitIterator;
    size_t killed = 0;
    size_t lost = 0;
    my_units->SelectManagerSystem(this);
    opposite_units->SelectManagerSystem(opposite_fraction_interaction_->reciever_);
    while (my_units->Get() != nullptr && opposite_units->Get() != nullptr) {
        Unit* my_unit = my_units->Get();
        Unit* opposite_unit = opposite_units->Get();
        my_unit->ToDamage(opposite_unit);
        opposite_unit->ToDamage(my_unit);
        my_unit->ToHeal(my_unit);
        opposite_unit->ToHeal(opposite_unit);
        if (my_unit->GetHP() < 0) {
            my_units->GetNext();
            lost += 1;
        }
        if (opposite_unit->GetHP() < 0) {
            opposite_units->GetNext();
            killed += 1;
        }
    }
    Command* update_my_army = new UpdateArmy;
    Command* organise_my_army = new OrganizeArmy;
    Command* update_opposite_army = new UpdateArmy;
    Command* organise_opposite_army = new OrganizeArmy;

    update_my_army->SetManagerSystem(this);
    organise_my_army->SetManagerSystem(this);
    update_opposite_army->SetManagerSystem(opposite_fraction_interaction_->reciever_);
    organise_opposite_army->SetManagerSystem(opposite_fraction_interaction_->reciever_);

    commands_list_.push_back(update_my_army);
    commands_list_.push_back(organise_my_army);
    opposite_fraction_interaction_->SendCommands(update_opposite_army);
    opposite_fraction_interaction_->SendCommands(organise_opposite_army);
    if (opposite_units->Get() == nullptr) {
        Command* create_new_army = new CreateGreaterArmyCommand();
        create_new_army->SetManagerSystem(opposite_fraction_interaction_->reciever_);
        opposite_fraction_interaction_->SendCommands(create_new_army);
    }
    delete my_units;
    delete opposite_units;
    std::cout << "In this battle you've killed " << killed << " opposite units and lost " << lost << " your units" << std::endl;
}

//////////////////////////////////////////////////    Proxy

void ProxyManagerSystem::CreateHealerUnit() {
    if (resources > 1) {
        PlayersManager::CreateHealerUnit();
        resources -= 1;
        std::cout << "You have created a healer!" << std::endl;
    }
    else {
        std::cout << "Sorry you don't have enough resources to do this command (need 2 resources)" << std::endl;
    }

}

void ProxyManagerSystem::CreateWarriorUnit() {
    if (resources > 1) {
        PlayersManager::CreateWarriorUnit();
        resources -= 1;
        std::cout << "You have created a warrior" << std::endl;
    }
    else {
        std::cout << "Sorry you don't have enough resources to do this command (need 2 resources)" << std::endl;
    }
}

void ProxyManagerSystem::CreateSquad() {
    if (players_warriors_.size() >= 2 && players_healers_.size() >= 1) {
        PlayersManager::CreateSquad();
        std::cout << "You have created a squad" << std::endl;
    }
    else {
        std::cout << "Sorry you don't have enough units to do this command (need 2 warriors and 1 healer)" << std::endl;
    }
}

void ProxyManagerSystem::CreateArmy() {
    if (players_squads_.size() >= 3) {
        PlayersManager::CreateArmy();
        std::cout << "You have created an army" << std::endl;
    }
    else {
        std::cout << "Sorry you don't have enough squads to do this command (need 3 squads)" << std::endl;
    }
}

void ProxyManagerSystem::SearchResources() {
    PlayersManager::SearchResources();
    std::cout << "Your units have found 1 resource" << std::endl;
}

void ProxyManagerSystem::GoToConquer() {
    if (players_warriors_.size() + players_healers_.size() +
    players_squads_.size() + players_armies_.size() > 0) {
        PlayersManager::GoToConquer();
    }
    else {
        std::cout << "Sorry you don't have any units! Create units and try again" << std::endl;
    }
}






