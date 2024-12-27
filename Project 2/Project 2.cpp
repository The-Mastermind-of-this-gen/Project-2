#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include<Windows.h>
#include<iostream>
#include<mmsystem.h>
#include<playsoundapi.h>
#pragma comment(lib, "winmm.lib")

#include "CC212SGL.h"
#define MR 21
#define MC 19
int SCREEN_X;
int SCREEN_Y;
int bufferX, bufferY;



//Link to the Graphics .lib file
#pragma comment(lib, "CC212SGL.lib")
//Declare instance from the Graphics 
CC212SGL gr;
//Enum for directions
typedef enum { UP, DOWN, LEFT, RIGHT, NONE,BD } Direction;

void waitFor(int start, int threshold)
{
	while (true)
	{
		float _t = (clock() / (float)CLOCKS_PER_SEC * 1000.0f - start / (float)CLOCKS_PER_SEC * 1000.0f);
		if (_t >= threshold)
			break;
	}
}

void P_C_F(int pac_x,int pac_y,int pacman_frames[6][4],int tile_size,int PCF,Direction* BD) {
	if (*BD==UP) {
		gr.drawImage(pacman_frames[PCF][1],pac_x,pac_y,gr.generateFromRGB(0,0,0));
	}
	if (*BD == RIGHT) {
		gr.drawImage(pacman_frames[PCF][2], pac_x, pac_y, gr.generateFromRGB(0, 0, 0));
	}
	if (*BD == LEFT) {
		gr.drawImage(pacman_frames[PCF][3], pac_x, pac_y, gr.generateFromRGB(0, 0, 0));
	}
	if (*BD == DOWN) {
		gr.drawImage(pacman_frames[PCF][0], pac_x, pac_y, gr.generateFromRGB(0, 0, 0));
	}
	if (*BD == NONE) {
			gr.drawImage(pacman_frames[PCF][0], pac_x, pac_y, gr.generateFromRGB(0, 0, 0));
		}

}
void loading_screen(int tile_size) {
	int loading = gr.loadImage("loading.png");

	SCREEN_X = (gr.getWindowWidth() - MC * tile_size) / 2;
	SCREEN_Y = gr.getWindowHeight() / 2;
	int loaded = 10;
	PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (true) {
		int frame_start = clock(); //Time Control Start
		gr.beginDraw();
		gr.drawImage(loading, SCREEN_X + 100, SCREEN_Y / 4, gr.generateFromRGB(0, 0, 0));
		gr.setDrawingColor(COLORS::BLUE);
		gr.drawSolidRectangle(SCREEN_X - 50, SCREEN_Y * 1.2, SCREEN_X * 2 + 30, 30);
		gr.setDrawingColor(COLORS::WHITE);
		gr.drawSolidRectangle(SCREEN_X - 45, SCREEN_Y * 1.2 + 5, loaded, 20);
		loaded += 5;
		if (loaded >= (SCREEN_X * 2 + 25))
			break;
		gr.endDraw();
		// Time Control End
		waitFor(frame_start, 1.0 / 30 * 1000);
	}
	//loading Frames
}
int main_menu(int tile_size) {
	int frame_start = clock(); //Time Control Start
	SCREEN_X = (gr.getWindowWidth() - MC * tile_size) / 2;
	SCREEN_Y = gr.getWindowHeight() / 2;
	int loading = gr.loadImage("loading.png");
	int logo_animate = SCREEN_Y / 4;
	int counter = 0;

	int choice_posX = SCREEN_X * 1.6;
	int choice_posY = SCREEN_Y * 4 / 5;
	char choice = 1;
	int iswhere = 1;
	char start[] = "start";
	char exit[] = "EXIT";
	char options[] = "Options";
	char highest_score[] = "Highest Score";

	while (choice == 1) {
		int frame_start = clock(); //Time Control Start

		if (kbhit()) {
			if (kbhit())
			{
				char c = getch();

				// Only change direction if Pac-Man is moving
				switch (c)
				{
				case 'w':iswhere--; break;
				case 's': iswhere++; break;
				case 'W': iswhere--; break;
				case 'S': iswhere++; break;
				}
				if (c == 13 && iswhere == 1)
					return 1;
				if (c == 13 && iswhere == 3) {
					return 2;
				}
				if (iswhere < 1)
					iswhere = 1;
				if (iswhere > 4)
					iswhere = 4;
			}
		}



		gr.beginDraw();
		gr.drawImage(loading, SCREEN_X + 100, logo_animate, gr.generateFromRGB(0, 0, 0));
		if (counter <= 15) {
			logo_animate -= 15;
			counter++;
		}
		/*else if (counter <= 50) {
			gr.setDrawingColor(COLORS::BLUE);
			gr.drawSolidRectangle(choice_pos, SCREEN_Y * 1.2, SCREEN_X * 2 + 30, 30);
			gr.setDrawingColor(COLORS::WHITE);
			gr.drawSolidRectangle(choice_pos, SCREEN_Y * 1.2 + 5,100, 50);

			counter++;
		}*/
		else {
			//start
			gr.setDrawingColor(COLORS::BLUE);
			if (iswhere == 1) {
				gr.setDrawingColor(COLORS::WHITE);
			}
			gr.drawSolidRectangle(choice_posX, choice_posY, 315, 100);
			gr.drawSolidCircle(choice_posX - 50, choice_posY, 100);
			gr.drawSolidCircle(choice_posX + 260, choice_posY, 100);
			gr.setDrawingColor(COLORS::WHITE);
			gr.setFontSizeAndBoldness(100, 100);
			gr.drawText(choice_posX + 70, choice_posY - 5, start);
			if (iswhere == 1) {
				gr.setDrawingColor(COLORS::BLUE);
				gr.setFontSizeAndBoldness(100, 100);
				gr.drawText(choice_posX + 70, choice_posY - 5, start);
			}

			//highest score

			gr.setDrawingColor(COLORS::BLUE);
			if (iswhere == 2) {
				gr.setDrawingColor(COLORS::WHITE);
			}
			gr.drawSolidRectangle(choice_posX, choice_posY + 150, 315, 100);
			gr.drawSolidCircle(choice_posX - 50, choice_posY + 150, 100);
			gr.drawSolidCircle(choice_posX + 260, choice_posY + 150, 100);
			gr.setDrawingColor(COLORS::WHITE);
			gr.setFontSizeAndBoldness(65, 100);
			gr.drawText(choice_posX - 15, choice_posY + 165, highest_score);
			if (iswhere == 2) {
				gr.setDrawingColor(COLORS::BLUE);
				gr.setFontSizeAndBoldness(65, 100);
				gr.drawText(choice_posX - 15, choice_posY + 165, highest_score);
			}

			//exit

			gr.setDrawingColor(COLORS::BLUE);
			if (iswhere == 3) {
				gr.setDrawingColor(COLORS::WHITE);
			}
			gr.drawSolidRectangle(choice_posX, choice_posY + 300, 315, 100);
			gr.drawSolidCircle(choice_posX - 50, choice_posY + 300, 100);
			gr.drawSolidCircle(choice_posX + 260, choice_posY + 300, 100);
			gr.setDrawingColor(COLORS::WHITE);
			gr.setFontSizeAndBoldness(100, 100);
			gr.drawText(choice_posX + 65, choice_posY + 305, exit);
			if (iswhere == 3) {
				gr.setDrawingColor(COLORS::BLUE);
				gr.setFontSizeAndBoldness(100, 100);
				gr.drawText(choice_posX + 65, choice_posY + 305, exit);
			}
		}
		gr.endDraw();

		// Time Control End
		waitFor(frame_start, 1.0 / 30 * 1000);
	}
	gr.endDraw();
	// Time Control End
	waitFor(frame_start, 1.0 / 30 * 1000);


}

