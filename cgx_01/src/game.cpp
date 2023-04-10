#include <iostream>

#include "game.h"
#include "graphics.h"
#include "math/matrix.h"

void Game::setKey(int key, int state)
{
    gameKeyState[key] = state > 0;
}

bool Game::getKey(int key)
{
    return gameKeyState[key];
}

void Game::setMouse(double dx, double dy, double sx, double sy)
{
    double yaw = cameraRotation.z - dx * mouseSpeed;
    double pitch = cameraRotation.x - dy * mouseSpeed;

    cameraRotation.z = yaw;
    cameraRotation.x = pitch;
}

void Game::load(Settings settings)
{
    mouseSpeed *= settings.mouseSpeed;
    walkSpeed *= settings.walkSpeed;

    scene = new Scene("scenes/ref.scene");
}

void Game::loop(const double &time)
{
    //A=65; S=83; D=68; W=87; Q=81; E=69
    Vector3 movement = Vector3();
    if (gameKeyState[87]) movement.y += walkSpeed * time;
    if (gameKeyState[83]) movement.y -= walkSpeed * time;
    if (gameKeyState[68]) movement.x += walkSpeed * time;
    if (gameKeyState[65]) movement.x -= walkSpeed * time;
    if (gameKeyState[81]) movement.z += walkSpeed * time;
    if (gameKeyState[69]) movement.z -= walkSpeed * time;

    movement = Matrix::rotation(cameraRotation) * movement;
    cameraPosition = cameraPosition + movement;

    Matrix tMatrix = Matrix::translation(-cameraPosition);
    Matrix rMatrix = -Matrix::rotation(cameraRotation);

    Graphics::updateCamera(rMatrix * tMatrix, cameraPosition);

    if (scene != nullptr)
    {
        scene->update(time);
    }
}

void Game::unload()
{
    delete scene;
    scene = nullptr;
}
