#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <list>


const float M_PI = 3.14159f;
struct Particle
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifetime = 0;
};

void InstanceParticule(std::list<Particle>& particles, int particuleCount, sf::Vector2f position, sf::Color color, int speedMin, int speedMax, float radius, float lifetime);
void UpdateParticles(std::list<Particle>& particles, float deltaTime);
Particle CreateParticle(sf::Vector2f position, sf::Color color, int speedMin, int speedMax, float radius, float lifetime);
