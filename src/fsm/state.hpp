#pragma once

// Forward declaration
class Controller;

class State {
public:
    virtual ~State() = default;

    /**
     * @brief Appelé UNE FOIS quand on entre dans cet état.
     * Sert à configurer le hardware (allumer LED, changer mode RF, etc.)
     */
    virtual void enter(Controller& controller) {}

    /**
     * @brief Appelé EN BOUCLE tant que cet état est actif.
     * Sert à lire les pins (Polling) et exécuter la logique.
     * @param controller Référence vers le RadioController pour demander un changement d'état.
     * @param dt Temps écoulé depuis le dernier appel (optionnel mais utile pour les timers).
     */
    virtual void update(Controller& controller, float dt) = 0;

    /**
     * @brief Appelé UNE FOIS quand on quitte cet état.
     * Sert à nettoyer (éteindre le micro, désactiver les amplis, etc.)
     */
    virtual void exit(Controller& controller) {}
};