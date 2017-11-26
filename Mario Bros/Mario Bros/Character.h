#pragma once
#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Vector2.h"
#include <string>

class Character
{
public:
	int hp;
	int speed;
	int width;
	int height;
	Vector2 position;
	Vector2 center;
	Vector2 velocity = Vector2(0,0);
	Vector2 acceleration = Vector2(0, 0);;
	Vector2 force;
	int type;
	float mass;
	char* icon[5][3];
	bool jumping = false;
	int jumpFrame = 0;
	int oldx;
	int oldy;
	bool flipped = false;
	int ctr = 0;

	Character(int type);
	~Character();
	void setCenter(float x, float y) {
		center.x = x; center.y = y;
	}
	void setWidthHeight(float x, float y) {
		width = x; height = y;
	}
	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}
	void addForce(Vector2 v);
	virtual void update(float dt);
	virtual void update(float dt, int lvl[45][100]);
	virtual void draw();

	void getHit();
	//Collisions

	bool isColliding(int width, int height);

	float MarioMinX;
	float MarioMaxX;
	float MarioMinY;
	float MarioMaxY;

	float EnemiesMinX;
	float EnemiesMaxX;
	float EnemiesMinY;
	float EnemiesMaxY;

};

