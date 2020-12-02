
#ifndef PLAYER_H
#define PLAYER_H

#include "Agent.h"


class Player {
    private:
        std::string name; //name of this player
        double salary; //contract salary of this player, has value of -1 if not yet specified
        Agent *agent; //agent player is assigned to
        
    public:
        Player(); //NOTE: Leaves salary and agent unset.
        Player(std::string name, double salary, Agent *agent);
        
        std::string getName() const;
        Agent* getAgent() const;
        double getSalary() const; //returns -1 if salary not yet specified

        void setName(std::string &newName);
        void setSalary(double newSal);
        void setAgent(Agent* agent); //sets the agent for the player and updates the agent objects accordingly.

        double calculateDeduction() const; //returns the deduction to pay this player's agent

        std::string printPayStub() const; //prints and returns the paystub for this player (inc. name, contract salary, deduction and net payment)
};


#endif