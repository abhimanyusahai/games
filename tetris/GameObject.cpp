#include "GameObject.hpp"
#include <thread>

BaseGameGraphics::BaseGameGraphics()
{
    // Create Game Title
    m_gameTitle.setFont(g_resources.retroFont);
    m_gameTitle.setString(GraphicsParams::gameTitleString);
    m_gameTitle.setCharacterSize(GraphicsParams::gameTitleFontSize);
    m_gameTitle.setColor(GraphicsParams::gameTitleFontColor);
    m_gameTitle.setPosition(GraphicsParams::gameTitlePosition);
    
    // Create Grid Outline
    m_gridOutline.setSize(GraphicsParams::gridSize);
    m_gridOutline.setPosition(GraphicsParams::gridPosition);
    m_gridOutline.setFillColor(GraphicsParams::gridColor);
    m_gridOutline.setOutlineThickness(GraphicsParams::gridOutlineThickness);
    m_gridOutline.setOutlineColor(GraphicsParams::gridOutlineColor);
    
    // Create Instructions Box
    m_instructionBox.setSize(GraphicsParams::instructionBoxSize);
    m_instructionBox.setPosition(GraphicsParams::instructionBoxPosition);
    m_instructionBox.setFillColor(GraphicsParams::infoBoxColor);
    m_instructionBox.setOutlineThickness(GraphicsParams::infoBoxOutlineThickness);
    m_instructionBox.setOutlineColor(GraphicsParams::infoBoxOutlineColor);
    m_instructionBoxImage.setTexture(g_resources.instructionBoxImage);
    m_instructionBoxImage.setPosition(GraphicsParams::instructionBoxImagePosition);
    
    // Create Score Box
    m_scoreBox.setSize(GraphicsParams::scoreBoxSize);
    m_scoreBox.setPosition(GraphicsParams::scoreBoxPosition);
    m_scoreBox.setFillColor(GraphicsParams::infoBoxColor);
    m_scoreBox.setOutlineThickness(GraphicsParams::infoBoxOutlineThickness);
    m_scoreBox.setOutlineColor(GraphicsParams::infoBoxOutlineColor);
    m_scoreText.setFont(g_resources.retroFont);
    m_scoreText.setCharacterSize(GraphicsParams::scoreTextFontSize);
    m_scoreText.setColor(GraphicsParams::scoreTextColor);
    m_scoreText.setPosition(GraphicsParams::scoreTextPosition);
    m_scoreText.setString(GraphicsParams::scoreTextString);
    
    // Create Next Tetromino Box
    m_nextTetrominoBox.setSize(GraphicsParams::nextTetrominoBoxSize);
    m_nextTetrominoBox.setPosition(GraphicsParams::nextTetrominoBoxPosition);
    m_nextTetrominoBox.setFillColor(GraphicsParams::infoBoxColor);
    m_nextTetrominoBox.setOutlineThickness(GraphicsParams::infoBoxOutlineThickness);
    m_nextTetrominoBox.setOutlineColor(GraphicsParams::infoBoxOutlineColor);
    
    // Create Control Panel
    m_ActionButton.setTexture(g_resources.controlPanelImage);
    m_ActionButton.setTextureRect(GraphicsParams::playButtonSpriteCoord);
    m_ActionButton.setPosition(GraphicsParams::playButtonPosition);
    m_QuitButton.setTexture(g_resources.controlPanelImage);
    m_QuitButton.setTextureRect(GraphicsParams::quitButtonSpriteCoord);
    m_QuitButton.setPosition(GraphicsParams::quitButtonPosition);
}

// Replace the "Play" button by a "Reset button once the game is started
void BaseGameGraphics::changePlayToReset()
{
    m_ActionButton.setTextureRect(GraphicsParams::resetButtonSpriteCoord);
    m_ActionButton.setPosition(GraphicsParams::resetButtonPosition);
}

void BaseGameGraphics::draw(sf::RenderWindow &window) const
{
    window.draw(m_gameTitle);
    window.draw(m_gridOutline);
    window.draw(m_instructionBox);
    window.draw(m_instructionBoxImage);
    window.draw(m_scoreBox);
    window.draw(m_scoreText);
    window.draw(m_nextTetrominoBox);
    window.draw(m_ActionButton);
    window.draw(m_QuitButton);
}

