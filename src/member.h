#ifndef MEMBER_H
#define MEMBER_H

class Member {
	private:
		//coordinates
		double x;
		double y;

	public:
		Member(); //constructor

		//cell the member will attempt to move to (1-8 left to right, up to down)
		void findMoveIntention();
		int moveIntention;

		//SIER compartment 
		//0 - empty, 1 - susceptible, 2 - exposed, 3 - infected, 4 - recovered
		int SIERstate;

		//getters
		int getx();
		int gety();

		//setter
		void moveMember(int xPos, int yPos);
}

#endif
