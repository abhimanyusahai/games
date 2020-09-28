#include "Tetromino.hpp"

GridCell::GridCell()
{
    activeTetromino = false;
    m_type = EMPTY;
    m_sprite.setTexture(g_resources.blocksImage);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
}

void GridCell::setPosition(sf::Vector2i coordinates)
{
    m_coordinates = coordinates;
    m_sprite.setPosition(GraphicsParams::gridPosition.x + (m_coordinates.y * GraphicsParams::gridCellSideLength), GraphicsParams::gridPosition.y + (m_coordinates.x * GraphicsParams::gridCellSideLength));
}

void GridCell::setType(Type type)
{
    m_type = type;
    
    // Update sprite
    switch (m_type)
    {
        case I: {m_sprite.setTextureRect(TetrominoParams::SpriteRects::I); break;}
        case O: {m_sprite.setTextureRect(TetrominoParams::SpriteRects::O); break;}
        case T: {m_sprite.setTextureRect(TetrominoParams::SpriteRects::T); break;}
        case S: {m_sprite.setTextureRect(TetrominoParams::SpriteRects::S); break;}
        case Z: {m_sprite.setTextureRect(TetrominoParams::SpriteRects::Z); break;}
        case J: {m_sprite.setTextureRect(TetrominoParams::SpriteRects::J); break;}
        case L: {m_sprite.setTextureRect(TetrominoParams::SpriteRects::L); break;}
        case EMPTY: {m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0)); break;}
    }
}

void GridCell::draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}

GridCellMatrix::GridCellMatrix()
{
}

void GridCellMatrix::initialize(sf::Vector2i position, sf::Vector2i size, bool activeTetromino)
{
    for (int iii = 0; iii < size.x; ++iii)
    {
        std::vector<GridCell> row;
        for (int jjj = 0; jjj < size.y; ++jjj)
        {
            GridCell cell;
            cell.setPosition(sf::Vector2i(position.x + iii, position.y + jjj));
            cell.activeTetromino = activeTetromino;
            row.push_back(cell);
        }
        m_cells.push_back(row);
    }
}

sf::Vector2i GridCellMatrix::getPosition()
{
    return m_cells[0][0].m_coordinates;
}

void GridCellMatrix::setPosition(sf::Vector2i position)
{
    sf::Vector2i initialPosition = getPosition();
    for (std::vector<GridCell> &row : m_cells)
    {
        for (GridCell &cell : row)
        {
            cell.m_coordinates.x += (position.x - initialPosition.x);
            cell.m_coordinates.y += (position.y - initialPosition.y);
        }
    }
}

void GridCellMatrix::setTypes(std::vector<sf::Vector2i> fillPositions, GridCell::Type type)
{
    for (sf::Vector2i &fillPosition : fillPositions)
    {
        m_cells[fillPosition.x][fillPosition.y].setType(type);
    }
}

void GridCellMatrix::setActiveTetrominoStatus(std::vector<sf::Vector2i> positions, bool activeTetromino)
{
    for (sf::Vector2i &position : positions)
    {
        m_cells[position.x][position.y].activeTetromino = activeTetromino;
    }
}

std::vector<std::vector<GridCell>>* GridCellMatrix::getCells()
{
    return &m_cells;
}

Grid::Grid()
{
    initialize(sf::Vector2i(0, 0), sf::Vector2i(GridParams::gridHeight, GridParams::gridWidth), false);
    m_linesNeeded = GameParams::linesNeededPerLevel;
    hardDropState = false;
}

Grid::GridMessage Grid::removeLines(int level, int &score)
{
    std::vector<std::vector<GridCell>> tempRows;
    GridCellMatrix firstRow;
    firstRow.initialize(sf::Vector2i(0, 0), sf::Vector2i(1, GridParams::gridWidth), false);
    
    for (int rowIndex : m_fullLines)
    {
        for (int iii {0}; iii < GridParams::gridHeight; ++iii)
        {
            if (iii != rowIndex)
                tempRows.push_back(m_cells[0]);
            m_cells.erase(m_cells.begin());
        }
        
        m_cells.push_back((*(firstRow.getCells()))[0]);
        for (std::vector<GridCell> &row : tempRows)
        {
            for (GridCell &cell : row)
            {
                if (cell.m_coordinates.x < rowIndex)
                    cell.m_coordinates.x += 1;
                cell.setPosition(cell.m_coordinates);
            }
            m_cells.push_back(row);
        }
        tempRows.clear();
    }
    
    score += (GameParams::scoresPerLine[m_fullLines.size() - 1] * (level + 1));
    m_linesNeeded -= m_fullLines.size();
    m_fullLines.clear();
    
    if (m_linesNeeded <= 0)
        return NEW_LEVEL;
    else
        return NONE;
}

