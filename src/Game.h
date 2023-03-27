#pragma once
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace SGF
{
	class Actor;
	class SpriteComponent;

	class Game
	{
	public:
		Game(const std::string& title, int width = 1024, int height = 768);
		virtual ~Game();

		void run();

		void addActor(Actor* actor);
		void removeActor(Actor* actor);

		void addSprite(SpriteComponent* sprite);
		void removeSprite(SpriteComponent* sprite);

		int getWidth() const { return width_; }
		int getHeight() const { return height_; }

		SDL_Texture* getTexture(const std::string& filePath);

	protected:
		virtual void processInput();
		void update();
		void render();
		virtual void loadData() = 0;

		SDL_Window* window_;
		SDL_Renderer* renderer_;
		bool isRunning_;
		uint32_t timer_;
		int width_;
		int height_;
		std::string title_;

		std::vector<Actor*> actors_;
		std::vector<Actor*> pendingActors_;
		bool updatingActors_;

		std::unordered_map<std::string, SDL_Texture*> textures_;
		std::vector<SpriteComponent*> sprites_;
	};
}

