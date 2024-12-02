#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>
#include <math.h>

#include "CC212SGL.h"

//Link to the Graphics .lib file
#pragma comment(lib, "CC212SGL.lib")

//Declare instance from the Graphics library
CC212SGL gr;

void waitFor(int start, int threshold)
{
	while (true)
	{
		float _t = (clock() / (float)CLOCKS_PER_SEC * 1000.0f - start / (float)CLOCKS_PER_SEC * 1000.0f);
		if (_t >= threshold)
			break;
	}
}
int main()
{
	gr.setup();
	gr.setFullScreenMode();
	gr.hideCursor();
	int map_pixle = gr.loadImage("map.jpg");
	int map[20][30] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	/*int dragon[3];
	float current_frame = 0;
	int dragon_frame_dir = 1;
	dragon[0] = gr.loadImage("red_frame0.png");
	dragon[1] = gr.loadImage("red_frame1.png");
	dragon[2] = gr.loadImage("red_frame2.png");
*/


/*for (int i = 0; i < 3; i++)
{
	char loc[20] = "red_frame";
	char final_loc[50];
	char mynum[10];

	itoa(i, mynum, 10);

	strcpy(final_loc, loc);
	strcat(final_loc, mynum);
	strcat(final_loc, ".png");

	dragon[i] = gr.loadImage(final_loc);
}*/


	while (true) //Endless loop to redner the graphics and perform the logic
	{
		int frame_start = clock(); //Time Control Start

		//Processing
		//if (current_frame <= 0)
		//	dragon_frame_dir = 1;
		//else if (current_frame >= 2)
		//	dragon_frame_dir = 0;
		//
		//if (dragon_frame_dir == 1)	//Upward direction
		//	current_frame += 1.0 / 3.0f;
		//else if (dragon_frame_dir == 0)
		//	current_frame -= 1.0 / 3.0f;
		//
		int x = 0;
		int y = 0;
		//Rendering
		gr.beginDraw();
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 30; j++) {
				if (map[i][j] == 1) {
					gr.setDrawingColor(COLORS::BLUE);
					gr.drawSolidRectangle(x, y, 40, 40);
				}
				x += 42;
				/*if (map[i][j] == 0) {
					gr.setDrawingColor(COLORS::RED);
					gr.drawSolidRectangle(x, y, 10, 10);
				}*/
			}
			y += 42;
			x = 0;
		}
		//gr.setDrawingColor(gr.generateFromRGB(10, 10, 201));
		//gr.drawSolidCircle(10, 10, 50);	

		gr.endDraw();



		waitFor(frame_start, 1.0 / 30 * 1000);	//Time Control End
	}

	return 0;
}