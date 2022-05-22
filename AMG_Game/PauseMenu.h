#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class PauseMenu
{
public:
	PauseMenu(float w, float h);
	void draw(RenderWindow& window);
	void moveup();
	void movedown();
	int pressed();

	~PauseMenu();
private:
	int selected;
	Font font;
	Text pausemenu[4];

};

 