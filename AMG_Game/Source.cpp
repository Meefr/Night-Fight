#include <SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <ctime>
#include <random>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Menu.h"
#include "PauseMenu.h"


using namespace sf;
using namespace std;

//***************PAGENUM***********************************************************
// player1 name -> 0 , player 2 name -> 6                                         *
// choose1 ->13 , choose2 ->14                                                    *
//  round 1 ->10 , round2 ->11 , round 3 ->12	                                  *
// instructions->3                                                                *
//*********************************************************************************

bool CIPlCT = 1; // cheak if the player choose anything.
int roundnum;//for gravity fun

string player1;
string player2;

Texture Ftex;
Sprite Fsprit;

Texture Atex;
Sprite Asprit;

Texture Ttex;
Sprite Tsprit;

Texture P1LogoTex;
Sprite P1LogoSprit;

Texture P2LogoTex;
Sprite P2LogoSprit;

Texture Enemy2Tex;


Texture types_text[4];

Texture r1, r2, fr;
Sprite round1, round2, finalround;

Texture PauseTex;
Sprite PauseSprite;

Texture texth;




SoundBuffer buffer;
Sound sound;
SoundBuffer buffer2;
Sound sound2;
SoundBuffer buffer3;
Sound sound3;
SoundBuffer buffer4;
Sound sound4;
SoundBuffer bufferMele;
Sound soundMele;
SoundBuffer bufferPlayer1;
Sound soundPlayer1;
SoundBuffer bufferPlayer2;
Sound soundPlayer2;
SoundBuffer bufferpistol;
SoundBuffer bufferrifle;
SoundBuffer bufferGG;
SoundBuffer bufferRound1;
Sound soundRound1;

SoundBuffer bufferAfterEnter;
Sound soundAfterEnter;

SoundBuffer bufferplayer1wins;
Sound soundplayer1wins;
SoundBuffer bufferplayer2wins;
Sound soundplayer2wins;




Clock enemy2Clock1, enemy2Clock2;
Clock P1MeleClock, P2MeleClock;

Font font;


int HeroTypeChoice[2];  // 0 -> player1 ,, 1 ->player2 // {  1 -> Fighter ,, 2 -> Assassin ,, 3 -> Tank  }
int player_t1, player_t2;//player 1 type & player2 type
int p1score = 0, p2score = 0;
int ground = 960;
int wrightwall = 1850;
int leftwall = 0;
double gr = 0.1;//gravity of power
double vvy = 0;//velociyt of powers
double vvy2 = 0;//velociyt of weapon
float playergun1 = 0;//animation gun for player1 
float playergun2 = 0;//animation gun for player2
vector<CircleShape>V;
CircleShape powers[3];

Vector2f powerupint[25];

int chose, h = 0;
bool Add1, Add2, timer1, timer2;

int timerpowerup1 = 1, timerpowerup2;
bool untargetable = 0, untargetable2 = 0;

bool bl = 1;
bool bl2 = 1;

int ChooseWeapon;

int pagenum = 1000;

Texture Enemyphoto;
//*********************************************************************************

struct Enemy
{
	Sprite shape;
	int speed;
	int maxi, mini;
	bool Move;
	bool DoDamage;
	int timer1, timer2;
	float x = 0;
};

struct Bullet
{
	// 1-> pistol , 2-> rifle , 3-> goldengun
	float Speed;
	int Damage;
	int Magazin;
	Sprite BulletSprite;
	int type;
	bool CoolDownBool = 1;
	int CoolDownuse;
	int moveTo;
	int meletimer = 2;
	Sound BulletSound;
};

Enemy enemy[6], enemy2[2];

//*********************************************************************************

class Weapon
{

	//***********************************************
public:

	//***********************************************
	Weapon()
	{
		photoPistol.loadFromFile("Pistol.PNG");
		photoRifle.loadFromFile("Rifle.PNG");
		photoGG.loadFromFile("GG.PNG");
		GunPhoto.setScale(0.2, 0.2);
		//PistolBullet.loadFromFile("PistolBulet.PNG"/*"heart.PNG"*/);
		RifleBullet.loadFromFile("RifleBulet.PNG"/*"heart.PNG"*/);
		//GGBullet.loadFromFile("GGBulet.PNG"/*"heart.PNG"*/);
		bufferpistol.loadFromFile("Pistol Sound.wav");
		bufferrifle.loadFromFile("Rifle sound.wav");
		bufferGG.loadFromFile("GG Sound.wav");
	}
	//***********************************************
	int BulletSpeed = 1;
	//int Bullet_scale = 1;
	int Magazin = 2;
	Sprite GunPhoto;
	Sound WeaponSound;
	Texture PistolBullet;
	Texture photoPistol;
	Texture RifleBullet;
	Texture GGBullet;
	Texture photoRifle;
	Texture photoGG;
	Texture GeneralBulletSprite;
	//Sprite GunPhoto;
	int WeaponType = 0; // 1-> pistol , 2-> rifle , 3-> goldengun
	int Cooldown;
	int Damage = 1;

};

class PowerUps // 1st class "Dealing with the powerup"
{
public:
	void add() //adding the powerup shapes.
	{
		V.push_back(powers[chose]);
		Add1 = 0;
	}
	void delet(int i = V.size() - 1) //deleating the powershapes .
	{
		if (V.size() > 0)
			V.erase(V.begin() + i);
		bl = 1;
	}
};
class Player_Powerups //2nd class "Dealing with the valuo of the powerup for each player'
{
	int health;
	float speed;
public:
	void setHealth(int x)
	{
		health = x;
	}
	void setSpeed(float x)
	{
		speed = x;
	}

	int getHealth()
	{
		return health;
	}
	float getSpeed()
	{
		return speed;
	}

};

class player // 3rd class "moving the players "
{
public:
	float dx, dy;
	FloatRect rect;
	bool onground = 0;
	Sprite sprite;
	float f;
	float timergaindamage;
	Bullet bullet;
	vector<Bullet>V_Bullets;

	struct HT // HeroType
	{
		float Speed;
		int Health;
	} HeroType;

	int lastkeypressed;
	int lastkeypressedused;

	//***********************************************

	player(Texture& i) {
		sprite.setTexture(i);
		sprite.setScale(1.7, 1.7);
		rect = FloatRect(0, 0, 30, 50);
		dx = 0.00001; dy = 0.00001;
		f = 0;
	}

	//***********************************************
	void update(float time) {

		rect.left += (dx * time);
		if (!onground) {
			dy += (0.0005 * time);
		}
		rect.top += (dy * time);
		onground = 0;
		if (rect.top > ground) {
			rect.top = ground;
			dy = 0;
			onground = 1;
		}
		if (rect.left > wrightwall) {
			rect.left = wrightwall;
		}
		if (rect.left < leftwall) {
			rect.left = leftwall;
		}
		f += (0.005 * time);
		if (f > 6) {
			f -= 6;
		}
		if (dx > 0) {
			sprite.setTextureRect(IntRect(30 * int(f), 0, 25, 50));
		}
		if (dx < 0) {
			sprite.setTextureRect(IntRect(30 * int(f) + 25, 0, -30, 50));
		}
		dx = 0;
		sprite.setPosition(rect.left, rect.top);
	}
};


//*********************************************************************************


void Gravity_Weapon(Weapon& w, Sprite arr[22], int roundnum)
{
	int ans;
	for (int i = 0; i < 22; i++)
	{
		if (roundnum == 2) {
			if (i == 1 || i == 0 || i == 2 || i == 3 || i == 4 || i == 8 || i == 11) {
				continue;
			}
		}

		if (!w.GunPhoto.getGlobalBounds().intersects(arr[i].getGlobalBounds()) && bl2)
		{
			vvy2 += gr;
		}
		if (w.GunPhoto.getGlobalBounds().intersects(arr[i].getGlobalBounds()) && bl2) {
			bl2 = 0;
			w.GunPhoto.setPosition(w.GunPhoto.getPosition().x, arr[i].getPosition().y - 40);
			ans = i;
			vvy2 = 0;
			break;
		}
	}
	if (bl2)
		w.GunPhoto.move(0, vvy2);
	else
	{
		static Clock cs;
		if (cs.getElapsedTime().asSeconds() > 0.03) {
			w.GunPhoto.move(0, -0.2);
			cs.restart();
		}
	}
}
void Gravity_Powerups(CircleShape& c, Sprite arr[22], int roundnum)
{
	for (int i = 0; i < 22; i++)
	{
		if (roundnum == 2) {
			if (i == 1 || i == 0 || i == 2 || i == 3 || i == 4 || i == 8 || i == 11) {
				continue;
			}
		}
		if (!c.getGlobalBounds().intersects(arr[i].getGlobalBounds()) && bl)
		{
			vvy += gr;
		}
		if (c.getGlobalBounds().intersects(arr[i].getGlobalBounds()) && bl) {
			bl = 0;
			c.setPosition(c.getPosition().x, /*ground + 7*/arr[i].getPosition().y - 40);
			vvy = 0;
		}
	}
	if (bl)
		c.move(0, vvy);
	else
	{
		static Clock cs;
		if (cs.getElapsedTime().asSeconds() > 0.03) {
			c.move(0, -0.2);
			cs.restart();
		}
	}
}

void MakeWeapon(int x, Weapon& weapon)
{
	// we need to add the gavity function 
	if (x == 1) //Pistol 
	{
		weapon.WeaponType = x;
		weapon.BulletSpeed = 4;
		weapon.Magazin = 3;
		weapon.Cooldown = 2;
		weapon.Damage = 1;
		weapon.GunPhoto.setTexture(weapon.photoPistol);
		weapon.GeneralBulletSprite = weapon.RifleBullet;
		weapon.WeaponSound.setBuffer(bufferpistol);
		//GunPhoto.setScale(1, 1);
		//GunPhoto.setPosition(xx, yy); //just add the gravity function . 
	}

	else if (x == 2) //Rifle 
	{
		weapon.WeaponType = x;
		weapon.BulletSpeed = 6;
		weapon.Magazin = 6;
		weapon.Cooldown = 1;
		weapon.Damage = 1;
		weapon.GunPhoto.setTexture(weapon.photoRifle);
		weapon.GeneralBulletSprite = weapon.RifleBullet;
		weapon.WeaponSound.setBuffer(bufferrifle);
	}
	else if (x == 3) //GoldenGun
	{

		weapon.WeaponType = x;
		weapon.BulletSpeed = 8;
		weapon.Magazin = 1;
		weapon.Cooldown = 1;
		weapon.Damage = 10;
		weapon.GunPhoto.setTexture(weapon.photoGG);
		weapon.GeneralBulletSprite = weapon.RifleBullet;
		weapon.WeaponSound.setBuffer(bufferGG);
	}

	weapon.GunPhoto.setScale(2, 2);
	weapon.GunPhoto.setPosition(powerupint[h]);
}

void p1(RenderWindow& window);
void p2(RenderWindow& window);
void His(RenderWindow& window);

void Round1(RenderWindow& window);
void Round2(RenderWindow& window);
void Round3(RenderWindow& window);

void OptionsWin(RenderWindow& window);

void GameOver(RenderWindow& window, int, int);

void UpdateHeroType(player&, player&);
void block(Sprite x[]);
void blockround2(Sprite x[]);
void blockround3(Sprite x[]);
void choose1(RenderWindow& window);
void choose2(RenderWindow& window);
//*********************************************************************************

int main()
{

	srand(static_cast<unsigned>(time(NULL)));
	Font font;
	font.loadFromFile("RythmOfDeath.ttf");
	RenderWindow Menuu(VideoMode(1920, 1080), "Night Fight", Style::None | Style::Fullscreen);
	Menuu.setFramerateLimit(60);
	Menu menu(1920, 1080);
	SoundBuffer buffer;
	buffer.loadFromFile("equip.wav");
	Sound sound;
	sound.setBuffer(buffer);
	SoundBuffer buffer2;
	buffer2.loadFromFile("Mainmenu.wav");
	Sound sound2;
	sound2.setBuffer(buffer2);
	SoundBuffer buffer3;
	buffer3.loadFromFile("select.wav");
	Sound sound3;
	sound3.setBuffer(buffer3);
	sound3.setVolume(25);

	buffer4.loadFromFile("GGsound.wav");

	sound4.setBuffer(buffer4);

	bufferMele.loadFromFile("MeleSound.wav");
	soundMele.setBuffer(bufferMele);

	bufferPlayer1.loadFromFile("Player 1.wav");
	soundPlayer1.setBuffer(bufferPlayer1);
	bufferPlayer2.loadFromFile("Player 2.wav");
	soundPlayer2.setBuffer(bufferPlayer2);

	bufferRound1.loadFromFile("Round1.wav");
	soundRound1.setBuffer(bufferRound1);

	bufferAfterEnter.loadFromFile("After Enter.wav");
	soundAfterEnter.setBuffer(bufferAfterEnter);

	bufferplayer1wins.loadFromFile("player1wins.wav");
	soundplayer1wins.setBuffer(bufferplayer1wins);
	bufferplayer2wins.loadFromFile("player2wins.wav");
	soundplayer2wins.setBuffer(bufferplayer2wins);

	Image icon;
	icon.loadFromFile("icon.PNG");
	//Menuu.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	types_text[0].loadFromFile("Fighter.png");
	types_text[1].loadFromFile("Tank.png");
	types_text[2].loadFromFile("Assassin.png");
	types_text[3].loadFromFile("NameWithoutSelect.png");

	r1.loadFromFile("Round1.PNG");
	r2.loadFromFile("Round2.PNG");
	fr.loadFromFile("FinalRound.PNG");
	round1.setTexture(r1);
	round2.setTexture(r2);
	finalround.setTexture(fr);


	Texture text;
	text.loadFromFile("wallpaperflare.com_wallpaper (2).JPG");
	Sprite bg;
	bg.setTexture(text);
	Enemyphoto.loadFromFile("ghost.png");

	Ftex.loadFromFile("FighterInfo.png");
	Atex.loadFromFile("AssassinInfo.png");
	Ttex.loadFromFile("TankInfo.png");

	P1LogoTex.loadFromFile("Player1Logo.png");
	P1LogoSprit.setTexture(P1LogoTex);
	P1LogoSprit.setScale(-1, 1);

	P2LogoTex.loadFromFile("Player2Logo.png");
	P2LogoSprit.setTexture(P2LogoTex);
	P2LogoSprit.setScale(-1, 1);

	PauseTex.loadFromFile("pausePH.png");
	PauseSprite.setTexture(PauseTex);
	//history

	ofstream offile;
	offile.open("history.txt", ios::app);

	Enemy2Tex.loadFromFile("enemy2spritesheet.png");



	for (int i = 0; i < 2; i++)
	{
		enemy2[i].shape.setTexture(Enemy2Tex);
		enemy2[i].shape.setScale(0.6, 0.6);
		enemy2[i].shape.setTextureRect(IntRect(0, 0, 156, 125));
		enemy2[i].speed = 2.5;
		enemy2[i].Move = 1;
		enemy2[i].DoDamage = 1;
		enemy2[i].timer1 = 0;
		enemy2[i].timer2 = 0;
	}


	enemy2[0].mini = 0;
	enemy2[0].maxi = 860;
	enemy2[0].shape.setPosition(0, 970);

	enemy2[1].mini = 1030;
	enemy2[1].maxi = 1880;
	enemy2[1].shape.setPosition(1920, 970);



	while (true) {
		if (pagenum == 1000)
		{
			soundRound1.stop();
			sound2.play();
			sound2.setVolume(30);
			sound2.setLoop(true);
			while (Menuu.isOpen()) {

				Event event;
				while (Menuu.pollEvent(event)) {
					if (event.type == Event::Closed) {
						Menuu.close();

					}


					if (event.type == Event::KeyPressed) {
						if (event.key.code == Keyboard::Up) {
							menu.moveup();
							sound3.play();
							break;
						}
						if (event.key.code == Keyboard::Down) {
							menu.movedown();
							sound3.play();
							break;
						}
						//page num
						if (event.key.code == Keyboard::Return) // return=enter
						{
							soundAfterEnter.play();
							if (menu.pressed() == 0) {

								//Menuu.close();


								pagenum = 0;
							}
							if (menu.pressed() == 1)
							{
								pagenum = 3;
							}
							if (menu.pressed() == 2) {
								pagenum = 15;
							}
							if (menu.pressed() == 3)
							{
								pagenum = 2;
							}
						}

					}
				}
				Menuu.clear();
				if (pagenum != 1000)break;
				Menuu.draw(bg);
				menu.draw(Menuu);
				Menuu.display();

			}
		}
		else if (pagenum == 10 || pagenum == 11 || pagenum == 12) {
			sound2.stop();
		}
		if (pagenum == 0) {
			CIPlCT = 0;
			p1(Menuu);
		}
		if (pagenum == 6) {
			CIPlCT = 0;
			p2(Menuu);
		}
		if (pagenum == 10) {
			roundnum = 1;
			Round1(Menuu);
			sound2.stop();
		}
		if (pagenum == 11) {
			roundnum = 2;
			Round2(Menuu);
			sound2.stop();
		}
		if (pagenum == 12) {
			roundnum = 3;
			Round3(Menuu);
			soundRound1.stop();
			sound2.stop();
		}
		if (pagenum == 13) {
			CIPlCT = 0;
			choose1(Menuu);
		}
		if (pagenum == 14) {
			CIPlCT = 0;
			choose2(Menuu);
		}

		if (pagenum == 3)//options
		{
			OptionsWin(Menuu);
		}
		if (pagenum == 15) {
			His(Menuu);
		}
		if (pagenum == 2)//EXIT
		{
			Menuu.close();
		}
		if (p1score + p2score >= 2) {
			offile << player2 + "...VS..." + player1 + "*" << endl;
			offile << p2score << "  :  " << p1score << "*" << endl;
			p1score = 0; p2score = 0;
		}
		if (!Menuu.isOpen())
			break;
	}
	return 0;
}

//*********************************************************************************

