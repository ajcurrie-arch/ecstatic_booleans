#include <string>
#include <iostream>
#include <stdexcept>
#include "Agent.h"
#include "Player.h"


using namespace std;



/*static bool Agent::isValidStipend(double stipend) {
    if (stipend >= 0.01 && stipend <= 0.05) {
        return true;
    } else {
        return false;
    }
}*/


/*static invalid_argument Agent::stipendException() {
    return invalid_argument("stipend ratio for agent is out of domain");
}*/


Agent::Agent() {
    playerSalaryList = AgentPlayerSalaryList();
    
    //Setting stipend ratio to 0 could result in incorrect financial calculations.
    stipendRatio = -1;
}




Agent::Agent(string n, double sRatio) {
    Agent();
    
    setName(n);
    setStipendRatio(sRatio);
}




std::string Agent::getName() const {
	return name;
}


//returns -1 if stipend ratio not yet set
double Agent::getStipendRatio() const {
	return stipendRatio;
}

//returns number of player salaries this agent currently has assigned to it
int Agent::getPlayersRepresentedCount() const {
	return playerSalaryList.getElementCount();
}





void Agent::setName(std::string &newName) {
	name = newName;
}


void Agent::setStipendRatio(double newStipend) {
    double lowerLimit = 0.01;
    double upperLimit = 0.05;
    
	if (newStipend >= (lowerLimit - 10E-30) && newStipend <= upperLimit + 10E-30) {
		stipendRatio = newStipend;
	} else {
	    //Allowing a stipend ratio to be set out of domain could result in incorrect financial calculations.
		throw invalid_argument("stipend ratio for agent set out of domain");
	}
}


/*double Agent::getPlayerSalary(int salIndex) const {
    
    if (salIndex < playersRepresentedCount) {
        
        if (salIndex < basePlayerSalaryArray.size()) {
    		return basePlayerSalaryArray[salIndex];
    
    	} else {
    	    int indInAdditionalArr = salIndex - basePlayerSalaryArray.size();
    	    
    	    return additionalPlayerSalaryArray[indInAdditionalArr];
    	}
    	
    } else {
        throw out_of_range("player salaries in agent accessed out of range");
    }
}*/


//facilitates interaction with statically allocated and dynamically allocated salary arrays
//Inserts a salary at an index in the whole of the player salary arrays put together
/*void Agent::setPlayerSalary(int salIndex, double value) {
    
    if (salIndex < basePlayerSalaryArray.size()) {
		basePlayerSalaryArray[salIndex] = value;

	} else {
	    int indInAdditionalArr = salIndex - basePlayerSalaryArray.size();
	    
	    if (indInAdditionalArr >= additionalPlayerSalaryCapacity) {
	        doubleAdditionalSalaryCapacity();
	    }
	    
	    additionalPlayerSalaryArray[indInAdditionalArr] = value;
	}
	
	if (salIndex >= playersRepresentedCount) {
        playersRepresentedCount = salIndex + 1;
    }
}*/

/*
void Agent::doubleAdditionalSalaryCapacity() {
    
    double *saveArray = additionalPlayerSalaryArray;
    int saveCapacity = additionalPlayerSalaryCapacity;
    
    additionalPlayerSalaryArray = new double[additionalPlayerSalaryCapacity * 2];
    
    
    int usedIndexes = playersRepresentedCount - basePlayerSalaryArray.size();
    for (int i = 0; i < usedIndexes; i++) {
        *(additionalPlayerSalaryArray + i) = *(saveArray + i);
    }
    
    
    additionalPlayerSalaryCapacity *= 2;
    
    delete saveArray;
}*/


//assigns a player salary to this agent
void Agent::addPlayerSalary(double playerSal) {

	playerSalaryList.add(playerSal);
	
}



//unassigns a player salary from this agent (if there are multiple matches, it unassigns just one)
void Agent::removePlayerSalary(double playerSal) {

	bool removeSuccessful = playerSalaryList.removeSalary(playerSal);
	
	if (!removeSuccessful) {
	    throw logic_error("tried to remove a player salary from an agent that was not assigned to it");
	}
}




//prints the pay stub for this agent (inc. name and net payment)
string Agent::printPayStub() const {
	string result =  "AGENT PAYSTUB\n";
	result     +=    "-------------\n";	

	result += "Agent name: " + name + "\n";


	double netPlayerSalary = playerSalaryList.sum();
	
	double salary = netPlayerSalary * stipendRatio;

    
	result += "Total payment: $" + to_string(salary) + "\n";


	cout << result;
	return result;
}