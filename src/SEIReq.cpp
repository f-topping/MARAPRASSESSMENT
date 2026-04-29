#include <iostream> //imports
#include <vector>

//"class"like structure struct with each state inside
struct State{
	double S, E, I, R;
};

int main(){
	//parameters
	double beta = 1.0;
	double sigma = 1.0;
	double gamma = 0.1;
	double members = 1000.0;

	//starting member amounts
	State state = {990.0,0.0,10.0,0.0};
	
	int days = 1000;
	double dt = 0.1; //timestep
	
	std::vector<State> history; //array(vector) of states called history

	for (int t = 0; t < days; ++t){
		history.push_back(state); //records SEIR amounts
		
		//solves the equations
		double dS = (-beta * state.S * state.I )/ members;
		double dE = ((beta * state.S * state.I) / members) - (sigma * state.E);
		double dI = (sigma * state.E) - (gamma * state.I);
		double dR = gamma * state.I;

		state.S += dS * dt;
		state.E += dE * dt;
		state.I += dI * dt;
		state.R += dR * dt;
	}
	
	//to csv
	std::cout << "t,S,E,I,R\n";
	for (int t = 0; t < history.size(); ++t){
		std::cout << t << "," << history[t].S << "," << history[t].E << "," << history[t].I << "," << history[t].R << "\n";
	}
	return 0;
}