void Round1(RenderWindow& window)
{
	Sprite blocks[25]; //map1 blocks
	p1score = 0;
	p2score = 0;
	int kks = 0; // chosing the weapon after 4 powerups.
	block(blocks);
	SoundBuffer buffer;
	buffer.loadFromFile("equip.wav");
	Sound sound;
	sound.setBuffer(buffer);

	SoundBuffer buffer3;
	buffer3.loadFromFile("select.wav");
	Sound sound3;
	sound3.setBuffer(buffer3);


	buffer4.loadFromFile("GGsound.wav");

	sound4.setBuffer(buffer4);
	SoundBuffer buffer5;
	buffer5.loadFromFile("GGsound.wav");
	Sound sound5;
	sound5.setBuffer(buffer5);

	SoundBuffer buffer6;
	buffer6.loadFromFile("Round1Sound.wav");
	Sound sound6;
	sound6.setBuffer(buffer6);
	SoundBuffer buffer7;
	buffer7.loadFromFile("damagesound.wav");
	Sound damagesound;
	damagesound.setBuffer(buffer7);


	bool paused = 0;
	PauseMenu pm(1920, 1080);

	Weapon weapon;
	bool use1 = 1; // for weapon player1 
	bool use2 = 1; // for weapon player2 
	Clock Bullettimer1;
	Clock Bullettimer2;
	CircleShape weaponCircle(20);

	float f = 0;

	Texture speedTex;
	speedTex.loadFromFile("thunder.png");
	Texture DecayTex;
	DecayTex.loadFromFile("decay.png");
	texth.loadFromFile("heart.PNG");

	powers[0].setFillColor(Color::Green);
	powers[0].setTexture(&speedTex);
	powers[0].setScale(1.3, 1.3);
	powers[1].setFillColor(Color::Blue);
	powers[1].setTexture(&DecayTex);
	powers[2].setFillColor(Color::Red);
	powers[2].setTexture(&texth);


	Clock clock;
	Clock clocktimer, clocktimer1, clocktimer2;
	Texture t;
	Texture t2;
	t.loadFromFile("pla1.png");
	player p(t);
	t2.loadFromFile("pla2.png");
	player p2(t2);

	UpdateHeroType(p, p2);

	p2.rect.top = 850;
	p.rect.left = 1849;
	p.rect.top = 850;
	p2.dx = 0.0000001;
	p2.dx += 0.0000001;
	p.lastkeypressed = 2;
	p2.lastkeypressed = 1;


	Player_Powerups PlayerPowerup[2]; // 0->player1_Powerups , 1->player2_Powerup
	PowerUps PowersSprits; // 	

	for (int i = 0; i < 2; i++)
	{
		if (i % 2 == 0)
		{
			PlayerPowerup[i].setSpeed(p.HeroType.Speed);
			PlayerPowerup[i].setHealth(p.HeroType.Health);
		}
		else
		{
			PlayerPowerup[i].setSpeed(p2.HeroType.Speed);
			PlayerPowerup[i].setHealth(p2.HeroType.Health);
		}
	}

	string s, s2, P1score, P2score;

	bool closed = 0;
	Font font;
	font.loadFromFile("RythmOfDeath.ttf");
	Text text;
	text.setFont(font);
	if (player1.size() > 2)
		text.setPosition(1920 - ((player1.size() + 10) * 20), 10);
	else
		text.setPosition(1920 - 190, 10);
	text.setFillColor(Color::Green);
	Text textscore;
	textscore.setFont(font);
	textscore.setPosition(940, 80);
	textscore.setFillColor(Color::White);

	Text text2;
	text2.setFont(font);
	text2.setPosition(80, 10);
	text2.setFillColor(Color::Green);

	text.setCharacterSize(60);
	text2.setCharacterSize(60);
	textscore.setCharacterSize(70);

	
	
	Sprite heart;
	heart.setTexture(texth);
	heart.setScale(0.2, 0.2);
	if (player2.size() > 2)
		heart.setPosition(text2.getPosition().x + (player2.size() + 3) * 20 + 10, text2.getPosition().y + 15); // for player on the left. 
	else
		heart.setPosition(120, text2.getPosition().y + 15);
	Sprite heart2;
	heart2.setTexture(texth);
	heart2.setScale(0.2, 0.2);
	heart2.setPosition(1800, text.getPosition().y + 15); // for the player on the right .

	Texture Enemyphoto;
	Enemyphoto.loadFromFile("ghost.png");


	Texture text5;
	text5.loadFromFile("block5.PNG");
	CircleShape players(20);
	Sprite player;
	Texture text6;
	text6.loadFromFile("wallpaperflare.com_wallpaper (8).JPG");
	Sprite background;
	background.setTexture(text6);

	for (int i = 0; i < 20; i++) {
		blocks[i].setTexture(text5);
	}

	bool qwertty = 0;
	bool qwertty2 = 0;
	for (int i = 0; i < 14; i++)
	{
		powerupint[i].x = blocks[i].getPosition().x + blocks[i].getScale().x * 256 / 2 - 20;
		powerupint[i].y = blocks[i].getPosition().y - 200;
	}
	// enemy
	for (int i = 0; i < 4; i++)
	{
		enemy[i].shape.setTexture(Enemyphoto);
		if (i < 2)
		{
			int y = rand() % 921 + 80;
			enemy[i].shape.setPosition(-600, y);
			enemy[i].speed = rand() % 8 + 8;
			enemy[i].shape.setScale(2.3, 2.3);
			enemy[i].shape.setTextureRect(IntRect(29, 0, -29, 24));
		}
		else
		{
			int y = rand() % 921 + 80;
			enemy[i].shape.setPosition(2620, y);
			enemy[i].speed = rand() % 8 + 8;
			enemy[i].shape.setScale(2.3, 2.3);
			enemy[i].shape.setTextureRect(IntRect(0, 0, 29, 24));
		}
	}

	// For PauseMenu 
	RectangleShape r(Vector2f(800, 800));
	r.setFillColor(Color::Black);
	r.setOrigin(400, 400);
	r.setPosition(1920 / 2, 1080 / 2);
	round1.setPosition(900, 30);
	round1.setScale(0.25, 0.25);
	sound6.play();
	soundRound1.play();
	soundRound1.setLoop(true);
	soundRound1.setVolume(20);
	while (window.isOpen())
	{
		Event event;
		if (paused)
		{
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed()) {
					paused = 0;
					window.close();
				}
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Up)) {
						pm.moveup();
						sound3.play();
						sound3.setVolume(25);
					}
					if (Keyboard::isKeyPressed(Keyboard::Down)) {
						pm.movedown();
						sound3.play();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					paused = 0;
				}
				if (event.key.code == Keyboard::Return) // return=enter
				{
					if (pm.pressed() == 0) {
						//sound.pause();
						paused = 0;
					}
					if (pm.pressed() == 1 && soundRound1.getVolume() <= 100)
					{
						soundRound1.setVolume(soundRound1.getVolume() + 10);
						soundMele.setVolume(soundMele.getVolume() + 10);
						sound4.setVolume(sound4.getVolume() + 10);
						sound5.setVolume(sound5.getVolume() + 10);
						sound3.setVolume(sound3.getVolume() + 10);
						sound.setVolume(sound.getVolume() + 10);
						sound6.setVolume(sound6.getVolume() + 10);
						soundAfterEnter.setVolume(soundAfterEnter.getVolume() + 10);
						weapon.WeaponSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p2.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						damagesound.setVolume(damagesound.getVolume() + 10);
					}
					if (pm.pressed() == 2 && soundRound1.getVolume() >= 0)
					{
						soundRound1.setVolume(soundRound1.getVolume() - 10);
						soundMele.setVolume(soundMele.getVolume() - 10);
						sound4.setVolume(sound4.getVolume() - 10);
						sound5.setVolume(sound5.getVolume() - 10);
						sound3.setVolume(sound3.getVolume() - 10);
						sound.setVolume(sound.getVolume() - 10);
						sound6.setVolume(sound6.getVolume() - 10);
						soundAfterEnter.setVolume(soundAfterEnter.getVolume() - 10);
						weapon.WeaponSound.setVolume(weapon.WeaponSound.getVolume() - 10);
						p.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p2.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						damagesound.setVolume(damagesound.getVolume() - 10);
					}
					if (pm.pressed() == 3) {
						pagenum = 1000;
						return;
					}
				}

			}
		}
		for (int i = 0; i < 14; i++)
		{
			if (p2.sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
			{
				if (i != 7 && i != 12 && i != 10 && i != 9) {
					if (((p2.rect.left >= blocks[i].getPosition().x + 240) || (p2.rect.left >= blocks[i].getPosition().x + 240.5))) {

						p2.rect.left = blocks[i].getPosition().x + 255;
					}
					else if (((p2.rect.left + 30 <= blocks[i].getPosition().x) || (p2.rect.left + 30.5 <= blocks[i].getPosition().x))) {
						p2.rect.left = blocks[i].getPosition().x - 45;
					}
					else {
						p2.dy = 0;
						p2.onground = 1;
						if (p2.rect.top > blocks[i].getPosition().y + 20)
						{
							p2.onground = 0;
						}
						else
						{
							p2.rect.top = blocks[i].getPosition().y - 80;
							p2.onground = 1;
						}
					}
				}
				else {

					if (((p2.rect.left >= blocks[i].getPosition().x + 120) || (p2.rect.left >= blocks[i].getPosition().x + 120.5)) && i != 7) {
						p2.rect.left = blocks[i].getPosition().x + 130;
					}
					else if (((p2.rect.left + 30 <= blocks[i].getPosition().x) || (p2.rect.left + 30.5 <= blocks[i].getPosition().x))) {
						p2.rect.left = blocks[i].getPosition().x - 45;
					}
					else {
						p2.dy = 0;
						p2.onground = 1;
						if (p2.rect.top > blocks[i].getPosition().y + 20)
						{
							p2.onground = 0;
						}
						else
						{
							p2.rect.top = blocks[i].getPosition().y - 80;
							p2.onground = 1;
						}
					}

				}
			}
			if (p.sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
			{
				if (i != 7 && i != 12 && i != 10 && i != 9) {
					if (((p.rect.left >= blocks[i].getPosition().x + 240) || (p.rect.left >= blocks[i].getPosition().x + 240.5))) {
						p.rect.left = blocks[i].getPosition().x + 255;
					}
					else if (((p.rect.left + 30 <= blocks[i].getPosition().x) || (p.rect.left + 30.5 <= blocks[i].getPosition().x))) {
						p.rect.left = blocks[i].getPosition().x - 45;

					}
					else {
						p.dy = 0;
						p.onground = 1;
						if (p.rect.top > blocks[i].getPosition().y + 20)
						{
							p.onground = 0;
						}
						else
						{
							p.rect.top = blocks[i].getPosition().y - 80;
							p.onground = 1;
						}
					}
				}
				else {
					if (((p.rect.left >= blocks[i].getPosition().x + 120) || (p.rect.left >= blocks[i].getPosition().x + 120.5)) && i != 7) {
						p.rect.left = blocks[i].getPosition().x + 130;
					}
					else if (((p.rect.left + 30 <= blocks[i].getPosition().x) || (p.rect.left + 30.5 <= blocks[i].getPosition().x))) {
						p.rect.left = blocks[i].getPosition().x - 45;
					}
					else {
						p.dy = 0;
						p.onground = 1;
						if (p.rect.top > blocks[i].getPosition().y + 20)
						{
							p.onground = 0;
						}
						else
						{
							p.rect.top = blocks[i].getPosition().y - 80;
							p.onground = 1;
						}
					}

				}

			}

		}


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mousePosition = Mouse::getPosition(window);
			cout << mousePosition.x << " " << mousePosition.y << endl;
		}

		if (!paused) {
			ChooseWeapon = rand() % 3 + 1;
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			time *= 2000;
			chose = rand() % 3;
			h = rand() % 14;

			for (int i = 0; i < 3; i++)
			{
				powers[i].setPosition(powerupint[h]);
				powers[i].setRadius(20);
			}

			while (window.pollEvent(event))
			{

				if (event.type == Event::Closed) {
					window.close();
				}
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						paused = 1;
					}
					if (Keyboard::isKeyPressed(Keyboard::G)) {
						PlayerPowerup[0].setHealth(0);
					}
					if (Keyboard::isKeyPressed(Keyboard::H)) {
						PlayerPowerup[1].setHealth(0);
					}
				}

			}


			if (p.bullet.Magazin > 0) {
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(126, 49, 42, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(126 + 42, 49, -42, 49));
				}
			}
			if (p2.bullet.Magazin > 0) {
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(126, 49, 42, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(126 + 42, 49, -42, 49));
				}

			}
			if (p.bullet.Magazin == 0) {
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(181, 0, 35, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(181 + 35, 0, -35, 49));
				}
			}
			if (p2.bullet.Magazin == 0) {
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(181, 0, 35, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(181 + 35, 0, -35, 49));
				}
			}


			if (p.sprite.getGlobalBounds().intersects(p2.sprite.getGlobalBounds()))
			{
				p.dy = 0;
				p.onground = 1;
				if (p.rect.top <= p2.rect.top - 50.5 || p.rect.top <= p2.rect.top - 50) {

					p.rect.top = p2.rect.top - 80;
					p.onground = 1;
				}
				else {
					p.onground = 0;
				}
			}
			if (p2.sprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds()))
			{
				p2.dy = 0;
				p2.onground = 1;
				if (p2.rect.top <= p.rect.top - 50.5 || p2.rect.top <= p.rect.top - 50) {

					p2.rect.top = p.rect.top - 80;
					p2.onground = 1;
				}
				else {
					p2.onground = 0;
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::LAlt)) {
					p2.dx = 0;
					p2.sprite.setTextureRect(IntRect(0, 49, 48, 49));

				}
				else {
					p2.dx = 0.1 * PlayerPowerup[1].getSpeed();
					p2.lastkeypressed = 1;
				}
				if ((p2.rect.left >= p.rect.left - 70 || p2.rect.left >= p.rect.left - 70.5) &&
					(p2.rect.left <= p.rect.left - 50 || p2.rect.left <= p.rect.left - 50.5)) {
					if ((p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50)
						&& (p2.rect.top <= p.rect.top + 49.5 || p2.rect.top <= p.rect.top + 50))
					{
						cout << "aa" << endl;
						p2.rect.left = p.rect.left - 72;
					}
				}


			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::RAlt)) {
					p.dx = 0;
					p.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else {
					p.dx = 0.1 * PlayerPowerup[0].getSpeed();
					p.lastkeypressed = 1;
				}
				if ((p.rect.left >= p2.rect.left - 70 || p.rect.left >= p2.rect.left - 70.5) &&
					(p.rect.left <= p2.rect.left - 50 || p.rect.left <= p2.rect.left - 50.5)) {
					if ((p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50)
						&& (p.rect.top <= p2.rect.top + 49.5 || p.rect.top <= p2.rect.top + 50))
					{
						p.rect.left = p2.rect.left - 72;
					}
				}


			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::RAlt)) {
					p.dx = 0;
					p.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}
				else {
					p.dx = -0.1 * PlayerPowerup[0].getSpeed();
					p.lastkeypressed = 2;
				}
				if ((p.rect.left <= p2.rect.left + 70 || p.rect.left <= p2.rect.left + 70.5) &&
					(p.rect.left >= p2.rect.left + 50 || p.rect.left >= p2.rect.left + 50.5)) {
					if ((p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50)
						&& (p.rect.top <= p2.rect.top + 49.5 || p.rect.top <= p2.rect.top + 50))
					{

						p.rect.left = p2.rect.left + 72;
					}
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Up) && qwertty == 0) {
				qwertty = 1;
				if (p.onground) {
					p.dy = -0.4;
					p.onground = 0;
				}
			}

			if (event.type == Event::KeyReleased || p.onground) {
				qwertty = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {

				if (!p.onground) {
					p.dy = 0.4;
					p.onground = 1;
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(49, 144, 42, 48));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(49 + 42, 144, -42, 48));
				}
			}


			if (Keyboard::isKeyPressed(Keyboard::Key::A)) {

				if (Keyboard::isKeyPressed(Keyboard::Key::LAlt)) {
					p2.dx = 0;
					p2.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));

				}
				else {
					p2.dx = -0.1 * PlayerPowerup[1].getSpeed();
					p2.lastkeypressed = 2;
				}
				if ((p2.rect.left <= p.rect.left + 70 || p2.rect.left <= p.rect.left + 70.5) &&
					(p2.rect.left >= p.rect.left + 50 || p2.rect.left >= p.rect.left + 50.5)) {
					if ((p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50)
						&& (p2.rect.top <= p.rect.top + 49.5 || p2.rect.top <= p.rect.top + 50))
					{

						p2.rect.left = p.rect.left + 72;
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::W) && qwertty2 == 0) {
				qwertty2 = 1;
				if (p2.onground) {
					p2.dy = -0.4;
					p2.onground = 0;
				}
			}
			if (event.type == Event::KeyReleased || p2.onground) {
				qwertty2 = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
				if (!p2.onground) {
					p2.dy = 0.4;
					p2.onground = 1;
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(48, 144, 42, 48));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(48 + 42, 144, -42, 48));
				}
			}



			// enemy 
			for (int i = 0; i < 4; i++)
			{
				enemy[i].x += 0.1;
				if (i < 2)
				{
					enemy[i].shape.setTextureRect(IntRect(29 * int(enemy[i].x) + 29, 0, -29, 24));
					if (enemy[i].shape.getPosition().x > 1920)
					{
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
						enemy[i].speed = rand() % 8 + 8;
					}
					enemy[i].shape.move(enemy[i].speed, 0);
					if (enemy[i].x > 3)
						enemy[i].x = 0;
					if (p.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
					}

					if (p2.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
					}
				}
				else
				{
					enemy[i].shape.setTextureRect(IntRect(29 * int(enemy[i].x), 0, 29, 24));
					if (enemy[i].shape.getPosition().x < -80)
					{
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
						enemy[i].speed = rand() % 8 + 8;
					}
					enemy[i].shape.move(-enemy[i].speed, 0);
					if (enemy[i].x > 3)
						enemy[i].x = 0;
					if (p.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
					}
					if (p2.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
					}
				}
			}

			/*p.onground = 0;
			p2.onground = 0;*/ // dont know why ??! // 2na bs l2et ele fo2eha kda f3mld da. 

			int timer = clocktimer.getElapsedTime().asSeconds();
			if (timer % 5 == 0 && !Add1 && timer % 9 != 0 /*need to change*/)
			{
				if (kks < 2)
				{
					PowersSprits.add();
				}
				Add1 = 1;
				if (kks >= 2)
				{
					bl2 = 1;
					MakeWeapon(ChooseWeapon, weapon);
					kks = 0;
				}
				kks++;

			}
			else if (timer % 9 == 0 && timer != 0 /*need to change*/)
			{

				PowersSprits.delet();
				Add1 = 0;
				clocktimer.restart();
			}
			if (weapon.WeaponType != 0)
				Gravity_Weapon(weapon, blocks, roundnum);

			if (p.sprite.getGlobalBounds().intersects(weapon.GunPhoto.getGlobalBounds()) && p.bullet.Magazin <= 0)
			{
				// 1-> pistol , 2-> rifle , 3-> goldengun

				p.bullet.BulletSprite.setTexture(weapon.GeneralBulletSprite);
				weapon.GunPhoto.setPosition(-1000, -1000);
				p.bullet.BulletSprite.setScale(2, 2);
				p.bullet.Speed = weapon.BulletSpeed;
				p.bullet.Damage = weapon.Damage;
				p.bullet.Magazin = weapon.Magazin;
				p.bullet.type = 1;
				p.bullet.CoolDownuse = weapon.Cooldown;
				p.bullet.BulletSound = weapon.WeaponSound;
				if (true) {
					sound.play();
				}
			}

			if (p2.sprite.getGlobalBounds().intersects(weapon.GunPhoto.getGlobalBounds()) && p2.bullet.Magazin <= 0)
			{

				// 1-> pistol , 2-> rifle , 3-> goldengun
				p2.bullet.BulletSprite.setTexture(weapon.GeneralBulletSprite);
				weapon.GunPhoto.setPosition(-1000, -1000);
				p2.bullet.BulletSprite.setScale(2, 2);
				p2.bullet.Speed = weapon.BulletSpeed;
				p2.bullet.Damage = weapon.Damage;
				p2.bullet.Magazin = weapon.Magazin;
				p2.bullet.type = 1;
				p2.bullet.CoolDownuse = weapon.Cooldown;
				p2.bullet.BulletSound = weapon.WeaponSound;
				sound.play();
			}



			if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.Magazin <= 0 && p2.bullet.meletimer >= 2)
			{
				if (p2.lastkeypressed == 1) {
					if ((p2.rect.left >= p.rect.left - 75 || p2.rect.left >= p.rect.left - 75.5) &&
						(p2.rect.left <= p.rect.left - 60 || p2.rect.left <= p.rect.left - 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				else if (p2.lastkeypressed == 2) {
					if ((p2.rect.left <= p.rect.left + 75 || p2.rect.left <= p.rect.left + 75.5) &&
						(p2.rect.left >= p.rect.left + 60 || p2.rect.left >= p.rect.left + 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				p2.bullet.meletimer = 0;
				//P2MeleClock.restart();
			}


			if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.Magazin <= 0 && p.bullet.meletimer >= 2)
			{
				if (p.lastkeypressed == 1) {
					if ((p.rect.left >= p2.rect.left - 75 || p.rect.left >= p2.rect.left - 75.5) &&
						(p.rect.left <= p2.rect.left - 60 || p.rect.left <= p2.rect.left - 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				else if (p.lastkeypressed == 2) {
					if ((p.rect.left <= p2.rect.left + 75 || p.rect.left <= p2.rect.left + 75.5) &&
						(p.rect.left >= p2.rect.left + 60 || p.rect.left >= p2.rect.left + 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				p.bullet.meletimer = 0;
				//P1MeleClock.restart();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.CoolDownBool && p.bullet.Magazin >= 1)
			{
				p.bullet.BulletSound.play();
				playergun1 += 0.5;
				if (playergun1 > 2) {
					playergun1 = 0;
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(42 * int(playergun1), 49, 42, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(42 * int(playergun1) + 42, 49, -42, 49));
				}
				p.V_Bullets.push_back(p.bullet);
				p.V_Bullets[p.V_Bullets.size() - 1].BulletSprite.setPosition(p.sprite.getPosition().x, p.sprite.getPosition().y);
				p.V_Bullets[p.V_Bullets.size() - 1].moveTo = p.lastkeypressed;
				p.bullet.Magazin--;
				p.bullet.CoolDownBool = 0;

			}

			else if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.Magazin <= 0)
			{

				soundMele.play();
				if (p.lastkeypressed == 1) {
					if ((p.rect.left >= p2.rect.left - 75 || p.rect.left >= p2.rect.left - 75.5) &&
						(p.rect.left <= p2.rect.left - 60 || p.rect.left <= p2.rect.left - 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::Right))
							p2.rect.left = p.rect.left + 105;

						}
					}
				}
				else if (p.lastkeypressed == 2) {
					if ((p.rect.left <= p2.rect.left + 75 || p.rect.left <= p2.rect.left + 75.5) &&
						(p.rect.left >= p2.rect.left + 60 || p.rect.left >= p2.rect.left + 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::Left))
							p2.rect.left = p.rect.left - 105;

						}
					}
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}

			}


			if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.CoolDownBool && p2.bullet.Magazin >= 1)
			{
				p2.bullet.BulletSound.play();
				playergun2 += 0.5;
				if (playergun2 > 2) {
					playergun2 = 0;
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(42 * int(playergun2), 49, 42, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(42 * int(playergun2) + 42, 49, -42, 49));
				}
				p2.V_Bullets.push_back(p2.bullet);
				p2.V_Bullets[p2.V_Bullets.size() - 1].BulletSprite.setPosition(p2.sprite.getPosition().x, p2.sprite.getPosition().y);
				p2.V_Bullets[p2.V_Bullets.size() - 1].moveTo = p2.lastkeypressed;
				p2.bullet.Magazin--;
				p2.bullet.CoolDownBool = 0;

			}

			else if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.Magazin <= 0)
			{
				soundMele.play();
				if (p2.lastkeypressed == 1) {
					if ((p2.rect.left >= p.rect.left - 75 || p2.rect.left >= p.rect.left - 75.5) &&
						(p2.rect.left <= p.rect.left - 60 || p2.rect.left <= p.rect.left - 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::D))
							p.rect.left = p2.rect.left + 105;
						}

					}
				}
				else if (p2.lastkeypressed == 2) {
					if ((p2.rect.left <= p.rect.left + 75 || p2.rect.left <= p.rect.left + 75.5) &&
						(p2.rect.left >= p.rect.left + 60 || p2.rect.left >= p.rect.left + 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::A))
							p.rect.left = p2.rect.left - 105;

						}

					}
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}
			}




			if (P1MeleClock.getElapsedTime().asSeconds() >= 1)
			{
				p.bullet.meletimer++;
				P1MeleClock.restart();
			}
			if (P2MeleClock.getElapsedTime().asSeconds() >= 1)
			{
				p2.bullet.meletimer++;
				P2MeleClock.restart();
			}


			for (int i = 0; i < p2.V_Bullets.size(); i++)
			{
				bool cheak = 0; // for earasing the bullets.
				if (p2.V_Bullets[i].moveTo == 2)
					p2.V_Bullets[i].BulletSprite.move(-7 * p2.V_Bullets[i].Speed, 0);
				if (p2.V_Bullets[i].moveTo == 1)
					p2.V_Bullets[i].BulletSprite.move(7 * p2.V_Bullets[i].Speed, 0);
				for (int k = 0; k < 4; k++)
				{
					if (k < 2)
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p2.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(-100, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
					else
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p2.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(2020, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
				}
				if (p2.V_Bullets[i].BulletSprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds()))
				{
					PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - p2.V_Bullets[i].Damage);
					damagesound.play();
					cheak = 1;
				}
				if (cheak)
					p2.V_Bullets.erase(p2.V_Bullets.begin() + i);
			}

			for (int i = 0; i < p.V_Bullets.size(); i++)
			{
				bool cheak = 0; // for earasing the bullets.
				if (p.V_Bullets[i].moveTo == 2)
					p.V_Bullets[i].BulletSprite.move(-7 * p.V_Bullets[i].Speed, 0);
				if (p.V_Bullets[i].moveTo == 1)
					p.V_Bullets[i].BulletSprite.move(7 * p.V_Bullets[i].Speed, 0);
				for (int k = 0; k < 4; k++)
				{
					if (k < 2)
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(-100, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
					else
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(2020, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
				}
				if (p.V_Bullets[i].BulletSprite.getGlobalBounds().intersects(p2.sprite.getGlobalBounds()))
				{
					PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - p.V_Bullets[i].Damage);
					damagesound.play();
					cheak = 1;
				}
				if (cheak)
					p.V_Bullets.erase(p.V_Bullets.begin() + i);
			}

			if (!p.bullet.CoolDownBool && use1)
			{
				Bullettimer1.restart();
				use1 = 0;
			}
			else
			{
				if (p.bullet.CoolDownuse <= (int)Bullettimer1.getElapsedTime().asSeconds())
				{
					p.bullet.CoolDownBool = 1;
					use1 = 1;
				}
			}

			if (!p2.bullet.CoolDownBool && use2)
			{
				Bullettimer2.restart();
				use2 = 0;
			}
			else
			{
				if (p2.bullet.CoolDownuse <= (int)Bullettimer2.getElapsedTime().asSeconds())
				{
					p2.bullet.CoolDownBool = 1;
					use2 = 1;
				}
			}
			for (int i = 0; i < V.size(); i++)
			{
				Gravity_Powerups(V[i], blocks, roundnum);
				if (p.sprite.getGlobalBounds().intersects(V[i].getGlobalBounds()))
				{
					//chose 0->speed 2->health 1->scale
					if (V[i].getFillColor() == Color::Green)
					{
						PlayerPowerup[0].setSpeed(p.HeroType.Speed + 0.5);
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Red)
					{
						if (PlayerPowerup[0].getHealth() < 10)
						{
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() + 1);
						}
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Blue)
					{
						PlayerPowerup[1].setSpeed(PlayerPowerup[1].getSpeed() - 3);
						PowersSprits.delet(i);
					}
					timer1 = 0;
				}
				else if (p2.sprite.getGlobalBounds().intersects(V[i].getGlobalBounds()))
				{
					//chose 0->speed 2->health 1->scale
					if (V[i].getFillColor() == Color::Green)
					{
						PlayerPowerup[1].setSpeed(3);
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Red)
					{

						if (PlayerPowerup[1].getHealth() < 10)
						{
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() + 1);
						}
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Blue)
					{
						PlayerPowerup[0].setSpeed(PlayerPowerup[0].getSpeed() - 3);
						PowersSprits.delet(i);
					}
					timer2 = 0;
				}
			}
			if (!timer1)
			{
				clocktimer1.restart();
				timer1 = 1;
			}
			else if (!timer2)
			{
				clocktimer2.restart();
				timer2 = 1;
			}
			timerpowerup2 = (int)clocktimer2.getElapsedTime().asSeconds();
			timerpowerup1 = (int)clocktimer1.getElapsedTime().asSeconds();

			if (timerpowerup1 == 5)
			{
				PlayerPowerup[0].setSpeed(p.HeroType.Speed);
				PlayerPowerup[1].setSpeed(p2.HeroType.Speed);
			}
			if (timerpowerup2 == 5)
			{
				PlayerPowerup[1].setSpeed(p2.HeroType.Speed);
				PlayerPowerup[0].setSpeed(p.HeroType.Speed);
			}
			p.update(time);
			p2.update(time);

			if (PlayerPowerup[0].getHealth() <= 0)
			{
				pagenum = 11;//Round2
				p2score++;
				return;
			}
			if (PlayerPowerup[1].getHealth() <= 0)
			{
				pagenum = 11;//Round2
				p1score++;
				return;
			}
		}

		if (true)
		{
			window.clear();
			window.draw(background);
			for (int i = 0; i < p.V_Bullets.size(); i++)
			{
				window.draw(p.V_Bullets[i].BulletSprite);
			}
			for (int i = 0; i < p2.V_Bullets.size(); i++)
			{
				window.draw(p2.V_Bullets[i].BulletSprite);
			}
			for (int i = 0; i < 14; i++) {
				window.draw(blocks[i]);
			}
			stringstream sc, ss;
			sc << PlayerPowerup[0].getHealth(); //int to string
			sc >> s;
			ss << PlayerPowerup[1].getHealth(); //int to string
			ss >> s2;
			stringstream po, po2;
			po2 << p1score; //int to string
			po2 >> P1score;
			po << p2score; //int to string
			po >> P2score;
			textscore.setString(P2score + ":" + P1score);
			text.setString(player1 + ':' + s);//setting the string to player 1 
			text2.setString(player2 + ':' + s2);//setting the string to player 2
			window.draw(heart);
			window.draw(heart2);
			window.draw(text2);
			window.draw(text);
			window.draw(textscore);
			window.draw(weapon.GunPhoto);
			for (int i = 0; i < V.size(); i++)
				window.draw(V[i]);
			window.draw(p.sprite);
			window.draw(p2.sprite);
			for (int i = 0; i < 4; i++)
				window.draw(enemy[i].shape);
			if (paused) {
				window.draw(r);
				window.draw(PauseSprite);
				pm.draw(window);
			}
			window.draw(round1);
			window.display();
		}

	}
}
void Round2(RenderWindow& window) {

	Sprite blocks[25]; //map1 blocks
	int kks = 0; // chosing the weapon after 4 powerups.

	blockround2(blocks);
	int m3 = 1;
	int minb3, maxb3;

	int m0 = 1;
	int minb0, maxb0;

	int m9 = 1;
	int minb9, maxb9;

	int m8 = 1;
	int minb8, maxb8;

	int m2 = 1;
	int minb2, maxb2;

	int m1 = 1;
	int minb1, maxb1;

	int m11 = 1;
	int minb11, maxb11;

	int m4 = 1;
	int minb4, maxb4;

	Texture BGTexture;
	Sprite BGSprite;
	BGTexture.loadFromFile("bg3.png");
	BGSprite.setTexture(BGTexture);

	SoundBuffer buffer;
	buffer.loadFromFile("equip.wav");
	Sound sound;
	sound.setBuffer(buffer);
	SoundBuffer buffer2;
	buffer2.loadFromFile("game.wav");
	Sound sound2;
	sound2.setBuffer(buffer2);
	SoundBuffer buffer3;
	buffer3.loadFromFile("select.wav");
	Sound sound3;
	sound3.setBuffer(buffer3);


	buffer4.loadFromFile("GGsound.wav");

	sound4.setBuffer(buffer4);
	SoundBuffer buffer5;
	buffer5.loadFromFile("GGsound.wav");
	Sound sound5;
	sound5.setBuffer(buffer5);

	SoundBuffer buffer6;
	buffer6.loadFromFile("Round2Sound.wav");
	Sound sound6;
	sound6.setBuffer(buffer6);
	sound6.play();
	SoundBuffer buffer7;
	buffer7.loadFromFile("damagesound.wav");
	Sound damagesound;
	damagesound.setBuffer(buffer7);


	bool paused = 0;
	PauseMenu pm(1920, 1080);

	Weapon weapon;
	bool use1 = 1; // for weapon player1 
	bool use2 = 1; // for weapon player2 
	Clock Bullettimer1;
	Clock Bullettimer2;
	CircleShape weaponCircle(20);

	float f = 0;
	
	Texture speedTex;
	speedTex.loadFromFile("thunder.png");
	Texture DecayTex;
	DecayTex.loadFromFile("decay.png");
	texth.loadFromFile("heart.PNG");

	powers[0].setFillColor(Color::Green);
	powers[0].setTexture(&speedTex);
	powers[0].setScale(1.3, 1.3);
	powers[1].setFillColor(Color::Blue);
	powers[1].setTexture(&DecayTex);
	powers[2].setFillColor(Color::Red);
	powers[2].setTexture(&texth);


	Clock clock;
	Clock clocktimer, clocktimer1, clocktimer2;
	Texture t;
	Texture t2;
	t.loadFromFile("pla1.png");
	player p(t);
	t2.loadFromFile("pla2.png");
	player p2(t2);

	UpdateHeroType(p, p2);

	p.rect.left = 1541;
	p.rect.top = 300;
	p2.rect.top = 300;
	p2.rect.left = 366;
	p2.dx = 0.0000001;
	p2.dx += 0.0000001;
	p.lastkeypressed = 2;
	p2.lastkeypressed = 1;

	p.update(0);
	p2.update(0);

	Player_Powerups PlayerPowerup[2]; // 0->player1_Powerups , 1->player2_Powerup
	PowerUps PowersSprits; // 	

	for (int i = 0; i < 2; i++)
	{
		if (i % 2 == 0)
		{
			PlayerPowerup[i].setSpeed(p.HeroType.Speed);
			PlayerPowerup[i].setHealth(p.HeroType.Health);
		}
		else
		{
			PlayerPowerup[i].setSpeed(p2.HeroType.Speed);
			PlayerPowerup[i].setHealth(p2.HeroType.Health);
		}
	}

	string s, s2, P1score, P2score;

	bool closed = 0;
	Font font;
	font.loadFromFile("RythmOfDeath.ttf");
	Text text;
	text.setFont(font);
	if (player1.size() > 2)
		text.setPosition(1920 - ((player1.size() + 10) * 20), 10);
	else
		text.setPosition(1920 - 190, 10);
	text.setFillColor(Color::Green);
	Text textscore;
	textscore.setFont(font);
	textscore.setPosition(940, 80);
	textscore.setFillColor(Color::White);

	Text text2;
	text2.setFont(font);
	text2.setPosition(80, 10);
	text2.setFillColor(Color::Green);

	text.setCharacterSize(60);
	text2.setCharacterSize(60);
	textscore.setCharacterSize(70);

	texth.loadFromFile("heart.PNG");
	Sprite heart;
	heart.setTexture(texth);
	heart.setScale(0.2, 0.2);
	if (player2.size() > 2)
		heart.setPosition(text2.getPosition().x + (player2.size() + 3) * 20 + 10, text2.getPosition().y + 15); // for player on the left. 
	else
		heart.setPosition(120, text2.getPosition().y + 15);
	Sprite heart2;
	heart2.setTexture(texth);
	heart2.setScale(0.2, 0.2);
	heart2.setPosition(1800, text.getPosition().y + 15); // for the player on the right .


	Texture Enemyphoto;
	Enemyphoto.loadFromFile("ghost.png");


	Texture text5;
	text5.loadFromFile("blockk2.PNG");

	Texture ttf;
	ttf.loadFromFile("underground2.PNG");

	CircleShape players(20);
	Sprite player;
	Texture text6;
	text6.loadFromFile("scorched_earth-wallpaper-1920x1080.JPG");
	Sprite background;
	background.setTexture(text6);

	for (int i = 0; i < 20; i++) {
		if (i == 7)
			blocks[i].setTexture(ttf);
		else
			blocks[i].setTexture(text5);
	}

	bool qwertty = 0;
	bool qwertty2 = 0;
	for (int i = 0; i < 16; i++)
	{
		powerupint[i].x = blocks[i].getPosition().x + blocks[i].getScale().x * 256 / 2 - 20;
		powerupint[i].y = blocks[i].getPosition().y - 200;
	}
	// enemy
	for (int i = 0; i < 5; i++)
	{
		enemy[i].shape.setTexture(Enemyphoto);
		if (i < 3)
		{
			int y = rand() % 921 + 80;
			enemy[i].shape.setPosition(-600, y);
			enemy[i].speed = rand() % 8 + 8;
			enemy[i].shape.setScale(2.3, 2.3);
			enemy[i].shape.setTextureRect(IntRect(29, 0, -29, 24));
		}
		else
		{
			int y = rand() % 921 + 80;
			enemy[i].shape.setPosition(2620, y);
			enemy[i].speed = rand() % 8 + 8;
			enemy[i].shape.setScale(2.3, 2.3);
			enemy[i].shape.setTextureRect(IntRect(0, 0, 29, 24));
		}
	}

	// For PauseMenu 
	RectangleShape r(Vector2f(800, 800));
	r.setFillColor(Color::Black);
	r.setOrigin(400, 400);
	r.setPosition(1920 / 2, 1080 / 2);

	round2.setPosition(900, 30);
	round2.setScale(0.25, 0.25);
	soundRound1.setLoop(true);
	soundRound1.setVolume(20);
	while (window.isOpen())
	{

		Event event;
		if (paused)
		{
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed()) {
					paused = 0;
					window.close();
				}
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Up)) {
						pm.moveup();
						sound3.play();
						sound3.setVolume(25);
					}
					if (Keyboard::isKeyPressed(Keyboard::Down)) {
						pm.movedown();
						sound3.play();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					paused = 0;
				}
				if (event.key.code == Keyboard::Return) // return=enter
				{
					if (pm.pressed() == 0) {
						//sound.pause();
						paused = 0;
					}
					if (pm.pressed() == 1 && soundRound1.getVolume() <= 100)
					{
						soundRound1.setVolume(soundRound1.getVolume() + 10);
						soundMele.setVolume(soundMele.getVolume() + 10);
						sound4.setVolume(sound4.getVolume() + 10);
						sound5.setVolume(sound5.getVolume() + 10);
						sound3.setVolume(sound3.getVolume() + 10);
						sound.setVolume(sound.getVolume() + 10);
						sound6.setVolume(sound6.getVolume() + 10);
						soundAfterEnter.setVolume(soundAfterEnter.getVolume() + 10);
						weapon.WeaponSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p2.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						damagesound.setVolume(damagesound.getVolume() + 10);
					}
					if (pm.pressed() == 2 && soundRound1.getVolume() >= 0)
					{
						soundRound1.setVolume(soundRound1.getVolume() - 10);
						soundMele.setVolume(soundMele.getVolume() - 10);
						sound4.setVolume(sound4.getVolume() - 10);
						sound5.setVolume(sound5.getVolume() - 10);
						sound3.setVolume(sound3.getVolume() - 10);
						sound.setVolume(sound.getVolume() - 10);
						sound6.setVolume(sound6.getVolume() - 10);
						soundAfterEnter.setVolume(soundAfterEnter.getVolume() - 10);
						weapon.WeaponSound.setVolume(weapon.WeaponSound.getVolume() - 10);
						p.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p2.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						damagesound.setVolume(damagesound.getVolume() - 10);
					}
					if (pm.pressed() == 3) {
						pagenum = 1000;
						return;
					}
				}

			}
		}

		for (int i = 0; i < 16; i++)
		{
			if (p2.sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
			{
				if (i != 7 && (i == 0 || i == 3 || i == 4 || i == 8 || i == 11)) {
					if (((p2.rect.left >= blocks[i].getPosition().x + 240) || (p2.rect.left >= blocks[i].getPosition().x + 240.5))) {

						p2.rect.left = blocks[i].getPosition().x + 255;
					}
					else if (((p2.rect.left + 30 <= blocks[i].getPosition().x) || (p2.rect.left + 30.5 <= blocks[i].getPosition().x))) {
						p2.rect.left = blocks[i].getPosition().x - 45;
					}
					else {
						p2.dy = 0;
						p2.onground = 1;
						if (p2.rect.top > blocks[i].getPosition().y + 20)
						{
							p2.onground = 0;
						}
						else
						{
							p2.rect.top = blocks[i].getPosition().y - 80;
							p2.onground = 1;
						}
					}
				}
				else {

					if (((p2.rect.left >= blocks[i].getPosition().x + 120) || (p2.rect.left >= blocks[i].getPosition().x + 120.5)) && i != 7) {
						p2.rect.left = blocks[i].getPosition().x + 130;
					}
					else if (((p2.rect.left + 30 <= blocks[i].getPosition().x) || (p2.rect.left + 30.5 <= blocks[i].getPosition().x)) && i != 7) {
						p2.rect.left = blocks[i].getPosition().x - 45;
					}
					else {
						p2.dy = 0;
						p2.onground = 1;
						if (p2.rect.top > blocks[i].getPosition().y + 20)
						{
							p2.onground = 0;
						}
						else
						{
							p2.rect.top = blocks[i].getPosition().y - 80;
							p2.onground = 1;
						}
					}

				}
			}
			if (p.sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
			{
				if (i != 7 && (i == 0 || i == 3 || i == 4 || i == 8 || i == 11)) {
					if (((p.rect.left >= blocks[i].getPosition().x + 240) || (p.rect.left >= blocks[i].getPosition().x + 240.5))) {
						p.rect.left = blocks[i].getPosition().x + 255;
					}
					else if (((p.rect.left + 30 <= blocks[i].getPosition().x) || (p.rect.left + 30.5 <= blocks[i].getPosition().x))) {
						p.rect.left = blocks[i].getPosition().x - 45;

					}
					else {
						p.dy = 0;
						p.onground = 1;
						if (p.rect.top > blocks[i].getPosition().y + 20)
						{
							p.onground = 0;
						}
						else
						{
							p.rect.top = blocks[i].getPosition().y - 80;
							p.onground = 1;
						}
					}
				}
				else {
					if (((p.rect.left >= blocks[i].getPosition().x + 120) || (p.rect.left >= blocks[i].getPosition().x + 120.5)) && i != 7) {
						p.rect.left = blocks[i].getPosition().x + 130;
					}
					else if (((p.rect.left + 30 <= blocks[i].getPosition().x) || (p.rect.left + 30.5 <= blocks[i].getPosition().x)) && i != 7) {
						p.rect.left = blocks[i].getPosition().x - 45;
					}
					else {
						p.dy = 0;
						p.onground = 1;
						if (p.rect.top > blocks[i].getPosition().y + 20)
						{
							p.onground = 0;
						}
						else
						{
							p.rect.top = blocks[i].getPosition().y - 80;
							p.onground = 1;
						}
					}

				}

			}

		}


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mousePosition = Mouse::getPosition(window);
			cout << mousePosition.x << " " << mousePosition.y << endl;
		}

		if (!paused) {
			ChooseWeapon = rand() % 3 + 1;
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			time *= 2000;
			chose = rand() % 3;
			h = rand() % 16;

			for (int i = 0; i < 3; i++)
			{
				powers[i].setPosition(powerupint[h]);
				powers[i].setRadius(20);
			}

			while (window.pollEvent(event))
			{

				if (event.type == Event::Closed) {
					window.close();
				}
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						paused = 1;
					}
					if (Keyboard::isKeyPressed(Keyboard::G)) {
						PlayerPowerup[0].setHealth(0);
					}
					if (Keyboard::isKeyPressed(Keyboard::H)) {
						PlayerPowerup[1].setHealth(0);
					}
				}

			}

			minb3 = 240;
			maxb3 = 500;
			if (blocks[3].getPosition().y >= maxb3) {

				m3 = 0;
			}
			if (blocks[3].getPosition().y <= minb3) {
				m3 = 1;
			}
			if (m3) {
				blocks[3].move(0, 1.5);
			}
			if (!m3) {
				blocks[3].move(0, -1.5);
			}

			minb0 = 240;
			maxb0 = 500;
			if (blocks[0].getPosition().y >= maxb0) {

				m0 = 0;
			}
			if (blocks[0].getPosition().y <= minb0) {
				m0 = 1;
			}
			if (m0) {
				blocks[0].move(0, 1.5);
			}
			if (!m0) {
				blocks[0].move(0, -1.5);
			}

			minb11 = 650;
			maxb11 = 910;
			if (blocks[11].getPosition().y >= maxb11) {

				m11 = 0;
			}
			if (blocks[11].getPosition().y <= minb11) {
				m11 = 1;
			}
			if (m11) {
				blocks[11].move(0, 1.5);
			}
			if (!m11) {
				blocks[11].move(0, -1.5);
			}

			minb4 = 650;
			maxb4 = 910;
			if (blocks[4].getPosition().y >= maxb4) {

				m4 = 0;
			}
			if (blocks[4].getPosition().y <= minb4) {
				m4 = 1;
			}
			if (m4) {
				blocks[4].move(0, 1.5);
			}
			if (!m4) {
				blocks[4].move(0, -1.5);
			}


			maxb8 = 200;
			minb8 = 910;
			if (blocks[8].getPosition().y <= maxb8) {

				m8 = 0;
			}
			if (blocks[8].getPosition().y >= minb8) {
				m8 = 1;
			}
			if (m8) {
				blocks[8].move(0, -3);
			}
			if (!m8) {
				blocks[8].move(0, 3);
			}

			minb2 = 800;
			maxb2 = 400;
			if (blocks[2].getPosition().y <= maxb2) {

				m2 = 0;
			}
			if (blocks[2].getPosition().y >= minb2) {
				m2 = 1;
			}
			if (m2) {
				blocks[2].move(0, -2.5);
			}
			if (!m2) {
				blocks[2].move(0, 2.5);
			}

			minb1 = 800;
			maxb1 = 400;
			if (blocks[1].getPosition().y <= maxb1) {

				m1 = 0;
			}
			if (blocks[1].getPosition().y >= minb1) {
				m1 = 1;
			}
			if (m1) {
				blocks[1].move(0, -2.5);
			}
			if (!m1) {
				blocks[1].move(0, 2.5);
			}

			if (p.bullet.Magazin > 0) {
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(126, 49, 42, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(126 + 42, 49, -42, 49));
				}
			}
			if (p2.bullet.Magazin > 0) {
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(126, 49, 42, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(126 + 42, 49, -42, 49));
				}

			}
			if (p.bullet.Magazin == 0) {
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(181, 0, 35, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(181 + 35, 0, -35, 49));
				}
			}
			if (p2.bullet.Magazin == 0) {
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(181, 0, 35, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(181 + 35, 0, -35, 49));
				}
			}



			if (p.sprite.getGlobalBounds().intersects(p2.sprite.getGlobalBounds()))
			{
				p.dy = 0;
				p.onground = 1;
				if (p.rect.top <= p2.rect.top - 50.5 || p.rect.top <= p2.rect.top - 50) {

					p.rect.top = p2.rect.top - 80;
					p.onground = 1;
				}
				else {
					p.onground = 0;
				}
			}
			if (p2.sprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds()))
			{
				p2.dy = 0;
				p2.onground = 1;
				if (p2.rect.top <= p.rect.top - 50.5 || p2.rect.top <= p.rect.top - 50) {

					p2.rect.top = p.rect.top - 80;
					p2.onground = 1;
				}
				else {
					p2.onground = 0;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::LAlt)) {
					//soundMele.play();
					p2.dx = 0;
					p2.sprite.setTextureRect(IntRect(0, 49, 48, 49));

				}
				else {
					p2.dx = 0.1 * PlayerPowerup[1].getSpeed();
					p2.lastkeypressed = 1;
				}
				if ((p2.rect.left >= p.rect.left - 70 || p2.rect.left >= p.rect.left - 70.5) &&
					(p2.rect.left <= p.rect.left - 50 || p2.rect.left <= p.rect.left - 50.5)) {
					if ((p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50)
						&& (p2.rect.top <= p.rect.top + 49.5 || p2.rect.top <= p.rect.top + 50))
					{
						p2.rect.left = p.rect.left - 72;
					}
				}


			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::RAlt)) {
					p.dx = 0;
					p.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else {
					p.dx = 0.1 * PlayerPowerup[0].getSpeed();
					p.lastkeypressed = 1;
				}
				if ((p.rect.left >= p2.rect.left - 70 || p.rect.left >= p2.rect.left - 70.5) &&
					(p.rect.left <= p2.rect.left - 50 || p.rect.left <= p2.rect.left - 50.5)) {
					if ((p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50)
						&& (p.rect.top <= p2.rect.top + 49.5 || p.rect.top <= p2.rect.top + 50))
					{
						p.rect.left = p2.rect.left - 72;
					}
				}


			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::RAlt)) {
					p.dx = 0;
					p.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}
				else {
					p.dx = -0.1 * PlayerPowerup[0].getSpeed();
					p.lastkeypressed = 2;
				}
				if ((p.rect.left <= p2.rect.left + 70 || p.rect.left <= p2.rect.left + 70.5) &&
					(p.rect.left >= p2.rect.left + 50 || p.rect.left >= p2.rect.left + 50.5)) {
					if ((p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50)
						&& (p.rect.top <= p2.rect.top + 49.5 || p.rect.top <= p2.rect.top + 50))
					{
						p.rect.left = p2.rect.left + 72;
					}
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Up) && qwertty == 0) {
				qwertty = 1;
				if (p.onground) {
					p.dy = -0.4;
					p.onground = 0;
				}
			}

			if (event.type == Event::KeyReleased || p.onground) {
				qwertty = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {

				if (!p.onground) {
					p.dy = 0.4;
					p.onground = 1;
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(49, 144, 42, 48));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(49 + 42, 144, -42, 48));
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::A)) {

				if (Keyboard::isKeyPressed(Keyboard::Key::LAlt)) {
					soundMele.play();
					p2.dx = 0;
					p2.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));

				}
				else {
					p2.dx = -0.1 * PlayerPowerup[1].getSpeed();
					p2.lastkeypressed = 2;
				}
				if ((p2.rect.left <= p.rect.left + 70 || p2.rect.left <= p.rect.left + 70.5) &&
					(p2.rect.left >= p.rect.left + 50 || p2.rect.left >= p.rect.left + 50.5)) {
					if ((p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50)
						&& (p2.rect.top <= p.rect.top + 49.5 || p2.rect.top <= p.rect.top + 50))
					{
						p2.rect.left = p.rect.left + 72;
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::W) && qwertty2 == 0) {
				qwertty2 = 1;
				if (p2.onground) {
					p2.dy = -0.4;
					p2.onground = 0;
				}
			}
			if (event.type == Event::KeyReleased || p2.onground) {
				qwertty2 = 0;
			}




			if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
				if (!p2.onground) {
					p2.dy = 0.4;
					p2.onground = 1;
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(48, 144, 42, 48));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(48 + 42, 144, -42, 48));
				}
			}
			/*if (Keyboard::isKeyPressed(Keyboard::Key::RAlt)) {
				p.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
			}*/

			/*if (Keyboard::isKeyPressed(Keyboard::Key::LAlt)) {
				p2.sprite.setTextureRect(IntRect(0, 49, 48, 49));
			}*/


			// enemy 
			for (int i = 0; i < 5; i++)
			{
				enemy[i].x += 0.1;
				if (i < 3)
				{
					enemy[i].shape.setTextureRect(IntRect(29 * int(enemy[i].x) + 29, 0, -29, 24));
					if (enemy[i].shape.getPosition().x > 1920)
					{
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
						enemy[i].speed = rand() % 8 + 8;
					}
					enemy[i].shape.move(enemy[i].speed, 0);
					if (enemy[i].x > 3)
						enemy[i].x = 0;
					if (p.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
					}

					if (p2.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
					}
				}
				else
				{
					enemy[i].shape.setTextureRect(IntRect(29 * int(enemy[i].x), 0, 29, 24));
					if (enemy[i].shape.getPosition().x < -80)
					{
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
						enemy[i].speed = rand() % 8 + 8;
					}
					enemy[i].shape.move(-enemy[i].speed, 0);
					if (enemy[i].x > 3)
						enemy[i].x = 0;
					if (p.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
					}
					if (p2.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
					}
				}
			}

			/*p.onground = 0;
			p2.onground = 0;*/ // dont know why ??! // 2na bs l2et ele fo2eha kda f3mld da. 

			int timer = clocktimer.getElapsedTime().asSeconds();
			if (timer % 5 == 0 && !Add1 && timer % 9 != 0 /*need to change*/)
			{
				if (kks < 2)
				{
					PowersSprits.add();
				}
				Add1 = 1;
				if (kks >= 2)
				{
					bl2 = 1;
					MakeWeapon(ChooseWeapon, weapon);
					kks = 0;
				}
				kks++;

			}
			else if (timer % 9 == 0 && timer != 0 /*need to change*/)
			{

				PowersSprits.delet();
				Add1 = 0;
				clocktimer.restart();
			}
			if (weapon.WeaponType != 0)
				Gravity_Weapon(weapon, blocks, roundnum);

			if (p.sprite.getGlobalBounds().intersects(weapon.GunPhoto.getGlobalBounds()) && p.bullet.Magazin <= 0)
			{
				// 1-> pistol , 2-> rifle , 3-> goldengun

				p.bullet.BulletSprite.setTexture(weapon.GeneralBulletSprite);
				weapon.GunPhoto.setPosition(-1000, -1000);
				p.bullet.BulletSprite.setScale(2, 2);
				p.bullet.Speed = weapon.BulletSpeed;
				p.bullet.Damage = weapon.Damage;
				p.bullet.Magazin = weapon.Magazin;
				p.bullet.type = 1;
				p.bullet.CoolDownuse = weapon.Cooldown;
				p.bullet.BulletSound = weapon.WeaponSound;
				if (true) {
					sound.play();
				}
			}

			if (p2.sprite.getGlobalBounds().intersects(weapon.GunPhoto.getGlobalBounds()) && p2.bullet.Magazin <= 0)
			{

				// 1-> pistol , 2-> rifle , 3-> goldengun
				p2.bullet.BulletSprite.setTexture(weapon.GeneralBulletSprite);
				weapon.GunPhoto.setPosition(-1000, -1000);
				p2.bullet.BulletSprite.setScale(2, 2);
				p2.bullet.Speed = weapon.BulletSpeed;
				p2.bullet.Damage = weapon.Damage;
				p2.bullet.Magazin = weapon.Magazin;
				p2.bullet.type = 1;
				p2.bullet.CoolDownuse = weapon.Cooldown;
				p2.bullet.BulletSound = weapon.WeaponSound;
				sound.play();
			}



			if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.Magazin <= 0 && p2.bullet.meletimer >= 2)
			{
				if (p2.lastkeypressed == 1) {
					if ((p2.rect.left >= p.rect.left - 75 || p2.rect.left >= p.rect.left - 75.5) &&
						(p2.rect.left <= p.rect.left - 60 || p2.rect.left <= p.rect.left - 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				else if (p2.lastkeypressed == 2) {
					if ((p2.rect.left <= p.rect.left + 75 || p2.rect.left <= p.rect.left + 75.5) &&
						(p2.rect.left >= p.rect.left + 60 || p2.rect.left >= p.rect.left + 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				p2.bullet.meletimer = 0;
				//P2MeleClock.restart();
			}


			if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.Magazin <= 0 && p.bullet.meletimer >= 2)
			{
				if (p.lastkeypressed == 1) {
					if ((p.rect.left >= p2.rect.left - 75 || p.rect.left >= p2.rect.left - 75.5) &&
						(p.rect.left <= p2.rect.left - 60 || p.rect.left <= p2.rect.left - 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				else if (p.lastkeypressed == 2) {
					if ((p.rect.left <= p2.rect.left + 75 || p.rect.left <= p2.rect.left + 75.5) &&
						(p.rect.left >= p2.rect.left + 60 || p.rect.left >= p2.rect.left + 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				p.bullet.meletimer = 0;
				//P1MeleClock.restart();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.CoolDownBool && p.bullet.Magazin >= 1)
			{
				p.bullet.BulletSound.play();
				playergun1 += 0.5;
				if (playergun1 > 2) {
					playergun1 = 0;
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(42 * int(playergun1), 49, 42, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(42 * int(playergun1) + 42, 49, -42, 49));
				}
				p.V_Bullets.push_back(p.bullet);
				p.V_Bullets[p.V_Bullets.size() - 1].BulletSprite.setPosition(p.sprite.getPosition().x, p.sprite.getPosition().y);
				p.V_Bullets[p.V_Bullets.size() - 1].moveTo = p.lastkeypressed;
				p.bullet.Magazin--;
				p.bullet.CoolDownBool = 0;

			}

			else if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.Magazin <= 0)
			{

				soundMele.play();
				if (p.lastkeypressed == 1) {
					if ((p.rect.left >= p2.rect.left - 75 || p.rect.left >= p2.rect.left - 75.5) &&
						(p.rect.left <= p2.rect.left - 60 || p.rect.left <= p2.rect.left - 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::Right))
							p2.rect.left = p.rect.left + 105;

						}
					}
				}
				else if (p.lastkeypressed == 2) {
					if ((p.rect.left <= p2.rect.left + 75 || p.rect.left <= p2.rect.left + 75.5) &&
						(p.rect.left >= p2.rect.left + 60 || p.rect.left >= p2.rect.left + 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::Left))
							p2.rect.left = p.rect.left - 105;

						}
					}
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}

			}


			if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.CoolDownBool && p2.bullet.Magazin >= 1)
			{
				p2.bullet.BulletSound.play();
				playergun2 += 0.5;
				if (playergun2 > 2) {
					playergun2 = 0;
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(42 * int(playergun2), 49, 42, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(42 * int(playergun2) + 42, 49, -42, 49));
				}
				p2.V_Bullets.push_back(p2.bullet);
				p2.V_Bullets[p2.V_Bullets.size() - 1].BulletSprite.setPosition(p2.sprite.getPosition().x, p2.sprite.getPosition().y);
				p2.V_Bullets[p2.V_Bullets.size() - 1].moveTo = p2.lastkeypressed;
				p2.bullet.Magazin--;
				p2.bullet.CoolDownBool = 0;

			}

			else if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.Magazin <= 0)
			{
				soundMele.play();
				if (p2.lastkeypressed == 1) {
					if ((p2.rect.left >= p.rect.left - 75 || p2.rect.left >= p.rect.left - 75.5) &&
						(p2.rect.left <= p.rect.left - 60 || p2.rect.left <= p.rect.left - 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::D))
							p.rect.left = p2.rect.left + 105;
						}

					}
				}
				else if (p2.lastkeypressed == 2) {
					if ((p2.rect.left <= p.rect.left + 75 || p2.rect.left <= p.rect.left + 75.5) &&
						(p2.rect.left >= p.rect.left + 60 || p2.rect.left >= p.rect.left + 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::A))
							p.rect.left = p2.rect.left - 105;

						}

					}
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}
			}




			if (P1MeleClock.getElapsedTime().asSeconds() >= 1)
			{
				p.bullet.meletimer++;
				P1MeleClock.restart();
			}
			if (P2MeleClock.getElapsedTime().asSeconds() >= 1)
			{
				p2.bullet.meletimer++;
				P2MeleClock.restart();
			}


			for (int i = 0; i < p2.V_Bullets.size(); i++)
			{
				bool cheak = 0; // for earasing the bullets.
				if (p2.V_Bullets[i].moveTo == 2)
					p2.V_Bullets[i].BulletSprite.move(-7 * p2.V_Bullets[i].Speed, 0);
				if (p2.V_Bullets[i].moveTo == 1)
					p2.V_Bullets[i].BulletSprite.move(7 * p2.V_Bullets[i].Speed, 0);
				for (int k = 0; k < 5; k++)
				{
					if (k < 3)
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p2.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(-100, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
					else
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p2.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(2020, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
				}
				if (p2.V_Bullets[i].BulletSprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds()))
				{
					PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - p2.V_Bullets[i].Damage);
					damagesound.play();
					cheak = 1;
				}
				if (cheak)
					p2.V_Bullets.erase(p2.V_Bullets.begin() + i);
			}

			for (int i = 0; i < p.V_Bullets.size(); i++)
			{
				bool cheak = 0; // for earasing the bullets.
				if (p.V_Bullets[i].moveTo == 2)
					p.V_Bullets[i].BulletSprite.move(-7 * p.V_Bullets[i].Speed, 0);
				if (p.V_Bullets[i].moveTo == 1)
					p.V_Bullets[i].BulletSprite.move(7 * p.V_Bullets[i].Speed, 0);
				for (int k = 0; k < 5; k++)
				{
					if (k < 3)
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(-100, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
					else
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(2020, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
				}
				if (p.V_Bullets[i].BulletSprite.getGlobalBounds().intersects(p2.sprite.getGlobalBounds()))
				{
					PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - p.V_Bullets[i].Damage);
					damagesound.play();
					cheak = 1;
				}
				if (cheak)
					p.V_Bullets.erase(p.V_Bullets.begin() + i);
			}

			if (!p.bullet.CoolDownBool && use1)
			{
				Bullettimer1.restart();
				use1 = 0;
			}
			else
			{
				if (p.bullet.CoolDownuse <= (int)Bullettimer1.getElapsedTime().asSeconds())
				{
					p.bullet.CoolDownBool = 1;
					use1 = 1;
				}
			}

			if (!p2.bullet.CoolDownBool && use2)
			{
				Bullettimer2.restart();
				use2 = 0;
			}
			else
			{
				if (p2.bullet.CoolDownuse <= (int)Bullettimer2.getElapsedTime().asSeconds())
				{
					p2.bullet.CoolDownBool = 1;
					use2 = 1;
				}
			}
			for (int i = 0; i < V.size(); i++)
			{
				Gravity_Powerups(V[i], blocks, roundnum);
				if (p.sprite.getGlobalBounds().intersects(V[i].getGlobalBounds()))
				{
					//chose 0->speed 2->health 1->scale
					if (V[i].getFillColor() == Color::Green)
					{
						PlayerPowerup[0].setSpeed(p.HeroType.Speed + 0.5);
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Red)
					{
						if (PlayerPowerup[0].getHealth() < 10)
						{
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() + 1);
						}
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Blue)
					{
						PlayerPowerup[1].setSpeed(PlayerPowerup[1].getSpeed() - 3);
						PowersSprits.delet(i);
					}
					timer1 = 0;
				}
				else if (p2.sprite.getGlobalBounds().intersects(V[i].getGlobalBounds()))
				{
					//chose 0->speed 2->health 1->scale
					if (V[i].getFillColor() == Color::Green)
					{
						PlayerPowerup[1].setSpeed(3);
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Red)
					{

						if (PlayerPowerup[1].getHealth() < 10)
						{
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() + 1);

						}
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Blue)
					{
						PlayerPowerup[0].setSpeed(PlayerPowerup[0].getSpeed() - 3);
						PowersSprits.delet(i);
					}
					timer2 = 0;
				}
			}
			if (!timer1)
			{
				clocktimer1.restart();
				timer1 = 1;
			}
			else if (!timer2)
			{
				clocktimer2.restart();
				timer2 = 1;
			}
			timerpowerup2 = (int)clocktimer2.getElapsedTime().asSeconds();
			timerpowerup1 = (int)clocktimer1.getElapsedTime().asSeconds();

			if (timerpowerup1 == 5)
			{
				PlayerPowerup[0].setSpeed(p.HeroType.Speed);
				PlayerPowerup[1].setSpeed(p2.HeroType.Speed);
			}
			if (timerpowerup2 == 5)
			{
				PlayerPowerup[1].setSpeed(p2.HeroType.Speed);
				PlayerPowerup[0].setSpeed(p.HeroType.Speed);
			}
			p.update(time);
			p2.update(time);

			if (PlayerPowerup[0].getHealth() <= 0)
			{
				p2score++;
				if (p1score == 2 || p2score == 2)
				{
					GameOver(window, p1score, p2score);
					return;
				}
				else
				{
					pagenum = 12;//Round3
					return;
				}
			}

			if (PlayerPowerup[1].getHealth() <= 0)
			{
				p1score++;
				if (p1score == 2 || p2score == 2)
				{
					GameOver(window, p1score, p2score);

					return;
				}
				pagenum = 12;//Round3
				return;
			}
		}

		if (true)
		{
			window.clear();
			window.draw(background);
			for (int i = 0; i < p.V_Bullets.size(); i++)
			{
				window.draw(p.V_Bullets[i].BulletSprite);
			}
			for (int i = 0; i < p2.V_Bullets.size(); i++)
			{
				window.draw(p2.V_Bullets[i].BulletSprite);
			}
			for (int i = 0; i < 16; i++) {
				window.draw(blocks[i]);
			}
			//window.draw(BGSprite);
			stringstream sc, ss;
			sc << PlayerPowerup[0].getHealth(); //int to string
			sc >> s;
			ss << PlayerPowerup[1].getHealth(); //int to string
			ss >> s2;
			stringstream po, po2;
			po2 << p1score; //int to string
			po2 >> P1score;
			po << p2score; //int to string
			po >> P2score;
			textscore.setString(P2score + ":" + P1score);
			text.setString(player1 + ':' + s);//setting the string to player 1 
			text2.setString(player2 + ':' + s2);//setting the string to player 2
			window.draw(heart);
			window.draw(heart2);
			window.draw(text2);
			window.draw(text);
			window.draw(textscore);
			window.draw(weapon.GunPhoto);
			for (int i = 0; i < V.size(); i++)
				window.draw(V[i]);
			window.draw(p.sprite);
			window.draw(p2.sprite);
			for (int i = 0; i < 5; i++)
				window.draw(enemy[i].shape);
			if (paused) {
				window.draw(r);
				window.draw(PauseSprite);
				pm.draw(window);
			}
			window.draw(round2);
			window.display();
		}

	}
}
void Round3(RenderWindow& window) {


	Sprite blocks[25]; //map1 blocks
	Clock BlockHideClock;

	pair<int, bool> BlockHideTimer[22];

	int kks = 0; // chosing the weapon after 4 powerups.
	blockround3(blocks);
	/*int minb8 = 0, maxb8 = 0;
	bool m8 = 1;
	int minb5 = 0, maxb5 = 0;
	bool m5 = 1;
	int minb13 = 0, maxb13 = 0;
	bool m13 = 1;
	int m9 = 1;
	int minb9 = 0, maxb9 = 0;

	int m3 = 1;
	int minb3 = 0, maxb3 = 0;*/

	SoundBuffer buffer;
	buffer.loadFromFile("equip.wav");
	Sound sound;
	sound.setBuffer(buffer);
	SoundBuffer buffer2;
	buffer2.loadFromFile("game.wav");
	Sound sound2;
	sound2.setBuffer(buffer2);
	SoundBuffer buffer3;
	buffer3.loadFromFile("select.wav");
	Sound sound3;
	sound3.setBuffer(buffer3);


	buffer4.loadFromFile("GGsound.wav");

	sound4.setBuffer(buffer4);
	SoundBuffer buffer5;
	buffer5.loadFromFile("GGsound.wav");
	Sound sound5;
	sound5.setBuffer(buffer5);

	SoundBuffer buffer6;
	buffer6.loadFromFile("FinalRoundSound.wav");
	Sound sound6;
	sound6.setBuffer(buffer6);
	sound6.play();
	SoundBuffer buffer7;
	buffer7.loadFromFile("damagesound.wav");
	Sound damagesound;
	damagesound.setBuffer(buffer7);

	bool paused = 0;
	PauseMenu pm(1920, 1080);

	Weapon weapon;
	bool use1 = 1; // for weapon player1 
	bool use2 = 1; // for weapon player2 
	Clock Bullettimer1;
	Clock Bullettimer2;
	CircleShape weaponCircle(20);

	float f = 0;
	
	Texture speedTex;
	speedTex.loadFromFile("thunder.png");
	Texture DecayTex;
	DecayTex.loadFromFile("decay.png");
	texth.loadFromFile("heart.PNG");

	powers[0].setFillColor(Color::Green);
	powers[0].setTexture(&speedTex);
	powers[0].setScale(1.3, 1.3);
	powers[1].setFillColor(Color::Blue);
	powers[1].setTexture(&DecayTex);
	powers[2].setFillColor(Color::Red);
	powers[2].setTexture(&texth);


	Clock clock;
	Clock clocktimer, clocktimer1, clocktimer2;
	Texture t;
	Texture t2;
	t.loadFromFile("pla1.png");
	player p(t);
	t2.loadFromFile("pla2.png");
	player p2(t2);

	UpdateHeroType(p, p2);

	p.rect.left = 1358;
	p.rect.top = 282;
	p.lastkeypressed = 2;
	p2.rect.top = 282;
	p2.rect.left = 500;
	p2.dx = 0.0000001;
	p2.dx += 0.0000003;
	p2.lastkeypressed = 1;

	p.update(0);
	p2.update(0);

	Player_Powerups PlayerPowerup[2]; // 0->player1_Powerups , 1->player2_Powerup
	PowerUps PowersSprits; // 	

	for (int i = 0; i < 2; i++)
	{
		if (i % 2 == 0)
		{
			PlayerPowerup[i].setSpeed(p.HeroType.Speed);
			PlayerPowerup[i].setHealth(p.HeroType.Health);
		}
		else
		{
			PlayerPowerup[i].setSpeed(p2.HeroType.Speed);
			PlayerPowerup[i].setHealth(p2.HeroType.Health);
		}
	}

	string s, s2, P1score, P2score;

	bool closed = 0;
	Font font;
	font.loadFromFile("RythmOfDeath.ttf");
	Text text;
	text.setFont(font);
	if (player1.size() > 2)
		text.setPosition(1920 - ((player1.size() + 10) * 20), 10);
	else
		text.setPosition(1920 - 190, 10);
	text.setFillColor(Color::Green);
	Text textscore;
	textscore.setFont(font);
	textscore.setPosition(940, 80);
	textscore.setFillColor(Color::White);

	Text text2;
	text2.setFont(font);
	text2.setPosition(80, 10);
	text2.setFillColor(Color::Green);

	text.setCharacterSize(60);
	text2.setCharacterSize(60);
	textscore.setCharacterSize(70);

	texth.loadFromFile("heart.PNG");
	Sprite heart;
	heart.setTexture(texth);
	heart.setScale(0.2, 0.2);
	if (player2.size() > 2)
		heart.setPosition(text2.getPosition().x + (player2.size() + 3) * 20 + 10, text2.getPosition().y + 15); // for player on the left. 
	else
		heart.setPosition(120, text2.getPosition().y + 15);
	Sprite heart2;
	heart2.setTexture(texth);
	heart2.setScale(0.2, 0.2);
	heart2.setPosition(1800, text.getPosition().y + 15); // for the player on the right .


	Texture Enemyphoto;
	Enemyphoto.loadFromFile("ghost.png");


	Texture text5;
	text5.loadFromFile("blockk3.PNG");

	Texture ttf;
	ttf.loadFromFile("underground3.PNG");


	CircleShape players(20);
	Sprite player;
	Texture text6;
	text6.loadFromFile("gods_and_monsters_video_game_2020-wallpaper-1920x1080.JPG");
	Sprite background;
	background.setTexture(text6);

	for (int i = 0; i < 22; i++) {
		if (i == 7)
			blocks[i].setTexture(ttf);
		else
			blocks[i].setTexture(text5);
		BlockHideTimer[i].first = 2;
		BlockHideTimer[i].second = 0;
	}

	bool qwertty = 0;
	bool qwertty2 = 0;
	for (int i = 0; i < 22; i++)
	{
		powerupint[i].x = blocks[i].getPosition().x + blocks[i].getScale().x * 256 / 2 - 20;
		powerupint[i].y = blocks[i].getPosition().y - 200;
	}
	// enemy
	for (int i = 0; i < 6; i++)
	{
		enemy[i].shape.setTexture(Enemyphoto);
		if (i < 3)
		{
			int y = rand() % 921 + 80;
			enemy[i].shape.setPosition(-600, y);
			enemy[i].speed = rand() % 8 + 8;
			enemy[i].shape.setScale(2.3, 2.3);
			enemy[i].shape.setTextureRect(IntRect(29, 0, -29, 24));
		}
		else
		{
			int y = rand() % 921 + 80;
			enemy[i].shape.setPosition(2620, y);
			enemy[i].speed = rand() % 8 + 8;
			enemy[i].shape.setScale(2.3, 2.3);
			enemy[i].shape.setTextureRect(IntRect(0, 0, 29, 24));
		}
	}

	// For PauseMenu 
	RectangleShape r(Vector2f(800, 800));
	r.setFillColor(Color::Black);
	r.setOrigin(400, 400);
	r.setPosition(1920 / 2, 1080 / 2);

	finalround.setPosition(860, 30);
	finalround.setScale(0.25, 0.25);

	soundRound1.setLoop(true);
	soundRound1.setVolume(20);

	BlockHideClock.restart();
	while (window.isOpen())
	{

		Event event;
		if (paused)
		{
			BlockHideClock.restart();
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed()) {
					paused = 0;
					window.close();
				}
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Up)) {
						pm.moveup();
						sound3.play();
						sound3.setVolume(25);
					}
					if (Keyboard::isKeyPressed(Keyboard::Down)) {
						pm.movedown();
						sound3.play();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					paused = 0;
				}
				if (event.key.code == Keyboard::Return) // return=enter
				{
					if (pm.pressed() == 0) {
						//sound.pause();
						paused = 0;
					}
					if (pm.pressed() == 1 && soundRound1.getVolume() <= 100)
					{
						soundRound1.setVolume(soundRound1.getVolume() + 10);
						soundMele.setVolume(soundMele.getVolume() + 10);
						sound4.setVolume(sound4.getVolume() + 10);
						sound5.setVolume(sound5.getVolume() + 10);
						sound3.setVolume(sound3.getVolume() + 10);
						sound.setVolume(sound.getVolume() + 10);
						sound6.setVolume(sound6.getVolume() + 10);
						soundAfterEnter.setVolume(soundAfterEnter.getVolume() + 10);
						weapon.WeaponSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p2.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						damagesound.setVolume(damagesound.getVolume() + 10);
					}
					if (pm.pressed() == 2 && soundRound1.getVolume() >= 0)
					{
						soundRound1.setVolume(soundRound1.getVolume() - 10);
						soundMele.setVolume(soundMele.getVolume() - 10);
						sound4.setVolume(sound4.getVolume() - 10);
						sound5.setVolume(sound5.getVolume() - 10);
						sound3.setVolume(sound3.getVolume() - 10);
						sound.setVolume(sound.getVolume() - 10);
						sound6.setVolume(sound6.getVolume() - 10);
						soundAfterEnter.setVolume(soundAfterEnter.getVolume() - 10);
						weapon.WeaponSound.setVolume(weapon.WeaponSound.getVolume() - 10);
						p.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						p2.bullet.BulletSound.setVolume(weapon.WeaponSound.getVolume() + 10);
						damagesound.setVolume(damagesound.getVolume() - 10);
					}
					if (pm.pressed() == 3) {
						pagenum = 1000;
						return;
					}
				}

			}
		}


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i mousePosition = Mouse::getPosition(window);
			cout << mousePosition.x << " " << mousePosition.y << endl;
		}

		if (!paused) {
			for (int i = 0; i < 22; i++)
			{
				if (p2.sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
				{
					if (((p2.rect.left >= blocks[i].getPosition().x + 120) || (p2.rect.left >= blocks[i].getPosition().x + 120.5)) && i != 7) {
						p2.rect.left = blocks[i].getPosition().x + 130;
					}
					else if (((p2.rect.left + 30 <= blocks[i].getPosition().x) || (p2.rect.left + 30.5 <= blocks[i].getPosition().x)) && i != 7) {
						p2.rect.left = blocks[i].getPosition().x - 45;
					}
					else {
						p2.dy = 0;
						p2.onground = 1;
						if (p2.rect.top > blocks[i].getPosition().y + 20)
						{
							p2.onground = 0;
						}
						else
						{
							p2.rect.top = blocks[i].getPosition().y - 80;
							p2.onground = 1;
							if (i != 7 && !BlockHideTimer[i].second)
							{
								BlockHideTimer[i].second = 1;
								BlockHideTimer[i].first = 0;
							}
						}
					}
				}
				if (p.sprite.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
				{

					if (((p.rect.left >= blocks[i].getPosition().x + 120) || (p.rect.left >= blocks[i].getPosition().x + 120.5)) && i != 7) {
						p.rect.left = blocks[i].getPosition().x + 130;
					}
					else if (((p.rect.left + 30 <= blocks[i].getPosition().x) || (p.rect.left + 30.5 <= blocks[i].getPosition().x)) && i != 7) {
						p.rect.left = blocks[i].getPosition().x - 45;
					}
					else {
						p.dy = 0;
						p.onground = 1;
						if (p.rect.top > blocks[i].getPosition().y + 20)
						{
							p.onground = 0;
						}
						else
						{
							p.rect.top = blocks[i].getPosition().y - 80;
							p.onground = 1;
							if (i != 7 && !BlockHideTimer[i].second)
							{
								BlockHideTimer[i].second = 1;
								BlockHideTimer[i].first = 0;
							}
						}
					}
				}

				if (BlockHideTimer[i].first >= 3)
				{
					blocks[i].setScale(0, 0);
				}
				if (BlockHideTimer[i].first >= 5)
				{
					blocks[i].setScale(0.5, 0.5);
				}

			}
			if (BlockHideClock.getElapsedTime().asSeconds() >= 1)
			{
				for (int i = 0; i < 22; i++)
				{
					cout << i << " <- i " << "- timer -> " << BlockHideTimer[i].first << endl;
					if (BlockHideTimer[i].second)
					{
						BlockHideTimer[i].first++;
					}
					if (BlockHideTimer[i].first >= 5)
					{
						BlockHideTimer[i].second = 0;
						//BlockHideTimer[i].first = 2;
					}
				}
				BlockHideClock.restart();
			}
			ChooseWeapon = rand() % 3 + 1;
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			time *= 2000;
			chose = rand() % 3;
			h = rand() % 22;

			for (int i = 0; i < 3; i++)
			{
				powers[i].setPosition(powerupint[h]);
				powers[i].setRadius(20);
			}

			while (window.pollEvent(event))
			{

				if (event.type == Event::Closed) {
					window.close();
				}
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						paused = 1;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::G)) {
					PlayerPowerup[0].setHealth(0);
				}
				if (Keyboard::isKeyPressed(Keyboard::H)) {
					PlayerPowerup[1].setHealth(0);
				}
			}


			if (p.bullet.Magazin > 0) {
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(126, 49, 42, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(126 + 42, 49, -42, 49));
				}
			}
			if (p2.bullet.Magazin > 0) {
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(126, 49, 42, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(126 + 42, 49, -42, 49));
				}

			}
			if (p.bullet.Magazin == 0) {
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(181, 0, 35, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(181 + 35, 0, -35, 49));
				}
			}
			if (p2.bullet.Magazin == 0) {
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(181, 0, 35, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(181 + 35, 0, -35, 49));
				}
			}



			if (p.sprite.getGlobalBounds().intersects(p2.sprite.getGlobalBounds()))
			{
				p.dy = 0;
				p.onground = 1;
				if (p.rect.top <= p2.rect.top - 50.5 || p.rect.top <= p2.rect.top - 50) {

					p.rect.top = p2.rect.top - 80;
					p.onground = 1;
				}
				else {
					p.onground = 0;
				}
			}
			if (p2.sprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds()))
			{
				p2.dy = 0;
				p2.onground = 1;
				if (p2.rect.top <= p.rect.top - 50.5 || p2.rect.top <= p.rect.top - 50) {

					p2.rect.top = p.rect.top - 80;
					p2.onground = 1;
				}
				else {
					p2.onground = 0;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::RAlt)) {
					p.dx = 0;
					p.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else {
					p.dx = 0.1 * PlayerPowerup[0].getSpeed();
					p.lastkeypressed = 1;
				}
				if ((p.rect.left >= p2.rect.left - 70 || p.rect.left >= p2.rect.left - 70.5) &&
					(p.rect.left <= p2.rect.left - 50 || p.rect.left <= p2.rect.left - 50.5)) {
					if ((p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50)
						&& (p.rect.top <= p2.rect.top + 49.5 || p.rect.top <= p2.rect.top + 50))
					{
						p.rect.left = p2.rect.left - 72;
					}
				}


			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::RAlt)) {
					p.dx = 0;
					p.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}
				else {
					p.dx = -0.1 * PlayerPowerup[0].getSpeed();
					p.lastkeypressed = 2;
				}
				if ((p.rect.left <= p2.rect.left + 70 || p.rect.left <= p2.rect.left + 70.5) &&
					(p.rect.left >= p2.rect.left + 50 || p.rect.left >= p2.rect.left + 50.5)) {
					if ((p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50)
						&& (p.rect.top <= p2.rect.top + 49.5 || p.rect.top <= p2.rect.top + 50))
					{
						p.rect.left = p2.rect.left + 72;
					}
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Up) && qwertty == 0) {
				qwertty = 1;
				if (p.onground) {
					p.dy = -0.4;
					p.onground = 0;
				}
			}

			if (event.type == Event::KeyReleased || p.onground) {
				qwertty = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {

				if (!p.onground) {
					p.dy = 0.4;
					p.onground = 1;
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(49, 144, 42, 48));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(49 + 42, 144, -42, 48));
				}
			}


			if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
				if (Keyboard::isKeyPressed(Keyboard::Key::LAlt)) {
					soundMele.play();
					p2.dx = 0;
					p2.sprite.setTextureRect(IntRect(0, 49, 48, 49));

				}
				else {
					p2.dx = 0.1 * PlayerPowerup[1].getSpeed();
					p2.lastkeypressed = 1;
				}
				if ((p2.rect.left >= p.rect.left - 70 || p2.rect.left >= p.rect.left - 70.5) &&
					(p2.rect.left <= p.rect.left - 50 || p2.rect.left <= p.rect.left - 50.5)) {
					if ((p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50)
						&& (p2.rect.top <= p.rect.top + 49.5 || p2.rect.top <= p.rect.top + 50))
					{
						p2.rect.left = p.rect.left - 72;
					}
				}


			}
			if (Keyboard::isKeyPressed(Keyboard::Key::A)) {

				if (Keyboard::isKeyPressed(Keyboard::Key::LAlt)) {
					soundMele.play();
					p2.dx = 0;
					p2.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));

				}
				else {
					p2.dx = -0.1 * PlayerPowerup[1].getSpeed();
					p2.lastkeypressed = 2;
				}
				if ((p2.rect.left <= p.rect.left + 70 || p2.rect.left <= p.rect.left + 70.5) &&
					(p2.rect.left >= p.rect.left + 50 || p2.rect.left >= p.rect.left + 50.5)) {
					if ((p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50)
						&& (p2.rect.top <= p.rect.top + 49.5 || p2.rect.top <= p.rect.top + 50))
					{
						p2.rect.left = p.rect.left + 72;
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::W) && qwertty2 == 0) {
				qwertty2 = 1;
				if (p2.onground) {
					p2.dy = -0.4;
					p2.onground = 0;
				}
			}
			if (event.type == Event::KeyReleased || p2.onground) {
				qwertty2 = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
				if (!p2.onground) {
					p2.dy = 0.4;
					p2.onground = 1;
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(48, 144, 42, 48));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(48 + 42, 144, -42, 48));
				}
			}

			// enemies 
			for (int i = 0; i < 2; i++)
			{
				enemy[i].x += 0.1;
				if (i < 2)
				{
					enemy[i].shape.setTextureRect(IntRect(29 * int(enemy[i].x) + 29, 0, -29, 24));
					if (enemy[i].shape.getPosition().x > 1920)
					{
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
						enemy[i].speed = rand() % 8 + 8;
					}
					enemy[i].shape.move(enemy[i].speed, 0);
					if (enemy[i].x > 3)
						enemy[i].x = 0;
					if (p.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
					}

					if (p2.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(-600, y);
					}
				}
				else
				{
					enemy[i].shape.setTextureRect(IntRect(29 * int(enemy[i].x), 0, 29, 24));
					if (enemy[i].shape.getPosition().x < -80)
					{
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
						enemy[i].speed = rand() % 8 + 8;
					}
					enemy[i].shape.move(-enemy[i].speed, 0);
					if (enemy[i].x > 3)
						enemy[i].x = 0;
					if (p.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
					}
					if (p2.sprite.getGlobalBounds().intersects(enemy[i].shape.getGlobalBounds()))
					{
						PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
						damagesound.play();
						int y = rand() % 921 + 80;
						enemy[i].shape.setPosition(2620, y);
					}
				}
			}
			for (int i = 0; i < 2; i++)
			{
				enemy2[i].x += 0.1;

				//enemy2[i].shape.setTextureRect(IntRect(0, 0, 156, 125))
				if (enemy2[i].shape.getPosition().x >= enemy2[i].maxi)
				{
					enemy2[i].Move = 0;
				}
				if (enemy2[i].shape.getPosition().x <= enemy2[i].mini)
				{
					enemy2[i].Move = 1;
				}
				if (enemy2[i].Move)
				{
					enemy2[i].shape.setTextureRect(IntRect(147.6923 * int(enemy2[i].x), 0, -147.6923, 125));
					if (p.sprite.getPosition().y >= 850)
					{
						if (p.sprite.getPosition().x <= enemy2[i].shape.getPosition().x + 460 && p.sprite.getPosition().x > enemy2[i].shape.getPosition().x)
							/*&& p.sprite.getPosition().y <= enemy2[i].shape.getPosition().y + 100 && p2.sprite.getPosition().y <= enemy2[i].shape.getPosition().y + 100)*/
						{
							enemy2[i].shape.move(enemy2[i].speed * 2, 0);
						}
						else
							enemy2[i].shape.move(enemy2[i].speed, 0);

					}
					if (p2.sprite.getPosition().y >= 850)
					{
						if (p2.sprite.getPosition().x <= enemy2[i].shape.getPosition().x + 460 && p2.sprite.getPosition().x > enemy2[i].shape.getPosition().x)
							/*&& p.sprite.getPosition().y <= enemy2[i].shape.getPosition().y + 100 && p2.sprite.getPosition().y <= enemy2[i].shape.getPosition().y + 100)*/
						{
							enemy2[i].shape.move(enemy2[i].speed * 2, 0);
						}
						else
							enemy2[i].shape.move(enemy2[i].speed, 0);

					}
					else
						enemy2[i].shape.move(enemy2[i].speed, 0);
				}
				if (!enemy2[i].Move)
				{
					enemy2[i].shape.setTextureRect(IntRect(147.6923 * int(enemy2[i].x), 0, 147.6923, 125));
					if (p.sprite.getPosition().y >= 850)
					{
						if (p.sprite.getPosition().x >= enemy2[i].shape.getPosition().x - 260 && p.sprite.getPosition().x < enemy2[i].shape.getPosition().x)
							/*&& p.sprite.getPosition().y <= enemy2[i].shape.getPosition().y + 100 && p2.sprite.getPosition().y <= enemy2[i].shape.getPosition().y + 100)*/
						{
							enemy2[i].shape.move(-enemy2[i].speed * 2, 0);
						}
						else
							enemy2[i].shape.move(-enemy2[i].speed, 0);

					}
					if (p2.sprite.getPosition().y >= 850)
					{
						if (p2.sprite.getPosition().x >= enemy2[i].shape.getPosition().x - 260 && p2.sprite.getPosition().x < enemy2[i].shape.getPosition().x)
							/*&& p.sprite.getPosition().y <= enemy2[i].shape.getPosition().y + 100 && p2.sprite.getPosition().y <= enemy2[i].shape.getPosition().y + 100)*/
						{
							enemy2[i].shape.move(-enemy2[i].speed * 2, 0);
						}
						else
							enemy2[i].shape.move(-enemy2[i].speed, 0);

					}
					else
						enemy2[i].shape.move(-enemy2[i].speed, 0);
				}
				if (enemy2[i].x > 13)
					enemy2[i].x = 1;
				if (p.sprite.getGlobalBounds().intersects(enemy2[i].shape.getGlobalBounds()) && enemy2[i].DoDamage)
				{
					PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 2);
					damagesound.play();
					enemy2[i].DoDamage = 0;
					enemy2[i].timer1 = 0;
					enemy2Clock1.restart();
				}

				if (p2.sprite.getGlobalBounds().intersects(enemy2[i].shape.getGlobalBounds()) && enemy2[i].DoDamage)
				{
					PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 2);
					damagesound.play();
					enemy2[i].DoDamage = 0;
					enemy2[i].timer2 = 0;
					enemy2Clock2.restart();
				}
				if (enemy2Clock1.getElapsedTime().asSeconds() >= 1)
				{
					for (int k = 0; k < 2; k++)
					{
						if (!enemy2[k].DoDamage)
						{
							enemy2[k].timer1++;
						}
					}
				}
				if (enemy2Clock2.getElapsedTime().asSeconds() >= 1)
				{
					for (int k = 0; k < 2; k++)
					{
						if (!enemy2[k].DoDamage)
						{
							enemy2[k].timer2++;
						}

					}
				}

				for (int k = 0; k < 2; k++)
				{
					if (enemy2[k].timer1 == 6)
					{
						enemy2[k].DoDamage = 1;
					}
					if (enemy2[k].timer2 == 6)
					{
						enemy2[k].DoDamage = 1;
					}
				}

			}




			int timer = clocktimer.getElapsedTime().asSeconds();
			if (timer % 5 == 0 && !Add1 && timer % 9 != 0 /*need to change*/)
			{
				if (kks < 2)
				{
					PowersSprits.add();
				}
				Add1 = 1;
				if (kks >= 2)
				{
					bl2 = 1;
					MakeWeapon(ChooseWeapon, weapon);
					kks = 0;
				}
				kks++;

			}
			else if (timer % 9 == 0 && timer != 0 /*need to change*/)
			{

				PowersSprits.delet();
				Add1 = 0;
				clocktimer.restart();
			}
			if (weapon.WeaponType != 0)
				Gravity_Weapon(weapon, blocks, roundnum);

			if (p.sprite.getGlobalBounds().intersects(weapon.GunPhoto.getGlobalBounds()) && p.bullet.Magazin <= 0)
			{
				// 1-> pistol , 2-> rifle , 3-> goldengun

				p.bullet.BulletSprite.setTexture(weapon.GeneralBulletSprite);
				weapon.GunPhoto.setPosition(-1000, -1000);
				p.bullet.BulletSprite.setScale(2, 2);
				p.bullet.Speed = weapon.BulletSpeed;
				p.bullet.Damage = weapon.Damage;
				p.bullet.Magazin = weapon.Magazin;
				p.bullet.type = 1;
				p.bullet.CoolDownuse = weapon.Cooldown;
				p.bullet.BulletSound = weapon.WeaponSound;
				if (true) {
					sound.play();
				}
			}

			if (p2.sprite.getGlobalBounds().intersects(weapon.GunPhoto.getGlobalBounds()) && p2.bullet.Magazin <= 0)
			{

				// 1-> pistol , 2-> rifle , 3-> goldengun
				p2.bullet.BulletSprite.setTexture(weapon.GeneralBulletSprite);
				weapon.GunPhoto.setPosition(-1000, -1000);
				p2.bullet.BulletSprite.setScale(2, 2);
				p2.bullet.Speed = weapon.BulletSpeed;
				p2.bullet.Damage = weapon.Damage;
				p2.bullet.Magazin = weapon.Magazin;
				p2.bullet.type = 1;
				p2.bullet.CoolDownuse = weapon.Cooldown;
				p2.bullet.BulletSound = weapon.WeaponSound;
				sound.play();
			}



			if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.Magazin <= 0 && p2.bullet.meletimer >= 2)
			{
				if (p2.lastkeypressed == 1) {
					if ((p2.rect.left >= p.rect.left - 75 || p2.rect.left >= p.rect.left - 75.5) &&
						(p2.rect.left <= p.rect.left - 60 || p2.rect.left <= p.rect.left - 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				else if (p2.lastkeypressed == 2) {
					if ((p2.rect.left <= p.rect.left + 75 || p2.rect.left <= p.rect.left + 75.5) &&
						(p2.rect.left >= p.rect.left + 60 || p2.rect.left >= p.rect.left + 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				p2.bullet.meletimer = 0;
				//P2MeleClock.restart();
			}


			if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.Magazin <= 0 && p.bullet.meletimer >= 2)
			{
				if (p.lastkeypressed == 1) {
					if ((p.rect.left >= p2.rect.left - 75 || p.rect.left >= p2.rect.left - 75.5) &&
						(p.rect.left <= p2.rect.left - 60 || p.rect.left <= p2.rect.left - 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				else if (p.lastkeypressed == 2) {
					if ((p.rect.left <= p2.rect.left + 75 || p.rect.left <= p2.rect.left + 75.5) &&
						(p.rect.left >= p2.rect.left + 60 || p.rect.left >= p2.rect.left + 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - 1);
							damagesound.play();
						}

					}
				}
				p.bullet.meletimer = 0;
				//P1MeleClock.restart();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.CoolDownBool && p.bullet.Magazin >= 1)
			{
				p.bullet.BulletSound.play();
				playergun1 += 0.5;
				if (playergun1 > 2) {
					playergun1 = 0;
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(42 * int(playergun1), 49, 42, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(42 * int(playergun1) + 42, 49, -42, 49));
				}
				p.V_Bullets.push_back(p.bullet);
				p.V_Bullets[p.V_Bullets.size() - 1].BulletSprite.setPosition(p.sprite.getPosition().x, p.sprite.getPosition().y);
				p.V_Bullets[p.V_Bullets.size() - 1].moveTo = p.lastkeypressed;
				p.bullet.Magazin--;
				p.bullet.CoolDownBool = 0;

			}

			else if (Keyboard::isKeyPressed(Keyboard::Key::RAlt) && p.bullet.Magazin <= 0)
			{

				soundMele.play();
				if (p.lastkeypressed == 1) {
					if ((p.rect.left >= p2.rect.left - 75 || p.rect.left >= p2.rect.left - 75.5) &&
						(p.rect.left <= p2.rect.left - 60 || p.rect.left <= p2.rect.left - 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::Right))
							p2.rect.left = p.rect.left + 105;

						}
					}
				}
				else if (p.lastkeypressed == 2) {
					if ((p.rect.left <= p2.rect.left + 75 || p.rect.left <= p2.rect.left + 75.5) &&
						(p.rect.left >= p2.rect.left + 60 || p.rect.left >= p2.rect.left + 60.5)) {
						if (p.rect.top >= p2.rect.top - 49.5 || p.rect.top >= p2.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::Left))
							p2.rect.left = p.rect.left - 105;

						}
					}
				}
				if (p.lastkeypressed == 1) {
					p.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else if (p.lastkeypressed == 2) {
					p.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}

			}


			if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.CoolDownBool && p2.bullet.Magazin >= 1)
			{
				p2.bullet.BulletSound.play();
				playergun2 += 0.5;
				if (playergun2 > 2) {
					playergun2 = 0;
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(42 * int(playergun2), 49, 42, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(42 * int(playergun2) + 42, 49, -42, 49));
				}
				p2.V_Bullets.push_back(p2.bullet);
				p2.V_Bullets[p2.V_Bullets.size() - 1].BulletSprite.setPosition(p2.sprite.getPosition().x, p2.sprite.getPosition().y);
				p2.V_Bullets[p2.V_Bullets.size() - 1].moveTo = p2.lastkeypressed;
				p2.bullet.Magazin--;
				p2.bullet.CoolDownBool = 0;

			}

			else if (Keyboard::isKeyPressed(Keyboard::Key::LAlt) && p2.bullet.Magazin <= 0)
			{
				soundMele.play();
				if (p2.lastkeypressed == 1) {
					if ((p2.rect.left >= p.rect.left - 75 || p2.rect.left >= p.rect.left - 75.5) &&
						(p2.rect.left <= p.rect.left - 60 || p2.rect.left <= p.rect.left - 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::D))
							p.rect.left = p2.rect.left + 105;
						}

					}
				}
				else if (p2.lastkeypressed == 2) {
					if ((p2.rect.left <= p.rect.left + 75 || p2.rect.left <= p.rect.left + 75.5) &&
						(p2.rect.left >= p.rect.left + 60 || p2.rect.left >= p.rect.left + 60.5)) {
						if (p2.rect.top >= p.rect.top - 49.5 || p2.rect.top >= p.rect.top - 50) {
							//if (!Keyboard::isKeyPressed(Keyboard::Key::A))
							p.rect.left = p2.rect.left - 105;

						}

					}
				}
				if (p2.lastkeypressed == 1) {
					p2.sprite.setTextureRect(IntRect(0, 49 * 3, 48, 49));
				}
				else if (p2.lastkeypressed == 2) {
					p2.sprite.setTextureRect(IntRect(0 + 48, 49 * 3, -48, 49));
				}
			}




			if (P1MeleClock.getElapsedTime().asSeconds() >= 1)
			{
				p.bullet.meletimer++;
				P1MeleClock.restart();
			}
			if (P2MeleClock.getElapsedTime().asSeconds() >= 1)
			{
				p2.bullet.meletimer++;
				P2MeleClock.restart();
			}

			for (int i = 0; i < p2.V_Bullets.size(); i++)
			{
				bool cheak = 0; // for earasing the bullets.
				if (p2.V_Bullets[i].moveTo == 2)
					p2.V_Bullets[i].BulletSprite.move(-7 * p2.V_Bullets[i].Speed, 0);
				if (p2.V_Bullets[i].moveTo == 1)
					p2.V_Bullets[i].BulletSprite.move(7 * p2.V_Bullets[i].Speed, 0);
				for (int k = 0; k < 6; k++)
				{
					if (k < 3)
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p2.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(-100, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
					else
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p2.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(2020, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
				}
				if (p2.V_Bullets[i].BulletSprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds()))
				{
					PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() - p2.V_Bullets[i].Damage);
					damagesound.play();
					cheak = 1;
				}
				if (cheak)
					p2.V_Bullets.erase(p2.V_Bullets.begin() + i);
			}

			for (int i = 0; i < p.V_Bullets.size(); i++)
			{
				bool cheak = 0; // for earasing the bullets.
				if (p.V_Bullets[i].moveTo == 2)
					p.V_Bullets[i].BulletSprite.move(-7 * p.V_Bullets[i].Speed, 0);
				if (p.V_Bullets[i].moveTo == 1)
					p.V_Bullets[i].BulletSprite.move(7 * p.V_Bullets[i].Speed, 0);
				for (int k = 0; k < 6; k++)
				{
					if (k < 3)
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(-100, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
					else
					{
						if (enemy[k].shape.getGlobalBounds().intersects(p.V_Bullets[i].BulletSprite.getGlobalBounds()))
						{
							int y = rand() % 921 + 80;
							enemy[k].shape.setPosition(2020, y);
							enemy[k].speed = rand() % 8 + 8;
							cheak = 1;
							break;
						}
					}
				}
				if (p.V_Bullets[i].BulletSprite.getGlobalBounds().intersects(p2.sprite.getGlobalBounds()))
				{
					PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() - p.V_Bullets[i].Damage);
					damagesound.play();
					cheak = 1;
				}
				if (cheak)
					p.V_Bullets.erase(p.V_Bullets.begin() + i);
			}

			if (!p.bullet.CoolDownBool && use1)
			{
				Bullettimer1.restart();
				use1 = 0;
			}
			else
			{
				if (p.bullet.CoolDownuse <= (int)Bullettimer1.getElapsedTime().asSeconds())
				{
					p.bullet.CoolDownBool = 1;
					use1 = 1;
				}
			}

			if (!p2.bullet.CoolDownBool && use2)
			{
				Bullettimer2.restart();
				use2 = 0;
			}
			else
			{
				if (p2.bullet.CoolDownuse <= (int)Bullettimer2.getElapsedTime().asSeconds())
				{
					p2.bullet.CoolDownBool = 1;
					use2 = 1;
				}
			}
			for (int i = 0; i < V.size(); i++)
			{
				Gravity_Powerups(V[i], blocks, roundnum);
				if (p.sprite.getGlobalBounds().intersects(V[i].getGlobalBounds()))
				{
					//chose 0->speed 2->health 1->scale
					if (V[i].getFillColor() == Color::Green)
					{
						PlayerPowerup[0].setSpeed(p.HeroType.Speed + 0.5);
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Red)
					{
						if (PlayerPowerup[0].getHealth() < 10)
						{
							PlayerPowerup[0].setHealth(PlayerPowerup[0].getHealth() + 1);
						}
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Blue)
					{
						PlayerPowerup[1].setSpeed(PlayerPowerup[1].getSpeed() - 3);
						PowersSprits.delet(i);
					}
					timer1 = 0;
				}
				else if (p2.sprite.getGlobalBounds().intersects(V[i].getGlobalBounds()))
				{
					//chose 0->speed 2->health 1->scale
					if (V[i].getFillColor() == Color::Green)
					{
						PlayerPowerup[1].setSpeed(3);
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Red)
					{

						if (PlayerPowerup[1].getHealth() < 10)
						{
							PlayerPowerup[1].setHealth(PlayerPowerup[1].getHealth() + 1);

						}
						PowersSprits.delet(i);
					}
					else if (V[i].getFillColor() == Color::Blue)
					{
						PlayerPowerup[0].setSpeed(PlayerPowerup[0].getSpeed() - 3);
						PowersSprits.delet(i);
					}
					timer2 = 0;
				}
			}
			if (!timer1)
			{
				clocktimer1.restart();
				timer1 = 1;
			}
			else if (!timer2)
			{
				clocktimer2.restart();
				timer2 = 1;
			}
			timerpowerup2 = (int)clocktimer2.getElapsedTime().asSeconds();
			timerpowerup1 = (int)clocktimer1.getElapsedTime().asSeconds();

			if (timerpowerup1 == 5)
			{
				PlayerPowerup[0].setSpeed(p.HeroType.Speed);
				PlayerPowerup[1].setSpeed(p2.HeroType.Speed);
			}
			if (timerpowerup2 == 5)
			{
				PlayerPowerup[1].setSpeed(p2.HeroType.Speed);
				PlayerPowerup[0].setSpeed(p.HeroType.Speed);
			}
			p.update(time);
			p2.update(time);

			if (PlayerPowerup[0].getHealth() <= 0)
			{
				p2score++;
				GameOver(window, p1score, p2score);
				return;
			}
			if (PlayerPowerup[1].getHealth() <= 0)
			{
				p1score++;
				GameOver(window, p1score, p2score);
				return;
			}

		}


		if (true)
		{
			window.clear();
			window.draw(background);
			for (int i = 0; i < p.V_Bullets.size(); i++)
			{
				window.draw(p.V_Bullets[i].BulletSprite);
			}
			for (int i = 0; i < p2.V_Bullets.size(); i++)
			{
				window.draw(p2.V_Bullets[i].BulletSprite);
			}
			for (int i = 0; i < 22; i++) {
				window.draw(blocks[i]);
			}
			stringstream sc, ss;
			sc << PlayerPowerup[0].getHealth(); //int to string
			sc >> s;
			ss << PlayerPowerup[1].getHealth(); //int to string
			ss >> s2;
			stringstream po, po2;
			po2 << p1score; //int to string
			po2 >> P1score;
			po << p2score; //int to string
			po >> P2score;
			textscore.setString(P2score + ":" + P1score);
			text.setString(player1 + ':' + s);//setting the string to player 1 
			text2.setString(player2 + ':' + s2);//setting the string to player 2
			window.draw(heart);
			window.draw(heart2);
			window.draw(text2);
			window.draw(text);
			window.draw(textscore);
			window.draw(weapon.GunPhoto);
			for (int i = 0; i < V.size(); i++)
				window.draw(V[i]);
			window.draw(p.sprite);
			window.draw(p2.sprite);
			for (int i = 0; i < 2; i++)
				window.draw(enemy2[i].shape);
			for (int i = 0; i < 6; i++)
				window.draw(enemy[i].shape);
			if (paused) {
				window.draw(r);
				window.draw(PauseSprite);
				pm.draw(window);
			}
			window.draw(finalround);
			window.display();

		}

	}
}




