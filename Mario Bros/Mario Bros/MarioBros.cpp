// Mario Bros.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MarioBros.h"
#include "console.h"


/* constructor */
MarioBros::MarioBros(void)
{

}

/* destructor */
MarioBros::~MarioBros(void)
{
/* deallocate memory and clean up here. if needed */
}

/*
* initializeGame()
* - this function is called in the constructor to initialize everything related
*   to the game, i..e loading sprites etc.
* - MUST be called prior to any drawing/updating (you should add in checks to ensure this occurs in the right order)
*/
void MarioBros::initializeGame()
{
	///* load the background */
	
	console.Initialize(vec2(100,45), "Mario Bros");
	
	//GetWindowRect(console, &r); //stores the console's current dimensions
	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	//MoveWindow(console, r.left, r.top, 1000, 800, TRUE);
	//Add Mario
	mario = new Character(0);
	mario->acceleration.set(0, 0);
	mario->force.set(0, 0);
	mario->velocity.set(0, 0);
	mario->setPosition(20, 20);
	mario->setCenter(2,2); // center of the sprites origin for rotation
	mario->width = 3;
	mario->height = 4;
	spriteListToDraw.push_back(mario);

	for (int i = 0; i < 3; i++) {
		Character* enemy;
		enemy = new Character(1);
		enemy->acceleration.set(0, 0);
		enemy->force.set(0, 0);
		enemy->velocity.set(0, 0);
		enemy->setPosition(2 + (i*5), 2 + (i * 5));
		enemy->setCenter(2, 2); // center of the sprites origin for rotation
		enemy->width = 3;
		enemy->height = 4;
		enemyList.push_back(enemy);
		spriteListToDraw.push_back(enemy);
	}


}

/* draw()
* - this gets called automatically about 30 times per second
* - this function just draws the sprites
*/
void MarioBros::draw()
{
	/* pre-draw - setup the rendering */
	PreDraw();

	/* draw - actually render to the screen */
	DrawGame();

	/* post-draw - after rendering, setup the next frame */
	PostDraw();
}

/*
* Pre-Draw() is for setting up things that need to happen in order to draw
*    the game, i.e. sorting, splitting things into appropriate lists etc.
*/


void MarioBros::PreDraw()//redraws mario
{

}

/*
* DrawGame()
*  - this is the actual drawing of the current frame of the game.
*/
void MarioBros::DrawGame()//draws the map and game the firt time only
{
	//system("CLS");
	for (int i = 0; i < levelY; i++) {//for y axis
		for (int j = 0; j < levelX; j++) {//for x axis

			if (level[i][j] <= 0)
				console.Print(" ", vec2(j, i), vec2(1, 1), 11);
			else if (level[i][j] == 1)
				console.Print("B", vec2(j, i), vec2(1, 1), 11);
			else if (level[i][j] == 2)
				console.Print("P", vec2(j, i), vec2(1, 1), 11);
		}
		//cout << endl;
	}
	for (int h = 0; h < mario->height; h++) {//for marios height of sprite
		for (int w = 0; w < mario->width; w++) {//for marios width of sprite
			int i = (int)(mario->position.y - (mario->height / 2) + h);
			int j = (int)(mario->position.x - (mario->width / 2) + w);
			console.Print(mario->icon[h][w], vec2(j, i), vec2(1, 1), 12);//draw that pixel
		}
	}
	for (int z = 0; z < enemyList.size(); z++) {
		for (int h = 0; h < enemyList[z]->height; h++) {//for enemy height of sprite
			for (int w = 0; w < enemyList[z]->width; w++) {//for enemy width of sprite
				int i = (int)(enemyList[z]->position.y - (enemyList[z]->height / 2) + h);
				int j = (int)(enemyList[z]->position.x - (enemyList[z]->width / 2) + w);
				console.Print(enemyList[z]->icon[h][w], vec2(j, i), vec2(1, 1), 2);//draw that pixel
			}
		}
	}
	console.Draw();
	console.Clear();
	//display game image
}

