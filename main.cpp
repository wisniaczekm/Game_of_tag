#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Enemy.hpp"

int main() {
    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(600, 400), "Game");

    // Tworzenie zegara do śledzenia czasu
    sf::Clock clock;

    // Tworzenie gracza
    Entity player(window.getSize().x / 2, window.getSize().y / 2);

    // Lista przeciwników
    std::vector<Enemy> enemies;

    // Zmienna do śledzenia czasu dodawania przeciwników
    sf::Clock enemyClock;
    sf::Time enemySpawnTime = sf::seconds(2.0f);

    while (window.isOpen()) {
        sf::Event event;

        // Przetwarzanie zdarzeń
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Przetwarzanie zdarzeń dla gracza
            player.processEvents(event);
        }

        // Czas ramki
        sf::Time deltaTime = clock.restart();

        // Aktualizowanie gracza
        player.update(deltaTime);

        // Aktualizowanie przeciwników
        for (auto it = enemies.begin(); it != enemies.end();) {
            it->update(player.getPosition(), deltaTime);

            // Sprawdzanie kolizji z graczem
            if (it->checkCollision(player.getBounds())) {
                std::cout << "Game over!" << "time " << std::clock << std::endl;
                window.close();
            }
            it++;
        }

        // Dodawanie nowych przeciwników co pewien czas
        if (enemyClock.getElapsedTime() >= enemySpawnTime) {
            // Losowa pozycja dla nowego przeciwnika
            float x = rand() % static_cast<int>(window.getSize().x);
            float y = rand() % static_cast<int>(window.getSize().y);
            enemies.emplace_back(x, y);

            // Reset zegara przeciwników
            enemyClock.restart();
        }

        // Czyszczenie okna
        window.clear();

        // Rysowanie gracza
        player.DrawTo(window);

        // Rysowanie przeciwników
        for (const auto& enemy : enemies) {
            enemy.DrawTo(window);
        }

        // Wyświetlanie okna
        window.display();
    }

    return 0;
}
