#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#ifndef constants_h
#define constants_h

namespace GraphicsParams {
    // Fonts
    const std::string retroFontFileName {"Minecraft.ttf"};
    const std::string unicodeFontFileName {"Arial Unicode.ttf"};
    
    // Game Title
    const int gameTitleFontSize {36};
    const sf::Color gameTitleFontColor {sf::Color(255, 0, 168)};
    const sf::Vector2f gameTitlePosition {380, 10};
    const std::string gameTitleString {"TETRIS"};
    
    // Game Window
    const sf::VideoMode videoMode {sf::VideoMode(600, 650)};
    const sf::Color windowBGColor {sf::Color::Black};
    
    // Tetris Grid
    const sf::Vector2f gridSize {230, 460};
    const sf::Vector2f gridPosition {48, 75};
    const sf::Color gridColor {sf::Color::Black};
    const sf::Color gridOutlineColor {sf::Color::Blue};
    const int gridOutlineThickness = 5;
    
    // Information Boxes Basic Display
    const int infoBoxOutlineThickness = 3;
    const sf::Color infoBoxColor {sf::Color::Black};
    const sf::Color infoBoxOutlineColor {sf::Color(128, 128, 128)};
    const std::string instructionBoxImageFileName {"instructions_box_image.png"};
    const sf::Vector2f instructionBoxImagePosition {353, 82};
    const sf::Vector2f instructionBoxSize {200, 150};
    const sf::Vector2f instructionBoxPosition {350, 75};
    const sf::Vector2f nextTetrominoBoxSize {225, 75};
    const sf::Vector2f nextTetrominoBoxPosition {50, 555};
    const sf::Vector2f nextTetrominoImagePosition {130, 570};
    const sf::Vector2f scoreBoxSize {200, 150};
    const sf::Vector2f scoreBoxPosition {350, 275};
    const int scoreTextFontSize {24};
    const sf::Vector2f scoreTextPosition {360, 280};
    const sf::Color scoreTextColor {sf::Color::Yellow};
    const std::string scoreTextString {"Level:\n\n"
                                       "Lines Left:\n\n"
                                       "Score:\n\n"};
    const sf::Vector2f scorePosition {460, 280};
    
    // Control Panel
    const std::string controlPanelFileName {"control_panel_image.png"};
    const sf::IntRect playButtonSpriteCoord {0, 0, 100, 50};
    const sf::Vector2f playButtonPosition {345, 525};
    const sf::IntRect resetButtonSpriteCoord {0, 102, 100, 50};
    const sf::Vector2f resetButtonPosition {345, 525};
    const sf::IntRect quitButtonSpriteCoord {0, 51, 100, 50};
    const sf::Vector2f quitButtonPosition {455, 525};
    
    // Game Over!
    const std::string gameOverImageFileName {"game_over.png"};
    const sf::Vector2f gameOverBoxPosition {150, 150};
    namespace GameOver
    {
        const sf::Vector2f resetButtonPosition {gameOverBoxPosition.x + 40, gameOverBoxPosition.y + 100};
        const sf::Vector2f quitButtonPosition {gameOverBoxPosition.x + 160, gameOverBoxPosition.y + 100};
        const int resetButtonDimensions[2] {100, 50};
        const int quitButtonDimensions[2] {100, 50};
    }
    
    // Grid Parameters
    const int gridCellSideLength {static_cast<int>((GraphicsParams::gridSize.x)/10)};
    const std::chrono::milliseconds pauseForLineClear {1000};
    const std::chrono::milliseconds pauseForNewLevel {3000};
}

namespace AudioParams
{
    const std::string songFileName("korobeiniki.wav");
}

// Main Menu Controls
namespace MenuOptions
{
    enum Option {
        START,
        RESET,
        QUIT
    };
}

namespace TetrominoParams
{
    namespace SpriteRects
    {
        const sf::IntRect I {0, 0, 23, 23};
        const sf::IntRect O {0, 23, 23, 23};
        const sf::IntRect T {0, 46, 23, 23};
        const sf::IntRect S {0, 69, 23, 23};
        const sf::IntRect Z {0, 92, 23, 23};
        const sf::IntRect J {0, 115, 23, 23};
        const sf::IntRect L {0, 138, 23, 23};
    }
    
