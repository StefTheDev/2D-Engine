#include "Engine.h"


int main(int argc, char* argv[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine* engine = new Engine("2DEngine");

	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;

	Uint32 startFrame, timeFrame;

	while (engine->GetState() != STOP)
	{
		startFrame = SDL_GetTicks();

		engine->Render();
		engine->Process();
		engine->Listen();

		timeFrame = SDL_GetTicks() - startFrame;

		if (FRAME_DELAY > timeFrame) SDL_Delay(FRAME_DELAY - timeFrame);
	}

	engine->Clean();

	delete engine;

	return 0;
}