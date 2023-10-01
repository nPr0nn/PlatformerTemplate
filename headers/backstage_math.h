
#include "raylib.h"
#include<cmath>
#include <iostream>
#include <memory>

class Player;
//class Entity;

bool CheckCollisionRayRec(Vector2 ray_origin, Vector2 ray_dir, Rectangle rec, Vector2 &c_point, Vector2 &c_normal, float &t_hit_near){

     Vector2 inv_dir = (Vector2) { 1/ray_dir.x, 1/ray_dir.y };
     Vector2 t_near  = (Vector2) { (rec.x - ray_origin.x)*inv_dir.x, (rec.y - ray_origin.y)*inv_dir.y };
     Vector2 t_far   = (Vector2) { (rec.x + rec.width - ray_origin.x)*inv_dir.x, (rec.y + rec.height - ray_origin.y)*inv_dir.y };

     if (std::isnan(t_far.y)  || std::isnan(t_far.x) || std::isnan(t_near.y) || std::isnan(t_near.x)){ 
          return false;
     }

     // Sort distances and early rejection
	if(t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if(t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
     if(t_near.x > t_far.y || t_near.y > t_far.x) return false; 

     // Find t of contact
     t_hit_near       = std::max(t_near.x, t_near.y);
     float t_hit_far  = std::min(t_far.x, t_far.y);

     if(t_hit_far < 0) return false; 

     // Find contact point
     c_point = (Vector2) { ray_origin.x+ t_hit_near*ray_dir.x, ray_origin.y + t_hit_near*ray_dir.y };
     
     // Find normal
     if(t_near.x > t_near.y)      c_normal = (inv_dir.x < 0) ? (Vector2) {1,0} : (Vector2) {-1,0};
     else if(t_near.x < t_near.y) c_normal = (inv_dir.y < 0) ? (Vector2) {0,1} : (Vector2) {0,-1};

     return true;
}

bool CheckCollisionEntityRec(std::unique_ptr<Player> &en, Rectangle rec_static, Vector2 &c_point, Vector2 &c_normal, float &t_hit_near){
     //if (!en->moving()) return false;
     
     float deltaT = 1;

     Rectangle expanded_target;
     expanded_target.x  = rec_static.x - 0.5*en->get_bounding_box().width;
     expanded_target.y  = rec_static.y - 0.5*en->get_bounding_box().height;
     expanded_target.width  = rec_static.width  + en->get_bounding_box().width;
     expanded_target.height = rec_static.height + en->get_bounding_box().height;
     
     Vector2 ray_origin = en->get_position();
     Vector2 ray_dir    = en->get_velocity();

     // DrawLineV(ray_origin, ray_dir, ORANGE);
     DrawRectangleLinesEx(expanded_target, 1, BLUE);

     if(CheckCollisionRayRec(ray_origin, ray_dir, expanded_target, c_point, c_normal, t_hit_near)){
          return (t_hit_near >= 0 && t_hit_near < 1);
     }
     return false;
}

bool ResolveCollisionEntityRec(std::unique_ptr<Player> &en, Rectangle rec_static){
     Vector2 c_point  = (Vector2) {0, 0};
     Vector2 c_normal = (Vector2) {0, 0};
     float   c_t      = 0.0;

     if(CheckCollisionEntityRec(en, rec_static, c_point, c_normal, c_t)){
          Vector2 new_velocity;
          
          DrawCircleV(c_point, 10, BLUE);
          DrawLineV( c_point, (Vector2){c_point.x + 60*c_normal.x, c_point.y + 60*c_normal.y}, ORANGE);

          new_velocity.x =  (1 - c_t) * std::abs(en->get_velocity().x);
          new_velocity.y =  (1 - c_t) * std::abs(en->get_velocity().y);

          //if(c_normal.y > 0){
               //new_velocity.y = 0;
          //}
          en->add_velocity(new_velocity, c_normal);


          return true;
     }

     return false;
}
