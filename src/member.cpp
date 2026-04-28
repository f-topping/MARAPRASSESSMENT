#include "member.h"
#include <cstdlib>
#include <iostream>
#include <random>


Member::Member(){
	//gives the members a default position, 0,0. will be changed by population.
	this->x = 0;
	this->y = 0;

	//default SEIR
	this->SEIRstate = -1;
	
	//default intentions
	this->moveIntention = 0;
}

//getters
int Member::getx(){
	return x;
}

int Member::gety(){
	return y;
}

int Member::getSEIRstate(){
	return SEIRstate;
}

//setters
void Member::moveMember(int xPos, int yPos){
	x = xPos;
	y = yPos;
}

void Member::setSEIRstate(int givenSEIRstate){
	this->SEIRstate = givenSEIRstate;
}
