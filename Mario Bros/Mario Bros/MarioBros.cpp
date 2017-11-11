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
		mario->setPosition(2,2);
		mario->setCenter(0,0); // center of the sprites origin for rotation

		spriteListToDraw.push_back(mario);



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


void MarioBros::PreDraw()
{
	for (int i = 0; i < levelY; i++) {
		for (int j = 0; j < levelX; j++) {
			if ((int)mario->position.y == i && (int)mario->position.x == j) {
				setCursorPosition(j, i);
				cout << mario->icon;
			}
			else if((int)mario->oldx == j && (int)mario->oldy == i){
				setCursorPosition(j, i);
				if (level[i][j] == 0)
					cout << ' ';
				else if (level[i][j] == 1)
					cout << 'B';
				else if (level[i][j] == 2)
					cout << 'P';
			}
			
		}
		cout << endl;
	}
	//display game image
}

/*
* DrawGame()
*  - this is the actual drawing of the current frame of the game.
*/
void MarioBros::DrawGame()
{
	system("CLS");
	for (int i = 0; i < levelY; i++) {
		for (int j = 0; j < levelX; j++) {
			if ((int)mario->position.y == i && (int)mario->position.x == j)
				cout << mario->icon;
			else if (level[i][j] == 0)
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

void MarioBros::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void MarioBros::PostDraw()
{
	const int X = levelX;
	const int Y = levelY;
	int x = (int)mario->oldx;
	int y = (int)mario->oldy;
	int a = (int)mario->position.x;
	int b = (int)mario->position.x;
	if (x != a || y != b) {
		setCursorPosition(a, b);
		cout << 'M';
		setCursorPosition(x, y);
		if (level[x][y] == 0)
			cout << ' ';
		else if (level[x][y] == 1)
			cout << 'B';
		else if (level[x][y] == 2)
			cout << 'P';
	}
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
	gravity.set(0, 0.8);

	int i = (int)mario->position.y;
	int j = (int)mario->position.x;
	mario->oldx = j;
	mario->oldy = i;
	mario->addForce(gravity);

	i = (int)mario->position.y;
	j = (int)mario->position.x;

	if (level[i][j] > 0) {
		mario->position.y++;//go under it
	}

	if (level[i + 1][j] > 0) {//if block below
		mario->force.y = 0;//no gravity
	}

	if (level[i - 1][j] > 0) {//if block above
		if (mario->velocity.y < 0) {//and moving upwards
			mario->velocity.y = 0;//no moving
			mario->force.y = 0;//no force
		}
		
	}
	//if (mario->jumping == true && mario->jumpFrame < 2) {//if jumping,
	//	mario->velocity.y = -1.;//move up
	//	mario->jumpFrame++;//count frames
	//}
	else {
		mario->jumpFrame = 0;
	}

	mario->update(0.05);

	if (mario->position.y < 1) mario->position.y = 1;
	if (mario->position.y > levelY -1) mario->position.y = levelY -1;
	if (mario->position.x < 0) mario->position.x = levelX-1;
	else if (mario->position.x > levelX-1) mario->position.x = 0;

	//if on ground
	if (level[i + 1][j] > 0) {//you can jump
		mario->jumpFrame = 0;
		mario->jumping = false;
	}
	//if inside a block
	if (level[i][j] > 0) {
		mario->position.y++;//go under it
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
		if (mario->jumping == false) {
			mario->addForce(Vector2(0, 10));
			mario->jumping = true;
		}
		mario->position.y--;
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

