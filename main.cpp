#include "raylib.h"
#include "src/Game.cpp"
#include <iostream>
#include <string.h>

int main(void){
     // Set window size and target FPS
     Vector2 window_dim = {720, 640};
     SetTargetFPS(60); 

     Game game = Game(window_dim);
     InitWindow(window_dim.x, window_dim.y, "Platformer Model");

     int frame_count = 0;
     
     while (!WindowShouldClose()){
          ClearBackground(BLACK);
          BeginDrawing();

          // Draw FPS on top left
          // const char *char_FPS = std::to_string(GetFPS()).c_str(); 
          // DrawText(char_FPS, 0, 0, 24, RAYWHITE);  

          game.update();
          game.draw();

          // Record
          frame_count += 1;
          const char *file_path      = "video_frames/screen_";
          const char *file_extension = ".png";
          char file_index[256]; 
          sprintf(file_index, "%04d", frame_count);
          char file_name[100]; 
          strcpy(file_name, file_path);
          strcat(file_name, file_index);
          strcat(file_name, file_extension); 

          EndDrawing();

          TakeScreenshot(file_name); 
     }

     CloseWindow();
     return -1;
}

