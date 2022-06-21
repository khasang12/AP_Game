#include "MainGame.h"
#include "Player.h"
#include "Platform.h"
#include <time.h>
#include <SFML\Audio.hpp>
#include <random>
#include <chrono>

#define PLAT 15
#define PLAT_ONE 5
void Game::initVariables()
{
	this->window = nullptr;
	this->p = Player();
	this->plat = new Platform[PLAT];
	this->plat_one = new OneTimePlatform[PLAT_ONE];
	font.loadFromFile("Fonts/OpenSans-Light.ttf");
}

void Game::initWindow()
{
	this->videoMode.height = 850;
	this->videoMode.width = 532;

	this->window = new RenderWindow(this->videoMode, "Doodle Jump", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::loadImages()
{
	this->background.loadFromFile("images/background.png");
	this->player.loadFromFile("images/doodle_1_70.png");
	this->tiles.loadFromFile("images/platform.png");
	this->tiles_one.loadFromFile("images/platform_white.png");

	auto image = sf::Image{};
	if (!image.loadFromFile("images/doodle_40.png"))
	{
		std::cout << "Error loading icon";
	}
	this->window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

void Game::loadPlatform()
{
	std::default_random_engine e(time(0));
	std::uniform_int_distribution<unsigned> x(0, this->videoMode.width-40);
	std::uniform_int_distribution<unsigned> y(100, this->videoMode.height);

	for (int i = 0; i < PLAT; i++) {
		plat[i].setCenterX(x(e));
		plat[i].setCenterY(y(e));
	}
	for (int j = 0; j < PLAT_ONE; j++) {
		plat_one[j].setCenterX(x(e));
		plat_one[j].setCenterY(y(e));
	}
}

void Game::gameMenu()
{
	Text text1, text2;
	text1.setFont(font);
	text2.setFont(font);

	text1.setCharacterSize(50);
	text2.setCharacterSize(20);

	text1.setFillColor(Color::Red);
	text2.setFillColor(Color::Black);
	text1.setStyle(Text::Bold);
	text1.setString("  Simple Doodle Jump");
	text2.setString("Made by Sang Kha - 2022");
	text1.setPosition(10, this->videoMode.width / 2);
	text2.setPosition(160, this->videoMode.width / 2 + 200);
	Sprite bg(this->background);
	while (this->running())
	{
		Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();
			if (event.key.code == Keyboard::Escape)
				this->window->close();
			if (event.key.code == Keyboard::Enter)
				this->start();
		}

		this->window->draw(bg);
		this->window->draw(text1); 
		this->window->draw(text2);
		this->window->display();
	}
}

void Game::updatePlayer()
{
	int step = 4;
	float acceleration = 0.35;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::uniform_int_distribution<unsigned> x(0, this->videoMode.width - 40);
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		int next = p.getX() + step;
		if (next > this->videoMode.width)
			p.setX(step);
		else
			p.setX(next);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		int next = p.getX() - step;
		if (next < -30)
			p.setX(this->videoMode.width + next);
		else
			p.setX(next);
	}
		
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->setSpeed(this->getSpeed() + acceleration);
		p.setScore(p.getScore() - 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->setSpeed(this->getSpeed() - acceleration);
		p.setScore(p.getScore() - 1);
	}

	this->setSpeed(this->getSpeed() + acceleration);
	p.setY(this->p.getY()+this->getSpeed());

	for (int i = 0; i < PLAT; i++) {
		float curSpeed = this->getSpeed();
		if ((p.getX() > plat[i].getCenter().x - 30) && (p.getX() < plat[i].getCenter().x - 30 + tiles.getSize().x)
			&& (p.getY() > plat[i].getCenter().y - 80) && (p.getY() < plat[i].getCenter().y - 70 + tiles.getSize().y)
			&& (this->getSpeed() > 0) && plat[i].getVisible() == true) {
			plat[i].actionAfterJumped(i);
			this->window->clear();
			if (curSpeed < 10) {
				this->setSpeed(-10);
			}
			else {
				this->setSpeed(curSpeed*-1);
			}
		}
	}
	for (int j = 0; j < PLAT_ONE; j++) {

		if ((p.getX() > plat_one[j].getCenter().x - 30) && (p.getX() < plat_one[j].getCenter().x - 30 + tiles_one.getSize().x)
			&& (p.getY() > plat_one[j].getCenter().y - 60) && (p.getY() < plat_one[j].getCenter().y - 60 + tiles_one.getSize().y)
			&& (this->getSpeed() > 0) && plat_one[j].getVisible() == true) {
			plat_one[j].actionAfterJumped(j);
			this->window->clear();
			float curSpeed = this->getSpeed();
			if (curSpeed < 10) {
				this->setSpeed(-10);
			}
			else {
				this->setSpeed(curSpeed * -1);
			}
		}
	}

	if (p.getY() < this->limitHeight) {
		for (int i = 0; i < PLAT; i++) {
			p.setY(this->limitHeight);
			plat[i].setCenterY(plat[i].getCenter().y - this->speed);

			if (plat[i].getCenter().y > this->videoMode.height) {
				plat[i].setVisible(true);
				plat[i].setCenterX(x(e));
				plat[i].setCenterY(0);
			}
		}
		for (int i = 0; i < PLAT_ONE; i++) {
			plat_one[i].setCenterY(plat_one[i].getCenter().y - this->speed);

			if (plat_one[i].getCenter().y > this->videoMode.height) {
				plat_one[i].setVisible(true);
				plat_one[i].setCenterX(x(e));
				plat_one[i].setCenterY(0);
			}
		}
		this->limitHeight = 100;
	}

	if (p.getY() == this->limitHeight && this->speed < -1.3) {
		p.setScore(p.getScore() + 1);
		this->window->clear();
	}

	if (p.getY() > this->videoMode.height - 20 || p.getScore() < 0) {
		this->gameOver();
		this->reset();
	}
}

void Game::gameOver()
{
	int score = this->p.getScore() > 0 ? this->p.getScore() : 0;
	Text text1, text2;
	text1.setFont(font);
	text2.setFont(font);


	text1.setCharacterSize(50);
	text2.setCharacterSize(20);

	text1.setFillColor(Color::Black);
	text2.setFillColor(Color::Red);
	text1.setStyle(Text::Bold);
	text1.setString("    Game Over\n    Score: "+to_string(score));
	text2.setString("Enter to Play Again");

	text1.setPosition(30, this->videoMode.width / 2);
	text2.setPosition(160, this->videoMode.width / 2 + 200);
	//this->window->clear();
	Sprite bg(this->background);
	while (this->running())
	{
		Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();
			if (event.key.code == Keyboard::Escape)
				this->window->close();
			if (event.key.code == Keyboard::Enter)
				return;
		}
			
		this->window->draw(bg);
		this->window->draw(text1);
		this->window->draw(text2);

		this->window->display();
	}
}

