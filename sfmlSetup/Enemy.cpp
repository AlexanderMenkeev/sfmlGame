#include "Enemy.h"


void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; //min = 3 max = 10
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount / 3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5 + 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
}
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}
Enemy::~Enemy()
{

}

//Getters
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}
const int& Enemy::getPoints() const
{
	return this->points;
}
const int& Enemy::getHP() const
{
	return this->hp;
}
const int& Enemy::getHpMax() const
{
	return this->hpMax;
}
const float & Enemy::getSpeed() const
{
	return this->speed;
}
const int& Enemy::getDamage() const
{
	return this->damage;
}


//Functions
void Enemy::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}
void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}