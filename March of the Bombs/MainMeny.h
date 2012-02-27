#pragma once

#include "Screen.h"

#include "KeyboardEvent.h"

class Game;

class MainMeny :
	public Screen
{

private:
	std::vector<Button> buttons;
	std::vector<SimpleImage> Backgrounds;
	Screen::ptr nextScreen;
	boost::shared_ptr<Game> game;

public:
	MainMeny(void);
	~MainMeny(void);
	void update(float deltaTime);
	void draw(Graphics::ptr graphics);
	Screen::ptr getNextScreen();

	void createButtons();
	void createBackground();
	void KeyboardEventMethod(KeyboardEvent* keyEvent);
};