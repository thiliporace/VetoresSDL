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
    : GameObject(initialPosition, w, h, assetName), isMoving(false) {}

void PlayerGameObject::update(float deltaTime){
    rect.x += velocity.x;
    rect.y += velocity.y;
}

void PlayerGameObject::moveTo(Vector2D& destination, float deltaTime){    
    velocity.x = destination.normalized().x * playerShipMoveSpeed * deltaTime;
    velocity.y = destination.normalized().y * playerShipMoveSpeed * deltaTime;
}

void PlayerGameObject::stopMoving(float deltaTime){
    velocity.x *= 0.99 * deltaTime;
    velocity.y *= 0.99 * deltaTime;
}
