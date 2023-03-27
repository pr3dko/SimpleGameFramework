#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"

namespace SGF
{
	Game::Game(const std::string& title, int width, int height) :
		window_(nullptr),
		renderer_(nullptr),
		isRunning_(true),
		timer_(0),
		width_(width),
		height_(height),
		title_(title),
		updatingActors_(false)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			throw SDL_GetError();
		}

		window_ = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
		if (!window_)
		{
			throw SDL_GetError();
		}

		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer_)
		{
			throw SDL_GetError();
		}

		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			throw IMG_GetError();
		}
	}

	Game::~Game()
	{
		while (!actors_.empty())
		{
			delete actors_.back();
		}

		for (auto i : textures_)
		{
			SDL_DestroyTexture(i.second);
		}

		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);

		IMG_Quit();
		SDL_Quit();
	}

	void Game::run()
	{
		while (isRunning_)
		{
			processInput();
			update();
			render();
		}
	}

	void Game::addActor(Actor* actor)
	{
		if (updatingActors_)
		{
			pendingActors_.push_back(actor);
		}
		else
		{
			actors_.push_back(actor);
		}
	}

	void Game::removeActor(Actor* actor)
	{
		// Check if actor is in pending list first
		auto iter = std::find(pendingActors_.begin(), pendingActors_.end(), actor);
		if (iter != actors_.end())
		{
			pendingActors_.erase(iter);
		}

		// Check if actor is in regular actor list
		iter = std::find(actors_.begin(), actors_.end(), actor);
		if (iter != actors_.end())
		{
			actors_.erase(iter);
		}
	}

	void Game::addSprite(SpriteComponent* sprite)
	{
		// Sprites must be inserted into the correct position to maintain order of drawing
		auto insertPoint = std::find_if(sprites_.begin(), sprites_.end(),
			[=](SpriteComponent* existingSprite) {return existingSprite->getDrawOrder() > sprite->getDrawOrder(); });
		sprites_.insert(insertPoint, sprite);
	}

	void Game::removeSprite(SpriteComponent* sprite)
	{
		auto iter = std::find(sprites_.begin(), sprites_.end(), sprite);
		sprites_.erase(iter);
	}

	void Game::processInput()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					isRunning_ = false;
					break;
			}
		}

		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		if (keyboardState[SDL_SCANCODE_ESCAPE])
		{
			isRunning_ = false;
		}

		updatingActors_ = true;
		for (auto actor : actors_)
		{
			actor->processInput(keyboardState);
		}
		updatingActors_ = false;
	}

	void Game::update()
	{
		// Cap frame time to 16ms (for 60fps)
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), timer_ + 16));

		// Calculate the time in seconds since the last frame
		float deltaTime = (SDL_GetTicks() - timer_) / 1000.0f;

		// Cap deltaTime if it gets too large (e.g. when debugging)
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}

		timer_ = SDL_GetTicks();

		updatingActors_ = true;
		for (auto actor : actors_)
		{
			actor->update(deltaTime);
		}
		updatingActors_ = false;

		for (auto actor : pendingActors_)
		{
			actors_.push_back(actor);
		}
		pendingActors_.clear();

		// Collect any actors that may have been killed while updating
		std::vector<Actor*> deadActors;
		for (auto actor : actors_)
		{
			if (actor->getState() == Actor::State::Dead)
			{
				deadActors.push_back(actor);
			}
		}
		// and remove them from game
		for (auto actor : deadActors)
		{
			delete actor;
		}
	}

	void Game::render()
	{
		// Clear screen
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
		SDL_RenderClear(renderer_);

		// Draw sprites
		for (auto sprite : sprites_)
		{
			sprite->draw(renderer_);
		}

		// Swap front and back image buffer
		SDL_RenderPresent(renderer_);
	}

	SDL_Texture* Game::getTexture(const std::string & filePath)
	{
		auto iter = textures_.find(filePath);
		if (iter != textures_.end())
		{
			return iter->second;
		}
		else
		{
			SDL_Surface* surface = IMG_Load(filePath.c_str());
			if (!surface)
			{
				SDL_Log("Failed to load image at %s. Error: %s\n", filePath.c_str(), IMG_GetError());
				return nullptr;
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
			SDL_FreeSurface(surface);
			if (!texture)
			{
				SDL_Log("Failed to create texture from surface. Error: %s\n", IMG_GetError());
				return nullptr;
			}

			textures_.emplace(filePath, texture);
			return texture;
		}
	}
}

