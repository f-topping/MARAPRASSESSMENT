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


	//possible moves     left      right   up      down , diagonals
	const std::vector<std::pair<int,int>> directs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

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
		
		//checks if the new position is off the lattice or already taken, skips to next 
		if (!isValid(newx, newy)) continue;
		if (isOccupied(newx, newy)) continue;

		//moves the member to the new position
		lattice[currentx][currenty] = nullptr; //makes the old position empty
		lattice[newx][newy] = p; //changes the pointer of the lattice to the new position
		p->moveMember(newx, newy); //changes the location properties of the member
		
		//checks if SEIR members S or E or I should move to next stage
		if(p->getSEIRstate() == 2){
			if(progressCheck(incubationRate)) p->setSEIRstate(3);
		}
		if(p->getSEIRstate() == 3){
			if(progressCheck(immunityRate)) p->setSEIRstate(4);
		}
		
		if(p->getSEIRstate() == 1){
			//counts infected neighbours for a chance to expose the member
			infectedNeighbours = 0;
			for (const auto& d : directs) { //checks each direction
				int checkx = currentx + d.first; //coordinates of neighouring cell
				int checky = currenty + d.second;
			
				if(!isValid(checkx, checky)) continue; //no need to check SEIR if cell is off the lattice
			
				Member* neighbour = lattice[checkx][checky];
				if(neighbour && neighbour->getSEIRstate() == 2){
					infectedNeighbours += 1;
				}
			}
			if(progressCheck(exposureRate*infectedNeighbours)) p->setSEIRstate(2);

		}//^maybe a switch-case method mightve looked better here
		history.push_back(countSEIR());
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

	this->members.resize(this->memberNumber);
	
	//for distributed start
	this->shouldRestart = true;
	this->potentialx = 0;
	this->potentialy = 0;

	//SEIR
	this->exposureRate = 0.05;
	this->incubationRate = 0.5;
	this->immunityRate = 0.5;
	this->infectedNeighbours = 0;
	std::vector<std::array<int, 4>> history;

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
			shouldRestart = true;
			while(shouldRestart){
				potentialx = this->uniform(0,this->lengthx);
				potentialy = this->uniform(0,this->lengthy);
				if(isOccupied(potentialx, potentialy)) continue;
				p->moveMember(potentialx, potentialy);
				p->setSEIRstate(this->uniform(1,4));
				shouldRestart = false;
			}
		}
	}
}

//checks if a coordinate pair is within the lattice bounds
//hard boundaries - may encourage susceptible survival as infected may not find them via an extra direction (moving right to wrap around left is effectively moving left)
bool Lattice::isValid(int testx, int testy){
	return testx >= 0 && testx < lengthx && testy >=0 && testy < lengthy;
}

//checks if a coordinate pair has a member associated
bool Lattice::isOccupied(int testx, int testy){
	return lattice[testx][testy] != nullptr;
}

//checks if a member should move to next stage of SEIR
bool Lattice::progressCheck(double rate){
	std::uniform_real_distribution<double> zeroOneDist(0.0,0.1);
	if(zeroOneDist(gen) > rate){
		return false;
	}
	else{
		return true;
	}
}

//counts each SEIR member (for each update)
std::array<int, 4> Lattice::countSEIR(){
	std::array<int, 4> counts = {0, 0, 0, 0}; //SEIR states counts
	for (auto& p_ptr : members) { //for each member ('s pointer)
		int currentState = p_ptr->getSEIRstate(); //get their state
		switch(currentState){ //goes through each possibility and increments where appropriate
			case 1: counts[0]++; break;
			case 2: counts[1]++; break;
			case 3: counts[2]++; break;
			case 4: counts[3]++; break;
		}
	}
	return counts;
}

void Lattice::writeCSV(){
	std::ofstream file("SEIRrecord.csv");
	file << "t,S,E,I,R \n";
	for (size_t t=0; t < history.size(); ++t){
		file << t << "," << history[t][0] << "," << history[t][1] << "," << history[t][2] << "," << history [t][3] << "\n";
	}
}
