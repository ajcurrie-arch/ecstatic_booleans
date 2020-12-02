
#ifndef AGENT_PLAYER_SALARY_LIST_H
#define AGENT_PLAYER_SALARY_LIST_H

#include <array>


/*Class designed to optimize memory usage for storing player salaries for an agent.
Uses statically allocated and dynamically allocated memory for arrays.*/
class AgentPlayerSalaryList {
    private:
        std::array<double, 3> baseArray; //statically allocated memory, for expected number of players per agent   unordered, no empty indexes between elements
        
        double* extraElementArray; //dynamically allocated memory in case there are more players than expected    unordered, no empty indexes between elements
        int extraElementCapacity; //capacity of extraElementArray  Note: This is dependent on extraElementArray
    
        int elementCount; //total number of indexes containing actual values, not the same as capacity
        
        void doubleExtraElementCapacity(); //doubles pointer array capacity, doubling reduces O classification for memory reallocation
        
        double get(int index) const; //get the value at 'index' index in the list as a whole
        void set(int index, double value); //Sets the value at 'index' index in the list as a whole. Automatically increases capacity if needed. Increases elementCount if needed.
        
    public:
        AgentPlayerSalaryList();
    
        int getElementCount() const; //returns the total number of indexes containing actual values in this AgentPlayerSalaryList
        void add(double salary); //adds an element to this AgentPlayerSalaryList
        bool removeSalary(double salary); //Removes exactly one of 'salary' from this list and updates elementCount accordingly. Returns true iff the element is removed successfully, and false if it is not found in the list.
        double sum() const; //returns the sum of all elements in this list
};


#endif