#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Tools.h"
#include "Character.h"
#include "ChooseStats.h"

void Initalization();
void NewRound();
void PlayerRound();
void DisplaySFML();
void ResetRound();
void CreateUI();
void RenderGame(sf::RenderWindow& window);
void IARound();
void CheckLife();
void WaitFor(float milliseconds);
void Update();

