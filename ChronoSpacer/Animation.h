#include <iostream>
#include <SFML/Graphics.hpp>



void BeginMovement(sf::CircleShape& square, const sf::Vector2f& startPosition, float& velocity, float& traveledDistance, float& maxDistance, bool& animating, bool& returning, bool moveLeft);
void DoAnimation(sf::CircleShape& square, float deltaTime, const sf::Vector2f& startPosition, float& velocity, float& traveledDistance, float& maxDistance, bool& animating, bool& returning);