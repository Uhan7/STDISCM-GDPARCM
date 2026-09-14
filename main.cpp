#include <SFML/Graphics.hpp>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

// Prototypes
unsigned int GetFrameRate();

// Constants
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const unsigned int ICON_COUNT = 480;
const unsigned int ICON_SIZE = 64;
const unsigned int ICON_COLUMNS = 30; // 1920 (window width) / 64 (icon width) = 30

int main()
{
    // Create Window
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Defense of the Epics");

    // Textures
    sf::Texture desertTexture("Media/Textures/Desert.png");
    std::vector<sf::Texture> iconTextures;

    // Fonts
    sf::Font font("Media/Sansation.ttf");

    // Sprites
    sf::Sprite desertBackground1(desertTexture);
    sf::Sprite desertBackground2(desertTexture);
    std::vector<sf::Sprite> iconSprites;

    // Texts
    sf::Text fpsText(font, "Hello World", 36);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition({20, 20});
    
    // Variables
    unsigned int frameCount = 0;
    float backgroundMovementSpeed = 0.25f;

    // Initializing Stuff
    desertBackground1.setPosition({0, 0});
    desertBackground2.setPosition({0, static_cast<float>(WINDOW_HEIGHT)});

    // Icon Textures
    for (unsigned int i = 0; i < ICON_COUNT; i++)
    {
        std::ostringstream filename;
        filename << "Media/Streaming/tile" << std::setw(3) << std::setfill('0') << i << ".png";
        iconTextures.emplace_back(filename.str());
    }

    // Icon Sprites
    for (unsigned int i = 0; i < ICON_COUNT; i++)
    {
        iconSprites.emplace_back(iconTextures[i]);

        const unsigned int column = i % ICON_COLUMNS;
        const unsigned int row = i / ICON_COLUMNS;

        iconSprites.back().setPosition({static_cast<float>(column * ICON_SIZE), static_cast<float>(row * ICON_SIZE)});
    }

    // Background Resizing
    const sf::Vector2u backgroundSize = desertTexture.getSize();

    desertBackground1.setScale({
        static_cast<float>(WINDOW_WIDTH) / static_cast<float>(backgroundSize.x),
        static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(backgroundSize.y)
    });

    desertBackground2.setScale({
        static_cast<float>(WINDOW_WIDTH) / static_cast<float>(backgroundSize.x),
        static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(backgroundSize.y)
    });

    // Main Loop
    while (window.isOpen())
    {
        // Events Loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // Updating
        fpsText.setString("FPS: " + std::to_string(GetFrameRate()));
        desertBackground1.move({0, -backgroundMovementSpeed});
        desertBackground2.move({0, -backgroundMovementSpeed});

        if (desertBackground1.getPosition().y <= -WINDOW_HEIGHT) desertBackground1.setPosition({0, static_cast<float>(WINDOW_HEIGHT)});
        if (desertBackground2.getPosition().y <= -WINDOW_HEIGHT) desertBackground2.setPosition({0, static_cast<float>(WINDOW_HEIGHT)});

        // Rendering
        window.draw(desertBackground1);
        window.draw(desertBackground2);
        for (const sf::Sprite& icon : iconSprites) window.draw(icon);
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