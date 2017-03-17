#include "PhongShip.h"

PhongShip::PhongShip()
{
    // Setup Cabin
    cabin.setDiffuse({0.1f, 0.9f, 0.1f});
    cabin.setScale(0.4f, 0.4f, 0.4f);
    //cabin.setRotation({1.0f, 0.0f, 0.0f}, -0.5f);
    cabin.setPosition({0.0f, 0.0f, -0.7f});
    cabin.applyChangesIntoModelMatrix();

    // Setup Body
    body.setDiffuse({0.9f, 0.9f, 0.9f});
    body.setScale({1.0f, 0.5f, 1.0f});
    body.setPosition({0.0f, 0.0f, 0.0f});
    body.applyChangesIntoModelMatrix();

    // Setup Wings
    //glm::vec3 wingColor{0.1f, 0.1f, 0.9f}; // blue
    glm::vec3 wingColor{0.1176f, 0.5647f, 1.0f}; // dodgerblue
    leftWing.setDiffuse(wingColor);
    leftWing.setScale(0.8f, 0.1f, 0.6f);
    leftWing.setPosition({-0.8f, 0.0f, 0.0f});
    leftWing.setRotation({0.0f, 0.0f, 1.0f}, 0.5f);
    leftWing.applyChangesIntoModelMatrix();

    rightWing.setDiffuse(wingColor);
    rightWing.setScale(0.8f, 0.1f, 0.6f);
    rightWing.setPosition({0.8f, 0.0f, 0.0f});
    rightWing.setRotation({0.0f, 0.0f, 1.0f}, -0.5f);
    rightWing.applyChangesIntoModelMatrix();

    // Setup Ailerons
    //glm::vec3 aileronColor{0.8f, 0.2f, 0.8f}; // purple
    glm::vec3 aileronColor{0.2941f, 0.0f, 0.5098f}; // indigo
    leftAileron.setDiffuse(aileronColor);
    leftAileron.setScale({0.1f, 0.5f, 0.5f});
    leftAileron.setPosition({-0.25f, 0.3f, 0.3f});
    leftAileron.setRotation({0.0f, 0.0f, 1.0f}, 0.5f);
    leftAileron.applyChangesIntoModelMatrix();

    rightAileron.setDiffuse(aileronColor);
    rightAileron.setScale({0.1f, 0.5f, 0.5f});
    rightAileron.setPosition({0.25f, 0.3f, 0.3f});
    rightAileron.setRotation({0.0f, 0.0f, 1.0f}, -0.5f);
    rightAileron.applyChangesIntoModelMatrix();
}

void PhongShip::draw() {

    auto uber_model = getModelMatrix();

    // Draw body
    body.draw(uber_model);

    // Draw cabin
    cabin.draw(uber_model);

    // Draw wings
    leftWing.draw(uber_model);
    rightWing.draw(uber_model);

    // Draw ailerons
    leftAileron.draw(uber_model);
    rightAileron.draw(uber_model);
}