void gameover(int game_over,int tile_size) {//game ending condition
	//load the game over image
	SCREEN_X = (gr.getWindowWidth() - MC * tile_size) / 2;
	SCREEN_Y = gr.getWindowHeight() /3.3;
	PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
	gr.beginDraw();
	gr.drawImage(game_over, SCREEN_X+70, SCREEN_Y, gr.generateFromRGB(0, 0, 0));
	gr.endDraw();
	Sleep(4000);

}
bool isvalid(int x, int y, int map[MR][MC], bool visited[MR][MC])
{
	if (x >= 0 && x < MR && y >= 0 && y < MC && !visited[x][y])
	{
		if (!(map[x][y] == 1 || (map[x][y] >= 61 && map[x][y] <= 64)))
			return true;
	}
	return false;
}

void enemyAI(int map[MR][MC])
{
	int dX[] = { -1, 1, 0, 0 };
	int dY[] = { 0, 0, -1, 1 };


	int eX = -1, eY = -1, pX = -1, pY = -1;

	//Locate enemy and Pac-Man
	for (int i = 0; i < MR; i++) {
		for (int j = 0; j < MC; j++) {
			if (map[i][j] == 99) {
				pX = i;
				pY = j;
			}
			if (map[i][j] == -5) {
				eX = i;
				eY = j;
			}
		}
	}
	if (eX == -1 || eY == -1 || pX == -1 || pY == -1) {
		return;

	}


	//Start BFS
	bool visited[MR][MC] = { false };
	int queue[MR * MC][2], front = 0, rear = 0;
	int parent[MR][MC][2];
	queue[rear][0] = eX;
	queue[rear][1] = eY;
	rear++;
	visited[eX][eY] = true;
	parent[eX][eY][0] = -1;
	parent[eX][eY][1] = -1;

	bool isFound = false;
	while (front < rear)
	{
		int x = queue[front][0];
		int y = queue[front][1];

		front++;

		if (x == pX && y == pY)
		{
			isFound = true;
			break;
		}

		for (int d = 0; d < 4; d++)
		{

			int nX = x + dX[d];
			int nY = y + dY[d];
			if (isvalid(nX, nY, map, visited)) {
				queue[rear][0] = nX;
				queue[rear][1] = nY;

				rear++;
				visited[nX][nY] = true;

				parent[nX][nY][0] = x;
				parent[nX][nY][1] = y;
			}

		}

	}

	//Start Backtrack
	if (isFound)
	{
		int cx = pX, cy = pY;

		while (parent[cx][cy][0] != eX || parent[cx][cy][1] != eY) {
			int tempX = parent[cx][cy][0];
			int tempY = parent[cx][cy][1];

			cx = tempX;
			cy = tempY;
		}
		map[eX][eY] = 0;
		map[cx][cy] = -5;
	}


}

