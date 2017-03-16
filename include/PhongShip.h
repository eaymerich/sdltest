#ifndef PHONGSHIP_H
#define PHONGSHIP_H

#include "PhongCube.h"


class PhongShip : public PhongCube {
public:
    PhongShip();
    virtual ~PhongShip() = default;
    virtual void draw() override;

protected:
    PhongCube body;
    PhongCube cabin;
    PhongCube leftWing;
    PhongCube rightWing;
    PhongCube leftAileron;
    PhongCube rightAileron;
};

#endif // PHONGSHIP_H
