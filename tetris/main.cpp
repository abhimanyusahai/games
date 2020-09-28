#include "GameObject.hpp"

// Main menu - player can choose "Start" or "Quit"
MenuOptions::Option displayMainMenu(sf::RenderWindow &window, const BaseGameGraphics &baseGameGraphics)
{
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Return QUIT if window closed
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return MenuOptions::QUIT;
            }
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Return START if "Start" button pressed
                if ((event.mouseButton.button == sf::Mouse::Left) &&
                    (event.mouseButton.x > GraphicsParams::playButtonPosition.x) &&
                    (event.mouseButton.x  < (GraphicsParams::playButtonPosition.x + GraphicsParams::playButtonSpriteCoord.width)) &&
                    (event.mouseButton.y  > GraphicsParams::playButtonPosition.y) &&
                    (event.mouseButton.y  < (GraphicsParams::playButtonPosition.y + GraphicsParams::playButtonSpriteCoord.height)))
                {
                    return MenuOptions::START;
                }
                
                // Return QUIT if "Quit" button pressed
                if ((event.mouseButton.button == sf::Mouse::Left) &&
                    (event.mouseButton.x > GraphicsParams::quitButtonPosition.x) &&
                    (event.mouseButton.x  < (GraphicsParams::quitButtonPosition.x + GraphicsParams::quitButtonSpriteCoord.width)) &&
                    (event.mouseButton.y  > GraphicsParams::quitButtonPosition.y) &&
                    (event.mouseButton.y  < (GraphicsParams::quitButtonPosition.y + GraphicsParams::quitButtonSpriteCoord.height)))
                {
                    window.close();
                    return MenuOptions::QUIT;
                }
            }
        }
        
        window.clear(GraphicsParams::windowBGColor);
        baseGameGraphics.draw(window);
        window.display();
    }
}

int main()
{
    sf::RenderWindow window(GraphicsParams::videoMode, GraphicsParams::gameTitleString);
    
    // Initialize base game graphics
    BaseGameGraphics baseGameGraphics;
    
    // Display main menu
    switch (displayMainMenu(window, baseGameGraphics))
    {
        case MenuOptions::START:
            {
                // Create GameObject and start game
                GameObject game;
                baseGameGraphics.changePlayToReset();
                game.play(window, baseGameGraphics);
                break;
            }
        case MenuOptions::QUIT:
                // Quit the program
            return 0;
    }
    
    return 0;
}
