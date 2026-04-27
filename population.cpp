#include "population.h"
#include <iostream>
#include <cmath>

//constructor
Population:Population(int seed, int memberNumber, double sideLength){
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

//uniform (rng) method
double Population::uniform(double min, double max){
	return (max-min)*this->uniformDist(gen)+min;

//places the members in random positions in the lattice for the simulation
void Population::randomStart(){
	for(Member &m : this->members){
		m.x = this->uniform(0, this->simulationLattice.getSidex());
		m.y = this->uniform(0, this->simulationLattice.getSidey());
		m.theta = this->uniform(-M_PI, M_PI);
