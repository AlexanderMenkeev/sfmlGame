#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>
#include<iostream>

class Bullet
{
private:
	int damage;
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed,int damage);
	virtual ~Bullet();

	//Getter
	const int& getDamage() const;
	const sf::FloatRect getBounds() const;

	void loseDamage(const int value);
	void update();
	void render(sf::RenderTarget* target);
};

#endif