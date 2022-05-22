#pragma once 

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Menu
{
public:
	Menu(float width, float height);
	void draw(RenderWindow& Menuu);
	void moveup();
	void movedown();
	int pressed() {
		return selected;
	}
	~Menu();
private:
	int selected;
	Font font;
	Text mainmenu[4];
};
