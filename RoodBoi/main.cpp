#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "MemoryManager.h"
#include "CentralProcessingUnit.h"

MemoryManager memManager();
CentralProcessingUnit cpu();

int main(int, char const**) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "RoodBoi");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Main Loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Draw one frame
        window.clear();

        window.display();
    }

    return EXIT_SUCCESS;
}
