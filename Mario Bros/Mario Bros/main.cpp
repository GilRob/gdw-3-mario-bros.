#include "stdafx.h"
#include <windows.h>
#include "MarioBros.h"
#include "console.h"

MarioBros* Game;

/* function DisplayCallbackFunction(void)
* Description:
*  - this is the openGL display routine
*  - this draws the sprites appropriately
*/
void DisplayCallbackFunction(void)
{
	Game->draw();
}

/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key)
{
	Game->keyboardDown(key);

}
/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key)
{
	Game->keyboardUp(key);
}

/* function main()
* Description:
*  - this is the main function
*  - does initialization and then calls glutMainLoop() to start the event handler
*/
int main()
{
	
	/* init the game */
	Game = new MarioBros();
	Game->initializeGame();
	Game->DrawGame();
	double i;
	bool run = true;
	int ctr = 0;
	while (run == true) {
		if (ctr < 0) ctr = 0;//dont let counter be less then 0
		if (GetAsyncKeyState('W') & 0x8000){ //if W pressed
			if (ctr < 10) {//only id counter is lower then threshhold value(1000)
				Game->mario->addForce(Vector2( 0, -3.5));
				ctr++;//incrase counter (can only jump for 1000 cycles
			}
		}
		else {
			if (Game->mario->velocity.y <= 0.1)
			ctr = 0;//while key isnt pressed, reduce jump counter back to 0
			else ctr = 10;
		}
		
		if (GetAsyncKeyState('D') & 0x8000) {
			//Game->keyboardDown('d');
			Game->mario->addForce(Vector2(1.5, 0));
		}
		if (GetAsyncKeyState('A') & 0x8000) {
			//Game->keyboardDown('a');
			Game->mario->addForce(Vector2(-1.5, 0));
		}
		if (GetAsyncKeyState('Q') & 0x8000) {
			Game->keyboardDown('q');
		}
		if (GetAsyncKeyState)
		Game->update();
		Game->DrawGame();
	}
	return 0;
}