bool MarioBros::isColliding(int i, int width, int height)
{
	
	float MarioMinX = mario->position.x - mario->width / 2.0;
	float MarioMaxX = mario->position.x + mario->width / 2.0;
	float MarioMinY = mario->position.y - mario->height / 2.0;
	float MarioMaxY = mario->position.y + mario->height / 2.0;

	float EnemiesMinX = enemyList[i]->position.x - enemyList[i]->width / 2.0;
	float EnemiesMaxX = enemyList[i]->position.x + enemyList[i]->width / 2.0;
	float EnemiesMinY = enemyList[i]->position.y - enemyList[i]->height / 2.0;
	float EnemiesMaxY = enemyList[i]->position.y + enemyList[i]->height / 2.0;

	//Trying Stuff
	if (buffer < 0) {
		if (level[(int)(mario->position.y - (height / 2)) - 1][(int)mario->position.x] == 2) {//if block above
			for (int j = 0; j < enemyList.size(); j++) {
				if (enemyList[j]->flipped == false) {
					enemyList[j]->flipped = true;
					buffer = 20;
					goto jump;
				}
				else {
					enemyList[j]->flipped = false;
					buffer = 20;
					goto jump;
				}
			}
		}
		if (level[(int)(mario->position.y - (height / 2)) - 1][(int)mario->position.x] > 0) {//if block above
			if ((MarioMaxX >= EnemiesMinX && MarioMinX <= EnemiesMaxX) || (EnemiesMinX >= MarioMaxX &&  EnemiesMaxX <= MarioMinX)) {//and mario overlapping x's with enemy
				if (enemyList[i]->flipped == false) {
					enemyList[i]->flipped = true;
					buffer = 20;
					goto jump;
				}
				else {
					enemyList[i]->flipped = false;
					buffer = 20;
					goto jump;
				}
			}
		}
	}
jump:
	buffer--;
	if (buffer < -1000000) buffer = 0;
	if (MarioMaxX >= EnemiesMinX && MarioMinX <= EnemiesMaxX && MarioMaxY >= EnemiesMinY && MarioMinY <= EnemiesMaxY)
	{
		return true;
	}
	if (EnemiesMinX >= MarioMaxX &&  EnemiesMaxX <= MarioMinX && EnemiesMinY >= MarioMaxY && EnemiesMaxY <= MarioMinY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MarioBros::setCursorPosition(int x, int y)
{

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = 0;
	lpCursor.dwSize = 1;
	SetConsoleCursorPosition(hOut, coord);
	SetConsoleCursorInfo(hOut, &lpCursor);
}

void MarioBros::PostDraw()
{
	//nothing
}


void MarioBros::drawSprites()
{
	for (int i = 0; i < spriteListToDraw.size(); i++) {
		spriteListToDraw[i]->draw();
	}

}

void MarioBros::update()
{
	// update our clock so we have the delta time since the last update
	clock_t start_t, end_t, total_t;
	int t;

	start_t = clock();
	//if birdlist empty, and piglist empty, end game
	Vector2 gravity;
	gravity.set(0, 1.5);

	int i = (int)mario->position.y;
	int j = (int)mario->position.x;
	mario->oldx = j;
	mario->oldy = i;
	mario->addForce(gravity);

	mario->update(0.7, level);//change the number to change the game speed

	for (int z = 0; z < enemyList.size(); z++) {
		int k = (int)enemyList[z]->position.y;
		int l = (int)enemyList[z]->position.x;
		enemyList[z]->oldx = l;
		enemyList[z]->oldy = k;
		//enemy->addForce(Vector2(1, 0));
		enemyList[z]->addForce(gravity);

		if (level[k][l] == -1) {
			enemyList[z]->setPosition(0, 3);
		}

		enemyList[z]->update(0.7, level);//change the number to change the game speed

		if (isColliding(z, (int)mario->width, (int)mario->height) == true)
		{

			if (enemyList[z]->flipped == true) {
				enemyList.erase(enemyList.begin() + z);
			}
			else {
				mario->getHit();
			}
		}
	}
	//cout << start_t;
}


/*************************************************/
/* INPUT - keyboard/mouse functions below        */
/*************************************************/
/* keyboardDown()
- this gets called when you press a key down
- you are given the key that was pressed
and where the (x,y) location of the mouse is when pressed
*/

void MarioBros::keyboardDown(unsigned char key)
{
	switch (key)
	{
	case 'w':
		//if (mario->jumping == false) {
			mario->addForce(Vector2(0, -3));
			mario->jumping = true;
		//}
		break;
	case 'a':
		mario->addForce(Vector2(-1, 0));
		//mario->position.x--;
		break;
	case 'd':
		mario->addForce(Vector2(1, 0));
		//mario->position.x++;
		break;
	//case 32: // the space bar
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	}
}
/* keyboardUp()
- this gets called when you lift a key up
- you are given the key that was pressed
and where the (x,y) location of the mouse is when pressed
*/
void MarioBros::keyboardUp(unsigned char key)
{
	switch (key)
	{
	case 'w':
		break;
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
	}
}

