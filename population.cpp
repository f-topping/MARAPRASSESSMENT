#include "population.h"

//constructor
Population:Population(int seed, int memberNumber, double sideLength){
	//constructing
	std::cout << "Creating population..." << std::endl;

	this->memberNumber = memberNumber; //number of people (subjects)
	this->sideLength = sideLength; //length of lattice side (where subjects will roam)
	
	//"random" number generator for positioning members at simulation creation
	this->gen = std::mt19937(seed);
}