void His(RenderWindow& window) {

	View view;
	view.setCenter(960, 540);
	ifstream infile;
	infile.open("history.txt", ios::in);
	Font font1;
	font1.loadFromFile("RythmOfDeath.ttf");
	Text text[100];
	Texture HistoryTex;
	HistoryTex.loadFromFile("HistoryPH.PNG");
	Sprite HistorySprit;
	HistorySprit.setTexture(HistoryTex);
	HistorySprit.setPosition(300, 30);
	for (int i = 0; i < 12; i++) {
		text[i].setFont(font1);
		text[i].setCharacterSize(80);
		text[i].setFillColor(Color::Red);
	}
	vector<string> lines;
	string line;
	while (getline(infile, line, '*')) {
		lines.push_back(line);
	}
	for (int i = 0; i < lines.size(); i++) {
		text[i].setString(lines[i]);
		text[i].setPosition(50, 100 * i);

	}


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();

			}

			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				pagenum = 1000;
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{
				//view.move(0, -10);
				//HistorySprit.move(0, -10);
				if (text[0].getPosition().y <= 5)
					for (int i = 0; i < lines.size() + 10; i++) {
						text[i].move(0, 10);
					}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Down))
			{
				//view.move(0, 10);
				if (text[(lines.size()) - 10].getPosition().y >= 880)
					for (int i = 0; i < lines.size() + 10; i++) {
						text[i].move(0, -10);
					}
				//HistorySprit.move(0, 10);
			}
			cout << lines.size() << endl;
		}

		window.clear();
		window.draw(HistorySprit);
		for (int i = 0; i < lines.size() + 10; i++) {
			window.draw(text[i]);
		}
		window.display();
	}




}

