#pragma once
#include "message.cpp"
#include <map>
#include <algorithm>
#include <iostream>

class General {
    public:
        int id;
        bool isTraitor;
        std::map<char,int> receivedInfo;
    
        General(int id, bool isTraitor){
            this->id = id;
            this->isTraitor = isTraitor;
            receivedInfo.insert(std::pair<char,int>('r',0));
            receivedInfo.insert(std::pair<char,int>('a',0));
        }
        int getId() {
            return id;
        }
        bool getIsTraitor() {

            return this->isTraitor;
        }
        Message* createMessage(int toId, char value){
            return new Message(id, toId, value);
        }
        Message* createSecundaryMessage(int toId){
            if(isTraitor){
                return createMessage( toId, ((receivedInfo['r']==1) ? 'a' : 'r'));
            } 
            else {
                return createMessage( toId, ((receivedInfo['r']==1) ? 'r' : 'a'));
            }
            
        }
        void receiveMessage(Message* m){
            receivedInfo[m->getContent()]++;
        }
        char getAction(){
            std::cout<< receivedInfo['r'] << "  " << receivedInfo['a'] <<std::endl;
            if (isTraitor) {
                return 'r';
            }
            else {
                // std::pair<char,int> pr = std::max_element(  receivedInfo.begin(), 
                //                                             receivedInfo.end(),
                //                                             [] (const std::pair<char,int> & p1, const std::pair<char,int> & p2) {
                //                                                 return p1.second < p2.second;
                //                                             }
                //                                         );

                return (receivedInfo['r']>=receivedInfo['a']) ? 'r' : 'a';
            }
        }

};