void inkyAI(int map[MR][MC])
{
	int dX[] = { -1, 1, 0, 0 };
	int dY[] = { 0, 0, -1, 1 };

	int eX = -1, eY = -1, pX = -1, pY = -1;

	// Locate Inky and Pac-Man
	for (int i = 0; i < MR; i++) {
		for (int j = 0; j < MC; j++) {
			if (map[i][j] == 99) {
				pX = i;
				pY = j;
			}
			if (map[i][j] == -3) {
				eX = i;
				eY = j;
			}
		}
	}
	if (eX == -1 || eY == -1 || pX == -1 || pY == -1) {
		return;
	}

	// Offset Inky's target position (less aggressive than enemyAI)
	int offsetX = (rand() % 3) - 1; // Randomly choose -1, 0, or 1
	int offsetY = (rand() % 3) - 1; // Randomly choose -1, 0, or 1

	// Aim at a point near Pac-Man, not directly at him
	int targetX = pX + offsetX;
	int targetY = pY + offsetY;

	// Make sure the target is within bounds
	if (targetX < 0) targetX = 0;
	if (targetX >= MR) targetX = MR - 1;
	if (targetY < 0) targetY = 0;
	if (targetY >= MC) targetY = MC - 1;

	// Start BFS from Inky to the target location
	bool visited[MR][MC] = { false };
	int queue[MR * MC][2], front = 0, rear = 0;
	int parent[MR][MC][2];
	queue[rear][0] = eX;
	queue[rear][1] = eY;
	rear++;
	visited[eX][eY] = true;
	parent[eX][eY][0] = -1;
	parent[eX][eY][1] = -1;

	bool isFound = false;
	while (front < rear)
	{
		int x = queue[front][0];
		int y = queue[front][1];

		front++;

		if (x == targetX && y == targetY) {
			isFound = true;
			break;
		}

		for (int d = 0; d < 4; d++)
		{
			int nX = x + dX[d];
			int nY = y + dY[d];
			if (isvalid(nX, nY, map, visited)) {
				queue[rear][0] = nX;
				queue[rear][1] = nY;

				rear++;
				visited[nX][nY] = true;

				parent[nX][nY][0] = x;
				parent[nX][nY][1] = y;
			}
		}
	}

	// Start Backtrack
	if (isFound)
	{
		int cx = targetX, cy = targetY;

		while (parent[cx][cy][0] != eX || parent[cx][cy][1] != eY) {
			int tempX = parent[cx][cy][0];
			int tempY = parent[cx][cy][1];

			cx = tempX;
			cy = tempY;
		}
		map[eX][eY] = 0;
		map[cx][cy] = -3;
	}
}

//void orangeAI()

