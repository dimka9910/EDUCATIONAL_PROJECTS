#ifndef EGG_HPP
#define EGG_HPP
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "wolf.hpp"

struct Point
{
  int x;
  int y;
};

class Egg
{
public:
  Egg(int chicken_);
  Point getEggXY(int i);
  sf::Sprite getEggSprite();
  int getPosition();
  bool catchCheck(Wolf & wolf_);
  void egg_setPosition(int x, int y);
  void move();

private:
  sf::Sprite egg_;
  sf::Texture eggTexture_;
  Point eggXY_[5];
  int chicken_;
  int position_;
  int eggSpin_[5];

};

#endif // EGG_H
