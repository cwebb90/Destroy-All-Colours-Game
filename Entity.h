/*Christopher Webb
Project PRJ254
Destroy All Colours Version 1
Entity.h*/

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <string>
#include "Level.h"
using namespace std;

class Entity
{
protected:
	int m_xpos;						//x and y positions of the Entity
	int m_ypos;
	int m_speed;
	string m_name;					//allows naming of object
	string m_filename;				//allows bitmap to be loaded in using a string as a filename
	Level* m_level;					//allows access to collision methods and coordinates
	ALLEGRO_BITMAP* Entitybit;	//bitmap for the Entity
	int Entity_width;				//need to calculate width and height to get proper coordinates to check collision, 
	int Entity_height;			//for example checking the top right corner of the bitmap would be x + width, y + height

public:

//constructor/destructor
	Entity(int xpos, int ypos, string name, string filename, Level* level, int speed);
	~Entity();

//movement
	void left();
	void right();
	void down();

//sets/gets
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	
//draws
	void draw();

//falling
	void fall();
};
