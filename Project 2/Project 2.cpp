#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "CC212SGL.h"
#define MR 21
#define MC 19

int SCREEN_X;
int SCREEN_Y;

//Link to the Graphics .lib file
#pragma comment(lib, "CC212SGL.lib")

//Declare instance from the Graphics Library
CC212SGL gr;

//Enum for directions
typedef enum { UP, DOWN, LEFT, RIGHT, NONE } Direction;

void waitFor(int start, int threshold)
{
	while (true)
	{
		float _t = (clock() / (float)CLOCKS_PER_SEC * 1000.0f - start / (float)CLOCKS_PER_SEC * 1000.0f);
		if (_t >= threshold)
			break;
	}
}

void map1draw(int map[MR][MC], int tile_size, int x, int y, int pac_x, int pac_y, int screenWidth, bool isAligned, int gridX, int gridY, int* pass) {
	int s = tile_size - 2;
	int food_eaten = 0;
	*pass = *pass + 1;
	if (*pass == 1)
		*pass = 0;
	/*
	Numbers meaning
	0 for un eaten food
	1 for wall
	2 for intial empty place
	3 for the starting bariar for the gosts
	4 for the portal
	5 for the portal
	10 for the food eaten
	61 for right half circle
	62 for left half circle
	63 for upper circle
	64 for downward circle
	*/

	// Drawing map
	for (int i = 0; i < MR; i++)
	{

		for (int j = 0; j < MC; j++)
		{
			if (map[i][j] == 1)
			{
				// Draw walls
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidRectangle(x, y, tile_size - 2, tile_size - 2);
			}
			else if (map[i][j] == 0 && i < MR)
			{
				// Draw food that is not eaten

				gr.setDrawingColor(COLORS::WHITE);
				gr.drawSolidCircle(x + ((tile_size - 0.15 * s) / 2), y + ((tile_size - 0.15 * s) / 2), 0.3 * s);
			}
			else if (map[i][j] == 2) {}
			else if (map[i][j] == 10) {
				food_eaten++;
			}
			else if (map[i][j] == 3) {
				gr.setDrawingColor(COLORS::WHITE);
				gr.drawSolidRectangle(x - 2, y + 1, tile_size + 2, tile_size / 4);
			}
			else if (map[i][j] == 5) {//right portal
				gr.setDrawingColor(COLORS::WHITE);
				gr.drawSolidEllipse(x + tile_size - tile_size / 3, y, tile_size / 3, tile_size);
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidEllipse((x + tile_size - tile_size / 3) + tile_size / 12, y + tile_size / 4, tile_size / 6, tile_size / 2);
			}
			else if (map[i][j] == 4) {//left portal
				gr.setDrawingColor(COLORS::WHITE);
				gr.drawSolidEllipse(x, y, tile_size / 3, tile_size);
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidEllipse(x + tile_size / 12, y + tile_size / 4, tile_size / 6, tile_size / 2);
			}
			else if (map[i][j] == 61) {
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidCircle(x, y, tile_size - 2);
				gr.drawSolidRectangle(x + tile_size / 2, y, tile_size / 2, tile_size - 2);
			}
			else if (map[i][j] == 62) {
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidCircle(x, y, tile_size - 2);
				gr.drawSolidRectangle(x - 2, y, tile_size / 2, tile_size - 2);
			}
			else if (map[i][j] == 63) {
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidCircle(x, y, tile_size - 2);
				gr.drawSolidRectangle(x, y + tile_size / 2, tile_size - 2, tile_size / 2);
			}
			else if (map[i][j] == 64) {
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidCircle(x, y, tile_size - 2);
				gr.drawSolidRectangle(x, y - 2, tile_size - 2, tile_size / 2);
			}
			if (isAligned && map[gridY][gridX] == map[i][j] && map[i][j] == 0) {
				map[gridY][gridX] = 10;
			}
			// Draw Pac-Man
			gr.setDrawingColor(COLORS::YELLOW);
			gr.drawSolidCircle(pac_x + s, pac_y + s, tile_size - 2 * s);
			//show score
			gr.setDrawingColor(COLORS::YELLOW);
			gr.drawSolidCircle(0, 0, 50);
			gr.setDrawingColor(COLORS::BLACK);
			gr.drawSolidCircle(10, 10, 10);
			gr.drawSolidCircle(30, 5, 10);
			gr.drawSolidEllipse(22, 15, 20, 28);
			gr.drawSolidRectangle(80, 0, 200, 100);
			char scoreString[5];
			itoa(food_eaten, scoreString, 10);
			char scoreinText[20] = "Score: ";
			strcat(scoreinText, scoreString);

			gr.setDrawingColor(COLORS::WHITE);
			gr.setFontSizeAndBoldness(50, 3);

			int centerText_X = 80; // x position at the center of the map
			int centerText_y = 0; // y position slightly below the map

			gr.drawText(centerText_X, centerText_y, scoreinText);

			x += tile_size;
		}
		y += tile_size;
		x = SCREEN_X;
	}

}

void motion(Direction* bufferdir)
{
	if (kbhit())
	{
		char c = getch();

		// Only change direction if Pac-Man is moving
		switch (c)
		{
		case 'w': *bufferdir = UP; break;
		case 'a': *bufferdir = LEFT; break;
		case 's': *bufferdir = DOWN; break;
		case 'd': *bufferdir = RIGHT; break;
		case 'W': *bufferdir = UP; break;
		case 'A': *bufferdir = LEFT; break;
		case 'S': *bufferdir = DOWN; break;
		case 'D': *bufferdir = RIGHT; break;
		}
	}
}

