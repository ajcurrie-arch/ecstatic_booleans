
#ifndef AGENT_H
#define AGENT_H

#include <string>
#include "AgentPlayerSalaryList.h"



class Agent {
    private:
        /*AgentPlayerSalaryList implemented instead of array for better memory optimization.
        Will ocassionally be slower due to dynamic alloc. and reallocation of memory.*/
        AgentPlayerSalaryList playerSalaryList; //list of all player salaries assigned to this agent
        
        
        std::string name; //name of this agent
        double stipendRatio; //this agent's stipend ratio, has value of -1 if not yet specified
        
        
    public:
        Agent(); //NOTE: Leaves stipend ratio unset.
        Agent(std::string name, double stipendRatio);
        
    	std::string getName() const;
    	double getStipendRatio() const; //returns -1 if stipend ratio not yet set
        int getPlayersRepresentedCount() const; //returns number of player salaries this agent currently has assigned to it
        
        void setName(std::string &newName);
        void setStipendRatio(double newStipend);
        
        void addPlayerSalary(double sal); //assigns a player salary to this agent
        void removePlayerSalary(double sal); //unassigns a player salary from this agent (if there are multiple matches, it unassigns just one)

        std::string printPayStub() const; //prints the pay stub for this agent (inc. name and net payment)
};


#endif