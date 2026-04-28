#include "lattice.h"
#include "member.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <random>

//updates the "system" every step (movements of members, SEIR change)
void Lattice::updateRule(){
	//shuffles order of members at start of turn to prevent the same member always having high priority, and some having low.
	std::shuffle(members.begin(), members.end(), gen);

	//possible moves	                        left      right   up      down
	//notably does NOT consider diagonals. Found the specification too vague to determine whether directionals were wanted or NOT.
	const std::vector<std::pair<int,int>> directs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

	//random choice generator
	std::uniform_int_distribution<> directsDist(0, directs.size() - 1);

	//cycles through members and moves them IF they are not moving to a clear spot
	for (auto& p_ptr : members) { //for its pointer
		Member* p = p_ptr.get(); //returns raw pointer
		
		//gets the current position so that adjacent can be determined
		int currentx = p->getx();
		int currenty = p->gety();
		
		//chooses random direction
		auto chosendirect = directs[directsDist(gen)];
 		
		//calculates new positions
		int newx = currentx + chosendirect.first;
		int newy = currenty + chosendirect.second;

		//moves the member to the new position
		lattice[newx][newy] = p; //changes the pointer of the lattice to the new position
		p->moveMember(newx, newy); //changes the location properties of the member
	}
}

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
			p->moveMember(this->uniform(0, this->lengthx), this->uniform(0, this->lengthy));
			p->setSEIRstate(this->uniform(1,4));
		}
	}
}
