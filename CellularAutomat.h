#pragma once

#include "GameComponent.h"

#include <vector>
#include <bitset>

class CellularAutomat : public GameComponent
{
public:
	CellularAutomat(Game& game, int size, int code, float density);
	void init();
	void draw(float elapsed);
	int evaluate(std::vector<bool> elements, int index);
private:
	std::bitset<8> lookup;
	std::vector<std::vector<bool>> elements;
	int size;
	float density;
};

