#include "egg.hpp"
#include "wolf.hpp"

Egg::Egg(int chicken_) : chicken_(chicken_), position_(0)
{
  if (chicken_ == 0)
  {
    eggXY_[0] = {55, 129};
    eggXY_[1] = {71, 139};
    eggXY_[2] = {88, 149};
    eggXY_[3] = {102, 158};
    eggXY_[4] = {117, 167};
    eggSpin_[0] = {58};
    eggSpin_[1] = {108};
    eggSpin_[2] = {-167};
    eggSpin_[3] = {-74};
    eggSpin_[4] = {0};
    egg_.rotate(eggSpin_[0]);
  }
  else if (chicken_ == 1)
  {
    eggXY_[0] = {513, 129};
    eggXY_[1] = {497, 138};
    eggXY_[2] = {481, 150};
    eggXY_[3] = {465, 157};
    eggXY_[4] = {452, 168};
    eggSpin_[0] = {-10};
    eggSpin_[1] = {-46};
    eggSpin_[2] = {-128};
    eggSpin_[3] = {140};
    eggSpin_[4] = {58};
    egg_.rotate(eggSpin_[0]);
  }
  else if (chicken_ == 2)
  {
    eggXY_[0] = {53, 203};
    eggXY_[1] = {70, 212};
    eggXY_[2] = {86, 222};
    eggXY_[3] = {103, 231};
    eggXY_[4] = {115, 242};
    eggSpin_[0] = {65};
    eggSpin_[1] = {102};
    eggSpin_[2] = {154};
    eggSpin_[3] = {-93};
    eggSpin_[4] = {-2};
    egg_.rotate(eggSpin_[0]);
  }
  else if (chicken_ == 3)
  {
    eggXY_[0] = {513, 203};
    eggXY_[1] = {498, 212};
    eggXY_[2] = {481, 223};
    eggXY_[3] = {465, 231};
    eggXY_[4] = {453, 243};
    eggSpin_[0] = {0};
    eggSpin_[1] = {-56};
    eggSpin_[2] = {-96};
    eggSpin_[3] = {152};
    eggSpin_[4] = {58};
    egg_.rotate(eggSpin_[0]);
  }

  eggTexture_.loadFromFile("img/egg/egg.png");
  egg_.setTexture(eggTexture_);
  egg_.setOrigin(7, 7);


}

void Egg::move()
{
  position_ += 1;
  egg_.setRotation(eggSpin_[position_]);
}

bool Egg::catchCheck(Wolf & wolf_)
{
  if (wolf_.getUp() == true)
    if (wolf_.getRight() == false) return (chicken_ == 0);
    else return (chicken_ == 1);
  else
    if (wolf_.getRight() == false) return (chicken_ == 2);
    else return (chicken_ == 3);
}

int Egg::getPosition()
{
  return position_;
}

void Egg::egg_setPosition(int x, int y)
{
 egg_.setPosition(x,y);
}

sf::Sprite Egg::getEggSprite()
{
  return egg_;
}

Point Egg::getEggXY(int i)
{
  return eggXY_[i];
}

