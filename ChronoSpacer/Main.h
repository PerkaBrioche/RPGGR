#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Tools.h"
#include "Character.h"

void Initalization();
void NewRound();
void PlayerRound();
void DisplaySFML();
void ResetRound();
void CreateUI();
void WriteText(sf::Font, sf::Text, sf::Text, std::string, sf::Vector2f, sf::Vector2f, int, int);

