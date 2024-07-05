#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    // Konstruktor obiektu
    Entity(float x, float y)
        : rect(sf::Vector2f(50, 50)), // Tworzenie kwadratu o wymiarach 50x50
          speed(200.0f), // Prędkość kwadratu
          up(false), down(false), left(false), right(false) {
        // Ustawienie położenia kwadratu
        rect.setPosition(x, y);
        // Ustawienie koloru kwadratu
        rect.setFillColor(sf::Color::Blue);
    }

    // Metody do obsługi wejścia klawiatury
    void processEvents(sf::Event &event) {
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            bool isPressed = (event.type == sf::Event::KeyPressed);
            switch (event.key.code) {
                case sf::Keyboard::W:
                    up = isPressed;
                    break;
                case sf::Keyboard::S:
                    down = isPressed;
                    break;
                case sf::Keyboard::A:
                    left = isPressed;
                    break;
                case sf::Keyboard::D:
                    right = isPressed;
                    break;
                default:
                    break;
            }
        }
    }

    // Aktualizowanie pozycji gracza
    void update(sf::Time deltaTime) {
        sf::Vector2f movement(0, 0);
        
        // Ruch na podstawie wejścia
        if (up) {
            movement.y -= speed * deltaTime.asSeconds();
        }
        if (down) {
            movement.y += speed * deltaTime.asSeconds();
        }
        if (left) {
            movement.x -= speed * deltaTime.asSeconds();
        }
        if (right) {
            movement.x += speed * deltaTime.asSeconds();
        }
        
        // Przesunięcie kwadratu
        rect.move(movement);
        
        // Upewnienie się, że kwadrat nie wychodzi poza granice okna
        sf::Vector2f position = rect.getPosition();
        if (position.x < 0) rect.setPosition(0, position.y);
        if (position.y < 0) rect.setPosition(position.x, 0);
        if (position.x + rect.getSize().x > 600) {
            rect.setPosition(600 - rect.getSize().x, position.y);
        }
        if (position.y + rect.getSize().y > 400) {
            rect.setPosition(position.x, 400 - rect.getSize().y);
        }
    }

    // Rysowanie kwadratu w oknie
    void DrawTo(sf::RenderWindow &window) {
        window.draw(rect);
    }

    // Dodane metody do zwracania położenia i ograniczeń gracza
    sf::Vector2f getPosition() const {
        return rect.getPosition();
    }

    sf::FloatRect getBounds() const {
        return rect.getGlobalBounds();
    }

private:
    sf::RectangleShape rect;
    float speed;
    bool up, down, left, right;
};