#ifndef INCLUDED_TEXTUREMANAGER
#define INCLUDED_TEXTUREMANAGER

#include <SFML\Graphics.hpp>
#include <thor\Resources.hpp>

class TextureManager {
public:
	TextureManager();
	~TextureManager();
	sf::Texture& getTexture(char id);
private:
	/*typedef std::vector<sf::Texture*> TextureList;
	TextureList mTextureList;*/
	thor::ResourceHolder<sf::Texture, std::string> holder;
};

#endif