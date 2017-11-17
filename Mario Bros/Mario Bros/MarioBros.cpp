// Mario Bros.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MarioBros.h"


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
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, 1000, 800, TRUE);
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

	enemy = new Character(1);
	enemy->acceleration.set(0, 0);
	enemy->force.set(0, 0);
	enemy->velocity.set(0, 0);
	enemy->setPosition(2, 2);
	enemy->setCenter(2, 2); // center of the sprites origin for rotation
	enemy->width = 3;
	enemy->height = 4;
	spriteListToDraw.push_back(enemy);



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
	for (int i = 0; i < levelY; i++) {//for y axis
		for (int j = 0; j < levelX; j++) {//for x axis

			for (int h = 0; h < mario->height; h++) {//for marios height of sprite
				for (int w = 0; w < mario->width; w++) {//for marios width of sprite
					if ((int)(mario->position.y - (mario->height / 2) + h) == i && (int)(mario->position.x - (mario->width / 2) + w) == j) {//if this pixel on marios sprites is equal to this pizxl on the map
						setCursorPosition(j, i);//set curser to this spot
						cout << mario->icon[h][w];//draw that pixel
					}
					else if ((int)(mario->oldx - (mario->width / 2) + w) == j && (int)(mario->oldy - (mario->height / 2) + h) == i) {//if this pixel on his old sprite is equal to this pixel on the map
						setCursorPosition(j, i);//set position of curser and erase that mario sprite (write map pixel on top)
						if (level[i][j] <= 0)
							cout << ' ';
						else if (level[i][j] == 1)
							cout << 'B';
						else if (level[i][j] == 2)
							cout << 'P';
						else if (level[i][j] == 3)
							cout << ' ';
					}
					//forw

				}
				//forh
			}
			for (int h = 0; h < enemy->height; h++) {//for enemy height of sprite
				for (int w = 0; w < enemy->width; w++) {//for enemy width of sprite
					if ((int)(enemy->position.y - (enemy->height / 2) + h) == i && (int)(enemy->position.x - (enemy->width / 2) + w) == j) {//if this pixel on marios sprites is equal to this pizxl on the map
						setCursorPosition(j, i);//set curser to this spot
						cout << enemy->icon[h][w];//draw that pixel
					}
					else if ((int)(enemy->oldx - (enemy->width / 2) + w) == j && (int)(enemy->oldy - (enemy->height / 2) + h) == i) {//if this pixel on his old sprite is equal to this pixel on the map
						setCursorPosition(j, i);//set position of curser and erase that enemy sprite (write map pixel on top)
						if (level[i][j] <= 0)
							cout << ' ';
						else if (level[i][j] == 1)
							cout << 'B';
						else if (level[i][j] == 2)
							cout << 'P';
						else if (level[i][j] == 3)
							cout << ' ';
					}
					//forw

				}
				//forh
			}

		}
	}

	setCursorPosition(levelX, levelY);//set curser to the bottom
	//display game image
}

/*
* DrawGame()
*  - this is the actual drawing of the current frame of the game.
*/
void MarioBros::DrawGame()//draws the map and game the firt time only
{
	system("CLS");
	for (int i = 0; i < levelY; i++) {//for y axis
		for (int j = 0; j < levelX; j++) {//for x axis
			//if (((int)mario->position.y - (mario->height / 2) + h) == i && ((int)mario->position.x - (mario->width / 2) + w) == j) {
			//	cout << mario->icon;
			//}
			//if ((int)mario->position.y + (mario->height / 2) >= i && (int)mario->position.y - (mario->height / 2) <= i) {  //if pixel is withing marios width 
			//	if ((int)mario->position.x + (mario->width / 2) >= j && (int)mario->position.x - (mario->width / 2) <= j) { //and within his height
			//		cout << mario->icon[1][1];//draw an M for now
			//	}
			//}
			//else if ((int)enemy->position.y + (enemy->height / 2) >= i && (int)enemy->position.y - (enemy->height / 2) <= i) {  //if pixel is withing marios width 
			//	if ((int)enemy->position.x + (enemy->width / 2) >= j && (int)enemy->position.x - (enemy->width / 2) <= j) { //and within his height
			//		cout << enemy->icon[1][1];//draw an E for now
			//	}
			//}
			if (level[i][j] <= 0)//else just draw the map at hat pixel
				cout << ' ';
			else if (level[i][j] == 1)
				cout << 'B';
			else if (level[i][j] == 2)
				cout << 'P';
		}
		cout << endl;
	}
	//display game image
}

bool MarioBros::isColliding(int width, int height)
{
	float MarioMinX = mario->position.x - mario->width / 2.0;
	float MarioMaxX = mario->position.x + mario->width / 2.0;
	float MarioMinY = mario->position.y - mario->height / 2.0;
	float MarioMaxY = mario->position.y + mario->height / 2.0;

	float EnemiesMinX = enemy->position.x - enemy->width / 2.0;
	float EnemiesMaxX = enemy->position.x + enemy->width / 2.0;
	float EnemiesMinY = enemy->position.y - enemy->height / 2.0;
	float EnemiesMaxY = enemy->position.y + enemy->height / 2.0;

	//Trying Stuff

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

	//if birdlist empty, and piglist empty, end game
	Vector2 gravity;
	gravity.set(0, 1.25);

	int i = (int)mario->position.y;
	int j = (int)mario->position.x;
	mario->oldx = j;
	mario->oldy = i;
	mario->addForce(gravity);

	int k = (int)enemy->position.y;
	int l = (int)enemy->position.x;
	enemy->oldx = l;
	enemy->oldy = k;
	enemy->addForce(Vector2(1, 0));
	enemy->addForce(gravity);

	if (level[k][l] == -1) {
		enemy->setPosition(0,3);
	}

	mario->update(0.09, level);//change the number to change the game speed
	enemy->update(0.09, level);//change the number to change the game speed

	if (isColliding((int)mario->width, (int)mario->height) == true)
	{
		enemy->getHit();
	}
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