/*
int pacman_animate() {
	

}*/
void map1draw(int map[MR][MC], int tile_size, int x, int y, int pac_x, int pac_y, int screenWidth, bool isAligned, int gridX, int gridY, int* pass, int* redGridX, int* redGridY, int* inkyGridX, int* inkyGridY,int pacman_frames[6][4],int PCF,Direction* BD) {
	int s = tile_size - 2;
	int food_eaten = 0;
	*pass = *pass + 1;
	if (*pass == 1)
		*pass = 0;
	/*
	Numbers meaning
	-1 for the ghost
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
	int ex = -1, ey = -1;
	int inkyX = -1, inkyY = -1;
	for (int i = 0; i < MR; i++)
	{

		for (int j = 0; j < MC; j++)
		{
			if (map[i][j] == 1)
			{	// Draw walls
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidRectangle(x, y, tile_size - 2, tile_size - 2);
			}
			else if (map[i][j] == 0 && i < MR)
			{	// Draw food that is not eaten

				gr.setDrawingColor(COLORS::WHITE);
				gr.drawSolidCircle(x + ((tile_size - 0.15 * s) / 2), y + ((tile_size - 0.15 * s) / 2), 0.3 * s);
			}
			else if (map[i][j] == 10)
			{
				food_eaten++;
			}
			else if (map[i][j] == 3)
			{
				gr.setDrawingColor(COLORS::WHITE);
				gr.drawSolidRectangle(x - 2, y + 1, tile_size + 2, tile_size / 4);
			}
			else if (map[i][j] == 5)
			{ //right portal
				gr.setDrawingColor(COLORS::WHITE);
				gr.drawSolidEllipse(x + tile_size - tile_size / 3, y, tile_size / 3, tile_size);
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidEllipse((x + tile_size - tile_size / 3) + tile_size / 12, y + tile_size / 4, tile_size / 6, tile_size / 2);
			}
			else if (map[i][j] == 4)
			{ //left portal
				gr.setDrawingColor(COLORS::WHITE);
				gr.drawSolidEllipse(x, y, tile_size / 3, tile_size);
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidEllipse(x + tile_size / 12, y + tile_size / 4, tile_size / 6, tile_size / 2);
			}
			else if (map[i][j] == 61)
			{
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidCircle(x, y, tile_size - 2);
				gr.drawSolidRectangle(x + tile_size / 2, y, tile_size / 2, tile_size - 2);
			}
			else if (map[i][j] == 62)
			{
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidCircle(x, y, tile_size - 2);
				gr.drawSolidRectangle(x - 2, y, tile_size / 2, tile_size - 2);
			}
			else if (map[i][j] == 63)
			{
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidCircle(x, y, tile_size - 2);
				gr.drawSolidRectangle(x, y + tile_size / 2, tile_size - 2, tile_size / 2);
			}
			else if (map[i][j] == 64)
			{
				gr.setDrawingColor(COLORS::BLUE);
				gr.drawSolidCircle(x, y, tile_size - 2);
				gr.drawSolidRectangle(x, y - 2, tile_size - 2, tile_size / 2);
			}
			else if (map[i][j] == -5)
			{ //draw ghost
				for (int i = 0; i < MR; i++)
					for (int j = 0; j < MC; j++)
					{
						if (map[i][j] == -5)
						{
							ex = i;
							ey = j;
						}
					}
				if (ex != -1 && ey != -1)
				{
					gr.setDrawingColor(COLORS::RED);
					ex *= tile_size;
					ey *= tile_size;

					ex += SCREEN_Y;
					ey += SCREEN_X;
					gr.drawSolidCircle(ey + s, ex + s, tile_size - 2 * s);
				}

			}
			else if (map[i][j] == -3)
			{ //draw ghost
				for (int i = 0; i < MR; i++)
					for (int j = 0; j < MC; j++)
					{
						if (map[i][j] == -3)
						{
							inkyX = i;
							inkyY = j;
						}
					}
				if (inkyX != -1 && inkyY != -1)
				{
					gr.setDrawingColor(COLORS::CYAN);
					inkyX *= tile_size;
					inkyY *= tile_size;

					inkyX += SCREEN_Y;
					inkyY += SCREEN_X;
					gr.drawSolidCircle(inkyY + s, inkyX + s, tile_size - 2 * s);
				}

			}
			else if (map[i][j] == -4)
			{ //draw ghost
				for (int i = 0; i < MR; i++)
					for (int j = 0; j < MC; j++)
					{
						if (map[i][j] == -5)
						{
							ex = i;
							ey = j;
						}
					}
				if (ex != -1 && ey != -1)
				{
					gr.setDrawingColor(COLORS::RED);
					ex *= tile_size;
					ey *= tile_size;

					ex += SCREEN_Y;
					ey += SCREEN_X;
					gr.drawSolidCircle(ey + s, ex + s, tile_size - 2 * s);
				}

			}
			else if (map[i][j] == 99) {
				// Draw Pac-Man
				P_C_F(pac_x+s-tile_size, pac_y+s-tile_size,pacman_frames,tile_size,PCF,BD);
			}

			if (isAligned && map[gridY][gridX] == map[i][j])
			{
				if (map[i][j] == 0)
					map[gridY][gridX] = 10;

				map[bufferY][bufferX] = 10;
				map[gridY][gridX] = 99;
				bufferX = gridX;
				bufferY = gridY;
			}





			//show score
			/*gr.setDrawingColor(COLORS::YELLOW);
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
			gr.setFontSizeAndBoldness(50, 3);*/

			int centerText_X = 80; // x position at the center of the map
			int centerText_y = 0; // y position slightly below the map

			//gr.drawText(centerText_X, centerText_y, scoreinText);

			x += tile_size;
		}
		y += tile_size;
		x = SCREEN_X;
		*redGridX = ex / tile_size;
		*redGridY = ey / tile_size;
		*inkyGridX = inkyX / tile_size;
		*inkyGridY = inkyY / tile_size;

	}


}
//########################################### To show the Debugging Matrix #######################################
void Debugging_matrix(int map[MR][MC],int *F3,bool* ON,int* SCREEN_X,int tile_size) {
	*ON = !(*ON);//to see if the Debugging matrix is on
	if (*F3 == 243 && *ON) {//F3 in the ascci Table is 243
		*SCREEN_X = 50;
		for (int yy = 0; yy < MR; yy++)
		{
			for (int xx = 0; xx < MC; xx++)
			{
				char buf[100];
				sprintf(buf, "%d", map[yy][xx]);
				gr.setFontSizeAndBoldness(15, 5);
				gr.drawText(1250 + xx * 35, 100 + yy * 35, buf);

			}
		}
	}
	else if (!(*ON)) {
		*SCREEN_X = (gr.getWindowWidth() + MC * tile_size) / 2 - gr.getWindowWidth() / 4;
	}

}

