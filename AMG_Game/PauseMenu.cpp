#include "PauseMenu.h"
#include <SFML/Graphics.hpp>

PauseMenu::PauseMenu(float width, float height) {
	font.loadFromFile("RythmOfDeath.ttf");

	//making the first word is the selected word
	pausemenu[0].setFont(font);
	pausemenu[0].setFillColor(Color::Red);
	pausemenu[0].setString("Resume");
	pausemenu[0].setCharacterSize(90);
	pausemenu[0].setPosition(Vector2f(width / 2 - 220, height / (4 + 1)));



	//second word(options)
	pausemenu[1].setFont(font);
	pausemenu[1].setFillColor(Color::White);
	pausemenu[1].setString("Volume Up");
	pausemenu[1].setCharacterSize(90);
	pausemenu[1].setPosition(Vector2f(width / 2 - 220, height / (4 + 1) * 2));






	//the third word(V down)
	pausemenu[2].setFont(font);
	pausemenu[2].setFillColor(Color::White);
	pausemenu[2].setString("Volume Down");
	pausemenu[2].setCharacterSize(90);
	pausemenu[2].setPosition(Vector2f(width / 2 - 220, height / (4 + 1) * 3));



	pausemenu[3].setFont(font);
	pausemenu[3].setFillColor(Color::White);
	pausemenu[3].setString("Back to Menu");
	pausemenu[3].setCharacterSize(90);
	pausemenu[3].setPosition(Vector2f(width / 2 - 220, height / (4 + 1) * 4));
	selected = 0;
}
PauseMenu::~PauseMenu() {

}
void PauseMenu::draw(RenderWindow& window) {
	for (int i = 0; i < 4; i++) {
		window.draw(pausemenu[i]);
	}
}
void PauseMenu::movedown() {
	if (selected + 1 <= 4)//not exit 
	{
		pausemenu[selected].setFillColor(Color::White);//brg3 lon awl wa7da a5leh abyd
		selected++;
		if (selected == 4) {
			selected = 0;
		}
		pausemenu[selected].setFillColor(Color::Red);//b8yr lon aly ana wa2f 3ndo
	}

}
void PauseMenu::moveup() {
	if (selected - 1 >= -1)//not exit 
	{
		pausemenu[selected].setFillColor(Color::White);//brg3 lon awl wa7da a5leh abyd
		selected--;
		if (selected == -1) {
			selected = 3;
		}
		pausemenu[selected].setFillColor(Color::Red);//b8yr lon aly ana wa2f 3ndo
	}

}
int PauseMenu::pressed() {
	return selected;
}


