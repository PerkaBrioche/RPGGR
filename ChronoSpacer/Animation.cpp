#include "Animation.h"





void DoAnimation(sf::CircleShape& square, float& traveledDistance, bool& animating, bool& returning,
    sf::Vector2f& currentVelocity, float velocity, float maxDistance,
    const sf::Vector2f& startPosition) {
    sf::Clock clockForAnimation;
    clockForAnimation.restart();
    float deltaTime = clockForAnimation.restart().asSeconds();

    std::cout << "Aniamtion" << std::endl;
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
                square.setPosition(startPosition);
            }
        }
    }
}

void BeginMovement(bool& animating, bool& returning, float& traveledDistance, sf::CircleShape& square,
    const sf::Vector2f& startPosition) {
    if (!animating) {
        animating = true;
        returning = false;
        traveledDistance = 0.f;
        square.setPosition(startPosition);
    }
}
