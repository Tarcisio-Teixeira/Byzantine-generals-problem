#pragma once
#include "messagebuffer.cpp"
#include "general.cpp"
#include "message.cpp"
#include <iostream>


int main(){
    int numberOfLoyals=6;
    int numberOfTraitors=6;
    std::vector<General*> generals;
    std::vector<Message*> messages;
    bool isComanderTraitor=false;
    char command = 'a';
    General* comander = new General(0,isComanderTraitor);
    generals.push_back(comander);
    for (int i=1; i<numberOfLoyals+1; ++i){
        General* g = new General(i,false);
        generals.push_back(g);
    }
    for (int i=numberOfLoyals+1; i<numberOfLoyals+numberOfTraitors+1; ++i){
        General* g = new General(i,true);
        generals.push_back(g);
    }
    MessageBuffer* mBuffer = new MessageBuffer(generals);

    for (int i = 1;  i<numberOfLoyals+numberOfTraitors+1; ++i){
        mBuffer->addMessage(comander->createMessage(i,command));
    }
    mBuffer->sendAllMessages();
    for (int j = 1;  j<numberOfLoyals+numberOfTraitors+1; ++j){
        for (int i = 1;  i<numberOfLoyals+numberOfTraitors+1; ++i){
            if (i!=j){
                mBuffer->addMessage(generals[j]->createSecundaryMessage(i));
            }
            
        }
        
    }
    mBuffer->sendAllMessages();

    std::map<char,int> results;
    results.insert(std::pair<char,int>('r',0));
    results.insert(std::pair<char,int>('a',0));
    for (int i = 1;  i<numberOfLoyals+numberOfTraitors+1; ++i){
        if (!(generals[i]->getIsTraitor())) {
            results[generals[i]->getAction()]++;
        }
    }

    std::cout << "The commander is " << (isComanderTraitor ? "a traitor " : "not a traitor ");
    std::cout << "and asked the generals to "<< ((command=='a')? "attack" : "retreat") << " and the results was: "<< std::endl;
    std::cout << "Loyals that attacked: " << results['a']<<std::endl;
    std::cout << "Loyals that retrieved: " << results['r']<<std::endl;
    return 0;

}
