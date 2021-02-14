#include "wolf.hpp"



Wolf::Wolf()
{
  score_ = 0;
  lose_ = 0;

  volkLTexture_.loadFromFile("img/wolf/wolf-p-0.png");
  volkRTexture_.loadFromFile("img/wolf/wolf-p-1.png");
  basketTexture_[0].loadFromFile("img/basket/basket-p-0-1.png");
  basketTexture_[1].loadFromFile("img/basket/basket-p-1-1.png");
  basketTexture_[2].loadFromFile("img/basket/basket-p-0-0.png");
  basketTexture_[3].loadFromFile("img/basket/basket-p-1-0.png");

  volkL_.setTexture(volkLTexture_);
  volkR_.setTexture(volkRTexture_);
  for (int i = 0; i < 4; i++)
  {
    basket_[i].setTexture(basketTexture_[i]);
  }

  volkL_.setPosition(178, 164);
  volkR_.setPosition(295, 165);
  basket_[0].setPosition(125, 157);
  basket_[1].setPosition(367, 165);
  basket_[2].setPosition(123, 234);
  basket_[3].setPosition(359, 240);
}


void Wolf::reset()
{
  up_ = false;
  right_ = true;
  score_ = 0;
  lose_ = 0;
}

void Wolf::resetLose()
{
  lose_ = 0;
}



int Wolf::getScore()
{
 return score_;
}

int Wolf::getLose()
{
  return lose_;
}

void Wolf::incrScore()
{
  score_++;
}

void Wolf::incrLose()
{
  lose_++;
}

sf::Sprite Wolf::getBasket()
{
  return (right_) ? ((up_) ? basket_[1] : basket_[3]) : ((up_) ? basket_[0] : basket_[2]);
}

sf::Sprite Wolf::getVolkLR()
{
  return (right_) ? volkR_ : volkL_;
}

void Wolf::readVolkKey()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  right_=false;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) right_=true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) up_=true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) up_=false;
}

bool Wolf::getUp()
{
  return up_;
}

bool Wolf::getRight()
{
  return right_;
}

