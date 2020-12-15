#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define MAX_NUMBER 5

class GameEnd
{
private:
	//Font
	sf::Font Font;


	//Texture
	sf::Texture bgTexture;
	sf::Texture scoreTexture;
	sf::Texture goalTexture;

	//Sprite
	sf::Sprite bgSprite;
	sf::Sprite scoreSprite;
	sf::Sprite goalSprite;

	//Core
	void initText();
	void initMenu();
	void initBotton(float width, float height);

public:
	GameEnd(float width, float height);
	virtual ~GameEnd();

	void update(float width, float height);

	void render(sf::RenderWindow& target);

	//Text
	sf::Text menu[MAX_NUMBER];

	const sf::FloatRect	botton1() const;
	const sf::FloatRect botton2() const;
	const sf::FloatRect botton3() const;
	const sf::FloatRect botton4() const;
};