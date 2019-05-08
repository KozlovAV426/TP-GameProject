#include "Interface.h"

Game::Game(size_t turn) {
    players_manager_ = new ProxyManagerSystem;
    if (turn == 1) {
        players_manager_->warrior_builder_ = new AllianceWarriorBuilder;
        players_manager_->healer_builder_ = new AllianceHealerBuilder;
        opposite_manager_ = new PlayersHordeManager;
    }
    else {
        players_manager_->warrior_builder_ = new HordeWarriorBuilder;
        players_manager_->healer_builder_ = new HordeHealerBuilder;
        opposite_manager_ = new PlayersAllianceManager;
    }
    relationships_ = new OppositeFractionRelationships;
    relationships_->SetReciever(opposite_manager_);
    relationships_->SetSender(players_manager_);
    players_manager_->SetOppositeFractionRelationship(relationships_);
    opposite_manager_->SetOppositeFractionRelationship(relationships_);
    for (int i = 0; i < opposite_manager_->level_; ++i) {
        opposite_manager_->CreateWarriorUnit();
        opposite_manager_->CreateHealerUnit();
    }
    logger_ = new Logger;
}

void Game::ShowMyStat() {
    logger_->my_stat_views_+= 1;

    std::cout << "Your warriors - " << players_manager_->players_warriors_.size() <<
              " and your healers - " << players_manager_->players_healers_.size() << std::endl;
    std::cout << "Your squads - " << players_manager_->players_squads_.size() <<
              " and your armies - " << players_manager_->players_armies_.size() << std::endl;
    std::cout << "You have " << players_manager_->resources << " resources" << std::endl;
    std::cout << "Health of all your units " << players_manager_->GetAllHealth() << std::endl;


}

void Game::ShowOppositeStat() {
    logger_->opposite_stat_views_ += 1;

    std::cout << "Your opposite warriors - " << opposite_manager_->players_warriors_.size() <<
              " and its healers - " << opposite_manager_->players_healers_.size() << std::endl;
    std::cout << "Your opposite squads - " << opposite_manager_->players_squads_.size() <<
              " and its armies - " << opposite_manager_->players_armies_.size() << std::endl;
    std::cout << "Health of opposite units " << opposite_manager_->GetAllHealth() << std::endl;
}

void Game::ShowHelp() {
    logger_->help_views_ += 1;

    std::cout << "#######################################################################################################" << std::endl;
    std::cout << "List of commands (press certain button) : 1 - show info about you, 2 - show info about opposite, " << std::endl;
    std::cout << "3 - send units to search for resources, 4 - send units to fight with opposite fraction, 5 - create warrior" << std::endl;
    std::cout << "6 - create healer, 7 - create squad, 8 - create army, 9 - show list of commands, 10 - exit " << std::endl;
    std::cout << "#######################################################################################################" << std::endl;
}

void Game::Handle() {
    double time = clock();
    ShowHelp();
    int command = 1;
    while (command != 10) {
        std::cin >> command;
        if (command == 1) {
            ShowMyStat();
        }
        if (command == 2) {
            ShowOppositeStat();
        }
        if (command == 3) {
            players_manager_->SearchResources();
        }
        if (command == 4) {
            players_manager_->GoToConquer();
        }
        if (command == 5) {
            double begin = clock();
            players_manager_->CreateWarriorUnit();
            logger_->unit_building_time_ = std::max(logger_->unit_building_time_, begin - clock());
        }
        if (command == 6) {
            double begin = clock();
            players_manager_->CreateHealerUnit();
            logger_->unit_building_time_ = std::max(logger_->unit_building_time_, begin - clock());
        }
        if (command == 7) {
            players_manager_->CreateSquad();
        }
        if (command == 8) {
            players_manager_->CreateArmy();
        }
        if (command == 9) {
            ShowHelp();
        }
        relationships_->ExecuteAllComands();
    }
    logger_->session_time_ = clock() - time;
}

Game::~Game() {
    delete players_manager_;
    delete opposite_manager_;
    delete relationships_;
    delete logger_;
}

void Logger::Analyze() {

    std::cout << "Player used command" << " 'show my statistics' " << my_stat_views_ << "  times" << std::endl;
    std::cout << "Player used command" << " 'show opposite statistics' " << opposite_stat_views_ << "  times" << std::endl;
    std::cout << "Player used command" << " 'show list of commands' " << help_views_ << " times" << std::endl;
    std::cout << "Session time " << session_time_ << std::endl;
    std::cout << "The longest unit creation time " << unit_building_time_ << std::endl;

}
