#ifndef WOLF_HPP
#define WOLF_HPP
#include <memory>
#include <SFML/Graphics.hpp>


struct Wolf
{
public:
  Wolf();
  int getScore();
  int getLose();
  bool getUp();
  bool getRight();
  void incrScore();
  void incrLose();
  void resetLose();
  void reset();
  void readVolkKey();
  sf::Sprite getVolkLR();
  sf::Sprite getBasket();

private:
  bool up_ = false;
  bool right_ = true;
  int score_;
  int lose_;

  sf::Sprite basket_[4];
  sf::Sprite volkL_;
  sf::Sprite volkR_;

  sf::Texture volkLTexture_;
  sf::Texture volkRTexture_;
  sf::Texture basketTexture_[4];
};

#endif
