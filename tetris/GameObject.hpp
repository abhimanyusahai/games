#ifndef GameObject_hpp
#define GameObject_hpp

#include "Tetromino.hpp"
#include <SFML/Audio.hpp>

// Static game graphics (Title, instructions, ...)
class BaseGameGraphics
{
private:
    sf::Text m_gameTitle;
    sf::RectangleShape m_gridOutline;
    sf::RectangleShape m_instructionBox;
    sf::Sprite m_instructionBoxImage;
    sf::RectangleShape m_scoreBox;
    sf::Text m_scoreText;
    sf::RectangleShape m_nextTetrominoBox;
    sf::Sprite m_ActionButton;
    sf::Sprite m_QuitButton;
    
public:
    BaseGameGraphics();
    void changePlayToReset();
    void draw(sf::RenderWindow &window) const;
};


class GameObject
{
private:
    int m_level;
    int m_score;
    int m_framesPerLine;
    sf::Text m_scoreText;
    Tetromino m_currentTetromino;
    Tetromino m_nextTetromino;
    Grid m_grid;
    sf::Clock m_clock;
    sf::Music m_music;
    
public:
    GameObject();
    void reset();
    Grid::GridMessage updateGrid(sf::RenderWindow &window);
    MenuOptions::Option displayGameOverMenu(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window, const BaseGameGraphics &baseGameGraphics);
    void play(sf::RenderWindow &window, const BaseGameGraphics &baseGameGraphics);
};

#endif /* GameObject_hpp */

