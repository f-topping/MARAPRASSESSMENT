#include "population.h"
#include <iostream>
#include <cmath>

//constructor
Population::Population(int seed, int memberNumber, double sideLength){
	//constructing
	std::cout << "Creating population..." << std::endl;

	this->memberNumber = memberNumber; //number of people (subjects)
	this->sideLength = sideLength; //length of lattice side (where subjects will roam)
	
	//lattice (region) associated with the population	
	this->simulationLattice = Lattice(sideLength, sideLength, 0, 0);
	this->members.resize(this->memberNumber);

	//"random" number generator for positioning members at simulation creation
	this->gen = std::mt19937(seed);
}

//uniform generator method
int Population::uniform(int min, int max){
	std::uniform_int_distribution<int> uniformIntDist(min, max);
	return uniformIntDist(gen);
}

//places the members in random positions in the lattice for the simulation
void Population::randomStart(){
	for(Member &p : this->members){
		p.moveMember(this->uniform(0,this->simulationLattice.getSidex()), this->uniform(0, this->simulationLattice.getSidey()));
		p.setSEIRstate(this->uniform(1,4));
	}
}
