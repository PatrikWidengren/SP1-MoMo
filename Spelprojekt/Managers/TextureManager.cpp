#include "TextureManager.h"
#include <iostream>
#include <string>

static const std::string filename_Grass_Uncut = "Resource Files/Sprites/Grass01_Uncut.png";
static const std::string filename_Grass_Cut = "Resource Files/Sprites/Grass01_Cut.png";

TextureManager::TextureManager() {
	holder.acquire("Grass_Uncut", thor::Resources::fromFile<sf::Texture>(filename_Grass_Uncut));
	holder.acquire("Grass_Cut", thor::Resources::fromFile<sf::Texture>(filename_Grass_Cut));
}

TextureManager::~TextureManager() {
	holder.release("Grass_Uncut");
	holder.release("Grass_Cut");
}

sf::Texture& TextureManager::getTexture(char id) {
	return &holder.acquire[id];
}