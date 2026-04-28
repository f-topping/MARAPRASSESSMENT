#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include "member.h"
#include <array>
#include <fstream>

class Lattice {
	private:
		//lattice sidelengths
		int lengthx;
		int lengthy;
		int seed;
		int memberNumber;

		//lattice array
		std::vector<std::vector<Member*>> lattice;
		std::vector<std::unique_ptr<Member>> members;
		
	public:
		//update rng
		void updateRule();
		std::vector<std::pair<int,int>> directs;
		std::uniform_int_distribution<> directsDist();
		std::uniform_real_distribution<double> zeroOneDist();
		bool isValid(int testx, int testy);
		bool isOccupied(int testx, int testy);

		Lattice(int lengthx, int lengthy, int seed, int memberNumber);

		//init rng
		std::mt19937 gen;
		std::uniform_int_distribution<int> uniformIntDist;
		int uniform(int min, int max);
		void randomStart();

		int potentialx;
		int potentialy;
		bool shouldRestart;
		
		//getters for probing
		int getSidex() const;
		int getSidey() const;

		//SEIR 
		double exposureRate; //exposure rate (theta) - chance a susceptible member becomes exposed after collision with infected
		double incubationRate; //incubation rate (sigma) - chance an exposed becomes infected after each step
		double immunityRate; //immunity rate (gamma) - chance an infected becomes recovered (immume) after each step
		bool progressCheck(double rate); //check
		int infectedNeighbours; //number of neighbours a cell has that are infected
		std::vector<std::array<int, 4>> history; //for recording all SEIR information
		std::array<int, 4> countSEIR(); //for counting No. each SEIR per step
		int currentState; //current SEIR state for counting
		void writeCSV(); //writes SEIR history to a csv for graphing
};
#endif
