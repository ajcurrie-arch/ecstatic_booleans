
#include "AgentPlayerSalaryList.h"
#include <stdexcept>


using namespace std;




AgentPlayerSalaryList::AgentPlayerSalaryList() {
    elementCount = 0;
    extraElementCapacity = 0;
}



//doubles pointer array capacity, doubling reduces O classification for memory reallocation
void AgentPlayerSalaryList::doubleExtraElementCapacity() {
    //Save the pointer array as it currently is.
    double *saveArray = extraElementArray; 
    
    //Make a new pointer array for this list with double the capacity.
    extraElementArray = new double[extraElementCapacity * 2];
    
    
    //Transfer the values from the old pointer array to the new one for this list.
    int usedIndexes = elementCount - baseArray.size(); //Calculates the indexes with actual elements in them in the pointer array.
    for (int i = 0; i < usedIndexes; i++) {
        *(extraElementArray + i) = *(saveArray + i);
    }
    
    
    //Update the capacity value.
    extraElementCapacity *= 2;
    
    //The old pointer array is no longer needed, so clear its memory for other usage.
    delete saveArray;
}


//get the value at 'index' index in the list as a whole
double AgentPlayerSalaryList::get(int index) const {
    
    if (index < elementCount) {
        
        if (index < baseArray.size()) {
            //If index is in statically allocated array, get the value from it.
    		return baseArray[index];
    
    	} else {
    	    //If index is in pointer array, get the value from the pointer array.
    	    
    	    int indInExtraArr = index - baseArray.size(); //Calculate index in pointer array indexes.
    	    
    	    return extraElementArray[indInExtraArr];
    	}
    	
    } else {
        throw out_of_range("salaries in AgentPlayerSalaryList accessed out of range");
    }
}



//returns the total number of indexes containing actual values in this AgentPlayerSalaryList
int AgentPlayerSalaryList::getElementCount() const {
    return elementCount;
}



/*Sets the value at 'index' index in the list as a whole. Automatically increases capacity if needed. 
Increases elementCount if needed. */
void AgentPlayerSalaryList::set(int index, double value) {
    
    if (index < baseArray.size()) {
        //If index is in statically allocated array, set the value in the statically allocated array.
		baseArray[index] = value;

	} else {
	    //If index is in pointer array, set the value in the pointer array.
	    
	    int indInAdditionalArr = index - baseArray.size(); //Calculate the index in the pointer array indexes.
	    
	    if (indInAdditionalArr >= extraElementCapacity) {//If setting on the end of pointer array and the pointer array has reached max capacity...
	        
	        //Increase the size of pointer array to make room. 
	        if (extraElementCapacity == 0) {
	            //If extraElementArray has not been used at all yet, initialize it to a starting capacity of 1.
	            extraElementArray = new double[1];
	            extraElementCapacity = 1;
	        } else {
	            
	            doubleExtraElementCapacity();
	        }
	    }
	    
	    //Now that there is definitely room in pointer array, set the value.
	    extraElementArray[indInAdditionalArr] = value;
	}
	
	//If setting this value increased the number of elements in the list, update elementCount accordingly.
	if (index >= elementCount) {
        elementCount = index + 1;
    }
}


//adds an element to this AgentPlayerSalaryList
void AgentPlayerSalaryList::add(double salary) {
    
    set(elementCount, salary);
}



/*Removes exactly one of 'salary' from this list and updates elementCount accordingly.
Returns true iff the element is removed successfully, and false if it is not found in the list.*/
bool AgentPlayerSalaryList::removeSalary(double salary) {

    //Do a linear search to find the element.
	for (int i = 0; i < elementCount; i++) {
		
		if (get(i) == salary) {
		    
		    //The size of list will decrease by 1, and this index is now vacant, so move last element to this index.
		    double lastElement = get(elementCount - 1);
		    set(i, lastElement);
		    
		    elementCount--;
		    
		    
		    //Element has been removed, so return true for success.
		    return true;
		}
	}
	
	//Linear search reached end of list. Return false for failure.
	return false;
}



//returns the sum of all elements in this list
double AgentPlayerSalaryList::sum() const {
    
    //Apply standard algorithm for summation.
    
    double sum = 0;
    
    for (int i = 0; i < elementCount; i++) {
        sum += get(i);
    }
    
    return sum;
}