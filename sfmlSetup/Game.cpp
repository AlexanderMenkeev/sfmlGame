#include "Game.h"
//Init everything
void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(900, 800), "Space shooter", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	this->textures["Rocket"] = new sf::Texture();
	this->textures["Rocket"]->loadFromFile("Textures/missile.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR: Failed to load font" << std::endl;

	//Init point text
	this->pointText.setPosition(670.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(30);
	this->pointText.setFillColor(sf::Color::White);

	//Init gameOverText
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height);

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 30.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
	   
	//Init restartButton
	if (!this->restartButtonTex.loadFromFile("Textures/restart1.png"))
	{
		std::cout << "ERROR: COULD NOT LOAD RESTART BUTTON TEXTURE" << std::endl;
	}
	this->restartButton.setTexture(restartButtonTex);
	this->restartButton.setScale(0.3f, 0.3f);
	this->restartButton.setPosition(
		this->window->getSize().x / 2.f - this->restartButton.getGlobalBounds().width / 2,
		this->window->getSize().y / 2.f + this->restartButton.getGlobalBounds().height);
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background1.jpg"))
	{
		std::cout << "ERROR: COULD NOT LOAD BACKGROUND TEXTURE" << std::endl;
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//Constructor/Destructor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}

	//Delete rockets
	for (auto *i : this->rockets)
	{
		delete i;
	}

	//Delete enemies
	for (auto *i : this->enemies)
	{
		delete i;
	}
}



//Functions
bool Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->player->getHp() > 0)
			this->update();

		this->render();

		if (sf::Mouse::getPosition(*window).x >= this->restartButton.getGlobalBounds().left && 
			sf::Mouse::getPosition(*window).x <= this->restartButton.getGlobalBounds().width / 2 + this->window->getSize().x / 2 &&
			sf::Mouse::getPosition(*window).y >= this->restartButton.getGlobalBounds().top &&
			sf::Mouse::getPosition(*window).y <= this->restartButton.getGlobalBounds().top + this->restartButton.getGlobalBounds().height &&
			sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			this->player->getHp() == 0)
	
			return true;
		
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	//Shooting
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f - 4.f,
				this->player->getPos().y,
				0.f,
				-1.f,
				5.f,
				5
			)
		);
	}

	//Launch missiles
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->player->canLaunchMissile())
	{
		//left rocket
		this->rockets.push_back(
			new Rocket(
				this->textures["Rocket"],
				this->player->getPos().x,
				this->player->getPos().y,
				0.f,
				-1.f,
				6.f,
				20
			)
		);

		//right rocket
		this->rockets.push_back(
			new Rocket(
				this->textures["Rocket"],
				this->player->getPos().x + this->player->getBounds().width / 1.2,
				this->player->getPos().y,
				0.f,
				-1.f,
				6.f,
				20
			)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Score: " << this->points;

	this->pointText.setString(ss.str());
	
	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));

	
}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}

		++counter;
	}
}

void Game::updateMissiles()
{
	//unsigned counter = 0;
	for (auto *rocket : this->rockets)
	{
		rocket->update();

		//Bullet culling (top of screen)
		//if (rocket->getBounds().top + rocket->getBounds().height < 0.f)
		//{
		//	//Delete rocket
		//	delete this->rockets.at(counter);
		//	delete this->rockets.at(counter+1);
		//	this->rockets.erase(this->rockets.begin() + counter);
		//	this->rockets.erase(this->rockets.begin() + counter + 1);
		//}
		//++counter;
	}
}

void Game::updateEnemies()
{
	//Spawn enemies
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		float x, y;
		x = rand() % this->window->getSize().x - 20.f; 
		y = -100.f;
		this->enemies.push_back(new Enemy(x, y));

		this->spawnTimer = 0.f;
	}

	
	unsigned counter = 0;
	for (auto *enemy : this->enemies)
	{
		enemy->update();
		
		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				enemies[i]->loseHp(bullets[k]->getDamage());

				if (enemies[i]->getHP() == 0)
				{
					this->points += this->enemies[i]->getPoints();
					bullets[k]->loseDamage(enemies[i]->getHpMax());
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);

					enemy_deleted = true;
				}
				else
				{
					delete this->bullets[k];
					this->bullets.erase(this->bullets.begin() + k);
				}
				
			}
		}
	}

	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->rockets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->rockets[k]->getBounds()))
			{
				enemies[i]->loseHp(rockets[k]->getDamage());

				if (enemies[i]->getHP() == 0)
				{
					this->points += this->enemies[i]->getPoints();
					rockets[k]->loseDamage(enemies[i]->getHpMax());
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);

					enemy_deleted = true;
				}
				else
				{
					delete this->rockets[k];
					this->rockets.erase(this->rockets.begin() + k);
				}

			}
		}
	}

}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateMissiles();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto *rocket : this->rockets)
	{
		rocket->render(this->window);
	}

	for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
	{	
		this->window->draw(this->gameOverText);
		this->window->draw(this->restartButton);
	}
	this->window->display();
}
