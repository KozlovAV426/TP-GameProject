#pragma once
#include "Builder.h"
#include <unistd.h>
#include <vector>

class Command;
class Relationships;


//////////////////////////////////////////////////          Abstract component

class Component {
public:
    virtual void AddComponent(Component* component) = 0;

    virtual size_t GetComponentsHP() = 0;

    virtual ~Component() = default;
};


///////////////////////////////////////////////// Concrete component

class Squad : public Component {
public:
    Squad(Unit* first_warrior, Unit* second_warrior, Unit* healer);

    virtual size_t GetComponentsHP() override;

    virtual void AddComponent(Component* component) override;

    std::vector<Unit*> units_;
};


/////////////////////////////////////////      Concrete component

class Army : public Component {
public:
    Army() = default;

    ~Army() override = default;

    virtual void AddComponent(Component* component) override;

    virtual size_t GetComponentsHP() override;

    std::vector<Component*> components_;
};


//////////////////////////////////////////////////////////  Abstract  Manager ( is in charge of economics of game )

class ManagerSystem {
public:
    ManagerSystem() = default;

    virtual void CreateWarriorUnit() = 0;

    virtual void CreateHealerUnit() = 0;

    virtual void CreateSquad() = 0;

    virtual void CreateArmy() = 0;

    virtual void SearchResources() = 0;

    virtual void GoToConquer() = 0;

    virtual size_t GetAllHealth();

    virtual void SetOppositeFractionRelationship(Relationships* relationships);

    virtual ~ManagerSystem() = default;

    std::vector<Unit*> players_warriors_;
    std::vector<Unit*> players_healers_;
    std::vector<Component*> players_squads_;
    std::vector<Component*> players_armies_;
    CharacterBuilder* warrior_builder_;
    CharacterBuilder* healer_builder_;
    CharacterGenerator generator_;
    Relationships* opposite_fraction_interaction_;
    std::vector<Command*> commands_list_;
    size_t level_ = 1;
    size_t resources = 0;
};

/////////////////////////////////////////////////////////// concrete Manager

class PlayersManager : public ManagerSystem {
public:
    PlayersManager() = default;

    virtual ~PlayersManager() = default;

    virtual void CreateWarriorUnit() override;

    virtual void CreateHealerUnit() override;

    virtual void CreateSquad() override;

    virtual void CreateArmy() override;

    virtual void SearchResources() override;

    virtual void GoToConquer() override;

};

class PlayersAllianceManager : public PlayersManager {
public:
    virtual ~PlayersAllianceManager() override;

    PlayersAllianceManager();
};

class PlayersHordeManager : public PlayersManager {
public:
    virtual ~PlayersHordeManager() override;

    PlayersHordeManager();
};

///////////////////////////////////////////////////////    Proxy ( interacts with player )

class ProxyManagerSystem : public PlayersManager {
public:
    ProxyManagerSystem() = default;

    virtual void CreateWarriorUnit() override;

    virtual void CreateHealerUnit() override;

    virtual void CreateSquad() override;

    virtual void CreateArmy() override;

    virtual void SearchResources() override;

    virtual void GoToConquer() override;
};

