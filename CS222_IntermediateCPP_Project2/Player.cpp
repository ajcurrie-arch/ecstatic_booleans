#include <string>
#include <iostream>
#include "Player.h"


using namespace std;



//constructors

Player::Player() {
    //Setting salary to 0 could result in incorrect financial calculations.
    salary = -1;
    
    agent = 0;
}



Player::Player(string n, double sal, Agent *agent) {
    Player();
    
    name = n;
    setSalary(sal);
    setAgent(agent);
}




//accessors

string Player::getName() const {
    return name;
}


Agent* Player::getAgent() const {
    return agent;
}

//returns -1 if salary not yet specified
double Player::getSalary() const {
	return salary;
}




//mutators

void Player::setName(string &newName) {
	name = newName;
}


void Player::setSalary(double newSal) {
    if (newSal >= 0) {
        
        //If this player has an agent to update, update the agent to account for change in salary.
        if (agent != 0) {
            agent -> removePlayerSalary(salary);
            agent -> addPlayerSalary(newSal);
        }
        
        salary = newSal;
        
    } else {
        throw invalid_argument("tried to set a player's salary to a negative number");
    }
}

//sets the agent for the player and updates the agent objects accordingly.
void Player::setAgent(Agent* newAgent) {
    
    if (agent == 0) {
        
        //Give the player its first agent.
        agent = newAgent;
        
        //Update the agent.
        agent -> addPlayerSalary(salary);
    } else {
        
        //Save the old agent for this player.
        Agent *oldAgent = agent;
        
        //Update old and new agents.
        oldAgent -> removePlayerSalary(salary);
        newAgent -> addPlayerSalary(salary);
        
        agent = newAgent;
    }
    
}



//returns the deduction to pay this player's agent
double Player::calculateDeduction() const {
	return salary * agent -> getStipendRatio();
}




//prints and returns the paystub for this player (inc. name, contract salary, deduction and net payment)
std::string Player::printPayStub() const {
	
	string result =  "PLAYER PAYSTUB\n";
	result     +=    "--------------\n";	

	result += "Player name: " + name + "\n";

	result += "Contract salary: $" + to_string(salary) + "\n";

	result += "Agent deduction: $" + to_string(calculateDeduction()) + "\n";

	result += "Net payment: $" + to_string(salary - calculateDeduction()) + "\n";


	cout << result;
	return result;
}