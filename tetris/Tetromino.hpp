#ifndef Tetromino_hpp
#define Tetromino_hpp

#include "GridObjects.hpp"
#include <random>
#include "Resources.cpp"

class Tetromino
{
public:
    GridCellMatrix m_boundingBox;
    
private:
    sf::Vector2i m_position; // Coordinates of top left cell of tetromino bounding box
    GridCell::Type m_type;
    std::vector<sf::Vector2i> m_clearingCellCoords; // Coordinates of cells occupied by the tetromino in its previous position, that need to be cleared by the grid
    
public:
    Tetromino();
    Tetromino(Tetromino &tetromino);
    void generateRandom();
    void initialize();
    GridCell::Type getType();
    friend Grid::GridMessage Grid::update(sf::RenderWindow &window, Tetromino &tetromino);
    bool inRestingPosition(Grid &grid);
    bool collidesOnLeft(Grid &grid);
    bool collidesOnRight(Grid &grid);
    void moveDownOneCell();
    void shiftLeft(Grid &grid);
    void shiftRight(Grid &grid);
    void rotate(Grid &grid);
    void draw(sf::RenderWindow &window);
};

#endif /* Tetromino_hpp */
