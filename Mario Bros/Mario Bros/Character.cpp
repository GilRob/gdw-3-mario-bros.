#include "stdafx.h"
#include "Character.h"
#include <string>

Character::Character(int type)
{
	if (type == 0) {//Sets his sprite by row and column (3x5)
		icon[0][0] = ' '; icon[0][1] = 'M'; icon[0][2] = ' ';
		icon[1][0] = 'M'; icon[1][1] = 'M'; icon[1][2] = 'M';
		icon[2][0] = ' '; icon[2][1] = 'M'; icon[2][2] = ' ';
		icon[3][0] = 'M'; icon[3][1] = 'M'; icon[3][2] = 'M';
		icon[4][0] = 'X'; icon[4][1] = 'X'; icon[4][2] = 'X';//Does not display bottom row
	}
	else if (type == 1) {
		icon[0][0] = ' '; icon[0][1] = 'E'; icon[0][2] = ' ';
		icon[1][0] = 'E'; icon[1][1] = 'E'; icon[1][2] = 'E';
		icon[2][0] = ' '; icon[2][1] = 'E'; icon[2][2] = ' ';
		icon[3][0] = 'E'; icon[3][1] = 'E'; icon[3][2] = 'E';
		icon[4][0] = 'X'; icon[4][1] = 'X'; icon[4][2] = 'X';//Does not display bottom row

	}
	mass = 1;
}


Character::~Character()
{
}

void Character::addForce(Vector2 f)
{
	force = force + f;
}

void Character::update(float dt)
{
	// physics update goes here!!!!
	acceleration = force * (1.0/mass);
	velocity = velocity*0.5 + acceleration*dt;
	velocity.x = velocity.x * 0.8 + acceleration.x*dt;
	position = position + velocity*dt;
	force.set(0, 0);
	// this should be collisions here!  
	// but for this example, just checking if we are at a particular pixel location on Y is fine....
	
	//if (position.y < 0) position.y = 0;
	//if (position.y > 11) position.y = 11;
	//if (position.x < 0) position.x = 16;
	//else if (position.x > 16) position.x = 0;
}

void Character::update(float dt, int lvl[45][100])
{

	int i = (int)position.y;//stores position
	int j = (int)position.x;//stores position

	//Enenmies
	if (icon[0][1] == 'E') {
		velocity.x = (1, 0);
	}

	//Not Enemies

	if (lvl[i][j] > 0) {//if inside a block
		position.y++;//go under it
	}


	if (lvl[i - 1 - (height/2)][j] > 0) {//if block above
		if (velocity.y < 0) {//and moving upwards
			velocity.y = 0;//no moving
			//force.y = 0;//no force
		}

	}

	
	if (lvl[i][j] > 0) {//if inside a block
		position.y++;//go under it
	}


	if (lvl[i + (height/2)][j] > 0) {//if block below
		addForce(Vector2(0, -1.25));//no gravity
		jumpFrame = 0;
		jumping = false;
	}

	// physics update goes here!!!!
	acceleration = force * (1.0 / mass);
	velocity = velocity*0.5 + acceleration*dt;
	velocity.x = velocity.x * 0.8 + acceleration.x*dt;
	position = position + velocity*dt;
	force.set(0, 0);

	if (position.y < 1) position.y = 1;
	if (position.y > 44) position.y = 44;
	if (position.x < 0) position.x = 99;
	else if (position.x > 99) position.x = 0;

	

}

void Character::draw()
{
	//sprite
}