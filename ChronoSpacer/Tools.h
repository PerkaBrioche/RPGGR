
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <random>

std::string GetDirectories(std::string dname);
std::string GetAppPath();
int GetRandomRange(int min, int max);
void InitializeSprite(sf::Sprite& targerImage, std::string assetName, sf::Vector2f targetScale, sf::Vector2f targetPosition);
void EditCircle(sf::CircleShape& circle, sf::Color color, float taille, sf::Vector2f circlePosition);
void CreateRect(sf::RectangleShape& carre, float longueur, float hauteur, sf::Color fillColor, sf::Color colorOutline, float tailleOutline, sf::Vector2f squarePosition);
int Clamp(int value, int min, int max);
sf::Text EditText(std::string string, sf::Vector2f positionText, sf::Vector2f scale);
void UpdateLifeTexts();
void AugmenterPercentageAttack(int& actualPercentage);
void ResetPercentage(int& actualPercentage);
bool TryPercentage(int actualPercentage);
void EndOfGame();

void SetBarUI(sf::RectangleShape& fillBar, sf::RectangleShape& backgroundBar, sf::Color bgColor, sf::Color fillbarColor, sf::Vector2f position, sf::Vector2f scale);

void UpdateBarUI(int newPercentage, float progress, float maxProgress, sf::RectangleShape& fillBar, sf::RectangleShape& backgroundBar);
