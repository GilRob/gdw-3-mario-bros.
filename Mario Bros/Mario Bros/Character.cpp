#include "stdafx.h"
#include "Character.h"
#include <string>

Character::Character(int type)
{
	if (type == 0) {
		icon = 'M';
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

void Character::draw()
{
	//sprite
}