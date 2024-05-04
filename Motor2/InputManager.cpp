#include "InputManager.h"

InputManager::InputManager()
{
	mouseCoords = vec2(0.0f, 0.0f);

}

InputManager::~InputManager()
{
}

void InputManager::pressKey(unsigned int keyID)
{
	this->keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
	this->keyMap[keyID] = false;

}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto it = keyMap.find(keyID);
	if (it != keyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}

}

void InputManager::setMouseCoords(float x, float y)
{
	mouseCoords.x = x;
	mouseCoords.y = y;
}
