
#include "raylib.h"
#include <iostream>

class Platform: public Entity{
     public:
          Platform(int id, float x, float y, float width, float height){
               name         = "plataforma " + std::to_string(id); 
               state        = "ok";
               position     = (Vector2)   { x, y };
               bounding_box = (Rectangle) { position.x - width/2, position.y - height/2, width, height };
          }

          void update() {
               bounding_box.x = position.x - bounding_box.width/2;
               bounding_box.y = position.y - bounding_box.height/2;
               return;
          }

          void draw() override {              
               DrawCircle(bounding_box.x, bounding_box.y, 5, WHITE);
               if(state == "ok") DrawRectangleLinesEx(bounding_box, 1, RED);
               else if(state == "colidindo") DrawRectangleLinesEx(bounding_box, 1, YELLOW);
               return;
          }
};


