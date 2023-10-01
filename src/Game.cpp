#pragma once

#include "raylib.h"
#include "Entity.cpp"
#include "Platform.cpp"
#include "Player.cpp"
#include "../headers/backstage_math.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <iostream>

class Game{
     private:
          int play_progression; 
  
          Vector2 origin;
          Vector2 window_limits;

          std::unique_ptr<Player> player;
          std::vector<std::unique_ptr<Entity>> entities;

     public:
          Game(Vector2 window_dim){
               play_progression = 0;
               window_limits    = window_dim;
               origin           = (Vector2){0, 0};
    
               // TODO Fazer o level loader
               player = std::make_unique<Player>(300, 100, 50, 50);
               
               auto box_1 = std::make_unique<Platform>(0, window_dim.x/2, window_dim.y/2, 100, 100); 
               entities.push_back( std::move(box_1) );

               auto box_2 = std::make_unique<Platform>(0, window_dim.x/2 - 100, window_dim.y/2 - 100, 200, 50); 
               entities.push_back( std::move(box_2) );

               for(int i = 0; i< 20; i++){
                    float s = 20;
                    auto box_3 = std::make_unique<Platform>(0, window_dim.x/2 - 100 + i*s, window_dim.y/2 + 200, s, 50); 
                    entities.push_back( std::move(box_3) );
               }

          }

          void update(){
               player->handle_inputs();

               // Collisions
               Vector2 c_point  = (Vector2) {0, 0};
               Vector2 c_normal = (Vector2) {0, 0};
               float   c_t      = 0.0;
               std::vector<std::pair<float, int>> collisions_to_resolve;
               
               for(int i = 0; i < (int) entities.size(); i++){
                    bool playercollision = CheckCollisionEntityRec(player, entities[i]->get_bounding_box(), c_point, c_normal, c_t);
                    if(playercollision) {
                         collisions_to_resolve.push_back(std::make_pair(c_t, i));
                         entities[i]->change_state("colidindo"); 
                    }
                    else entities[i]->change_state("ok");
               }

               std::sort(collisions_to_resolve.begin(), collisions_to_resolve.end());

               for(auto z : collisions_to_resolve){
                    ResolveCollisionEntityRec(player, entities[z.second]->get_bounding_box());
               }

               player->update();

               return;
          }

          void draw(){
               player->draw();
               for(int i = 0; i < (int) entities.size(); i++){
                    entities[i]->draw();
               }
               return;
          }
};
