#include <SDL2/SDL.h>
#include "Game.h"

Game* g_game = 0;

//how many FPS we want to run at
const int FPS = 60; 

//divided by num of ms in a second, giving time to delay game between loops to keep a constant frame rate
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
 {
   //the start time of the frame, and the time it took the last frame
   Uint32 frameStart, frameTime;

   std::cout << "\n\nMain: game init attempt..\n";

   if(TheGame::Instance()->init("Games Framework Core Modules", 100, 100, 640, 480, true)) {
   std::cout << "Main: game init successful\n";

   //main game loop
   while (TheGame::Instance()->running())
     {
       //get time at start of frame (num ms since calling SDL_Init)
       frameStart = SDL_GetTicks();
       
       //run core game loop
       TheGame::Instance()->handleEvents();
       TheGame::Instance()->update();
       TheGame::Instance()->render();

       //how long the frame took to run
       frameTime = SDL_GetTicks() - frameStart;

       //if time taken to run frame is less than desired 
       if(frameTime < DELAY_TIME)
       {
         //call delay to make wait for time to reach desired FPS
         SDL_Delay((int)(DELAY_TIME - frameTime));
       }
     }
   }
   else
   {
     std::cout << "Main: game init failure - " << SDL_GetError() << "\n";
     return -1;
   }
  
   std::cout << "Main: game closing\n";
   TheGame::Instance()->clean();

   return 0;
 }
