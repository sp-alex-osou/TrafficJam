#include "CellularAutomat.h"
#include <ctime>

CellularAutomat::CellularAutomat(Game& game, int size, int code, float density) : GameComponent(game), size(size), lookup(std::bitset<8>(code)), density(density)
{
}


void CellularAutomat::init()
{
	std::vector<bool> elements(size);

	std::srand((int)time(0));

	// straße initialisieren
	for (int i = 0; i < size; ++i)
		elements[i] = std::rand() / (RAND_MAX + 1.0f) < density;

	this->elements.push_back(elements);

	bool cars = true;
	int current = 0;

	// solange autos auf der straße
	while (cars)
	{
		cars = false;

		// für jedes feld
		for (int i = 0; i < size; ++i)
		{
			// nächsten zustand bestimmten
			elements[i] = lookup[evaluate(this->elements[current], i)];

			if (elements[i])
				cars = true;
		}

		this->elements.push_back(elements);
		current++;
	}
}


int CellularAutomat::evaluate(std::vector<bool> elements, int index)
{
	// aktuelles feld und die felder davor und danach überprüfen
	int d0 = (index < (int)elements.size() - 1 && elements[index + 1]) ? 1 : 0;
	int d1 = elements[index] ? 1 : 0;
	int d2 = (index > 0 && elements[index - 1]) ? 1 : 0;

	// binär auf dezimal umrechnen
	return d0 + 2 * d1 + 4 * d2;
}


void CellularAutomat::draw(float elapsed)
{
	CL_Vec2<float> fieldSize;

	CL_Rect viewport = window.get_viewport();
	
	fieldSize.x = (float)viewport.get_width() / size;
	fieldSize.y = (float)viewport.get_height() / elements.size();

	// für alle straßen und felder
	for (int row = 0; row < (int)elements.size(); row++)
		for (int col = 0; col < size; col++)
		{
			// farbe bestimmen
			CL_Colorf color = elements[row][col] ? CL_Colorf::red : CL_Colorf::black;
			CL_Pointf p = CL_Pointf(col * fieldSize.x, row * fieldSize.y);

			// feld zeichnen
			CL_Draw::fill(window.get_gc(), p, p + fieldSize, color);
			CL_Draw::box(window.get_gc(), p, p + fieldSize, CL_Colorf::white);
		}
}