void OptionsWin(RenderWindow& window)
{
	int choice = 1;

	Texture R, L, O1, O2, O3, OBG, AMGname, Escap;
	R.loadFromFile("Right.PNG");
	L.loadFromFile("Left.PNG");
	O1.loadFromFile("Option1.PNG");
	O2.loadFromFile("Option2.PNG");
	O3.loadFromFile("Option3.PNG");
	OBG.loadFromFile("OptionBG.PNG");
	AMGname.loadFromFile("AMG.PNG");
	Escap.loadFromFile("Esc.PNG");
	//choice:
	//option1 -> 1 , option2 -> 2 , option3 -> 3 , AMG -> 4


	Sprite right, left, option1, option2, option3, optionBG, AMG, Esc;
	right.setTexture(R);
	left.setTexture(L);
	option1.setTexture(O1);
	option2.setTexture(O2);
	option3.setTexture(O3);
	optionBG.setTexture(OBG);
	AMG.setTexture(AMGname);
	Esc.setTexture(Escap);

	//sacling 
	option1.setScale(0.5, 0.5);
	option2.setScale(0.5, 0.5);
	option3.setScale(0.5, 0.5);
	AMG.setScale(0.5, 0.5);
	right.setScale(0.3, 0.3);
	left.setScale(0.3, 0.3);
	Esc.setScale(0.3, 0.3);
	option1.setOrigin(option1.getLocalBounds().width / 2, option1.getLocalBounds().height / 2);
	option1.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	option2.setOrigin(option2.getLocalBounds().width / 2, (option2.getLocalBounds().height / 2) + 150);
	option2.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	option3.setOrigin(option3.getLocalBounds().width / 2, option3.getLocalBounds().height / 2);
	option3.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	optionBG.setOrigin(optionBG.getLocalBounds().width / 2, optionBG.getLocalBounds().height / 2);
	optionBG.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	AMG.setOrigin(AMG.getLocalBounds().width / 2, AMG.getLocalBounds().height / 2);
	AMG.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	right.setPosition(1720, 950);
	left.setPosition(100, 950);
	Esc.setPosition(1770, 50);

	/*Text Enter;
	Text Exit;
	Enter.setString("  Press Enter to go to main menu...");
	Enter.setPosition(630, 560);
	Enter.setCharacterSize(20);
	Enter.setFont(font);
	Enter.setFillColor(Color::Red);
	Exit.setString(" Press Esc to Exit Night Fight....(T_T)");
	Exit.setPosition(580, 600);
	Exit.setCharacterSize(20);
	Exit.setFont(font);
	Exit.setFillColor(Color::Red);*/
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
				soundAfterEnter.play();
				pagenum = 1000;
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				if (choice < 4)
					choice++;
				else
					choice = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				if (choice > 1)
					choice--;
				else
					choice = 4;
			}
		}


		window.clear();
		window.draw(optionBG);
		if (choice == 1)
			window.draw(option1);
		if (choice == 2)
			window.draw(option2);
		if (choice == 3)
			window.draw(option3);
		if (choice == 4)
			window.draw(AMG);
		/*window.draw(Enter);
		window.draw(Exit);*/
		window.draw(right);
		window.draw(left);
		window.draw(Esc);
		window.display();

	}
}

