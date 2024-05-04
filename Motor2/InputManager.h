#pragma once
#include <glm/glm.hpp>
#include<unordered_map>
using namespace std;
using namespace glm;
class InputManager
{
public:
	InputManager();
	~InputManager();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	bool isKeyDown(unsigned int keyID);
	void setMouseCoords(float x, float y);
	vec2 getMouseCoords() const { return mouseCoords; }
private :
	unordered_map<unsigned int, bool> keyMap;
	vec2 mouseCoords;


};

