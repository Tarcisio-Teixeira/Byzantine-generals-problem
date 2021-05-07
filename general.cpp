#pragma once
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>

class General {
    public:
        int id;
        bool isTraitor;
    
        General(int id, bool isTraitor){
            this->id = id;
            this->isTraitor = isTraitor;
        }
        int getId() {
            return id;
        }
        bool getIsTraitor() {
            return this->isTraitor;
        }
        char decideMessage(char c){
            double u;
            if (isTraitor) {
                u =  ((double) rand() / (RAND_MAX));
                if (u<1./2.) return 'a';
                else if (u<3./3.) return 'r';
                else return 'n';
            }
            else return (c=='n') ? 'r' : c;

        }
        std::vector<char> generateMessages(int numOfLieutenants, char received){
            std::vector<char> res;
            for (int i=0; i<numOfLieutenants; ++i){
                res.push_back(decideMessage(received));
            }
            return res;
        }
        
};