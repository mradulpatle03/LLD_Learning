#include<bits/stdc++.h>
using namespace std;

class VendingMachine;

class VendingState{
    public:
        virtual VendingState* insertCoin(VendingMachine* machine, int coin) = 0;
        virtual VendingState* selectItem(VendingMachine* machine) = 0;
        virtual VendingState* dispense(VendingMachine* machine) = 0;
        virtual VendingState* returnCoin(VendingMachine* machine) = 0;
        virtual VendingState* refill(VendingMachine* machine, int quantity) = 0;
        virtual string getStateName() = 0;
};

class VendingMachine{
    private:
        VendingState* currState;
        int quantity;
        int price;
        int totalCoins;

        VendingState* noCoinState;
        VendingState* hasCoinState;
        VendingState* dispenseState;
        VendingState* soldOutState;

    public:
        VendingMachine(int quantity, int price);

        void insertCoin(int coin);
        void selectItem();
        void dispense();
        void returnCoin();
        void refill(int quantity);

        void display();

        VendingState* getNoCoinState(){
            return noCoinState;
        }
        VendingState* getHasCoinState(){
            return hasCoinState;
        }
        VendingState* getDispenseState(){
            return dispenseState;
        }
        VendingState* getSoldOutState(){
            return soldOutState;
        }

        VendingState* getCurrentState(){
            return currState;
        }
        void setCurrentState(VendingState* state){
            currState = state;
        }
        int getQuantity(){
            return quantity;
        }
        void decrementQuantity(int q=1){
            quantity-=q;
        }
        void incrementQuantity(int q=1){
            quantity+=q;
        }
        int getPrice(){
            return price;
        }
        int getTotalCoins(){
            return totalCoins;
        }
        void setTotalCoins(int coins){
            totalCoins = coins;
        }
        void addTotalCoins(int coins){
            totalCoins += coins;
        }
        void setQuantity(int quantity){
            this->quantity = quantity;
        }
        void setPrice(int price){
            this->price = price;
        }
};

class NoCoinState : public VendingState{
    public:
        VendingState* insertCoin(VendingMachine* machine, int coin){
            machine->addTotalCoins(coin);
            cout<<"Please select an item."<<endl;
            return machine->getHasCoinState();
        }
        VendingState* selectItem(VendingMachine* machine){
            cout<<"Please insert a coin first."<<endl;
            return machine->getNoCoinState();
        }
        VendingState* dispense(VendingMachine* machine){
            cout<<"Please insert a coin first."<<endl;
            return machine->getNoCoinState();
        }
        VendingState* returnCoin(VendingMachine* machine){
            cout<<"Please insert a coin first."<<endl;
            return machine->getNoCoinState();
        }
        VendingState* refill(VendingMachine* machine, int quantity){
            cout<<"Inserting items."<<endl;
            machine->incrementQuantity(quantity);
            return machine->getNoCoinState();
        }

        string getStateName(){
            return "No_Coin";
        }
};

class HasCoinState : public VendingState{
    public:
        VendingState* insertCoin(VendingMachine* machine, int coin){
            machine->addTotalCoins(coin);
            cout<<"Please select an item."<<endl;
            return machine->getHasCoinState();
        }
        VendingState* selectItem(VendingMachine* machine){
            if(machine->getTotalCoins() < machine->getPrice()){
                cout<<"Please insert more coins."<<endl;
                return machine->getHasCoinState();
            }
            int change = machine->getTotalCoins() - machine->getPrice();
            machine->setTotalCoins(change);
            machine->decrementQuantity();
            return machine->getDispenseState();
        }
        VendingState* dispense(VendingMachine* machine){
            cout<<"Please select an item first."<<endl;
            return machine->getHasCoinState();
        }
        VendingState* returnCoin(VendingMachine* machine){
            cout<<"Returning coin."<< machine->getTotalCoins()<<endl;
            machine->setTotalCoins(0);
            return machine->getNoCoinState();
        }
        VendingState* refill(VendingMachine* machine, int quantity){
            cout<<"Inserting items."<<endl;
            machine->incrementQuantity(quantity);
            return machine->getHasCoinState();
        }

        string getStateName(){
            return "Has_Coin";
        }
};

class DispenseState : public VendingState{
    public:
        VendingState* insertCoin(VendingMachine* machine, int coin){
            cout<<"Please wait for the item to be dispensed."<<endl;
            return machine->getDispenseState();
        }
        VendingState* selectItem(VendingMachine* machine){
            cout<<"Please wait for the item to be dispensed."<<endl;
            return machine->getDispenseState();
        }
        VendingState* dispense(VendingMachine* machine){
            cout<<"Dispensing item."<<endl;
            machine->decrementQuantity();
            if(machine->getQuantity() == 0){
                return machine->getSoldOutState();
            }
            return machine->getNoCoinState();
        }
        VendingState* returnCoin(VendingMachine* machine){
            cout<<"Please wait for the item to be dispensed."<<endl;
            return machine->getDispenseState();
        }
        VendingState* refill(VendingMachine* machine, int quantity){
            cout<<"Please wait for the item to be dispensed."<<endl;
            return machine->getDispenseState();
        }

        string getStateName(){
            return "Dispense";
        }
};

class SoldOutState : public VendingState{
    public:
        VendingState* insertCoin(VendingMachine* machine, int coin){
            cout<<"Machine is sold out."<<endl;
            return machine->getSoldOutState();
        }
        VendingState* selectItem(VendingMachine* machine){
            cout<<"Machine is sold out."<<endl;
            return machine->getSoldOutState();
        }
        VendingState* dispense(VendingMachine* machine){
            cout<<"Machine is sold out."<<endl;
            return machine->getSoldOutState();
        }
        VendingState* returnCoin(VendingMachine* machine){
            cout<<"Machine is sold out."<<endl;
            return machine->getSoldOutState();
        }
        VendingState* refill(VendingMachine* machine, int quantity){
            cout<<"Refilling..."<<endl;
            machine->setQuantity(quantity);
            return machine->getNoCoinState();
        }

        string getStateName(){
            return "Sold_Out";
        }
};

VendingMachine::VendingMachine(int quantity, int price){
    this->quantity = quantity;
    this->price = price;
    this->totalCoins = 0;

    this->noCoinState = new NoCoinState();
    this->hasCoinState = new HasCoinState();
    this->dispenseState = new DispenseState();
    this->soldOutState = new SoldOutState();

    this->currState = noCoinState;

    cout<<"Vending machine created."<<endl;
}


void VendingMachine::insertCoin(int coin){
    this->currState = this->currState->insertCoin(this, coin);
}

void VendingMachine::selectItem(){
    this->currState = this->currState->selectItem(this);
}

void VendingMachine::dispense(){
    this->currState = this->currState->dispense(this);
}

void VendingMachine::returnCoin(){
    this->currState = this->currState->returnCoin(this);
}

void VendingMachine::refill(int quantity){
    this->currState = this->currState->refill(this, quantity);
}

void VendingMachine::display(){
    cout<<"Quantity: "<<this->quantity<<endl;
    cout<<"Price: "<<this->price<<endl;
    cout<<"Total Coins: "<<this->totalCoins<<endl;
    cout<<"Current State: "<<this->currState->getStateName()<<endl;
}

int main(){

    VendingMachine* machine = new VendingMachine(5, 10);
    machine->display();
    machine->insertCoin(10);
    machine->selectItem();
    machine->dispense();
    machine->returnCoin();
    machine->refill(10);
    machine->display();
}