#pragma once
#include "Platform.h"
#include <map>
using std::map;
class Platform;
class GameStateManager;

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual bool Input(map<int, bool> keys) = 0;
	virtual bool MouseInput(int x, int y) = 0;
	virtual bool Update() = 0;
	virtual void Close() = 0;
};

