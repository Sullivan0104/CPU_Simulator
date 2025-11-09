#pragma once
#include <vector>

class Observer 
{
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Subject 
{
    std::vector<Observer*> observers;

public:

    void attach(Observer* obs) { observers.push_back(obs); }
protected:
    void notify() 
    {
        for (auto* o : observers) o->update();
    }
};
