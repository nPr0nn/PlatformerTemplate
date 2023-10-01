
#include "raylib.h"
#include <iostream>

class Player: public Entity{
     protected:
          Vector2 speed;
          Vector2 acc;
          
          float GRAV;
          float ACC;
          float FRICC;

     public:
          Player(float x, float y, float width, float height){
               name         = "player"; 
               state        = "movendo";
               position     = (Vector2)   { x, y };

               ACC          = 1;
               GRAV         = 1;
               FRICC        = -0.1;
               speed        = (Vector2)   { 7, 7 };
               
               bounding_box = (Rectangle) { position.x - width/2, position.y - height/2, width, height };
          }

          void add_velocity(Vector2 new_speed, Vector2 new_dir){
               velocity = (Vector2) { velocity.x + new_dir.x * new_speed.x, velocity.y + new_dir.y * new_speed.y } ;
               return;
          }
          
          void add_acceleration(Vector2 new_acc, Vector2 new_dir){
               acceleration = (Vector2) { acceleration.x + new_dir.x * new_acc.x, acceleration.y + new_dir.y * new_acc.y };
               return;
          }

          void handle_inputs(){
               if(IsKeyDown(KEY_A))      acceleration.x = -ACC;
               else if(IsKeyDown(KEY_D)) acceleration.x =  ACC;
               else                      acceleration.x =  0;
               //if(IsKeyDown(KEY_A))      velocity.x = -speed.x;
               //else if(IsKeyDown(KEY_D)) velocity.x =  speed.x;
               //else                      velocity.x =  0;

               //if(IsKeyDown(KEY_W))      velocity.y = -speed.y;
               //else if(IsKeyDown(KEY_S)) velocity.y =  speed.y;
               //else                      velocity.y =  0;
          
               acceleration.y  = GRAV;
               velocity.y     += acceleration.y;
               if(velocity.y > 10) velocity.y = 10;

               if(IsKeyPressed(KEY_SPACE)) velocity.y = -20;

               acceleration.x += velocity.x * FRICC;
               velocity.x     += acceleration.x;
               return;
          }

          void update() override{

               position.x = position.x + velocity.x;
               position.y = position.y + velocity.y;

               bounding_box.x = position.x - bounding_box.width/2;
               bounding_box.y = position.y - bounding_box.height/2;
               return;
          }

          void draw() override { 
               DrawRectangleLinesEx(bounding_box, 1, GREEN);
               return;
          }
};



