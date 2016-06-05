#ifndef MAIN_HPP
#define MAIN_HPP

#include <SDL/SDL.h>

//#define PARA_GUI_USED

class fileNotFound {};
	
int main(int argc, char* argv[]);
void initGL(int width, int height);
void initSDL(int width, int height);
/// Update animation and controls/display independently
void update(Uint32 ms);
void draw();
void handleInput(SDL_Event *e);
int mainLoop();
void terminateApp();
#endif //MAIN_HPP

