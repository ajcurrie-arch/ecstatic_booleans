/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <array>
#include <iostream>
#include "Agent.h"
#include "Player.h"

using namespace std;



array<Agent, 6> agentArray;
array<Player, 15> playerArray;


//prints during-the-year option menu.
void printOptionMenu() {
	cout << "Options: \n";
	cout << "1: Change agent for a player. \n";
	cout << "2: Change a player's salary. \n";
	cout << "3: Print end of the year pay stubs. \n";
}

//Prints a list of all agents inputted by associate.
void printAgentList() {
	for (const auto &agent : agentArray) {
		cout << agent.getName() + " ";
	}
	cout << "\n";
}

//Prints a list of all players inputted by associate.
void printPlayerList() {
    for (const Player &player : playerArray) {
        cout << player.getName() + " ";
    }
    cout << "\n";
}

//Returns a pointer to a player with the given name, or a nullptr if there is no such player.
Player* findPlayer(const string &playerName) {
	for (Player &player : playerArray) {
		if (player.getName() == playerName) {
			return &player;
		}
	}
	
	return 0;
}

//Returns a pointer to an agent with the given name, or a nullptr if there is no such agent.
Agent* findAgent(const string &agentName) {
	for (auto &agent : agentArray) {
		if (agent.getName() == agentName) {
			return &agent;
		}
	}
	
	return 0;
}

//asks the user to choose a player, prompts them with 'prompt'. Returns pointer to user chosen player.
Player* requestPlayerChoice(string prompt) {
    Player* selectedPlayer;
    
    bool playerInputtedSuccessfully = false;
    while (!playerInputtedSuccessfully) {
        cout << prompt;
        
        string inputtedName;
		cin >> inputtedName;
		
		selectedPlayer = findPlayer(inputtedName);
		
		if (selectedPlayer != 0) {
		    playerInputtedSuccessfully = true;
		} else {
		    cout << "There is no player named " + inputtedName + " on the team. \n";
		    cout << "Players: \n";
		    
		    printPlayerList();
		    
		    cout << "\n";
		}
    }
    
    return selectedPlayer;
}

//asks the user to choose an agent, prompting them with 'prompt'. Returns pointer to user chosen agent.
Agent* requestAgentChoice(string prompt) {
    Agent* selectedAgent;
    
    cout << "Agent options: \n";
    printAgentList();
    
    bool agentInputtedSuccessfully = false;
    while (!agentInputtedSuccessfully) {
        cout << prompt;
        
        string inputtedName;
		cin >> inputtedName;
		
		selectedAgent = findAgent(inputtedName);
		
		if (selectedAgent != 0) {
		    agentInputtedSuccessfully = true;
		} else {
		    cout << "There is no agent named " + inputtedName + " available for the team. \n";
		    cout << "Agents: \n";
		    
		    printAgentList();
		    
		    cout << "\n";
		}
    }
    
    return selectedAgent;
    
    
}


