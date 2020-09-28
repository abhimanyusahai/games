#include "Tetromino.hpp"

std::random_device rd;
std::mt19937 gen(rd());
static std::uniform_int_distribution<> g_dis(1,7);

Tetromino::Tetromino()
{
    generateRandom();
    initialize();
}
    
Tetromino::Tetromino(Tetromino &tetromino)
{
    generateRandom();
    if (m_type == tetromino.getType())
        generateRandom();
    initialize();
}
    
void Tetromino::generateRandom()
{
    switch (g_dis(gen))
    {
        case 1: m_type = GridCell::Type::I; break;
        case 2: m_type = GridCell::Type::O; break;
        case 3: m_type = GridCell::Type::T; break;
        case 4: m_type = GridCell::Type::S; break;
        case 5: m_type = GridCell::Type::Z; break;
        case 6: m_type = GridCell::Type::J; break;
        case 7: m_type = GridCell::Type::L; break;
    }
}
    
void Tetromino::initialize()
{
    switch (m_type)
    {
        case GridCell::Type::I:
            m_position = TetrominoParams::SpawningPosition::I;
            m_boundingBox.initialize(TetrominoParams::SpawningPosition::I, TetrominoParams::BoundingBoxSize::I, true);
            m_boundingBox.setTypes(TetrominoParams::FilledPositions::I, GridCell::Type::I);
            break;
        case GridCell::Type::O:
            m_position = TetrominoParams::SpawningPosition::O;
            m_boundingBox.initialize(TetrominoParams::SpawningPosition::O, TetrominoParams::BoundingBoxSize::O, true);
            m_boundingBox.setTypes(TetrominoParams::FilledPositions::O, GridCell::Type::O);
            break;
        case GridCell::Type::T:
            m_position = TetrominoParams::SpawningPosition::T;
            m_boundingBox.initialize(TetrominoParams::SpawningPosition::T, TetrominoParams::BoundingBoxSize::T, true);
            m_boundingBox.setTypes(TetrominoParams::FilledPositions::T, GridCell::Type::T);
            break;
        case GridCell::Type::S:
            m_position = TetrominoParams::SpawningPosition::S;
            m_boundingBox.initialize(TetrominoParams::SpawningPosition::S, TetrominoParams::BoundingBoxSize::S, true);
            m_boundingBox.setTypes(TetrominoParams::FilledPositions::S, GridCell::Type::S);
            break;
        case GridCell::Type::Z:
            m_position = TetrominoParams::SpawningPosition::Z;
            m_boundingBox.initialize(TetrominoParams::SpawningPosition::Z, TetrominoParams::BoundingBoxSize::Z, true);
            m_boundingBox.setTypes(TetrominoParams::FilledPositions::Z, GridCell::Type::Z);
            break;
        case GridCell::Type::J:
            m_position = TetrominoParams::SpawningPosition::J;
            m_boundingBox.initialize(TetrominoParams::SpawningPosition::J, TetrominoParams::BoundingBoxSize::J, true);
            m_boundingBox.setTypes(TetrominoParams::FilledPositions::J, GridCell::Type::J);
            break;
        case GridCell::Type::L:
            m_position = TetrominoParams::SpawningPosition::L;
            m_boundingBox.initialize(TetrominoParams::SpawningPosition::L, TetrominoParams::BoundingBoxSize::L, true);
            m_boundingBox.setTypes(TetrominoParams::FilledPositions::L, GridCell::Type::L);
            break;
    }
}
    
GridCell::Type Tetromino::getType() { return m_type; }
    
