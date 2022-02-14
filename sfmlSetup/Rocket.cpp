#include "Rocket.h"

Rocket::Rocket()
{
}
Rocket::Rocket(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, int damage)
{
		this->shape.setTexture(*texture);
		this->shape.scale(0.04f, 0.04f);
		this->shape.setPosition(pos_x, pos_y);
		this->direction.x = dir_x;
		this->direction.y = dir_y;
		this->movementSpeed = movement_speed;
		this->damage = damage;
}
Rocket::~Rocket()
{
	
}

const sf::FloatRect Rocket::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Rocket::getDamage() const
{
	return this->damage;
}

void Rocket::loseDamage(const int value)
{
	this->damage -= value;
	if (this->damage < 0)
		this->damage = 0;
}

void Rocket::update()
{
	this->shape.move(this->movementSpeed * this->direction);
}

void Rocket::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}
