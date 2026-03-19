#include<bits/stdc++.h>
using namespace std;

// mediator design pattern

class IColleague;

class IMediator{
    public:
        virtual void addColleague(IColleague*) = 0;
        virtual void notifyAll(string from,string msg) = 0;
        virtual void notify(string from, string to,string msg) = 0;
        virtual ~IMediator(){}
};

class IColleague{
    protected:
        IMediator* mediator;
    
    public:
        IColleague(IMediator* _mediator){
            mediator = _mediator;
            mediator->addColleague(this);
        }

        virtual ~IColleague(){}

        virtual string getName() = 0;
        virtual void sendMessageToAll(string msg) = 0;
        virtual void sendMessage(string to,string msg) = 0;
        virtual void receiveMessage(string from,string msg) = 0;
};

class User: public IColleague{
    private:
        string name;
    public:
        User(IMediator* _mediator, string _name) : IColleague(_mediator), name(_name){}
        string getName(){
            return name;
        }
        void sendMessageToAll(string msg){
            mediator->notifyAll(name,msg);
        }
        void sendMessage(string to,string msg){
            mediator->notify(name,to,msg);
        }
        void receiveMessage(string from,string msg){
            cout << "Message received from " << from << ": " << msg << endl;
        }
};

class ChatRoom : public IMediator{
    private:
        vector<IColleague*> users;
        vector<pair<string, string>> muted;
    public:
        void addColleague(IColleague* user){
            users.push_back(user);
        }

        void notifyAll(string from,string msg){
            for(auto user:users){
                if(user->getName() == from){
                    continue;
                }
                
                bool isMuted=false;

                for(auto mutedUser:muted){
                    if(mutedUser.first == from && mutedUser.second == user->getName()){
                        isMuted=true;
                        break;
                    }
                }

                if(!isMuted){
                    user->receiveMessage(from,msg);
                }
            }
        }

        void notify(string from,string to,string msg){
            // dont send if muted

            for(auto user:users){
                if(user->getName() == from){
                    continue;
                }
                
                if(user->getName() == to){
                    for(auto mutedUser:muted){
                        if(mutedUser.first == from && mutedUser.second == user->getName()){
                            continue;
                        }
                    }
                    user->receiveMessage(from,msg);
                    break;
                }
            }
        }

        void mute(string from, string to){
            muted.push_back({from,to});
        }
};

int main(){

    ChatRoom* chatRoom = new ChatRoom();
    User* user1 = new User(chatRoom,"user1");
    User* user2 = new User(chatRoom,"user2");
    User* user3 = new User(chatRoom,"user3");

    user1->sendMessageToAll("Hello everyone!");
    user2->sendMessageToAll("Hello everyone!");
    user3->sendMessageToAll("Hello everyone!");

    user1->sendMessage("user2","Hi user2!");
    user2->sendMessage("user1","Hi user1!");
    user1->sendMessage("user3","Hi user3!");
    return 0;
}