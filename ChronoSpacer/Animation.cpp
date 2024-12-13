#include "Animation.h"

// Fonction pour démarrer le mouvement
void BeginMovement(sf::CircleShape& square, const sf::Vector2f& startPosition, float& velocity, float& traveledDistance, float& maxDistance, bool& animating, bool& returning, bool moveLeft) {
    if (!animating) {
        animating = true;
        returning = false;
        traveledDistance = 0.f;
        // Configure la bonne direction selon le paramètre moveLeft
        velocity = moveLeft ? -std::abs(velocity) : std::abs(velocity);
        // Positionner au point de départ
        square.setPosition(startPosition);

    }
}

// Logique de mouvement avec retour
void DoAnimation(sf::CircleShape& square, float deltaTime, const sf::Vector2f& startPosition, float& velocity, float& traveledDistance, float& maxDistance, bool& animating, bool& returning) {
    if (animating) {
        float moveDistance = velocity * deltaTime;
        if (!returning) {
            // On se déplace vers la position maximale
            square.move(moveDistance, 0.f);
            traveledDistance += std::abs(moveDistance);

            if (traveledDistance >= maxDistance) {
                // On atteint la distance maximale, on commence le retour
                returning = true;
            }
        }
        else {
            // On revient vers la position de départ
            square.move(-moveDistance, 0.f);
            traveledDistance -= std::abs(moveDistance);

            if (traveledDistance <= 0.f) {
                // Fin de l'animation - on est de retour à la position de départ
                square.setPosition(startPosition);
                animating = false;  // Arrêter l'animation
                returning = false;  // Réinitialiser l'état de retour
                traveledDistance = 0.f; // Réinitialiser la distance
            }
        }
    }
}
