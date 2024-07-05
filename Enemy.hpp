#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Enemy {
public:
    // Konstruktor przeciwnika
    Enemy(float startX, float startY) {
        shape.setSize(sf::Vector2f(20, 20)); // Rozmiar przeciwnika
        shape.setFillColor(sf::Color::Red); // Kolor przeciwnika
        shape.setPosition(startX, startY);
        speed = 100.0f; // Prędkość przeciwnika
    }

    // Aktualizacja pozycji przeciwnika w kierunku gracza
    void update(const sf::Vector2f &playerPos, sf::Time deltaTime) {
        sf::Vector2f direction = playerPos - shape.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
        shape.move(direction * speed * deltaTime.asSeconds());
    }

    // Rysowanie przeciwnika
    void DrawTo(sf::RenderWindow &window) const { // Dodano const do argumentu
        window.draw(shape);
    }

    // Sprawdzanie kolizji z graczem
    bool checkCollision(const sf::FloatRect &playerBounds) const {
        return shape.getGlobalBounds().intersects(playerBounds);
    }

private:
    sf::RectangleShape shape;
    float speed;
};