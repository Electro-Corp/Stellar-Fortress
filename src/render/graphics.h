/*
  Header file for the graphics system of
  Stellar Fortress

  Uses SFML
*/
#ifndef GRAPHICS_H
#define GRAPHCIS_H
#include <SFML/Graphics.hpp>
class Renderer{
private:
sf::RenderWindow* renderWindow;
public:
  Renderer(int width, int height);

  void procEvents();

  void display();
};
#include "graphics.cpp"
#endif