#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <string>
#include <vector>
#include "game.hpp"

const int w=570,h=350;

void foo()
{
  sf::RenderWindow window(sf::VideoMode(w, h), "NU POGODI!");

  Wolf wolf_;
  Game game;

  sf::Clock clock;


  while (window.isOpen())
  {

    std::uniform_int_distribution<std::size_t> randomNunbersRange(0, 3);
    std::random_device rd;
    std::mt19937 randomNumbers(rd());

    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    game.incrTimer(time);

    sf::Event e;
    while (window.pollEvent(e))
    {
      if (e.type == sf::Event::Closed)
        window.close();
    }

    /////////////////////ЧТЕНИЕ НАЖАТИЯ СТРЕЛО//////////////////////////////////
    wolf_.readVolkKey();
    //////////////////////////// РЕСТАРТ ///////////////////////////////////////
    if(wolf_.getLose() == 3)
    {
      game.drowRestart(window); window.display();
      wolf_.reset();
      game.clearVector();
      while (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
      {
        if (window.pollEvent(e))
        {
          if (e.type == sf::Event::Closed)
          {
            window.close();
            break;
          }
        }
      }
    }
    ////////////////////////////////////////////////////////////////////////////

    //////////////////////// ГЕНЕРАТОР ЯИЧЕК ///////////////////////////////////
    int Random = randomNunbersRange(randomNumbers);
    game.eggGen(Random);
    //////////////////// обработка результатов волка ///////////////////////////
    game.wolfeResultsHandler(wolf_);
    //////////////////////////ОТРИСОВКА/////////////////////////////////////////
    window.clear();
    game.drowBackGround(window);
    //////////////////// ВЫВОД РЕЗУЛЬТАТОВ /////////////////////////////////////
    game.resultsOut(window,wolf_);
    ///////////////////////////ЯИЧКИ////////////////////////////////////////////
    game.drowEggs(window);
    //////////////////////////ВОЛК С КОРЗИНКОЙ//////////////////////////////////
    window.draw(wolf_.getVolkLR());
    window.draw(wolf_.getBasket());
    ////////////////////////////ВЫВОД НА ЭКРАН//////////////////////////////////
    window.display();
  }
}
