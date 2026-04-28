#ifndef MEMBER_H
#define MEMBER_H

class Member {
	private:
		//coordinates
		int x;
		int y;

		//SEIR compartment
		//0-empty, 1-susceptible, 2-exposed, 3-infected, 4-recovered
		int SEIRstate;

	public:
		Member(); //constructor

		//which way a member will try to go (will fail if cell does not exist or is occupied)	
		int moveIntention;

		//getters
		int getx();
		int gety();
		int getSEIRstate();

		//setters
		void moveMember(int xPos, int yPos);
		void setSEIRstate(int SEIRstate);
};

#endif
