#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Tools.h"
#include "Character.h"
#include "ChooseStats.h"
#include "Particule.h"
#include "Animation.h"


void Initalization();
void NewRound();
bool PlayerRound();
void DisplaySFML();
void ResetRound();
void CreateUI();
void RenderGame(sf::RenderWindow& window);
void IARound();
void CheckLife();
void WaitFor(float milliseconds);
void Update();
void ReceiveParticles(std::list<Particle> parts);
void PlayParticles(int numberPart, sf::Vector2f pos, sf::Color color);
void TriggerParticules(struct Character Chara);
void WaitFor(float seconds);
void PopUpXp(int xp);