void Game::reset()
{
	this->window->clear();
	this->loadPlatform();
	p.setX(0);
	p.setY(250);
	p.setScore(0);
	this->limitHeight = 300;
	this->speed = 0;
	for (int j = 0; j < PLAT_ONE; j++) {
		plat_one[j].setVisible(true);
	}
	for (int i = 0; i < PLAT; i++) {
		plat[i].setVisible(true);
	}
}

// Constructors/ Destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->loadImages();
	this->loadPlatform();
	this->gameMenu();
}

Game::~Game()
{
	delete this->window;
	delete this->plat;
	delete this->plat_one;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::start()
{
	while (this->running()) {
		//Update
		this->update(); //Clear old frame

		//Render
		this->render(); //tell app that window is done drawing
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
	this->updatePlayer();
}

void Game::render()
{
	
	this->window->clear();
	// Draw game objects
	Sprite bg(this->background), pl(this->player);
	Sprite sp;
	this->window->draw(bg);
	Text textscore,highscore;
	textscore.setFont(font);
	textscore.setCharacterSize(20);
	textscore.setFillColor(Color::Black);
	textscore.setStyle(Text::Bold);
	textscore.setString("Score: " + to_string(p.getScore()));
	this->window->draw(textscore);

	for (int i = 0; i < PLAT; i++) {
		bool checkVisible = plat[i].getVisible();		
		if (checkVisible) {
			sp.setTexture(tiles);
			sp.setPosition(plat[i].getCenter().x, plat[i].getCenter().y);
			this->window->draw(sp);
		}

	}
	for (int i = 0; i < PLAT_ONE; i++) {
		bool checkVisible = plat_one[i].getVisible();
		if (checkVisible) {
			sp.setTexture(tiles_one);
			sp.setPosition(plat_one[i].getCenter().x, plat_one[i].getCenter().y);
			this->window->draw(sp);
		}
	}
	pl.setPosition(p.getX(), p.getY());
	this->window->draw(pl);
	this->window->display();
}

float Game::getSpeed()
{
	return this->speed;
}

void Game::setSpeed(float s)
{
	this->speed = s;
}
