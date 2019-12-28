#include "Engine.h"

Engine::Engine(std::string name)
{
	Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);

		window = SDL_CreateWindow(name.c_str(), (displayMode.w - WINDOW_WIDTH) / 2, (displayMode.h - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT, flags);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		surface = SDL_GetWindowSurface(window);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_UpdateWindowSurface(window);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	}

	int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!IMG_Init(imageFlags) & imageFlags) std::cout << "Unable to initialise Images..." << std::endl;

	if (TTF_Init() == -1) std::cout << "Unable to initialise Fonts..." << std::endl;

	engineState = RUNNING;

	object = new Object(typeid(1));
	object->AddComponent<TransformComponent>();
	object->AddComponent<SpriteComponent>(surface, renderer, "Resources/Sprites/Red.png");

	std::cout << "Constructed Object with index: " << object->GetIndex().hash_code() << std::endl;
}

void Engine::Render()
{
	SDL_RenderClear(renderer);

	object->Render(renderer);

	SDL_RenderPresent(renderer);
}

void Engine::Process()
{
	lastFrame = currentFrame;
	currentFrame = SDL_GetPerformanceCounter();

	object->Process((currentFrame - lastFrame) / SDL_GetPerformanceFrequency());
}

void Engine::Listen()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT: {
			engineState = STOP;
			break;
		}
		default:
			break;
	}
}

void Engine::Clean()
{
	delete object;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	exit(0);
}

EngineState Engine::GetState() const
{
	return engineState;
}
