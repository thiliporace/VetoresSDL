//
//  EnemyGameObject.hpp
//  VetoresSDL
//
//  Created by Thiago Liporace on 21/05/25.
//

#ifndef EnemyGameObject_hpp
#define EnemyGameObject_hpp

#include <stdio.h>

#include "GameObject.hpp"

class EnemyGameObject: public GameObject{
public:
    float fov = 180;
    
    Vector2D forwardVector = Vector2D(0,1);
    
    void update(float deltaTime) override;
    
    EnemyGameObject(Vector2D initialPosition, int w, int h, const std::string& assetName);
};

#endif /* EnemyGameObject_hpp */
