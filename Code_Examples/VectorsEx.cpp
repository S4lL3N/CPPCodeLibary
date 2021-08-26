#include <iostream>
#include "VectorsEx.h"
#include <vector>

//you must use c++ 11 when compling to use vectors. ie: g++ vectorsEx.cpp -std=c++11

 void VectorsEx::loadVector(){
     //prompt user for input
     std::cout<<"How many numbers would you like to add to the vector? \n"<<std::endl;
    
    //take user input for vector size
     int vectorSize;
     std::cin>>vectorSize;
    
    // creating a vector or a dynamic list.
     std::vector<int> data;

    //temp storage for user input.
    int tempData;

    std::cout<<"the vectorSize vari = " << vectorSize;

    //loop through user input and add to the vector.
    for(int i = 0; i < vectorSize; i++){
        std::cout<<"\nenter number " << i + 1 << ": ";
        std::cin>> tempData;
        data.push_back(tempData);
    }

    printVector(data);


 }

void VectorsEx::printVector(std::vector<int> data){
    std::cout<<"\nPrinting vector contents....\n";
    for(int i = 0; i < data.size(); i++){
        std::cout<<"\nvector index "<< i << ":" << data[i];
    }
}



