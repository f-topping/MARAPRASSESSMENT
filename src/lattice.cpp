#include "lattice.h"
#include "member.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <random>

//constructor
Lattice::Lattice(int lengthx, int lengthy, int seed, int memberNumber){
	//constructing
	std::cout << "Building Lattice..." << std::endl;
	
	//properties
	this->lengthx = lengthx; //length of lattice sides
	this->lengthy = lengthy;
	this->seed = seed; //rng seed number
	this->memberNumber = memberNumber; //number of "people" to be distributed
	
	//lattice (region) associated with the members
	this->lattice = std::vector<std::vector<Member*>>(lengthx, std::vector<Member*>(lengthy, nullptr));
	
	//rng
	this->gen = std::mt19937(seed);
}

//getters
int Lattice::getSidex() const{
	return lengthx;
}

int Lattice::getSidey() const{
	return lengthy;
}

//rng for int numbers, input limits returns a random int between
int Lattice::uniform(int min, int max){
	std::uniform_int_distribution<int> uniformIntDist(min,max);
	return uniformIntDist(gen);
}

//provides members random properties
void Lattice::randomStart(){
	//auto deduces std::unique_ptr<Member>
	for(auto& p : members){
		if (p){
			p->moveMember(this->uniform(0, this->lattice.getSidex()), this->uniform(0, this->lattice.getSidey()));
			p->setSEIRstate(this->uniform(1,4));
		}
	}
}
