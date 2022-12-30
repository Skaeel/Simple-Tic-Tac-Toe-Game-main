#include "Header.h"

#undef main
int main(int argc, char* argv[])
{
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return 1;

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN,
		&window, &renderer);

	if (window == 0)
		return 1;

	SDL_SetWindowTitle(window, "Tic-Tac-Toe Game");
	SDL_Event event;
	int clickInProgress = 0;
	int mouse_x = 0; int mouse_y = 0;

	int gameLoop = 1;
	clearGameData();
	while (gameLoop)
	{
		clearScreen();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				gameLoop = 0;

			if (winner == 0)
			{
				if (!clickInProgress && event.type == SDL_MOUSEBUTTONDOWN)
					clickInProgress = 1;

				if (clickInProgress && event.type == SDL_MOUSEBUTTONUP)
				{
					SDL_GetMouseState(&mouse_x, &mouse_y);
					int string = mouse_y / round(FIELD_SIZE);
					int row = mouse_x / round(FIELD_SIZE);

					if (fieldData[string][row] == 0)
					{
						fieldData[string][row] = currentPlayer;
						currentPlayer *= -1;
						checkWin();
					}
					clickInProgress = 0;
				}
			}
		}
		
		if (winner != 0)
		{
			if (SDLK_ESCAPE)
			{
				clearGameData();
				drawField();
			}
		}
		else
			drawField();
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}