#ifndef __SHIP_CONTROLLER_H__
#define __SHIP_CONTROLLER_H__

#include "EventHandler.h"
#include "PhongShip.h"

class ShipController : public EventHandler {
public:
    ShipController(PhongShip* aShipModel);
    virtual ~ShipController() = default;
    virtual void update();

    virtual void handleKeyDown(
        SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) override;
    virtual void handleKeyUp(
        SDL_Keycode sym, SDL_Scancode scancode, Uint16 mod) override;
    virtual void handleExit() override;

protected:
    bool goLeft;
    bool goRight;
    bool goUp;
    bool goDown;
    float horizontalSpeed;
    float verticalSpeed;
    PhongShip* shipModel;
private:
};

#endif // __SHIP_CONTROLLER_H__
