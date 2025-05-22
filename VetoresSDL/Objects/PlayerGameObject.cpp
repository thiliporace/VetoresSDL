//
//  PlayerGO.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include "PlayerGameObject.hpp"
#include <stdio.h>
#include <iostream>

PlayerGameObject::PlayerGameObject(Vector2D initialPosition, int w, int h, const std::string& assetName)
    : GameObject(initialPosition, w, h, assetName), isMoving(false), upVector(Vector2D(0,-1)), playerWidth(w), forwardVector(Vector2D(0,-1)) {
        mousePosX = std::make_shared<int>(0);
        mousePosY = std::make_shared<int>(0);
    }

void PlayerGameObject::update(float deltaTime){
    rect.x += velocity.x;
    rect.y += velocity.y;
    
    SDL_GetMouseState(mousePosX.get(), mousePosY.get());
    
    Vector2D mouseVector = Vector2D(*mousePosX - (rect.x + playerWidth/2),*mousePosY - rect.y);
    rotation = upVector.angleBetween(mouseVector);
    
    forwardVector = upVector.rotatedVector(rotation);
    std::cout << velocity.y << std::endl;
}

void PlayerGameObject::moveTo(Vector2D& destination, float deltaTime){    
    velocity.x = destination.normalized().x * playerShipMoveSpeed * deltaTime;
    velocity.y = destination.normalized().y * playerShipMoveSpeed * deltaTime;
}

void PlayerGameObject::stopMoving(float deltaTime){
    velocity.x *= 0.99;
    velocity.y *= 0.99;
}

void PlayerGameObject::moveAutomatically(float deltaTime){
    velocity.x = forwardVector.normalized().x * playerDashSpeed * deltaTime;
    velocity.y = forwardVector.normalized().y * playerDashSpeed * deltaTime;
}
