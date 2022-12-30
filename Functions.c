#include "Header.h"

extern SDL_Surface* screen_surface = 0;
extern SDL_Window* window = 0;
extern SDL_Renderer* renderer = 0;
extern SDL_Color textColorP1 = { 255, 0,0 };
extern SDL_Color textColorP2 = { 0, 0, 255 };
extern const int SCREEN_WIDTH = 500;
extern const int SCREEN_HEIGHT = 500;
extern int currentPlayer = 1;
extern int winner = 0;

typedef struct _sColor {
	int r;
	int g;
	int b;
} sColor;

extern const sColor backGroudColor = { 255, 255, 255 };
extern const sColor fieldLineColor = { 0, 0, 0 };
extern const sColor crossLineColor = { 196, 0, 0 };
extern const sColor zeroLineColor = { 0, 0, 196 };

extern int fieldData[3][3] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

void checkWin()
{
	for (int string = 0; string < 3; ++string)
	{
		int sum1 = 0;
		int sum2 = 0;
		for (int row = 0; row < 3; ++row)
		{
			sum1 += fieldData[string][row];
			sum2 += fieldData[row][string];
		}

		if (sum1 == 3 || sum2 == 3)
		{
			winner = 1;
			break;
		}
		else if (sum1 == -3 || sum2 == -3)
		{
			winner = -1;
			break;
		}

		if (winner != 0)
			return;

		sum1 = 0;
		sum2 = 0;
		for (int i = 0; i < 3; ++i)
		{
			sum1 += fieldData[i][i];
			sum2 += fieldData[i][2 - i];
		}
		
		if (sum1 == 3 || sum2 == 3)
			winner = 1;
		else if (sum1 == -3 || sum2 == -3)
			winner = -1;
	}
}

void clearScreen()
{
	SDL_SetRenderDrawColor(renderer, backGroudColor.r, backGroudColor.g,
		backGroudColor.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void drawLine(int x, int y, int x1, int y1, sColor color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g,
		color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x, y, x1, y1);
}

void drawCircle(int x0, int y0, int radX, sColor color)
{
	float pi = 3.14159265358979323846264338327950288419716939937510;
	float pih = pi / 2.0;

	const int prec = 6;
	float theta = 0;

	int x = (float)radX * cos(theta);
	int y = (float)radX * sin(theta);
	int x1 = x;
	int y1 = y;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
		SDL_ALPHA_OPAQUE);

	float step = pih / (float)prec;
	for (theta = step; theta <= pih; theta += step)
	{
		x1 = (float)radX * cosf(theta) + 0.5;
		y1 = (float)radX * sinf(theta) + 0.5;

		if ((x != x1) || (y != y1))
		{
			SDL_RenderDrawLine(renderer, x0 + x, y0 - y, x0 + x1, y0 - y1);
			SDL_RenderDrawLine(renderer, x0 - x, y0 - y, x0 - x1, y0 - y1);
			SDL_RenderDrawLine(renderer, x0 - x, y0 + y, x0 - x1, y0 + y1);
			SDL_RenderDrawLine(renderer, x0 + x, y0 + y, x0 + x1, y0 + y1);
		}

		x = x1;
		y = y1;
	}

	if (x != 0)
	{
		x = 0;
		SDL_RenderDrawLine(renderer, x0 + x, y0 - y, x0 + x1, y0 - y1);
		SDL_RenderDrawLine(renderer, x0 - x, y0 - y, x0 - x1, y0 - y1);
		SDL_RenderDrawLine(renderer, x0 - x, y0 + y, x0 - x1, y0 + y1);
		SDL_RenderDrawLine(renderer, x0 + x, y0 + y, x0 + x1, y0 + y1);
	}
}

void drawCross(int string, int row)
{
	int x = row * FIELD_SIZE;
	int y = string * FIELD_SIZE;
	int indent = 10;
	drawLine(x + indent, y + indent, x + FIELD_SIZE - indent, y + FIELD_SIZE - indent, crossLineColor);
	drawLine(x + FIELD_SIZE - indent, y + indent, x + indent, y + FIELD_SIZE - indent, crossLineColor);
}

void drawZero(int string, int row)
{
	int x = row * FIELD_SIZE;
	int y = string * FIELD_SIZE;
	int rad = FIELD_SIZE / 2 - 10;
	drawCircle(x + FIELD_SIZE / 2, y + FIELD_SIZE / 2, rad, zeroLineColor);
}

void drawField()
{
	int offset = SCREEN_WIDTH / 3;
	for (int i = 0; i < 2; ++i)
	{
		drawLine(0, offset, SCREEN_WIDTH, offset, fieldLineColor);
		drawLine(offset, 0, offset, SCREEN_HEIGHT, fieldLineColor);
		offset += offset;
	}

	for (int string = 0; string < 3; ++string)
		for (int row = 0; row < 3; ++row)
		{
			if (fieldData[string][row] == 1)
				drawCross(string, row);
			else if (fieldData[string][row] == -1)
				drawZero(string, row);
		}
}

void clearGameData()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			fieldData[i][j] = 0;
	currentPlayer = 1;
	winner = 0;
}