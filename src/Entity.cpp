
#include "raylib.h"
#include <iostream>

class Entity{
     protected:
          std::string  name;
          std::string  state;
          Vector2 position;
          Vector2 velocity;
          Vector2 acceleration;
          Rectangle bounding_box;
        
     public:
          virtual ~Entity() { }

          virtual Vector2 get_position(){
               return position;
          }

          virtual Vector2 get_velocity(){
               return velocity;
          }

          virtual Vector2 get_acceleration(){
               return acceleration;
          }

          virtual Rectangle get_bounding_box(){
               return bounding_box;
          }

          virtual bool moving(){
               if (velocity.x == 0 && velocity.y == 0) return false;
               return true;
          }

          virtual void change_state(std::string new_state){
               state = new_state;
               return;
          }

          virtual void update(){
               return;
          }

          virtual void draw(){
               return;
          }
};


