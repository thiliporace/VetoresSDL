//
//  PlayerGO.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#ifndef PlayerGameObject_hpp
#define PlayerGameObject_hpp

#include <stdio.h>

#include "GameObject.hpp"

class PlayerGameObject: public GameObject{
private:
    bool isMoving;
    
    const float playerShipMoveSpeed = 300;
public:
    void update(float deltaTime) override;
    
    void moveTo(Vector2D& destination, float deltaTime);
    
    void stopMoving(float deltaTime);
    
    void setIsMoving(bool b);
    
    void calculateSpeed(float deltaTime);
    
    PlayerGameObject(Vector2D initialPosition, int w, int h, const std::string& assetName);
};

#endif /* PlayerGO_hpp */
