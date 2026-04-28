#include <iostream>
#include "lattice.h"

int main(){
	Lattice myLattice(100,100,10, 25); //makes a grid with members
	myLattice.randomStart(); //gives each member a random position and SEIR state
	for (int i = 0; i < 10; i++){ //does some turns
		myLattice.updateRule();
	}
	return 0; 	
}
