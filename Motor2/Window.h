#pragma once
#include<SDL/SDL.h>
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
	void swapWindow();
	void clearWindow();
	int getScreenWidth()const {
		return screenWidth;
	}
	int getScreenHeight() const {
		return screenHeight;
	}

};

