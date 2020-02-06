#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../memory/MemoryManager.h"
#include "../cpu/CentralProcessingUnit.h"

CentralProcessingUnit cpu;

std::string romPath;

int main(int numArgs, char const** args) {
    // Get ROM path
    if (numArgs != 2) {
        std::cout << "Usage: roodboi [path_to_rom]" << std::endl;

        if (numArgs > 2) return EXIT_FAILURE;

        // I'm lazy, lol
        std::cout << "Using default ROM path..." << std::endl;
        romPath = "/Users/samreha/Documents/roms/gb/Tetris.gb";
    } else
        romPath = args[1];

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "RoodBoi");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("media/images/icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // CPU debug text
    sf::Font font;
    font.loadFromFile("media/fonts/arial.ttf");

    sf::Text text("CPU STATE:", font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);

    // Test memory
    try {
        MemoryManager::instance()->loadROM(romPath);
    } catch (const char* msg) {
        std::cout << "Failed to open ROM \"" << romPath << "\" with error message: " << msg << std::endl;
        return EXIT_FAILURE;
    }
    MemoryManager::instance()->debugDumpMem();

    cpu.initialize();

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

        cpu.tick();

        text.setString("CPU STATE:\nAF:" + std::to_string(cpu.getRegisterValue(AF))
                       + "\nBC:" + std::to_string(cpu.getRegisterValue(BC))
                       + "\nDE:" + std::to_string(cpu.getRegisterValue(DE))
                       + "\nHL:" + std::to_string(cpu.getRegisterValue(HL))
                       + "\nSP:" + std::to_string(cpu.getRegisterValue(SP))
                       + "\nPC:" + std::to_string(cpu.getRegisterValue(PC)));

        // Draw one frame
        window.clear();
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}
