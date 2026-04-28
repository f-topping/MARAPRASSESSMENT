#ifndef LATTICE_H
#define LATTICE_H

#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include "member.h"

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
		std::vector<int> directs;
		std::uniform_int_distribution directsDist();

		Lattice(int lengthx, int lengthy, int seed, int memberNumber);

		//init rng
		std::mt19937 gen;
		std::uniform_int_distribution<int> uniformIntDist;
		int uniform(int min, int max);
		void randomStart();

		int getSidex() const;
		int getSidey() const;
};
#endif
