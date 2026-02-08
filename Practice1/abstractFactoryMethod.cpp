#include<bits/stdc++.h>
using namespace std;

class Burger{
    public:
        virtual void prepare(string type)=0;
        virtual ~Burger(){};
};

class VegBurger:public Burger{
    public:
        void prepare(string type) override{
            cout<<"Preparing "<<type<<" Veg Burger"<<endl;
        }
};

class NonVegBurger:public Burger{
    public:
        void prepare(string type) override{
            cout<<"Preparing "<<type<<" Non-Veg Burger"<<endl;
        }
};

class Pizza{
    public:
        virtual void prepare(string type)=0;
        virtual ~Pizza(){};
};

class VegPizza:public Pizza{
    public:
        void prepare(string type) override{
            cout<<"Preparing "<<type<<" Veg Pizza"<<endl;
        }
};

class NonVegPizza:public Pizza{
    public:
        void prepare(string type) override{
            cout<<"Preparing "<<type<<" Non-Veg Pizza"<<endl;
        }
};

class AbstractFactory{
    public:
        virtual Burger* createBurger()=0;
        virtual Pizza* createPizza()=0;
        virtual ~AbstractFactory(){};
};

class VegFactory:public AbstractFactory{
    public:
        Burger* createBurger() override{
            return new VegBurger();
        }
        Pizza* createPizza() override{
            return new VegPizza();
        }
};

class NonVegFactory:public AbstractFactory{
    public:
        Burger* createBurger() override{
            return new NonVegBurger();
        }
        Pizza* createPizza() override{
            return new NonVegPizza();
        }
};



int main(){
    
    AbstractFactory* vegDhaba = new VegFactory();
    Burger* veggiBurger = vegDhaba->createBurger();
    Pizza* veggiPizza = vegDhaba->createPizza();

    veggiBurger->prepare("Veggi burger");
    veggiPizza->prepare("Veggi pizza");

    return 0;
}