#pragma once
#include "general.cpp"
#include "function.cpp"
#include <iostream>


int main(){
    int numberOfIterations=1, numberOfLoyals=15, numberOfTraitors=7;
    bool isComanderTraitor=true;
    std::map<char,int> results = simulate(numberOfIterations, numberOfLoyals, numberOfTraitors, isComanderTraitor );
    std::cout << "The commander is " << (isComanderTraitor ? "a traitor " : "not a traitor ")<< "and the results were on average: "<<std::endl;
    std::cout << "Loyals that attacked: " << ((double) results['a'])/numberOfIterations <<std::endl;
    std::cout << "Loyals that retreated: " <<( (double) results['r'])/numberOfIterations<<std::endl;
    return 0;

}
