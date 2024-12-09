#include "Particule.h"


void InstanceParticule(std::list<Particle> &particles,int particuleCount, sf::Vector2f position, sf::Color color, int speedMin, int speedMax, float radius, float lifetime)
{
   
    for (int i = 0; i < particuleCount; i++) 
    {
        particles.push_back(CreateParticle(position, color, speedMin, speedMax, radius, lifetime));
    }
    
}
Particle CreateParticle(sf::Vector2f position, sf::Color color, int speedMin, int speedMax, float radius, float lifetime) 
{
    Particle particle;
    particle.shape.setRadius(radius);
    particle.shape.setFillColor(color);
    particle.shape.setPosition(position);

    float angle = static_cast<float>(rand() % 360);
    float speed = static_cast<float>(rand() % speedMin + speedMax);

    particle.velocity = sf::Vector2f
    (
        cos(angle * M_PI / 180.f) * speed,
        sin(angle * M_PI / 180.f) * speed
    );

    particle.lifetime = lifetime;
    return particle;
}

void UpdateParticles(std::list<Particle>& particles, float deltaTime) 
{
    for (std::list<Particle>::iterator it = particles.begin(); it != particles.end();) 
    {
        (*it).lifetime -= deltaTime;
        if ((*it).lifetime <= 0) {
            it = particles.erase(it);
        }
        else {
            (*it).shape.move((*it).velocity * deltaTime);

            sf::Color color = (*it).shape.getFillColor();
            color.a = static_cast<sf::Uint8>(255* ((*it).lifetime / 2.f));
            (*it).shape.setFillColor(color);

            ++it;
        }
    }
}