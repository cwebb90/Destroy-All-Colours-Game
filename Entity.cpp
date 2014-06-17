/*Christopher Webb
Project PRJ254
Destroy All Colours Version 1
Entity.cpp*/

#include "Entity.h"
#include <conio.h>
#include <iostream>
using namespace std;

Entity::Entity(int xpos, int ypos, string name, string filename, Level* level, int speed)
{
	m_xpos = xpos;						//allows for positioning Entitys in the arena
	m_ypos = ypos;
	m_name = name;
	m_speed = speed;
	m_filename = filename;
	Entitybit = al_load_bitmap(m_filename.c_str());	//loads bitmap
	m_level = level;
	Entity_width = 60;
	Entity_height = 60;

	al_convert_mask_to_alpha(Entitybit, al_map_rgb(255, 0, 255)); //clears the background of the bitmaps
	
	if (!Entitybit)												//checks to see if bitmap has loaded correctly, displays error if it has not
	{
		cout << "Entity bitmap creation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_bitmap(Entitybit);		
	}
}


void Entity::left()	//movement methods
{
	m_xpos = (m_xpos-m_speed);
	if(	m_level->isWall(m_xpos, m_ypos)==true||m_level->isWall(m_xpos, m_ypos + Entity_height -1)==true)
	{
		m_xpos = (m_xpos+m_speed);
	}
}

void Entity::right()	
{
	m_xpos = (m_xpos+m_speed);
	if(		m_level->isWall(m_xpos + Entity_width -1, m_ypos)==true||m_level->isWall(m_xpos + Entity_width -1, m_ypos +Entity_height -1)==true)
	{
		m_xpos = (m_xpos-m_speed);
	}
}


void Entity::down()
{
	bool wall_below = m_level->isWall(m_xpos,m_ypos + Entity_height +1)||m_level->isWall(m_xpos + Entity_width -1, m_ypos + Entity_height +1);
	bool ball_below = m_level->isBall(m_xpos,m_ypos + Entity_height +1)||m_level->isBall(m_xpos + Entity_width -1, m_ypos + Entity_height +1);

	if(!wall_below && !ball_below)
	{
	m_ypos = (m_ypos+m_speed);		//unused
	}
}


void Entity::setX(int x)//standard programming practice
{
	m_xpos=x;
}

void Entity::setY(int y)
{
	m_ypos=y;
}

int Entity::getX()
{
	return m_xpos;
}

int Entity::getY()
{
	return m_ypos;
}

int Entity::getHeight()
{
	return Entity_height;
}

int Entity::getWidth()
{
	return Entity_width;
}

Entity::~Entity()
{	
	al_destroy_bitmap(Entitybit);
}

void Entity::draw()
{	
	al_draw_bitmap_region(Entitybit, 0, 0, 60, 60, m_xpos, m_ypos, 0);		
}		
