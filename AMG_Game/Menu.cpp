#include "Menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu(float width, float height) {
	font.loadFromFile("RythmOfDeath.ttf");

	//making the first word is the selected word
	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color::Red);
	mainmenu[0].setString("Play");
	mainmenu[0].setCharacterSize(80);
	mainmenu[0].setPosition(Vector2f(width / 2 - 800, height / (4 + 1)));



	//second word(options)
	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color::White);
	mainmenu[1].setString("Instructions");
	mainmenu[1].setCharacterSize(80);
	mainmenu[1].setPosition(Vector2f(width / 2 - 800, height / (4 + 1) * 2));






	//the third word(exit)
	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color::White);
	mainmenu[2].setString("History");
	mainmenu[2].setCharacterSize(80);
	mainmenu[2].setPosition(Vector2f(width / 2 - 800, height / (4 + 1) * 3));



	mainmenu[3].setFont(font);
	mainmenu[3].setFillColor(Color::White);
	mainmenu[3].setString("Exit");
	mainmenu[3].setCharacterSize(80);
	mainmenu[3].setPosition(Vector2f(width / 2 - 800, height / (4 + 1) * 4));
	selected = 0;
}
Menu::~Menu() {

}

void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < 4; i++) {
		window.draw(mainmenu[i]);
	}
}

void Menu::movedown() {
	if (selected + 1 <= 4)//not exit 
	{
		mainmenu[selected].setFillColor(Color::White);//brg3 lon awl wa7da a5leh abyd
		selected++;
		if (selected == 4) {
			selected = 0;
		}
		mainmenu[selected].setFillColor(Color::Red);//b8yr lon aly ana wa2f 3ndo
	}

}
void Menu::moveup() {
	if (selected - 1 >= -1)//not play
	{
		mainmenu[selected].setFillColor(Color::White);//brg3 lon awl wa7da a5leh abyd
		selected--;
		if (selected == -1) {
			selected = 3;
		}
		mainmenu[selected].setFillColor(Color::Red);//b8yr lon aly ana wa2f 3ndo
	}

}
