#include "TileMapComponent.h"
#include <fstream>
#include <sstream>
#include "Actor.h"

namespace SGF
{
	TileMapComponent::TileMapComponent(Actor* owner, int tileWidth, int tileHeight, int drawOrder) :
		SpriteComponent(owner, drawOrder),
		tileWidth_(tileWidth),
		tileHeight_(tileHeight)
	{

	}

	void TileMapComponent::loadFromFile(const std::string& filePath)
	{
		tileMap_.clear();

		std::ifstream file(filePath);
		if (!file.is_open())
		{
			SDL_Log("Failed to open tile map file at %s\n", filePath.c_str());
			return;
		}

		std::string line;
		while (std::getline(file, line))
		{
			std::vector<int> temp;
			std::istringstream ss(line);
			for (int i; ss >> i; )
			{
				temp.push_back(i);
				if (ss.peek() == ',')
				{
					ss.ignore();
				}
			}

			tileMap_.emplace_back(std::move(temp));
		}
	}

	void TileMapComponent::draw(SDL_Renderer* renderer)
	{
		if (texture_)
		{
			// Assume the owner of a tilemap component has a scale of 1.0
			SDL_Rect destRect, srcRect;
			destRect.w = srcRect.w = tileWidth_;
			destRect.h = srcRect.h = tileHeight_;

			int tileMapWidth = tileMap_[0].size() * tileWidth_;
			int tileMapHeight = tileMap_.size() * tileHeight_;

			int srcImageCols = width_ / tileWidth_;

			for (std::vector<std::vector<int>>::size_type row = 0; row < tileMap_.size(); row++)
			{
				destRect.y = static_cast<int>(owner_->getPosition().y - tileMapHeight / 2 + row * tileHeight_);

				for (std::vector<int>::size_type col = 0; col < tileMap_[0].size(); col++)
				{
					destRect.x = static_cast<int>(owner_->getPosition().x - tileMapWidth / 2 + col * tileWidth_);
					srcRect.x = (tileMap_[row][col] % srcImageCols) * tileWidth_;
					srcRect.y = static_cast<int>(tileMap_[row][col] / srcImageCols) * tileHeight_;
					SDL_RenderCopy(renderer, texture_, &srcRect, &destRect);
				}
			}
		}
	}

}
