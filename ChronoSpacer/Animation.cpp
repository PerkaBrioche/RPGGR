#include "Animation.h"


float velocity = 200.f;
float maxDistance = 50.f;
bool animating = false;
bool returning = false;
sf::Vector2f currentVelocity(velocity, 0.f);
float traveledDistance = 0.f;


void BeginMovement( sf::CircleShape& square,const sf::Vector2f& startPosition) {
    if (!animating) {
        animating = true;
        returning = false;
        traveledDistance = 0.f;
        square.setPosition(startPosition);
        currentVelocity = sf::Vector2f(velocity, 0.f);
    }
}


void DoAnimation(sf::CircleShape& square,float deltaTime, const sf::Vector2f& startPosition) {
    if (animating) {
        if (!returning) {
            square.move(currentVelocity * deltaTime);
            traveledDistance += velocity * deltaTime;

            if (traveledDistance >= maxDistance) {
                returning = true;
                currentVelocity = -currentVelocity;
            }
        }
        else {
            square.move(currentVelocity * deltaTime);
            traveledDistance -= velocity * deltaTime;

            if (traveledDistance <= 0.f) {
                animating = false;
                returning = false;
                square.setPosition(startPosition);
            }
        }
    }
}


