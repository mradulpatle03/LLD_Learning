#include<bits/stdc++.h>
using namespace std;

class Memento{
    private:
        unordered_map<int,int> mpp;
    public:
        Memento(unordered_map<int,int> mpp){
            this->mpp = mpp;
        }
        // setter
        void setMemento(unordered_map<int,int> mpp){
            this->mpp = mpp;
        }
        // getter
        unordered_map<int,int> getMemento(){
            return mpp;
        }
};  

class Database{
    private:
        unordered_map<int,int> mpp;
    public:
        void insert(int key,int value){
            mpp[key] = value;
            cout<<"key: "<<key<<" value: "<<value <<" inserted"<<endl;
        }
        void deleteKey(int key){
            if(mpp.find(key)!=mpp.end()){
                mpp.erase(key);
                cout<<"key: "<<key<<" deleted"<<endl;
            }
            else{
                cout<<"key: "<<key<<" not found"<<endl;
            }
        }
        void update(int key,int value){
            if(mpp.find(key)!=mpp.end()){
                mpp[key] = value;
                cout<<"key: "<<key<<" updated to value: "<<value<<endl;
            }
            else{
                cout<<"key: "<<key<<" not found"<<endl;
            }
        }

        Memento* createMemento(){
            Memento* memento = new Memento(mpp);
            cout<<"memento created"<<endl;
            return memento;
        }

        void restoreMemento(Memento* memento){
            mpp = memento->getMemento();
            cout<<"memento restored"<<endl;
        }
        void display(){
            cout<<"database: "<<endl;
            for(auto it:mpp){
                cout<<"key: "<<it.first<<" value: "<<it.second<<endl;
            }
        }
};

class CareTaker{
    private:
        vector<Memento*> mementos;
    public:
        void addMemento(Memento* memento){
            mementos.push_back(memento);
        }
        Memento* getMemento(){
            return mementos.back();
        }
};

int main(){

    Database* database = new Database();
    CareTaker* careTaker = new CareTaker();

    database->insert(1,10);
    database->insert(2,20);
    database->insert(3,30);
    
    database->display();

    careTaker->addMemento(database->createMemento());

    database->insert(4,40);
    database->insert(5,50);

    database->display();

    database->restoreMemento(careTaker->getMemento());

    database->display();
    return 0;
}