int main() {

	cout << "Associate, please input information to create profiles.\n";

	
    
	for (Agent &agent : agentArray) {
	    cout << "Please input information to create an agent profile.\n";
		cout << "Enter name of agent: \n";
		std::string name;
		cin >> name;
        
        bool stipendSetSuccessFully = false;
        while (!stipendSetSuccessFully) { //Repeat asking for a stipend value until it is done w/out error.
    		cout << "Enter agent's stipend ratio (as percentage): \n";
    		string stipendPercentageStr;
    		cin >> stipendPercentageStr;
    		double stipendPercentage = stod(stipendPercentageStr);
    		
    		
    		double stipend = stipendPercentage / 100;
    		//cout << "stipend: " << stipend;
            
            
            stipendSetSuccessFully = true; //Assume that the stipend is set successfully until determined otherwise.
            
            try {
                agent = Agent(name, stipend);
            } catch (const invalid_argument &e) {//If the agent object returns an invalid_argument exception, it should be because the stipend was set out of range.
                cout << "I'm sorry, that stipend ratio is not within the expected range of stipend ratios. Try again.\n";
                
                stipendSetSuccessFully = false;
            }
        }
	}


	for (Player &player : playerArray) {
	    cout << "Please input information to create a player profile.\n";
		cout << "Enter name of player: \n";
		string name;
		cin >> name;
		
		player.setName(name);

        
        bool salarySetSuccessfully = false;
        while (!salarySetSuccessfully) { //Repeat asking for a player salary until it is set without error.
    		cout << "Enter contract salary of player (in millions of dollars): \n";
    		string contractSalInMillionsStr;
    		cin >> contractSalInMillionsStr; //Salary inputs are expected to be in the millions.
    		double salaryInMillions = stod(contractSalInMillionsStr);
            
            double salaryInDollars = salaryInMillions * 1000000;
            
            salarySetSuccessfully = true; //Assume that the salary is set successfully until determined otherwise.
            try {
    		    player.setSalary(salaryInDollars);
            } catch (const invalid_argument &e) { //Catch any exception that comes up from setting the salary to a specific value (probably resulting from the value being negative).
                cout << "There was an error setting the salary of the player to $" << salaryInDollars << ".\n";
                
                //Let the user know what went wrong in case it is something other than a negative value.
                cout << "The specific error message is \"" << e.what() << "\".\n";
                
                salarySetSuccessfully = false;
            }
        }
        
        
        Agent* playerAgent = requestAgentChoice("Please specify the name of the agent for the player: \n");
        player.setAgent(playerAgent);
	}



	bool yearOver = false; //false until associate prints paystubs 

	while (!yearOver) {
		printOptionMenu();

		string menuSelection;
		cin >> menuSelection;

		if (menuSelection == "1") { //"Change agent for a player. "
            
            //Ask for player.
			Player *selectedPlayer = requestPlayerChoice("What player do you want to change agent for? \n");

			Agent *selectedPlayerAgent = selectedPlayer -> getAgent(); 
            
            
            //Print current agent information.
            cout << selectedPlayer -> getName() + " is currently assigned to agent " + selectedPlayerAgent -> getName() + ".\n";
            
            
            //Ask for new agent.
			Agent *newAgent = requestAgentChoice("Which agent would you like to switch " + selectedPlayer -> getName() + " to? \n");

			selectedPlayer -> setAgent(newAgent);
				
        } else if (menuSelection == "2") { //"Change agent for a player. "
            
            //Ask for player.
			Player *selectedPlayer = requestPlayerChoice("What is the name of the player to change salary for? \n");
            
            double currentSalaryInDollars = selectedPlayer -> getSalary();
            double currentSalaryInMillions = currentSalaryInDollars / 1000000;
            
            
            //Print current salary.
			cout << "Current salary for " + selectedPlayer -> getName() + ": ";
			cout << "$" + to_string(currentSalaryInMillions) + "M\n";
            
            
            //Ask user to set new salary.
            bool salarySetSuccessfully = false;
            while (!salarySetSuccessfully) { //Repeat until the salary is set without error.
    			cout << "Enter new salary (in millions of dollars): ";
    			double newSalaryInMillions;
    			string newSalaryInMillionsStr;
    			cin >> newSalaryInMillionsStr;
    			newSalaryInMillions = stod(newSalaryInMillionsStr);
                
                double newSalaryInDollars = newSalaryInMillions * 1000000;
                
                salarySetSuccessfully = true; //Assume that salary is set successfully until determined otherwise.
                try {
                    
    			    selectedPlayer -> setSalary(newSalaryInDollars);
    			    
                } catch (const invalid_argument &e) { //Catch any exception that comes up from setting the salary to a specific value (probably resulting from the value being negative).
                    
                    cout << "There was an error setting the salary of the player to $" << newSalaryInDollars << ".\n";
                    
                    //Let the user know what went wrong in case it is something other than a negative value.
                    cout << "The specific error message is \"" << e.what() << "\".\n";
                
                    salarySetSuccessfully = false;
                }
            }
            
        } else { // case 3: "Print end of the year pay stubs. "
        
			for (const auto &player : playerArray) {
				player.printPayStub();
			} 

			for (const auto &agent : agentArray) {
			    if (agent.getPlayersRepresentedCount() != 0) { //Only print agents that are relevant to the team, i.e. have at least one player on team assigned to them.
				    agent.printPayStub();
			    }
			}

			yearOver = true; //Pay stubs have been printed, so game year is over.
		}
	}
}
