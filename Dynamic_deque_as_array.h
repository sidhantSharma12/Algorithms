#define DYNAMIC_DEQUE_AS_ARRAY_H

#include <iostream>
using namespace std;


class Dynamic_deque_as_array {

	public : 
			 Dynamic_deque_as_array(int = 10);
			 ~Dynamic_deque_as_array();

			 int head() const;
		     int tail() const;
		     int size() const; 
		     bool empty() const;
		     int capacity() const;

		     void enqueue_head(const int  &);
		     void enqueue_tail(const int  &);
		     int dequeue_head();
		     int dequeue_tail();
		     void clear();
		     void doubleArraySize();


 
 	private :
 	        int * array; 
 		  	int mHead;
 		  	int mTail;
 		  	int count;
 		  	int arraySize;


 		  	

};

Dynamic_deque_as_array::Dynamic_deque_as_array(int n){
	
	arraySize=std::max(1,n); //if the user inputs a non-positive size, set the array size to one. Otherwise set the array size to n.
	array= new int[arraySize]; 
	count=0;
	

}
 
Dynamic_deque_as_array::~Dynamic_deque_as_array(){
   delete [] array; //deleting the memory intially created

}

int Dynamic_deque_as_array::size() const{
	return count; 
}

int Dynamic_deque_as_array::capacity() const {//not sure what capacity means
	return arraySize;
}


bool Dynamic_deque_as_array::empty() const {
	return count==0;
}

int Dynamic_deque_as_array::head() const {
	return *(array+mHead); 
}


int Dynamic_deque_as_array::tail() const {
	return *(array+mTail);
}

void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
	
	if(count==0){  //insert at start of array
		*array=obj;
		mHead=0;
		mTail=0; //make head and tail both point to the same int object.
		count++;
	}

	else {

		if(count==arraySize){
   		   doubleArraySize(); //double the array size
		}

		 mHead=(mHead+1+arraySize)%arraySize;//increase head index by one and then store the integer.
		 *(array+mHead)=obj;
		 count++;
   }
}


void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
	if(count==0){ //insert at start of array
		*array=obj;
		mHead=0;
		mTail=0; //make head and tail both point to the same int object.
		count++;
	}

	else {

		if(count==arraySize){
   		   doubleArraySize(); //double the array size
		}

		mTail= (mTail-1+arraySize)%arraySize; //decrease tail index by one and then store the integer. 
		*(array+mTail)=obj;
		count++;
	}
}


int Dynamic_deque_as_array::dequeue_head() {
	
	if(count==0){
		throw underflow(); //not valid to dequeue empty array
	}

	int returnValue= *(array+mHead);//integer value you're returning
	
	mHead=(mHead-1+arraySize)%arraySize;//decrease head index by one after storing return value
	count--;
	return returnValue;
}

int Dynamic_deque_as_array::dequeue_tail() {
	
	if(count==0){
		throw underflow(); //not valid to dequeue empty array
	}

	int returnValue= *(array+mTail);//integer value you're returning
	
	mTail=(mTail+1+arraySize)%arraySize;//increase tail index by one after storing return value
	count--;
	return returnValue;

}


void Dynamic_deque_as_array::clear() {
	mHead=0;
	mTail=0;
	count=0; //make head and tail point to the same location (which is the start of the array).
}

void  Dynamic_deque_as_array::doubleArraySize(){
	int newSize=arraySize*2;
	int * newArray= new int[newSize]; //make a new array which is double the size of the old array
	
	for(int i=0; i<arraySize; i++){
		*(newArray+i)= *(array+mTail); //store the values from the old array into the new array. Restore by dequeuing from tail all the way till head.
		mTail=(mTail+1)%arraySize;
	}
	delete [] array; //delete the old array
	
	array=newArray;//make array pointer point to the new array
	arraySize=newSize; 
	
	mTail=0; //already ordered from tail to head in new array. Therefore, tail will be at zero index.
    mHead=count-1;//head will contain the value of the top most integer index.
}