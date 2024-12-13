#include "Animation.h"

// Fonction pour d�marrer le mouvement
void BeginMovement(sf::CircleShape& square, const sf::Vector2f& startPosition, float& velocity, float& traveledDistance, float& maxDistance, bool& animating, bool& returning, bool moveLeft) {
    if (!animating) {
        animating = true;
        returning = false;
        traveledDistance = 0.f;
        // Configure la bonne direction selon le param�tre moveLeft
        velocity = moveLeft ? -std::abs(velocity) : std::abs(velocity);
        // Positionner au point de d�part
        square.setPosition(startPosition);

    }
}

// Logique de mouvement avec retour
void DoAnimation(sf::CircleShape& square, float deltaTime, const sf::Vector2f& startPosition, float& velocity, float& traveledDistance, float& maxDistance, bool& animating, bool& returning) {
    if (animating) {
        float moveDistance = velocity * deltaTime;
        if (!returning) {
            // On se d�place vers la position maximale
            square.move(moveDistance, 0.f);
            traveledDistance += std::abs(moveDistance);

            if (traveledDistance >= maxDistance) {
                // On atteint la distance maximale, on commence le retour
                returning = true;
            }
        }
        else {
            // On revient vers la position de d�part
            square.move(-moveDistance, 0.f);
            traveledDistance -= std::abs(moveDistance);

            if (traveledDistance <= 0.f) {
                // Fin de l'animation - on est de retour � la position de d�part
                square.setPosition(startPosition);
                animating = false;  // Arr�ter l'animation
                returning = false;  // R�initialiser l'�tat de retour
                traveledDistance = 0.f; // R�initialiser la distance
            }
        }
    }
}
