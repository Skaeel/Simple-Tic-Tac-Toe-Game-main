#pragma once

#ifndef _HEADER
#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>

#define _HEADER
#define FIELD_SIZE  SCREEN_WIDTH / 3

SDL_Surface* screen_surface;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* text;
SDL_Color textColorP1;
SDL_Color textColorP2;

const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;

typedef struct _sColor sColor;

int fieldData[3][3];
int currentPlayer;
int winner;

void checkWin();
void clearScreen();
void drawLine(int x, int y, int x1, int x2, sColor color);
void drawCircle(int x0, int y0, int radX, sColor color);
void drawCross(int string, int row);
void drawZero(int string, int row);
void drawField();
void clearGameData();

#endif  !_HEADER