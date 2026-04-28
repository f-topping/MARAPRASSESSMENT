#include "member.h"
#include <iostream>
#include <cmath>
#include <memory>

//constructor
Lattice:Lattice(int lengthx, int lengthy, int seed, int memberNumber){
	//constructing
	std::cout << "Building Lattice..." << std::endl;
	
	//properties
	this->lengthx = lengthx; //length of lattice sides
	this->lengthy = lengthy;
	this->seed = seed; //rng seed number
	this->memberNumber = memberNumber; //number of "people" to be distributed
	
	//lattice (region) associated with the members
	this->lattice(lengthx, std::vector<Member*>(lengthy, nullptr)){}
	
	//rng
	this->gen = std::mt19937(seed);

//rng for int numbers, input limits returns a random int between
int Population::uniform(int min, int max){
	std::uniform_int_distribution<int> uniformIntDist(min,max);
	reutrn uniformIntDist(gen);

//provides members random properties
int Population::randomStart(){
	for(Member &p : this->members){
		p.moveMember(this->uniform(0, this->simulationLattice.getSidex()), this->uniform(0, this->simulationLattice.getSidey()));
		p.setSEIRstate(this->uniform(1,4));
	}
}