void GameOver(RenderWindow& window, int p1score, int p2score)
{

	Texture WinnerTex;
	Sprite WinnerSprit;

	WinnerTex.loadFromFile("WinnerTex.png");
	WinnerSprit.setTexture(WinnerTex);
	Text text;
	if (p1score > p2score) {
		text.setString(player1);
		//text.setOrigin(960, 422);
		text.setPosition(880, 350);
		text.setCharacterSize(100);
		text.setFont(font);
		text.setFillColor(Color::White);
	}
	else {
		text.setString(player2);
		//text.setOrigin(960, 422);
		text.setPosition(880, 350);
		text.setCharacterSize(100);
		text.setFont(font);
		text.setFillColor(Color::White);
	}

	if (p1score >= 2)
		soundplayer1wins.play();
	else
		soundplayer2wins.play();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
				soundAfterEnter.play();
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				soundAfterEnter.play();
				pagenum = 1000;
				return;
			}
		}
		window.clear();
		window.draw(WinnerSprit);
		window.draw(text);
		window.display();
	}
}

void UpdateHeroType(player& p, player& p2)
{
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			if (HeroTypeChoice[i] == 1) // Fighter
			{
				p.HeroType.Speed = 2.4;
				p.HeroType.Health = 15;
			}
			else if (HeroTypeChoice[i] == 3) // Assassin
			{
				p.HeroType.Speed = 2.7;
				p.HeroType.Health = 10;
			}
			else if (HeroTypeChoice[i] == 2) // Tank
			{
				p.HeroType.Speed = 2;
				p.HeroType.Health = 20;
			}
		}
		else
		{
			if (HeroTypeChoice[i] == 1) // Fighter
			{
				p2.HeroType.Speed = 2.4;
				p2.HeroType.Health = 15;
			}
			else if (HeroTypeChoice[i] == 3) // Assassin
			{
				p2.HeroType.Speed = 2.7;
				p2.HeroType.Health = 10;
			}
			else if (HeroTypeChoice[i] == 2) // Tank
			{
				p2.HeroType.Speed = 2;
				p2.HeroType.Health = 20;
			}
		}
	}
}

