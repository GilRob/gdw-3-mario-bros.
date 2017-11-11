#include "stdafx.h"
#include <windows.h>
#include "MarioBros.h"

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
	while (run == true) {
		if (GetAsyncKeyState('W') & 0x8000){ //VK_DOWN
			//Game->keyboardDown('w');
				Game->mario->velocity.y = - 0.8;
			//if (Game->mario->jumping == false) {
			//	Game->mario->jumping = true;
			//	Game->mario->jumpFrame = 0;
			//}
		}
		if (GetAsyncKeyState('D') & 0x8000) {
			//Game->keyboardDown('d');
			Game->mario->addForce(Vector2(1, 0));
		}
		if (GetAsyncKeyState('A') & 0x8000) {
			//Game->keyboardDown('a');
			Game->mario->addForce(Vector2(-1, 0));
		}
		if (GetAsyncKeyState('Q') & 0x8000) {
			Game->keyboardDown('q');
		}
		Game->update();
		//Game->drawSprites();
		Game->PreDraw();
	}
	return 0;
}