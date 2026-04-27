#ifndef POPULATION_H
#define SYSTEM_H

#include  <random>

class Population {
	public:
		//for making people
		Population(int seed, int memberNumber, double sideLength);
		int seed;
		int memberNumber;
		double sideLength;
		
		//for initialising locations
		std::mt19937 gen;
		std::uniform_real_distribution<double> uniformDist;
		double uniform(double min double max);
		void randomStart();
};
