#pragma once
#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Character.h"
#include <algorithm>
#include <cmath>

using namespace std;

class MarioBros
{
public:
	/* initialization */
	MarioBros(void);
	~MarioBros(void);
	void initializeGame();


	// add a sprite to the draw list
	// only sprites in the draw list will be drawn

	/* draw/rendering routines */
	void draw(); // called from the main

	void PreDraw(); // prior to drawing
	void DrawGame(); // actual drawing the frame
	void PostDraw(); // cleanup and prepare for next frame

	void drawSprites(); // draw the sprite list

							   /* update routines, the game loop */
	void update(); // called from main frequently

				   /* input callback functions */
	void keyboardDown(unsigned char key);
	void keyboardUp(unsigned char key);

	/*********************************/
	/* DATA */
	/*********************************/


	// here is the sprite to draw to the screen

	Character *mario;
	int levelX = 17;
	int levelY = 12;
	int level[12][17] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,0,0,2,0,0,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	// the background scroller


	/* sprite list to draw */
	std::vector<Character*> spriteListToDraw;
	std::vector<Character*> enemyList;

	/* you could have more lists of sprite pointers */
	/* such as spritesToUpdateForPhysics
	or      spritesToUpdateForCollisions
	etc....
	*/

	/* timer's for rendering and animation/physics update */
};
