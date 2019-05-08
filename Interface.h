#include "Relationships.h"
#include <ctime>

class Logger {
public:
    size_t my_stat_views_ = 0;
    size_t opposite_stat_views_ = 0;
    double session_time_ = 0;
    size_t help_views_ = 0;
    double unit_building_time_ = 0;

    void Analyze();

};

class Game {
    ManagerSystem* players_manager_;
    ManagerSystem* opposite_manager_;
    Relationships* relationships_;

public:

    Game(size_t turn);

    void ShowMyStat();

    void ShowOppositeStat();

    void ShowHelp();

    void Handle();

    ~Game();
    Logger* logger_;
};
