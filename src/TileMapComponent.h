#pragma once
#include "SpriteComponent.h"
#include <string>
#include <vector>

namespace SGF
{
	class TileMapComponent : public SpriteComponent
	{
	public:
		TileMapComponent(Actor* owner, int tileWidth, int tileHeight, int drawOrder = 10);

		void loadFromFile(const std::string& filePath);
		void draw(SDL_Renderer* renderer) override;
		const std::vector<std::vector<int>>& getTileMap() const { return tileMap_; }

	private:
		std::vector<std::vector<int>> tileMap_;
		int tileWidth_;
		int tileHeight_;
	};
}
