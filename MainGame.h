#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Platform.h"
#include "Player.h"
using namespace sf;
/*
	Wrapper Class for the game engine
*/
class Game {
private:
	//Variables
	int limitHeight = 250;
	float speed;
	//Window
	RenderWindow* window;
	Event ev;
	VideoMode videoMode;
	//RectangleShape gameoverBackground(Vector2f(500, 700));
	//Objects
	Font font;
	Texture background;
	Texture tiles;
	Texture tiles_one;
	Platform* plat;
	OneTimePlatform* plat_one;
	Player p;
	Texture player;
	//Private functions
	void initVariables();
	void initWindow();
	void loadImages();
	void loadPlatform();
	void gameMenu();
	void updatePlayer();
	void gameOver();
	void reset();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();
	
	//Accessors
	const bool running() const;

	//functions
	void start();
	void pollEvents();
	void update();
	void render();
	float getSpeed();
	void setSpeed(float s);
};