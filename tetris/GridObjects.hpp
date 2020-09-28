#ifndef GridObjects_hpp
#define GridObjects_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class GridCell
{
public:
    enum Type
    {
        EMPTY,
        I,
        O,
        T,
        S,
        Z,
        J,
        L
    };
    bool activeTetromino;
    Type m_type;
    sf::Vector2i m_coordinates; // Coordinates on the grid
    sf::Sprite m_sprite;
    
    GridCell();
    void setPosition(sf::Vector2i coordinates);
    void setType(Type type);
    void draw(sf::RenderWindow &window);
};


class GridCellMatrix
{
protected:
    std::vector<std::vector<GridCell>> m_cells;
    
public:
    GridCellMatrix();
    void initialize(sf::Vector2i position, sf::Vector2i size, bool activeTetromino);
    sf::Vector2i getPosition();
    void setPosition(sf::Vector2i position);
    void setTypes(std::vector<sf::Vector2i> fillPositions, GridCell::Type type);
    void setActiveTetrominoStatus(std::vector<sf::Vector2i> positions, bool activeTetromino);
    std::vector<std::vector<GridCell>>* getCells();
};

class Tetromino;

class Grid : public GridCellMatrix
{
public:
    std::vector<int> m_fullLines;
    int m_linesNeeded;
    bool hardDropState;
    enum GridMessage
    {
        NONE,
        NEW_TETROMINO,
        LINE_COMPLETED,
        NEW_LEVEL,
        GAME_OVER
    };

    Grid();
    Grid::GridMessage update(sf::RenderWindow &window, Tetromino &tetromino);
    Grid::GridMessage removeLines(int level, int &score);
    void draw(sf::RenderWindow &window);
};

#endif /* GridObjects_hpp */
