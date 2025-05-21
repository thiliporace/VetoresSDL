//
//  main.cpp
//  VetoresSDL
//
//  Created by Thiago Liporace on 19/05/25.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <cmath>

#include "Vector2D.hpp"
#include "SdlManager.hpp"
#include "PlayerGameObject.hpp"
#include "EnemyGameObject.hpp"

const float MS_PER_UPDATE = 0.004;

SdlManager* sdlManager = SdlManager::getInstance();

std::shared_ptr<PlayerGameObject> playerShip = std::make_shared<PlayerGameObject>(Vector2D(400,400), 40, 40, "player.png");

std::shared_ptr<Vector2D> playerDirectionVector;

std::shared_ptr<EnemyGameObject> enemyShip = std::make_shared<EnemyGameObject>(Vector2D(400,100), 40, 40, "enemy.png");

std::list<std::shared_ptr<GameObject>> gameObjectsInScene;

Vector2D enemyToPlayerVector;

void vectorCalculations(){
    enemyToPlayerVector = Vector2D(playerShip->rect.x - enemyShip->rect.x, playerShip->rect.y - enemyShip->rect.y);
    
    float angleBetweenEnemyAndPlayer = (enemyShip->forwardVector.angleBetween(enemyToPlayerVector)) * (180/M_PI);
    
    bool isPlayerInLineOfSight = angleBetweenEnemyAndPlayer < (enemyShip->fov/2) ? true : false;
    
    std::cout << "player in line of sight: " << isPlayerInLineOfSight << std::endl;
    
    float dotProductBetweenPlayerAndEnemy = enemyShip->forwardVector.dotProduct(*playerDirectionVector);
    
    bool isPlayerFacingEnemy = dotProductBetweenPlayerAndEnemy > 0 ? false : true;
    
    if (dotProductBetweenPlayerAndEnemy != 0) std::cout << "player facing enemy: " << isPlayerFacingEnemy << std::endl;
}

void update(float deltaTime){
    for (auto& gameObject : gameObjectsInScene){
        gameObject->update(deltaTime);
    }
    
    vectorCalculations();
}

void render(SDL_Renderer* renderer){
    SDL_RenderClear(renderer);
    
    for(auto& gameObject : gameObjectsInScene){
        if (!gameObject->getTexture()) continue;
        SDL_RenderCopyF(renderer, gameObject->getTexture(), NULL, &gameObject->rect);
    }
    
    SDL_RenderPresent(renderer);
}

void handlePlayerMovement(float deltaTime){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    playerDirectionVector = std::make_shared<Vector2D>(Vector2D(0,0));
    
    if (playerShip == nullptr) {
        std::cout << "player nao encontrado" << std::endl;
        return;
    }
    if (keystate[SDL_SCANCODE_W]) {
        playerDirectionVector->y -= 1;
    }
    if (keystate[SDL_SCANCODE_A]){
        playerDirectionVector->x -= 1;
    }
    if (keystate[SDL_SCANCODE_D]){
        playerDirectionVector->x += 1;
    }
    if (keystate[SDL_SCANCODE_S]){
        playerDirectionVector->y += 1;
    }
    
    if(playerDirectionVector->x != 0 || playerDirectionVector->y != 0){
        playerShip->moveTo(*playerDirectionVector, deltaTime);
    }
    else{
        playerShip->stopMoving(deltaTime);
    }
}

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

int main(int argc, const char * argv[]) {
    SDL_Renderer* renderer = sdlManager->getRenderer();
       
    SDL_Event event;
    bool quit = false;
   
    double previous = getCurrentTime();
   
    double lag = 0.0;
    
    gameObjectsInScene.push_back(playerShip);
    gameObjectsInScene.push_back(enemyShip);
    
    while (!quit){
        double current = getCurrentTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;
        
        while(SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        
        handlePlayerMovement(MS_PER_UPDATE);
        
        while (lag >= MS_PER_UPDATE){
            update(MS_PER_UPDATE);
            lag -= MS_PER_UPDATE;
        }
        
        render(renderer);
    }
    
    return 0;
}
