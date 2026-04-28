#ifndef POPULATION_H
#define SYSTEM_H

#include <random>
#include <vector>
#include "member.h"

class Population {
	public:
		//for making people
		Population(int seed, int memberNumber, double sideLength);
		int seed;
		int memberNumber;
		double sideLength;

		std::vector<Member> members;
		
		//for initialising locations
		std::mt19937 gen;
		std::uniform_int_distribution<int> uniformIntDist;
		int uniform(int min, int max);
		void randomStart();
};

#endif