    namespace SpawningPosition // Coordinates of top left cell of tetromino sprite in the grid matrix, top left element of grid matrix is (0,-2)
    {
        const sf::Vector2i I {-2, 3};
        const sf::Vector2i O {-2, 4};
        const sf::Vector2i T {-2, 3};
        const sf::Vector2i S {-2, 3};
        const sf::Vector2i Z {-2, 3};
        const sf::Vector2i J {-2, 3};
        const sf::Vector2i L {-2, 3};
    }
    
    namespace BoundingBoxSize
    {
        const sf::Vector2i I {4, 4};
        const sf::Vector2i O {2, 2};
        const sf::Vector2i T {3, 3};
        const sf::Vector2i S {3, 3};
        const sf::Vector2i Z {3, 3};
        const sf::Vector2i J {3, 3};
        const sf::Vector2i L {3, 3};
    }
    
    namespace FilledPositions // Cells of bounded box filled in zero (normal) orientation
    {
        const std::vector<sf::Vector2i> I {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
        const std::vector<sf::Vector2i> O {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        const std::vector<sf::Vector2i> T {{0, 1}, {1, 0}, {1, 1}, {1, 2}};
        const std::vector<sf::Vector2i> S {{0, 1}, {0, 2}, {1, 0}, {1, 1}};
        const std::vector<sf::Vector2i> Z {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
        const std::vector<sf::Vector2i> J {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
        const std::vector<sf::Vector2i> L {{0, 2}, {1, 0}, {1, 1}, {1, 2}};
    }
    
    namespace SpriteCoords
    {
        const sf::IntRect I {0, 0, 92, 92};
        const sf::IntRect O {23, 92, 46, 46};
        const sf::IntRect T {0, 161, 69, 69};
        const sf::IntRect S {0, 230, 69, 69};
        const sf::IntRect Z {0, 299, 69, 69};
        const sf::IntRect J {0, 368, 69, 69};
        const sf::IntRect L {0, 437, 69, 69};
    }
    
    namespace SpriteOrigins
    {
        const sf::Vector2f I {(static_cast<float>(SpriteCoords::I.width))/2, (static_cast<float>(SpriteCoords::I.height))/2};
        const sf::Vector2f O {(static_cast<float>(SpriteCoords::O.width))/2, (static_cast<float>(SpriteCoords::O.height))/2};
        const sf::Vector2f T {(static_cast<float>(SpriteCoords::T.width))/2, (static_cast<float>(SpriteCoords::T.height))/2};
        const sf::Vector2f S {(static_cast<float>(SpriteCoords::S.width))/2, (static_cast<float>(SpriteCoords::S.height))/2};
        const sf::Vector2f Z {(static_cast<float>(SpriteCoords::Z.width))/2, (static_cast<float>(SpriteCoords::Z.height))/2};
        const sf::Vector2f J {(static_cast<float>(SpriteCoords::J.width))/2, (static_cast<float>(SpriteCoords::J.height))/2};
        const sf::Vector2f L {(static_cast<float>(SpriteCoords::L.width))/2, (static_cast<float>(SpriteCoords::L.height))/2};
    }
    const std::string blocksImageFileName {"blocks.png"};
}

namespace GridParams
{
    const int numOfHiddenRows {2};
    const int gridWidth {10};
    const int gridHeight {20};
}

namespace GameParams
{
    const int linesNeededPerLevel {10};
    const int framesPerSecond {60};
    const int maxLevel {29};
    namespace FramesPerLine {
        const int level0 {48};
        const int decrease1 {5};
        const int pivot1 {9};
        const int decrease2 {2};
        const int pivot2 {10};
        const int decrease3 {1};
        const int maxLevel {30};
        const int hardDrop {5};
    }
    static int scoresPerLine[4] {40, 100, 300, 1200};
}

enum class GridState
{
    NEW_TETROMINO,
    REGULAR
};

#endif /* constants_h */