//############################################ For Pacman motion ########################################

void motion(Direction* bufferdir,Direction* BD,int map[MR][MC],int* F3,bool*ON,int *SCREEN_X,int tile_size)
{
	if (kbhit())
	{
		char c = getch();
		// Only change direction if Pac-Man is moving
		switch (c)
		{
		case 'w': *bufferdir = UP;
			*BD = UP;
			break;
		case 'a': *bufferdir = LEFT;
			*BD = LEFT;
			break;
		case 's': *bufferdir = DOWN;
			*BD = DOWN;
			break;
		case 'd': *bufferdir = RIGHT;
			*BD = RIGHT;
			break;
		case 'W': *bufferdir = UP;
			*BD = UP;
			break;
		case 'A': *bufferdir = LEFT;
			*BD = LEFT;
			break;
		case 'S': *bufferdir = DOWN;
			*BD = DOWN;
			break;
		case 'D': *bufferdir = RIGHT;
			*BD = RIGHT;
			break;
		case 243:// TO show the Debugging matrix
			Debugging_matrix(map,&*F3,&*ON,&*SCREEN_X,tile_size);
			break;
		}
	}
}
//################################################# MAIN FUNCTION ################################################
int main()
{
	gr.setup();
	gr.setFullScreenMode();
	gr.hideCursor(); // Hide the cursor. It's annoying
	int pacman_frames[6][4];
	int PCF = 0;
	int tile_size = 50;

	float redspeed = 0.0;
	float inkyspeed = 0.0;
	float cyanSpeed;

	int speed = tile_size;
	int pass = 0;
	int redGridX, redGridY;
	int inkyGridX, inkyGridY;


//#################################LOADING FRAMES AS FARMERS##################################################
	pacman_frames[0][0]=gr.loadImage("Images//Pacman//D_Pacman0.png");
	pacman_frames[1][0] = gr.loadImage("Images//Pacman//D_Pacman1.png");
	pacman_frames[2][0] = gr.loadImage("Images//Pacman//D_Pacman2.png");
	pacman_frames[3][0] = gr.loadImage("Images//Pacman//D_Pacman3.png");
	pacman_frames[4][0] = gr.loadImage("Images//Pacman//D_Pacman4.png");
	pacman_frames[5][0] = gr.loadImage("Images//Pacman//D_Pacman5.png");
	//Pacman UP
	pacman_frames[0][1] = gr.loadImage("Images//Pacman//U_Pacman0.png");
	pacman_frames[1][1] = gr.loadImage("Images//Pacman//U_Pacman1.png");
	pacman_frames[2][1] = gr.loadImage("Images//Pacman//U_Pacman2.png");
	pacman_frames[3][1] = gr.loadImage("Images//Pacman//U_Pacman3.png");
	pacman_frames[4][1] = gr.loadImage("Images//Pacman//U_Pacman4.png");
	pacman_frames[5][1] = gr.loadImage("Images//Pacman//U_Pacman5.png");
	//Pacman Right
	pacman_frames[0][2] = gr.loadImage("Images//Pacman//R_Pacman0.png");
	pacman_frames[1][2] = gr.loadImage("Images//Pacman//R_Pacman1.png");
	pacman_frames[2][2] = gr.loadImage("Images//Pacman//R_Pacman2.png");
	pacman_frames[3][2] = gr.loadImage("Images//Pacman//R_Pacman3.png");
	pacman_frames[4][2] = gr.loadImage("Images//Pacman//R_Pacman4.png");
	pacman_frames[5][2] = gr.loadImage("Images//Pacman//R_Pacman5.png");
	//Paxman Left
	pacman_frames[0][3] = gr.loadImage("Images//Pacman//L_Pacman0.png");
	pacman_frames[1][3] = gr.loadImage("Images//Pacman//L_Pacman1.png");
	pacman_frames[2][3] = gr.loadImage("Images//Pacman//L_Pacman2.png");
	pacman_frames[3][3] = gr.loadImage("Images//Pacman//L_Pacman3.png");
	pacman_frames[4][3] = gr.loadImage("Images//Pacman//L_Pacman4.png");
	pacman_frames[5][3] = gr.loadImage("Images//Pacman//L_Pacman5.png");


	//game over image
	int game_over = gr.loadImage("Game over.png");
//################################################ LOADING SCREEN ##########################################################
	//loading_screen(tile_size);
//################################################# MAIN MENU ##############################################	
	// C is the choice 
	int c = main_menu(tile_size);
	//if the user choose exit the main function return zero
	if (c == 2)
		return 0;
//###########################################################################################################

	SCREEN_X = (gr.getWindowWidth() - MC * tile_size) - gr.getWindowWidth() / 4;
	SCREEN_Y = 0;

	Direction pacmanDir = NONE;
	Direction bufferedDir = NONE;
	Direction BD = RIGHT;
	int map[MR][MC] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,99,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
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
		{1,-3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-5,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

	};


	int screenWidth = (int)gr.getWindowWidth();
	int screenHeight = (int)gr.getWindowHeight();

	int pac_x = (SCREEN_X)+tile_size;
	int pac_y = (SCREEN_Y)+tile_size;

	bufferX = (int)((pac_x - SCREEN_X) / tile_size);
	bufferY = (int)((pac_y - SCREEN_Y) / tile_size);

	bool isMoving = false;
	Direction movingBuffer;

	PlaySound(TEXT("waka.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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

//##################################################### Rendering ###########################################
		gr.beginDraw();
		//draw map
		PCF++;
		if (PCF == 6)
			PCF = 0;
		map1draw(map, tile_size, x, y, pac_x, pac_y, screenWidth, isAligned, gridX, gridY, &pass, &redGridX, &redGridY, &inkyGridX, &inkyGridY,pacman_frames,PCF,&BD);
		//game ending condition
		if ((redGridX + 1 == gridY && redGridY + 1 == gridX) || (inkyGridX+1  == gridY && inkyGridY+1  == gridX)) {
			gameover(game_over,tile_size);
			break;
		}
//##################################### Handle key press to change direction of Pacman ######################################
		int F3;
		bool ON = false;
		motion(&bufferedDir,&BD,map,&F3,&ON,&SCREEN_X,tile_size);
//##################################### Controling the gosts speed  ######################################################
		redspeed += 0.6f;
		inkyspeed += 1.0f;
		if (redspeed >= 1.0f) {
			enemyAI(map);
			redspeed = 0;
		}
		if (inkyspeed >= 1.0) {
			inkyAI(map);
			inkyspeed = 0;
		}
//####################################################################################################################
		gr.endDraw();
//################################################# Time Control End #############################################
		waitFor(frame_start, 1.0 / 30 * 1000);
	}

	return 0;
}