GameObject::GameObject()
{
    m_level = 0;
    m_score = 0;
    m_framesPerLine = GameParams::FramesPerLine::level0;
    m_scoreText.setFont(g_resources.retroFont);
    m_scoreText.setCharacterSize(GraphicsParams::scoreTextFontSize);
    m_scoreText.setColor(GraphicsParams::scoreTextColor);
    m_scoreText.setString(std::to_string(m_level) + "\n\n      " + std::to_string(m_grid.m_linesNeeded) + "\n\n" + std::to_string(m_score));
    m_scoreText.setPosition(GraphicsParams::scorePosition);
    m_nextTetromino = Tetromino(m_currentTetromino);
    m_music.openFromFile(resourcePath() + AudioParams::songFileName);
    m_music.play();
    m_music.setLoop(true);
}

void GameObject::reset()
{
    m_music.play();
    m_music.setLoop(true);
    m_grid = Grid();
    m_currentTetromino = Tetromino();
    m_nextTetromino = Tetromino(m_currentTetromino);
    m_level = 0;
    m_score = 0;
    m_framesPerLine = GameParams::FramesPerLine::level0;
    m_scoreText.setString(std::to_string(m_level) + "\n\n      " + std::to_string(m_grid.m_linesNeeded) + "\n\n" + std::to_string(m_score));
}

Grid::GridMessage GameObject::updateGrid(sf::RenderWindow &window)
{
    switch(m_grid.update(window, m_currentTetromino))
    {
        case Grid::NEW_TETROMINO:
            m_currentTetromino = m_nextTetromino;
            m_nextTetromino = Tetromino(m_currentTetromino);
            return Grid::NEW_TETROMINO;
        case Grid::LINE_COMPLETED:
            return Grid::LINE_COMPLETED;
        case Grid::GAME_OVER:
            return Grid::GAME_OVER;
        case Grid::NONE:
            return Grid::NONE;
    }
}

MenuOptions::Option GameObject::displayGameOverMenu(sf::RenderWindow &window)
{
    sf::Sprite gameOverBox;
    gameOverBox.setTexture(g_resources.gameOverImage);
    gameOverBox.setPosition(GraphicsParams::gameOverBoxPosition);
    window.draw(gameOverBox);
    window.display();
    sf::Event event;
    while (true)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return MenuOptions::QUIT;
            }
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if ((event.mouseButton.button == sf::Mouse::Left) &&
                    (event.mouseButton.x > GraphicsParams::GameOver::resetButtonPosition.x) &&
                    (event.mouseButton.x  < (GraphicsParams::GameOver::resetButtonPosition.x + GraphicsParams::GameOver::resetButtonDimensions[0])) &&
                    (event.mouseButton.y  > GraphicsParams::GameOver::resetButtonPosition.y) &&
                    (event.mouseButton.y  < (GraphicsParams::GameOver::resetButtonPosition.y + GraphicsParams::GameOver::resetButtonDimensions[1])))
                {
                    reset();
                    return MenuOptions::RESET;
                }
                if ((event.mouseButton.button == sf::Mouse::Left) &&
                    (event.mouseButton.x > GraphicsParams::GameOver::quitButtonPosition.x) &&
                    (event.mouseButton.x  < (GraphicsParams::GameOver::quitButtonPosition.x + GraphicsParams::GameOver::quitButtonDimensions[0])) &&
                    (event.mouseButton.y  > GraphicsParams::GameOver::quitButtonPosition.y) &&
                    (event.mouseButton.y  < (GraphicsParams::GameOver::quitButtonPosition.y + GraphicsParams::GameOver::quitButtonDimensions[1])))
                {
                    return MenuOptions::QUIT;
                }
            }
        }
    }
}

void GameObject::draw(sf::RenderWindow &window, const BaseGameGraphics &baseGameGraphics)
{
    window.clear(GraphicsParams::windowBGColor);
    baseGameGraphics.draw(window);
    window.draw(m_scoreText);
    Tetromino nextTetromino;
    nextTetromino = m_nextTetromino;
    nextTetromino.draw(window);
    m_grid.draw(window);
    window.display();
}

