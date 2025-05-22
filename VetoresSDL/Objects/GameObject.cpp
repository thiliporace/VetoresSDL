//
//  GameObject.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include "GameObject.hpp"
#include "SdlManager.hpp"

#include <stdio.h>
#include <iostream>
#include <SDL2_image/SDL_image.h>

using namespace std;

GameObject::GameObject(Vector2D& initialPosition, int objectWidth, int objectHeight, const std::string& assetName) : velocity(Vector2D(0,0)), width(objectWidth), height(objectHeight), rotation(0) {
    SdlManager* sdlManager = SdlManager::getInstance();
        
    spriteTexture = nullptr;
    
    sprite = IMG_Load(assetName.c_str());
    
    if (!sprite){
        cout << "Error Surface: " << SDL_GetError() << endl;
        return;
    }
    
    spriteTexture = SDL_CreateTextureFromSurface(sdlManager->getRenderer(), sprite);
    
    if (!spriteTexture){
        cout << "Error Texture: " << SDL_GetError() << endl;
        return;
    }
    
    SDL_FreeSurface(sprite);
    
    int wPosition = static_cast<int>(rect.w);
    int hPosition = static_cast<int>(rect.h);
    
    SDL_QueryTexture(spriteTexture, NULL, NULL, &wPosition, &hPosition); //Conecta textura com posicao
    
    rect.x = initialPosition.x;
    rect.y = initialPosition.y;
    
    width = objectWidth;
    height = objectHeight;
    
    rect.w = width;
    rect.h = height;
}

GameObject::~GameObject(){
    if (spriteTexture) {
        SDL_DestroyTexture(spriteTexture);
        spriteTexture = nullptr;
    }
}

SDL_Texture* GameObject::getTexture(){
    return spriteTexture;
}
