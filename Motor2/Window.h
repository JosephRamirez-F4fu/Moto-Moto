#pragma once
#include<SDL/SDL.h>
#include<string>
using namespace std;
enum WindowFlags 
{ INVISIBLE = 0x1,FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Window
{
private:
	SDL_Window* window;
	int screenWidth;
	int screenHeight;
public:
	Window();
	~Window();
	int create(string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
	void swapWindow();
	int getScreenWidth()const {
		return screenWidth;
	}
	int getScreenHeight() const {
		return screenHeight;
	}

};

