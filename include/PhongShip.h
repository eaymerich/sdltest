#ifndef PHONG_SHIP_H
#define PHONG_SHIP_H

#include "PhongCube.h"
#include "PhongStaticCube.h"

class PhongShip : public PhongCube {
public:
    PhongShip();
    virtual ~PhongShip() = default;
    virtual void draw() override;

protected:
    PhongStaticCube body;
    PhongStaticCube cabin;
    PhongStaticCube leftWing;
    PhongStaticCube rightWing;
    PhongStaticCube leftAileron;
    PhongStaticCube rightAileron;
};

#endif // PHONG_SHIP_H
