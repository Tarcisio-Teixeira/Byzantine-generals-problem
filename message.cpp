#pragma once
#include <vector>


class Message {
    private:
        int id;
        char content;
        int fromId;
        int toId;
    public:
        Message( int fromId, int toId, char content){
            // this->id = id;
            this->fromId = fromId;
            this->toId = toId;
            this->content = content;
        }
        int getId() const{
            return id;
        }
        char getContent(){
            return content;
        }
        int getFromId(){
            return fromId;
        }
        int getToId(){
            return toId;
        }

};

