#include "game.hpp"

const int scoreBonus = 200;
const double delay = 1;
const int oX = 0;
const int oY = 0;

Game::Game()
{
  wait = 2;
  tickTimer_ = 0;
  tickDelay_ = delay;

  backGroundTexture_.loadFromFile("img/game-bg.jpg");
  numbersTexture_.loadFromFile("img/score/nums.png");
  numberEmptyTexture_.loadFromFile("img/score/num-bg.png");
  losePointTexture_.loadFromFile("img/loss/loss.png");
  restartTexture_.loadFromFile("img/restart.png");

  backGround_.setTexture(backGroundTexture_);
  restart_.setTexture(restartTexture_);
  lossPoint_.setTexture(losePointTexture_);
  lossPoint_.setTextureRect(sf::IntRect(0, 0, 38, 32));
  backGround_.setPosition(oX, oY);

  for (int i = 0; i < 10; i++) // НОМЕРА РЕЗУЛЬТАТА
  {
    num_[i].setTexture(numbersTexture_);
    num_[i].setTextureRect(sf::IntRect(i*31, 0, 31, 47));

  }
  num_[10].setTexture(numberEmptyTexture_);// ПУСТОЙ НОМЕР
}

void Game::eggGen(int Random)
{
  if (tickTimer_ > tickDelay_)
  {
    tickTimer_=0;
    wait--;
    for (auto i = eggVector_.begin(); i != eggVector_.end(); i++)
    {
      (*i)->move();
    }
    if (wait == 0)
    {
      wait = 3;
      eggVector_.emplace_back(new Egg(Random));
    }
  }
}

void Game::wolfeResultsHandler(Wolf & wolf_)
{
  for (auto i = eggVector_.begin(); i != eggVector_.end();)
  {
    if ((*i)->getPosition() > 4)
    {
      if ((*i)->catchCheck(wolf_))
      {
        wolf_.incrScore();
        tickDelay_ += -0.0005; // отвечает за ускорение
        if (wolf_.getScore() % scoreBonus == 0) wolf_.resetLose(); //обнуление промахов
      }
      else wolf_.incrLose();
      eggVector_.erase(i);
    } else ++i;
  }
}

void Game::incrTimer(float time)
{
  tickTimer_+=time;
}

void Game::resultsOut(sf::RenderWindow & window, Wolf & wolf_)
{
  for (int i = 0; i < 3; i++)
  {
    num_[10].setPosition(300 + i*33, 20);  window.draw(num_[10]);
    int one = wolf_.getScore() % 10;
    num_[one].setPosition(300 + 2*33, 20); window.draw(num_[one]);
    if (wolf_.getScore() > 9)
    {
      int ten = (wolf_.getScore() % 100) / 10;
      num_[ten].setPosition(300 + 1*33, 20); window.draw(num_[ten]);
      if (wolf_.getScore() > 99)
      {
        int hun = (wolf_.getScore() % 1000) / 100;
        num_[hun].setPosition(300 + 0*33, 20); window.draw(num_[hun]);
      }
    }
  }

  for (int i = 0; i < wolf_.getLose(); i++)
  {
    lossPoint_.setPosition(326 + i*40, 114);  window.draw(lossPoint_);
  }
}

void Game::drowRestart(sf::RenderWindow & window)
{
  restart_.setPosition(0, 136);  window.draw(restart_);
}

void Game::drowBackGround(sf::RenderWindow & window)
{
  window.draw(backGround_);
}

void Game::drowEggs(sf::RenderWindow & window)
{
  for (auto i = eggVector_.begin(); i != eggVector_.end(); i++)
  {
    (*i)->egg_setPosition((*i)->getEggXY((*i)->getPosition()).x, (*i)->getEggXY((*i)->getPosition()).y);
    window.draw((*i)->getEggSprite());
  }
}
void Game::clearVector()
{
  for (auto i = eggVector_.begin(); i != eggVector_.end();)
  {
    eggVector_.erase(i);
  }
}
