#include "stdafx.h"
#include "Character.h"
#include <string>

Character::Character(int x)
{
	if (x == 0) {//Sets his sprite by row and column (3x5)
		type = 0;
		icon[0][0] = " "; icon[0][1] = "M"; icon[0][2] = " ";
		icon[1][0] = "M"; icon[1][1] = "M"; icon[1][2] = "M";
		icon[2][0] = " "; icon[2][1] = "M"; icon[2][2] = " ";
		icon[3][0] = "M"; icon[3][1] = "M"; icon[3][2] = "M";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";//Does not display bottom row
	}
	else if (x == 1) {
		type = 1;
		icon[0][0] = " "; icon[0][1] = " "; icon[0][2] = "E";
		icon[1][0] = "E"; icon[1][1] = "E"; icon[1][2] = "E";
		icon[2][0] = "E"; icon[2][1] = "E"; icon[2][2] = "E";
		icon[3][0] = "E"; icon[3][1] = " "; icon[3][2] = "E";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";//Does not display bottom row

	}
	else if (x == 2){
		type = 2;
		icon[0][0] = "E"; icon[0][1] = " "; icon[0][2] = " ";
		icon[1][0] = "E"; icon[1][1] = "E"; icon[1][2] = "E";
		icon[2][0] = "E"; icon[2][1] = "E"; icon[2][2] = "E";
		icon[3][0] = "E"; icon[3][1] = " "; icon[3][2] = "E";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";//Does not display bottom row
	}
	mass = 1;
}



Character::~Character()
{
}

void Character::getHit()
{
	if (type == 0) {
		icon[0][0] = " "; icon[0][1] = "D"; icon[0][2] = " ";
		icon[1][0] = "D"; icon[1][1] = "D"; icon[1][2] = "D";
		icon[2][0] = " "; icon[2][1] = "D"; icon[2][2] = " ";
		icon[3][0] = "D"; icon[3][1] = "D"; icon[3][2] = "D";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";
	}													   
	if (type == 1) {									   
		icon[0][0] = " "; icon[0][1] = " "; icon[0][2] = "D";
		icon[1][0] = "D"; icon[1][1] = "D"; icon[1][2] = "D";
		icon[2][0] = "D"; icon[2][1] = "D"; icon[2][2] = "D";
		icon[3][0] = "D"; icon[3][1] = " "; icon[3][2] = "D";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";
	}
	if (type == 2) {
		icon[0][0] = "D"; icon[0][1] = " "; icon[0][2] = " ";
		icon[1][0] = "D"; icon[1][1] = "D"; icon[1][2] = "D";
		icon[2][0] = "D"; icon[2][1] = "D"; icon[2][2] = "D";
		icon[3][0] = "D"; icon[3][1] = " "; icon[3][2] = "D";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";


	}


	

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
}

void Character::update(float dt, int lvl[45][100])
{
	acceleration = force * (1.0 / mass);
	velocity = velocity*0.5 + acceleration*dt;
	velocity.x = velocity.x * 0.8 + acceleration.x*dt;
	position = position + velocity*dt;
	force.set(0, 0); 

	//int i = (int)position.y;//stores position
	//int j = (int)position.x;//stores position

	//Testing Reverse Movement

	//Enemies
	if (type == 1 && flipped == false) {
		icon[0][0] = " "; icon[0][1] = " "; icon[0][2] = "E";
		icon[1][0] = "E"; icon[1][1] = "E"; icon[1][2] = "E";
		icon[2][0] = "E"; icon[2][1] = "E"; icon[2][2] = "E";
		icon[3][0] = "E"; icon[3][1] = " "; icon[3][2] = "E";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";//Does not display bottom row
		addForce(Vector2(1, 0));
		ctr = 0;
	}
	if (type == 2 && flipped == false) {
		icon[0][0] = "E"; icon[0][1] = " "; icon[0][2] = " ";
		icon[1][0] = "E"; icon[1][1] = "E"; icon[1][2] = "E";
		icon[2][0] = "E"; icon[2][1] = "E"; icon[2][2] = "E";
		icon[3][0] = "E"; icon[3][1] = " "; icon[3][2] = "E";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";//Does not display bottom row
		addForce(Vector2(-1, 0));
		ctr = 0;
	}
	else if (type == 1 && flipped == true) {
		icon[0][0] = "E"; icon[0][1] = " "; icon[0][2] = "E";
		icon[1][0] = "E"; icon[1][1] = "E"; icon[1][2] = "E";
		icon[2][0] = "E"; icon[2][1] = "E"; icon[2][2] = "E";
		icon[3][0] = " "; icon[3][1] = " "; icon[3][2] = "E";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";
		//velocity.x = (0, 0);
		ctr++;
		if (ctr >= 10000) {
			ctr = 0;
			flipped = false;
		}
		
	}
	else if (type == 2 && flipped == true) {
		icon[0][0] = "E"; icon[0][1] = " "; icon[0][2] = "E";
		icon[1][0] = "E"; icon[1][1] = "E"; icon[1][2] = "E";
		icon[2][0] = "E"; icon[2][1] = "E"; icon[2][2] = "E";
		icon[3][0] = " "; icon[3][1] = " "; icon[3][2] = "E";
		icon[4][0] = "X"; icon[4][1] = "X"; icon[4][2] = "X";
		//velocity.x = (0, 0);
		ctr++;
		if (ctr >= 10000) {
			ctr = 0;
			flipped = false;
		}
	}
	//Not Enemies
	for (int k = 0; k < height / 2; k++) {//bottom half
		for (int l = (width / -2); l < width / 2; l++) {
			while (lvl[(int)position.y + k][(int)position.x + l] > 0) {//if inside a block
				position.y--;//go above it
				velocity.y = 0;//no moving
				jumpFrame = 0;
				jumping = false;
			}
		}
	}
	for (int k = (height / -2); k < 0; k++) {//top half
		for (int l = (width / -2); l < width / 2; l++) {
			while (lvl[(int)position.y + k][(int)position.x + l] > 0) {//if inside a block
				position.y++;//go under it
				velocity.y = 0;//no moving
			}
		}
	}

	

	if (position.y < 1) position.y = 1;
	if (position.y > 44) position.y = 44;
	if (position.x < 0) position.x = 99;
	else if (position.x > 99) position.x = 0;

	

}

void Character::draw()
{
	//sprite
}