void Grid::draw(sf::RenderWindow &window)
{
    for (std::vector<GridCell> &gridRow : m_cells)
    {
        for (GridCell &gridCell : gridRow)
        {
            gridCell.draw(window);
        }
    }
}

Grid::GridMessage Grid::update(sf::RenderWindow &window, Tetromino &tetromino)
{
    // Clear cells previously occupied by tetromino
    for (sf::Vector2i clearingCellCoord : tetromino.m_clearingCellCoords)
    {
        if (clearingCellCoord.x >= 0 && clearingCellCoord.y >= 0)
        {
            setTypes({sf::Vector2i(clearingCellCoord.x, clearingCellCoord.y)}, GridCell::Type::EMPTY);
            setActiveTetrominoStatus({sf::Vector2i(clearingCellCoord.x, clearingCellCoord.y)}, false);
        }
    }
    
    // Update grid cells to reflect tetromino
    for (std::vector<GridCell> &row : *(tetromino.m_boundingBox.getCells()))
    {
        for (GridCell &cell : row)
        {
            if (cell.m_coordinates.x >= 0 && cell.m_coordinates.x <= (GridParams::gridHeight - 1) && cell.m_coordinates.y >= 0 && cell.m_coordinates.y <= (GridParams::gridWidth - 1))
            {
                if (cell.m_type != GridCell::EMPTY) // If filled tetromino cell within bounding box
                {
                    m_cells[cell.m_coordinates.x][cell.m_coordinates.y].setType(cell.m_type);
                    m_cells[cell.m_coordinates.x][cell.m_coordinates.y].activeTetromino = true;
                }
                else // Empty cell within bounding box
                {
                    // If the corresponding grid cell is an active tetromino, make it inactive and set its sprite to empty
                    if (m_cells[cell.m_coordinates.x][cell.m_coordinates.y].activeTetromino)
                    {
                        m_cells[cell.m_coordinates.x][cell.m_coordinates.y].setType(cell.m_type);
                        m_cells[cell.m_coordinates.x][cell.m_coordinates.y].activeTetromino = false;
                    }
                    // else do nothing (let the cell stay as it is on the grid because it contains an inactive tetromino
                }
            }
        }
    }
    
    // If tetromino has come in resting position
    // 0. check if the tetromino was just spawned - if yes, then send game over signal
    // 1. set the corresponding grid cells to "inactive tetromino"
    // 2. check across the grid if there are any complete lines. if a complete line is found:
    //    - decrement lines needed and display new lines needed (>=0)
    //    - change grid cells to remove this line (shift all upper cells one cell down)
    //    - loop till the last low of the grid is reached
    //    - update scores
    // 3. check lines needed:
    //    - if lines needed <= 0, ask for new level
    //    - else ask for new tetromino
    if (tetromino.inRestingPosition(*this))
    {
        for (std::vector<GridCell> &row : *(tetromino.m_boundingBox.getCells()))
        {
            for (GridCell &cell : row)
            {
                // Game over?
                if (cell.m_type != GridCell::EMPTY && cell.m_coordinates.x == 0)
                    return GAME_OVER;
                // If not, continue with game
                if (cell.m_coordinates.x >= 0 && cell.m_coordinates.x <= (GridParams::gridHeight - 1) && cell.m_coordinates.y >= 0 && cell.m_coordinates.y <= (GridParams::gridWidth - 1))
                {
                    if (cell.m_type != GridCell::EMPTY) // Filled tetromino cell within bounding box
                        m_cells[cell.m_coordinates.x][cell.m_coordinates.y].activeTetromino = false;
                }
            }
        }
        
        int fullCellCount {0};
        for (std::vector<GridCell> &row: m_cells)
        {
            for (GridCell &cell : row)
            {
                if (cell.m_type != GridCell::EMPTY)
                    if (++fullCellCount == 10)
                        m_fullLines.push_back(cell.m_coordinates.x);
            }
            fullCellCount = 0;
        }
        if (m_fullLines.size() > 0)
        {
            return Grid::LINE_COMPLETED;
        }
        else
            return NEW_TETROMINO;
    }
    
    return NONE;
}
