/*Christopher Webb
Project PRJ254
Destroy All Colours Version 1
Player.cpp*/

#include "Player.h"
#include <conio.h>
#include <iostream>
using namespace std;

Player::Player(int xpos, int ypos, string name, string filename, Level* level, int points)  : Entity(xpos, ypos, name, filename, level, points)
{
	m_points = points; //unused in final product, easier to include in level
	movecycle = 0;
}


int Player::getPoints()
{
	return m_points;	//we can use this method to check against the total energy needed to complete the level
}

void Player::setPoints(int points)
{
	points = m_points;
}

void Player::gainPoint() //causing logic errors 
{
	m_points++;
}

void Player::dropBall()
{
	
}

void Player::playerLeft()	//player movement methods move one block at a time, so balls can only fall in certain y positions
{
	m_xpos = (m_xpos - 60); // or what ever size of bitmap is
	if(	m_level->isWall(m_xpos, m_ypos)==true||m_level->isWall(m_xpos, m_ypos + Entity_height -1)==true)
	{
		m_xpos = (m_xpos+60);
	}
}

void Player::playerRight()
{
	m_xpos = (m_xpos + 60); // or what ever size of bitmap is
	if(		m_level->isWall(m_xpos + Entity_width -1, m_ypos)==true||m_level->isWall(m_xpos + Entity_width -1, m_ypos +Entity_height -1)==true)
	{
		m_xpos = (m_xpos-60);
	}
}
