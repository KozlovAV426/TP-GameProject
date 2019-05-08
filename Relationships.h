#include "Structure.h"

////////////////////////////////////////////////////////  Command

class Command {
public:
    Command() = default;

    void SetManagerSystem(ManagerSystem* manager);

    virtual void Execute() = 0;

    ~Command() = default;

protected:
    ManagerSystem* manager_system_;
};


class UpdateArmy : public Command {
public:
    virtual void Execute() override;
};

class OrganizeArmy : public Command {
public:
    virtual void Execute() override;
};

class CreateGreaterArmyCommand : public Command {
public:
    CreateGreaterArmyCommand() = default;

    virtual void Execute() override;
};

/////////////////////////////////////////////////   Mediator (connects two fractions between each other)

class Relationships {
public:
    virtual void SendCommands(Command* command) = 0;

    void ExecuteAllComands();

    void SetReciever(ManagerSystem* reciever);

    void SetSender(ManagerSystem* sender);

    ManagerSystem* reciever_;
    ManagerSystem* sender_;
};

class OppositeFractionRelationships : public Relationships {
public:
    virtual void SendCommands(Command* command) override;

};


////////////////////////////////////////////////// Iterator  ( it is used when we need get all player's units, which
                                                         //  are located in components )
class Iterator {
protected:
    ManagerSystem* manager_system_;
    std::vector<Unit*> units_;
    std::vector<Unit*>::iterator iter_;

public:
    virtual void GetNext() = 0;

    virtual Unit* Get() = 0;

    void SelectManagerSystem(ManagerSystem* manager_system);

    Iterator() = default;
};

class UnitIterator : public Iterator {
public:
    void GetNext() override;

    Unit* Get() override;

};