bool Tetromino::inRestingPosition(Grid &grid)
{
    for (std::vector<GridCell> &row: *(m_boundingBox.getCells()))
    {
        for (GridCell &cell : row)
        {
            if (cell.m_type != GridCell::EMPTY)
            {
                // Return true if tetromino has hit the base
                if (cell.m_coordinates.x == (GridParams::gridHeight - 1))
                    return true;
                
                // ...or if tetromino lands on another inactive tetromino
                if (cell.m_coordinates.x >= 0 && cell.m_coordinates.x <= (GridParams::gridHeight - 1) && cell.m_coordinates.y >= 0 && cell.m_coordinates.y <= (GridParams::gridWidth - 1))
                {
                    if ((*(grid.getCells()))[cell.m_coordinates.x + 1][cell.m_coordinates.y].m_type != GridCell::EMPTY &&
                        (*(grid.getCells()))[cell.m_coordinates.x + 1][cell.m_coordinates.y].activeTetromino == false)
                        return true;
                }
            }
        }
    }
    return false;
}
    
bool Tetromino::collidesOnLeft(Grid &grid)
{
    for (std::vector<GridCell> &row: *(m_boundingBox.getCells()))
    {
        for (GridCell &cell : row)
        {
            if (cell.m_type != GridCell::EMPTY)
            {
                // Tetromino hits left wall
                if (cell.m_coordinates.y < 0)
                    return true;
                
                // Tetromino hits an inactive tetromino grid cell on the left
                if (cell.m_coordinates.x >= 0 && cell.m_coordinates.x <= (GridParams::gridHeight - 1) && cell.m_coordinates.y >= 0 && cell.m_coordinates.y <= (GridParams::gridWidth - 1))
                {
                    if ((*(grid.getCells()))[cell.m_coordinates.x][cell.m_coordinates.y].m_type != GridCell::EMPTY &&
                        (*(grid.getCells()))[cell.m_coordinates.x][cell.m_coordinates.y].activeTetromino == false)
                        return true;
                }
            }
        }
    }
    return false;
}
    
bool Tetromino::collidesOnRight(Grid &grid)
{
    for (std::vector<GridCell> &row: *(m_boundingBox.getCells()))
    {
        for (GridCell &cell : row)
        {
            if (cell.m_type != GridCell::EMPTY)
            {
                // Tetromino hits right wall
                if (cell.m_coordinates.y > (GridParams::gridWidth - 1))
                    return true;
                
                // Tetromino hits inactive tetromino grid cell on the right
                if (cell.m_coordinates.x >= 0 && cell.m_coordinates.x <= (GridParams::gridHeight - 1) && cell.m_coordinates.y >= 0 && cell.m_coordinates.y <= (GridParams::gridWidth - 1))
                {
                    if ((*(grid.getCells()))[cell.m_coordinates.x][cell.m_coordinates.y].m_type != GridCell::EMPTY &&
                        (*(grid.getCells()))[cell.m_coordinates.x][cell.m_coordinates.y].activeTetromino == false)
                        return true;
                }
            }
        }
    }
    return false;
}
    
void Tetromino::moveDownOneCell()
{
    // Clear previous position
    for (GridCell &cell : (*(m_boundingBox.getCells()))[0])
    {
        if (cell.m_type != GridCell::EMPTY)
        {
            m_clearingCellCoords.push_back(sf::Vector2i(cell.m_coordinates.x, cell.m_coordinates.y));
        }
    }
    
    // Move tetromino bounding box down one cell and update position
    m_boundingBox.setPosition(sf::Vector2i(m_boundingBox.getPosition().x + 1, m_boundingBox.getPosition().y));
    
    // Update tetromino position
    m_position = m_boundingBox.getPosition();
}
    
void Tetromino::shiftLeft(Grid &grid)
{
    // Clear previous position
    for (std::vector<GridCell> &row : *(m_boundingBox.getCells()))
    {
        if (row.back().m_type != GridCell::EMPTY)
        {
            m_clearingCellCoords.push_back(sf::Vector2i(row.back().m_coordinates.x, row.back().m_coordinates.y));
        }
    }
    
    // Move tetromino left
    m_boundingBox.setPosition(sf::Vector2i(m_boundingBox.getPosition().x, m_boundingBox.getPosition().y - 1));
    m_position = m_boundingBox.getPosition();
    
    // If collision with left wall, move tetromino back right and undo clearing of previous position
    if (collidesOnLeft(grid))
    {
        m_boundingBox.setPosition(sf::Vector2i(m_boundingBox.getPosition().x, m_boundingBox.getPosition().y + 1));
        m_clearingCellCoords.clear();
    }
    
    // Update tetromino position
    m_position = m_boundingBox.getPosition();
}
    