int main()
{
	int tile_size = 50;
	int speed = tile_size;
	int pass = 0;

	SCREEN_X = (gr.getWindowWidth() + MC * tile_size) / 2;
	SCREEN_Y = 0;

	gr.setup();
	gr.setFullScreenMode();
	gr.hideCursor(); // Hide the cursor. It's annoying

	Direction pacmanDir = NONE;
	Direction bufferedDir = NONE;



	int map[MR][MC] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,61,62,0,61,1,62,0,1,0,61,62,0,61,1,62,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,61,62,0,1,0,1,1,1,1,1,0,1,0,61,62,0,1},
		{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
		{1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
		{2,2,2,1,0,1,0,0,0,0,0,0,0,1,0,1,2,2,2},
		{1,1,1,1,0,1,0,1,3,3,3,1,0,1,0,1,1,1,1},
		{4,0,0,0,0,0,0,1,2,2,2,1,0,0,0,0,0,0,5},
		{1,1,1,1,0,63,0,1,1,1,1,1,0,63,0,1,1,1,1},
		{2,2,2,1,0,1,0,0,0,0,0,0,0,1,0,1,2,2,2},
		{1,1,1,1,0,64,0,1,1,1,1,1,0,64,0,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,0,61,1,62,0,1,0,61,1,62,0,1,1,0,1},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,62,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,61,1},
		{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

	};


	int screenWidth = (int)gr.getWindowWidth();
	int screenHeight = (int)gr.getWindowHeight();


	int pac_x = (SCREEN_X)+tile_size;
	int pac_y = (SCREEN_Y)+tile_size;

	bool isMoving = false;
	Direction movingBuffer;


	while (true) //Endless loop to render the graphics and perform the logic
	{
		int frame_start = clock(); //Time Control Start
		int y = (SCREEN_Y);
		int x = (SCREEN_X);


		int gridX = (int)((pac_x - SCREEN_X) / tile_size);
		int gridY = (int)((pac_y - SCREEN_Y) / tile_size);

		bool isAligned = (pac_x - SCREEN_X) % (tile_size) == 0 && ((pac_y - SCREEN_Y) % tile_size) == 0;

		char str[200];


		// Check for direction change
		if (isAligned && bufferedDir != pacmanDir)
		{
			int targetX = gridX, targetY = gridY;

			if (bufferedDir == UP)
				targetY -= 1;
			if (bufferedDir == LEFT)
				targetX -= 1;
			if (bufferedDir == DOWN)
				targetY += 1;
			if (bufferedDir == RIGHT)
				targetX += 1;
			//if (bufferedDir == NONE) {}

			if (map[targetY][targetX] != 1 && map[targetY][targetX] != 61 && map[targetY][targetX] != 62 && map[targetY][targetX] != 63 && map[targetY][targetX] != 64)
				pacmanDir = bufferedDir;
		}

		if (((map[gridY - 1][gridX] == 1 && pacmanDir == UP) || (map[gridY][gridX + 1] == 1 && pacmanDir == RIGHT) || (map[gridY + 1][gridX] == 1 && pacmanDir == DOWN) || (map[gridY][gridX - 1] == 1 && pacmanDir == LEFT)) || ((map[gridY - 1][gridX] == 61 && pacmanDir == UP) || (map[gridY][gridX + 1] == 61 && pacmanDir == RIGHT) || (map[gridY + 1][gridX] == 61 && pacmanDir == DOWN) || (map[gridY][gridX - 1] == 61 && pacmanDir == LEFT)) || ((map[gridY - 1][gridX] == 62 && pacmanDir == UP) || (map[gridY][gridX + 1] == 62 && pacmanDir == RIGHT) || (map[gridY + 1][gridX] == 62 && pacmanDir == DOWN) || (map[gridY][gridX - 1] == 62 && pacmanDir == LEFT)) || ((map[gridY - 1][gridX] == 62 && pacmanDir == UP) || (map[gridY][gridX + 1] == 62 && pacmanDir == RIGHT) || (map[gridY + 1][gridX] == 62 && pacmanDir == DOWN) || (map[gridY][gridX - 1] == 62 && pacmanDir == LEFT)) || ((map[gridY - 1][gridX] == 63 && pacmanDir == UP) || (map[gridY][gridX + 1] == 63 && pacmanDir == RIGHT) || (map[gridY + 1][gridX] == 63 && pacmanDir == DOWN) || (map[gridY][gridX - 1] == 63 && pacmanDir == LEFT)) || ((map[gridY - 1][gridX] == 64 && pacmanDir == UP) || (map[gridY][gridX + 1] == 64 && pacmanDir == RIGHT) || (map[gridY + 1][gridX] == 64 && pacmanDir == DOWN) || (map[gridY][gridX - 1] == 64 && pacmanDir == LEFT)))
			pacmanDir = NONE;
		if (map[gridY][gridX] == 4) {
			pac_x += tile_size * MC - 2 * tile_size;
			gridX += tile_size * MC - 2 * tile_size;
		}
		if (map[gridY][gridX] == 5) {
			pac_x -= tile_size * MC - 2 * tile_size;
			gridX -= tile_size * MC - 2 * tile_size;
		}


		if (pacmanDir == UP)
			pac_y -= speed;
		if (pacmanDir == LEFT)
			pac_x -= speed;
		if (pacmanDir == DOWN)
			pac_y += speed;
		if (pacmanDir == RIGHT)
			pac_x += speed;



		// Rendering
		gr.beginDraw();

		//draw map
		map1draw(map, tile_size, x, y, pac_x, pac_y, screenWidth, isAligned, gridX, gridY, &pass);

		// Handle key press to change direction
		motion(&bufferedDir);


		gr.endDraw();

		// Time Control End
		waitFor(frame_start, 1.0 / 30 * 1000);
	}

	return 0;
}