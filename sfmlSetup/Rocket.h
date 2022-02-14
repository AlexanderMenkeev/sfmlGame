#ifndef ROCKET_H
#define ROCKET_h

#include<SFML/Graphics.hpp>

#pragma once
class Rocket
{
private:
	int damage;
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Rocket();
	Rocket(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, int damage);
	virtual ~Rocket();

	//Getter
	const sf::FloatRect getBounds() const;
	const int& getDamage() const;

	void loseDamage(const int value);

	void update();
	void render(sf::RenderTarget* target);
};
#endif