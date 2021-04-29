#pragma once
#include "message.cpp"
#include "general.cpp"

class MessageBuffer {
    private:
        std::vector<Message*> messages;
        std::vector<General*> generals;
        int numMessages;
    public:
        MessageBuffer(std::vector<General*> generals){
            this->generals =generals;
            numMessages = 0;
        }
        void addMessage(Message* m){
            messages.push_back(m);
        }
        void sendMessage(Message* m){
            int toId = m->getToId();
            generals[toId]->receiveMessage(m);
        }
        void sendAllMessages(){
            for (std::vector<Message*>::iterator it = messages.begin(); it != messages.end(); ++it){
                sendMessage(*it);
            }
            messages.clear();
        }
};