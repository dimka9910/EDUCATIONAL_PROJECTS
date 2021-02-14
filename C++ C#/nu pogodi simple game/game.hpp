#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <memory>
#include "egg.hpp"
#include "wolf.hpp"


class Game
{
public:
  Game();
  void eggGen(int);
  void wolfeResultsHandler(Wolf&);
  void incrTimer(float time);
  void resultsOut(sf::RenderWindow & window, Wolf & wolf_);
  void drowRestart(sf::RenderWindow & window);
  void drowBackGround(sf::RenderWindow & window);
  void drowEggs(sf::RenderWindow & window);
  void clearVector();

private:
  double tickDelay_;
  double tickTimer_;
  std::vector<std::unique_ptr<Egg>> eggVector_;

  sf::Sprite lossPoint_;
  sf::Sprite num_[11];
  sf::Sprite backGround_;
  sf::Sprite restart_;

  sf::Texture restartTexture_;
  sf::Texture backGroundTexture_;
  sf::Texture numbersTexture_;
  sf::Texture numberEmptyTexture_;
  sf::Texture losePointTexture_;

  int wait;

};

#endif // GAME_H
