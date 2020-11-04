#include "Player.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Pictures/Player1.png"))
		printf("EROOR::Picture player can't be load!");
}

void Player::initSpite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(1.f, 1.f);

	this->currentFrame = sf::IntRect(0, 0, 100, 100);

	this->sprite.setPosition(900, 690);

	this->sprite.setTextureRect(this->currentFrame);
}

void Player::initAnimation()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->accelerationJump = 5.f;
	this->drag = 0.9f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSpite();
	this->initAnimation();
	this->initPhysics();

	this->movementSpeed = 5.f;
}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return animationSwitch;
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);

	//acceleration
	this->velocity.x += dirX * this->acceleration;
	this->velocity.y += dirY * this->accelerationJump;

	//limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
	if (std::abs(this->velocity.y) > this->velocityMax)
	{
		this->velocity.y = this->velocityMax * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimation();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget & target)
{
	target.draw(this->sprite);

	sf::CircleShape Circ;
	Circ.setFillColor(sf::Color::Red);
	Circ.setRadius(3.f);
	Circ.setPosition(this->sprite.getPosition());

	target.draw(Circ);
}

void Player::updatePhysics()
{
	//gravity
	this->velocity.y += (1.0 * this->gravity);
	if (std::abs(this->velocity.x) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
		this->jumping = 0;
	}

	//decceleration
	this->velocity *= (this->drag);

	//limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
	{
		this->velocity.y = 0.f;
		this->jumping = 0;
	}

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	//Keyboard
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		this->animState = PLAYER_ANIMATION_STATES::KICK;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->jumping == 0)
	{
		this->move(0.f, -3.f);
		this->jumping = 1;
	}
	/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->sprite.move(0.f, 1.f);
	}*/
}

void Player::updateAnimation()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left >= 200.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT || this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 100.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left >= 200.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::KICK)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f)
		{
			this->currentFrame.top = 200.f;
			this->currentFrame.left += 100.f;
			if (this->currentFrame.left >= 400.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
		this->animationTimer.restart();
}
