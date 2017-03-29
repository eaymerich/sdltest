#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "EventHandler.h"

class Input_Manager
{
public:
    Input_Manager();
    virtual ~Input_Manager() = default;
    virtual void readInput();
    virtual void setEventHandler(EventHandler* handler);
private:
    EventHandler* eventHandler;
};

#endif // INPUT_MANAGER_H