void p1(RenderWindow& window) {
	SoundBuffer ks;
	soundPlayer1.play();
	ks.loadFromFile("keyboard.wav");
	Sound keysound;
	keysound.setBuffer(ks);
	Sprite type;
	type.setTexture(types_text[3]);
	if (!player1.empty())
		player1.clear();
	font.loadFromFile("RythmOfDeath.ttf");
	Text txt2;
	P1LogoSprit.setPosition(980, 70);

	txt2.setFont(font);
	txt2.setCharacterSize(100);
	txt2.setPosition(100, 220);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::TextEntered) {
				if (!Keyboard::isKeyPressed(Keyboard::Escape))
				{
					player1 += static_cast<char>(event.text.unicode);
					keysound.play();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && player1.size() > 0) {
				player1.resize(player1.size() - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && player1.size() > 1 && CIPlCT) {
				soundAfterEnter.play();
				pagenum = 13;//choose1
				return;

			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) && CIPlCT) {
				soundAfterEnter.play();
				pagenum = 1000;
				return;
			}
			if (event.type == Event::KeyReleased) {
				CIPlCT = 1;
			}
		}


		txt2.setString(player1);
		window.clear();
		window.draw(type);
		window.draw(txt2);
		window.draw(P1LogoSprit);

		window.display();
	}

}
void p2(RenderWindow& window) {
	SoundBuffer ks;
	soundPlayer2.play();
	ks.loadFromFile("keyboard.wav");
	Sound keysound;
	keysound.setBuffer(ks);
	Sprite type;
	type.setTexture(types_text[3]);
	if (!player2.empty())
		player2.clear();
	font.loadFromFile("RythmOfDeath.ttf");

	Text txt2;
	txt2.setCharacterSize(100);
	txt2.setPosition(100, 220);
	txt2.setFont(font);
	P2LogoSprit.setPosition(980, 70);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::TextEntered) {
				if (!Keyboard::isKeyPressed(Keyboard::Escape))
				{
					player2 += static_cast<char>(event.text.unicode);
					keysound.play();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && player2.size() > 1) {
				player2.resize(player2.size() - 1);
			}

			if (Keyboard::isKeyPressed(Keyboard::Return) && player2.size() > 1 && CIPlCT) {
				soundAfterEnter.play();
				pagenum = 14;//choose2
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) && CIPlCT) {
				soundAfterEnter.play();
				pagenum = 13;
				return;
			}
			if (event.type == Event::KeyReleased) {
				CIPlCT = 1;
			}
		}

		txt2.setString(player2);
		window.clear();
		window.draw(type);
		window.draw(txt2);
		window.draw(P2LogoSprit);
		window.display();
	}

}
void choose1(RenderWindow& window) {

	//Fighter Informations
	Fsprit.setTexture(Ftex);
	Fsprit.setPosition(-300, 190);

	//Tank Informations
	Tsprit.setTexture(Ttex);
	Tsprit.setPosition(-300, 190);

	//Assassin Informations
	Asprit.setTexture(Atex);
	Asprit.setPosition(-300, 190);

	P1LogoSprit.setPosition(770, 180);

	Text txt2;
	txt2.setCharacterSize(160);
	txt2.setPosition(550, 8);
	txt2.setFont(font);
	txt2.setString(player1);
	SoundBuffer buffer3;
	buffer3.loadFromFile("select.wav");
	Sound sound3;
	sound3.setBuffer(buffer3);
	Sprite types[3];
	//bool CIPlCT = 0; // cheak if the player choose anything.
	for (int i = 0; i < 3; i++) {
		types[i].setTexture(types_text[i]);
	}
	int type = 1;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (type < 3) {
					sound3.play();
					type++;
				}
				//CIPlCT = 1;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (type > 1) {
					sound3.play();
					type--;
				}
				//CIPlCT = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && CIPlCT) {
				soundAfterEnter.play();
				pagenum = 6;
				return;
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape) && CIPlCT) {
				soundAfterEnter.play();
				pagenum = 0;
				return;
			}
			if (event.type == Event::KeyReleased) {
				CIPlCT = 1;
			}


		}
		window.clear();
		if (type == 1) {
			Asprit.setPosition(-300, 190);
			Tsprit.setPosition(-300, 190);
			window.draw(types[0]);
			window.draw(Fsprit);
			if (Fsprit.getPosition().x <= 20)
			{
				Fsprit.move(10, 0);
			}

		}
		if (type == 2) {
			Fsprit.setPosition(-300, 190);
			Asprit.setPosition(-300, 190);
			window.draw(types[1]);
			window.draw(Tsprit);
			if (Tsprit.getPosition().x <= 20)
			{
				Tsprit.move(10, 0);
			}
		}
		if (type == 3) {
			Fsprit.setPosition(-300, 190);
			Tsprit.setPosition(-300, 190);
			window.draw(types[2]);
			window.draw(Asprit);
			if (Asprit.getPosition().x <= 20)
			{
				Asprit.move(10, 0);
			}
		}
		window.draw(txt2);
		window.draw(P1LogoSprit);
		window.display();
		HeroTypeChoice[0] = type;
	}
}
void choose2(RenderWindow& window) {
	Text txt2;
	txt2.setCharacterSize(160);
	txt2.setPosition(550, 8);
	txt2.setFont(font);
	txt2.setString(player2);

	//Fighter Informations
	Fsprit.setTexture(Ftex);
	Fsprit.setPosition(-300, 190);

	//Tank Informations
	Tsprit.setTexture(Ttex);
	Tsprit.setPosition(-300, 190);

	//Assassin Informations
	Asprit.setTexture(Atex);
	Asprit.setPosition(-300, 190);

	P2LogoSprit.setPosition(770, 180);

	SoundBuffer buffer3;
	buffer3.loadFromFile("select.wav");
	Sound sound3;
	sound3.setBuffer(buffer3);
	//bool CIPlCT = 0; // cheak if the player choose anything.
	Sprite types[3];
	for (int i = 0; i < 3; i++) {
		types[i].setTexture(types_text[i]);
	}
	int type = 1;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (type < 3) {
					sound3.play();
					type++;
				}
				CIPlCT = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (type > 1) {
					sound3.play();
					type--;
				}
				CIPlCT = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Return) && CIPlCT) {
				soundAfterEnter.play();
				pagenum = 10;
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) && CIPlCT) {
				soundAfterEnter.play();
				pagenum = 6;
				return;
			}
			if (event.type == Event::KeyReleased) {
				CIPlCT = 1;
			}

		}
		window.clear();
		float xF, yF, xA, yA, xT, yT;
		if (type == 1) {
			Asprit.setPosition(-300, 190);
			Tsprit.setPosition(-300, 190);
			window.draw(types[0]);
			window.draw(Fsprit);
			if (Fsprit.getPosition().x <= 20)
			{
				Fsprit.move(10, 0);
			}

		}
		if (type == 2) {
			Fsprit.setPosition(-300, 190);
			Asprit.setPosition(-300, 190);
			window.draw(types[1]);
			window.draw(Tsprit);
			if (Tsprit.getPosition().x <= 20)
			{
				Tsprit.move(10, 0);
			}
		}
		if (type == 3) {
			Fsprit.setPosition(-300, 190);
			Tsprit.setPosition(-300, 190);
			window.draw(types[2]);
			window.draw(Asprit);
			if (Asprit.getPosition().x <= 20)
			{
				Asprit.move(10, 0);
			}
		}
		window.draw(txt2);
		window.draw(P2LogoSprit);
		window.display();

		HeroTypeChoice[1] = type;
	}
}
void block(Sprite blocks[]) {
	blocks[0].setPosition(1400, 640);
	blocks[0].setScale(1, 0.5);
	blocks[1].setPosition(1100, 500);
	blocks[1].setScale(1, 0.5);
	blocks[2].setPosition(340, 380);
	blocks[2].setScale(1, 0.5);
	blocks[3].setPosition(-10, 500);
	blocks[3].setScale(1, 0.5);
	blocks[4].setPosition(1430, 370);
	blocks[4].setScale(1, 0.5);
	blocks[5].setPosition(650, 255);
	blocks[5].setScale(1, 0.5);
	blocks[6].setPosition(510, 780);
	blocks[6].setScale(1, 0.5);
	blocks[7].setPosition(-800, 1040);
	blocks[7].setScale(50, 0.5);
	blocks[8].setPosition(850, 910);
	blocks[8].setScale(1, 0.5);
	blocks[9].setPosition(1750, 500);
	blocks[9].setScale(0.5, 0.5);
	blocks[10].setPosition(340, 640);
	blocks[10].setScale(0.5, 0.5);
	blocks[11].setPosition(680, 590);
	blocks[11].setScale(1, 0.5);
	blocks[12].setPosition(1200, 780);
	blocks[12].setScale(0.5, 0.5);
	blocks[13].setPosition(1050, 255);
	blocks[13].setScale(1, 0.5);
}
void blockround2(Sprite blocks[]) {
	blocks[0].setPosition(1660, 200);
	blocks[0].setScale(1, 0.5);
	blocks[1].setPosition(510, 950);
	blocks[1].setScale(0.5, 0.5);
	blocks[2].setPosition(1330, 200);
	blocks[2].setScale(0.5, 0.5);
	blocks[3].setPosition(0, 200);
	blocks[3].setScale(1, 0.5);
	blocks[4].setPosition(0, 950);
	blocks[4].setScale(1, 0.5);
	blocks[5].setPosition(680, 300);
	blocks[5].setScale(0.5, 0.5);
	blocks[6].setPosition(325, 300);
	blocks[6].setScale(0.5, 0.5);
	blocks[7].setPosition(0, 1040);
	blocks[7].setScale(1, 0.5);
	blocks[8].setPosition(850, 100);
	blocks[8].setScale(1, 0.5);
	blocks[9].setPosition(1155, 910);
	blocks[9].setScale(0.5, 0.5);
	blocks[10].setPosition(320, 910);
	blocks[10].setScale(0.5, 0.5);
	blocks[11].setPosition(1660, 950);
	blocks[11].setScale(1, 0.5);
	blocks[12].setPosition(680, 910);
	blocks[12].setScale(0.5, 0.5);
	blocks[13].setPosition(1150, 300);
	blocks[13].setScale(0.5, 0.5);
	blocks[14].setPosition(1500, 300);
	blocks[14].setScale(0.5, 0.5);
	blocks[15].setPosition(1500, 910);
	blocks[15].setScale(0.5, 0.5);

}
void blockround3(Sprite blocks[]) {
	blocks[0].setPosition(700, 650);
	blocks[0].setScale(0.5, 0.5);
	blocks[1].setPosition(460, 780);
	blocks[1].setScale(0.5, 0.5);
	blocks[2].setPosition(1330, 280);
	blocks[2].setScale(0.5, 0.5);
	blocks[3].setPosition(0, 280);
	blocks[3].setScale(0.5, 0.5);
	blocks[4].setPosition(1800, 280);
	blocks[4].setScale(0.5, 0.5);
	blocks[5].setPosition(700, 400);
	blocks[5].setScale(0.5, 0.5);
	blocks[6].setPosition(225, 400);
	blocks[6].setScale(0.5, 0.5);
	blocks[7].setPosition(0, 1040); // the large block.
	blocks[7].setScale(1, 0.5);
	blocks[8].setPosition(460, 280);
	blocks[8].setScale(0.5, 0.5);
	blocks[9].setPosition(1050, 910);
	blocks[9].setScale(0.5, 0.5);
	blocks[10].setPosition(225, 910);
	blocks[10].setScale(0.5, 0.5);
	blocks[11].setPosition(900, 280);
	blocks[11].setScale(0.5, 0.5);
	blocks[12].setPosition(700, 910);
	blocks[12].setScale(0.5, 0.5);
	blocks[13].setPosition(1050, 400);
	blocks[13].setScale(0.5, 0.5);
	blocks[14].setPosition(1600, 400);
	blocks[14].setScale(0.5, 0.5);
	blocks[15].setPosition(1600, 910);
	blocks[15].setScale(0.5, 0.5);
	blocks[16].setPosition(1600, 650);
	blocks[16].setScale(0.5, 0.5);
	blocks[17].setPosition(1050, 650);
	blocks[17].setScale(0.5, 0.5);
	blocks[18].setPosition(1330, 520);
	blocks[18].setScale(0.5, 0.5);
	blocks[19].setPosition(1330, 780);
	blocks[19].setScale(0.5, 0.5);
	blocks[20].setPosition(225, 650);
	blocks[20].setScale(0.5, 0.5);
	blocks[21].setPosition(460, 520);
	blocks[21].setScale(0.5, 0.5);
}