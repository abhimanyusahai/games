#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "constants.h"

struct Resources
{
    sf::Font retroFont;
    sf::Texture instructionBoxImage;
    sf::Texture controlPanelImage;
    sf::Texture blocksImage;
    sf::Texture gameOverImage;
};

static Resources loadResources(std::string retroFontFileName, std::string instructionBoxFileName, std::string controlPanelFileName, std::string blocksImageFileName,
                        std::string gameOverImageFileName)
{
    Resources resources;
    resources.retroFont.loadFromFile(resourcePath() + retroFontFileName);
    resources.instructionBoxImage.loadFromFile(resourcePath() + instructionBoxFileName);
    resources.controlPanelImage.loadFromFile(resourcePath() + controlPanelFileName);
    resources.blocksImage.loadFromFile(resourcePath() + blocksImageFileName);
    resources.gameOverImage.loadFromFile(resourcePath() + gameOverImageFileName);
    return resources;
}

static Resources g_resources = loadResources(GraphicsParams::retroFontFileName, GraphicsParams::instructionBoxImageFileName, GraphicsParams::controlPanelFileName, TetrominoParams::blocksImageFileName, GraphicsParams::gameOverImageFileName);