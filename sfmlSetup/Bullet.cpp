#include "Bullet.h"

Bullet::Bullet()
{

}
Bullet::Bullet(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, int damage)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	this->damage = damage;
}
Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}
const int& Bullet::getDamage() const
{
	return this->damage;
}

void Bullet::loseDamage(const int value)
{
	this->damage -= value;
	if (this->damage < 0)
		this->damage = 0;
}
void Bullet::update()
{
	//Movement
	this->shape.move(this->movementSpeed * this->direction);
}
void Bullet::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}
