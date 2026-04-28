#include "member.h"
#include <cstdlib>
#include <iostream>
#include <random>


Member::Member(){
	//gives the members a default position, 0,0. will be changed by population.
	this->x = 0;
	this->y = 0;

	//random number generator 
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> distribution(1,4);

	//what state the member will have upon creation.
	//as this is the member, SIER 0 is not possible.
	this->SIERstate = distribution(1, 4);
}

//which tile the member would try to move to.
void Member::findMoveIntention(){
	this->moveIntention = distribution(1, 8);
}

int Member::getx(){
	return this->x;
}

int Member::gety(){
	return this->y;
}

void Member::moveMember(int xPos, int yPos){
	this->x = xPos;
	this->y = yPos;
}

