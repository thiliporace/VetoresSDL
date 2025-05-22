//
//  GameObject.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <string.h>
#include <stdio.h>
#include <list>
#include <SDL2/SDL.h>

#include "Vector2D.hpp"

class GameObject {
private:
    SDL_Surface* sprite;
    
    SDL_Texture* spriteTexture;
    
    int width,height;

protected:
    bool isAlive;

public:
    float rotation;
    
    SDL_FRect rect;
    
    Vector2D velocity;
    
    GameObject(Vector2D& initialPosition, int objectWidth, int objectHeight, const std::string& assetName);
    
    virtual void update(float deltaTime) = 0;
    
    SDL_Texture* getTexture();
    
    virtual ~GameObject();
};

#endif /* GameObject_hpp */