void GameObject::play(sf::RenderWindow &window, const BaseGameGraphics &baseGameGraphics)
{
    sf::Time secondsPerLine;
    Tetromino nextTetromino;
    sf::Event event;
    while(window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            
            if (event.type == sf::Event::KeyPressed)
            {
                // Move tetromino left if left key pressed
                if (event.key.code == sf::Keyboard::Left)
                {
                    m_currentTetromino.shiftLeft(m_grid);
                    if (updateGrid(window) == Grid::GAME_OVER)
                        if (displayGameOverMenu(window) == MenuOptions::QUIT)
                            return;
                }
                
                // Move tetromino right if right key pressed
                if (event.key.code == sf::Keyboard::Right)
                {
                    m_currentTetromino.shiftRight(m_grid);
                    if (updateGrid(window) == Grid::GAME_OVER)
                        if (displayGameOverMenu(window) == MenuOptions::QUIT)
                            return;
                }
                
                // Rotate tetromino if up key pressed
                if (event.key.code == sf::Keyboard::Up)
                {
                    m_currentTetromino.rotate(m_grid);
                    if (updateGrid(window) == Grid::GAME_OVER)
                        if (displayGameOverMenu(window) == MenuOptions::QUIT)
                            return;
                }
                
                // Hard drop if down key is pressed
                if (event.key.code == sf::Keyboard::Down)
                    m_grid.hardDropState = true;
            }
            
            // Return to soft drop if down key released
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Down)
                    m_grid.hardDropState = false;
            }
            
            // Reset or quit if the appropriate mouse buttons are clicked on
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if ((event.mouseButton.button == sf::Mouse::Left) &&
                    (event.mouseButton.x > GraphicsParams::quitButtonPosition.x) &&
                    (event.mouseButton.x  < (GraphicsParams::quitButtonPosition.x + GraphicsParams::quitButtonSpriteCoord.width)) &&
                    (event.mouseButton.y  > GraphicsParams::quitButtonPosition.y) &&
                    (event.mouseButton.y  < (GraphicsParams::quitButtonPosition.y + GraphicsParams::quitButtonSpriteCoord.height)))
                {
                    return 0;
                }
                if ((event.mouseButton.button == sf::Mouse::Left) &&
                    (event.mouseButton.x > GraphicsParams::resetButtonPosition.x) &&
                    (event.mouseButton.x  < (GraphicsParams::resetButtonPosition.x + GraphicsParams::playButtonSpriteCoord.width)) &&
                    (event.mouseButton.y  > GraphicsParams::resetButtonPosition.y) &&
                    (event.mouseButton.y  < (GraphicsParams::resetButtonPosition.y + GraphicsParams::playButtonSpriteCoord.height)))
                {
                    reset();
                }
            }
        }
        
        // Move tetromino down one cell
        if (m_grid.hardDropState)
            secondsPerLine = sf::Time(sf::seconds(float(GameParams::FramesPerLine::hardDrop)/GameParams::framesPerSecond));
        else
            secondsPerLine = sf::Time(sf::seconds(float(m_framesPerLine)/GameParams::framesPerSecond));
        if (m_clock.getElapsedTime() >= secondsPerLine)
        {
            m_currentTetromino.moveDownOneCell();
            switch(updateGrid(window))
            {
                case Grid::GAME_OVER:
                    m_music.stop();
                    if (displayGameOverMenu(window) == MenuOptions::QUIT)
                        return;
                case Grid::LINE_COMPLETED:
                    draw(window, baseGameGraphics);
                    std::this_thread::sleep_for(GraphicsParams::pauseForLineClear);
                    m_currentTetromino = m_nextTetromino;
                    m_nextTetromino = Tetromino(m_currentTetromino);
                    if (m_grid.removeLines(m_level, m_score) == Grid::NEW_LEVEL)
                    {
                        m_scoreText.setString(std::to_string(m_level) + "\n\n      " + std::to_string(std::max(m_grid.m_linesNeeded, 0)) + "\n\n" + std::to_string(m_score));
                        draw(window, baseGameGraphics);
                        std::this_thread::sleep_for(GraphicsParams::pauseForNewLevel);
                        m_grid = Grid();
                        m_currentTetromino = Tetromino();
                        m_level += 1;
                        if (m_level < GameParams::FramesPerLine::pivot1)
                            m_framesPerLine -= GameParams::FramesPerLine::decrease1;
                        else if (m_level < GameParams::FramesPerLine::pivot2)
                            m_framesPerLine -= GameParams::FramesPerLine::decrease2;
                        else if (m_level < GameParams::FramesPerLine::maxLevel)
                            m_framesPerLine -= GameParams::FramesPerLine::decrease3;
                    }
                    m_scoreText.setString(std::to_string(m_level) + "\n\n      " + std::to_string(std::max(m_grid.m_linesNeeded, 0)) + "\n\n" + std::to_string(m_score));
            }
            m_clock.restart();
        }
        
        // Draw the game and grid, update score
        draw(window, baseGameGraphics);
    }
}
