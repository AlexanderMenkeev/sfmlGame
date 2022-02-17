#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 3.f;

	this->missileCooldownMax = 50.f;
	this->missileCooldown = this->missileCooldownMax;

	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 1;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/aircraft.png"))
	{
		std::cout << "Could not load player texture file." << std::endl;
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(0.06f, 0.06f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->setPosition(450.f, 700.f);
}

Player::~Player()
{

}

//Getters
const sf::Vector2f & Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int & Player::getHp() const
{
	return this->hp;
}

const int & Player::getHpMax() const
{
	return this->hpMax;
}

//Setters
void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

const bool Player::canLaunchMissile()
{
	if (this->missileCooldown >= this->missileCooldownMax)
	{
		this->missileCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;

	if (this->missileCooldown < this->missileCooldownMax)
		this->missileCooldown += 0.5f;
}

//Functions
void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