void Tetromino::shiftRight(Grid &grid)
{
    // Clear previous position
    for (std::vector<GridCell> &row : *(m_boundingBox.getCells()))
    {
        if (row[0].m_type != GridCell::EMPTY)
        {
            m_clearingCellCoords.push_back(sf::Vector2i(row[0].m_coordinates.x, row[0].m_coordinates.y));
        }
    }
    
    // Move tetromino right
    m_boundingBox.setPosition(sf::Vector2i(m_boundingBox.getPosition().x, m_boundingBox.getPosition().y + 1));
    m_position = m_boundingBox.getPosition();
    
    // If collision with right wall, move tetromino back left and undo clearing of previous position
    if (collidesOnRight(grid))
    {
        m_boundingBox.setPosition(sf::Vector2i(m_boundingBox.getPosition().x, m_boundingBox.getPosition().y - 1));
        m_clearingCellCoords.clear();
    }
    
    // Update tetromino position
    m_position = m_boundingBox.getPosition();
}
    
void Tetromino::rotate(Grid &grid)
{
    // Clear previous position
    // might not be required
    
    // Rotate the tetromino bounding box cell-coordinates
    int boxSize = m_boundingBox.getCells()->size();
    std::vector<sf::Vector2i> originalCoords;
    
    for (std::vector<GridCell> &row : *(m_boundingBox.getCells()))
    {
        for (GridCell &cell : row)
        {
            originalCoords.push_back(sf::Vector2i(cell.m_coordinates.x, cell.m_coordinates.y));
            int rel_x = cell.m_coordinates.x - m_position.x;
            int rel_y = cell.m_coordinates.y - m_position.y;
            cell.m_coordinates.x = m_position.x + rel_y;
            cell.m_coordinates.y = m_position.y + ((boxSize - 1) - rel_x);
        }
    }
    
    // Check if there's any collision - if yes then revert to original coordinates and return
    if (collidesOnLeft(grid) || collidesOnRight(grid))
    {
        for (int iii{0}; iii < boxSize; ++iii)
        {
            for (int jjj{0}; jjj < boxSize; ++jjj)
            {
                (*(m_boundingBox.getCells()))[iii][jjj].m_coordinates = originalCoords[jjj + iii*boxSize];
            }
        }
        return;
    }
    
    // Tranpose the bounding box
    GridCellMatrix tempBoundingBox;
    for (int iii{0}; iii < boxSize; ++iii)
    {
        std::vector<GridCell> tempRow;
        for (int jjj{0}; jjj < boxSize; ++jjj)
        {
            tempRow.push_back((*(m_boundingBox.getCells()))[(boxSize - 1) - jjj][iii]);
        }
        tempBoundingBox.getCells()->push_back(tempRow);
    }
    m_boundingBox = tempBoundingBox;
}
    
void Tetromino::draw(sf::RenderWindow &window)
{
    int iii {0};
    for (std::vector<GridCell> &gridRow : *(m_boundingBox.getCells()))
    {
        int jjj {0};
        for (GridCell &gridCell : gridRow)
        {
            gridCell.m_sprite.setPosition(sf::Vector2f(GraphicsParams::nextTetrominoImagePosition.x + jjj*GraphicsParams::gridCellSideLength,
                                                       GraphicsParams::nextTetrominoImagePosition.y + iii*GraphicsParams::gridCellSideLength));
            gridCell.draw(window);
            ++jjj;
        }
        if (iii++ == 1)
            break;
    }
}