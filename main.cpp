#include <SFML/Graphics.hpp>
#include <string>

// Prototypes
unsigned int GetFrameRate();

// Constants
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

int main()
{
    // Create Window
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Defense of the Epics");

    // Textures
    sf::Texture desertTexture("Media/Textures/Desert.png");

    // Fonts
    sf::Font font("Media/Sansation.ttf");

    // Sprites
    sf::Sprite desertBackground(desertTexture);

    // Texts
    sf::Text fpsText(font, "Hello World", 36);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition({WINDOW_WIDTH - 600.f, WINDOW_HEIGHT - 300.f});
    
    // Initializing
    unsigned int frameCount = 0;

    // Main Loop
    while (window.isOpen())
    {
        // Event Loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // Updating
        fpsText.setString("FPS: " + std::to_string(GetFrameRate()));

        // Rendering
        window.draw(desertBackground);
        window.draw(fpsText);

        // Refresh
        window.display();
        window.clear();
    }
}

unsigned int GetFrameRate()
{
    static sf::Clock clock;
    static unsigned int frameCount = 0;
    static unsigned int currentFps = 0;

    frameCount++;

    const float elapsedSeconds = clock.getElapsedTime().asSeconds();

    if (elapsedSeconds >= 0.5f)
    {
        currentFps = static_cast<unsigned int>(static_cast<float>(frameCount) / elapsedSeconds);

        frameCount = 0;
        clock.restart();
    }

    return currentFps;
}