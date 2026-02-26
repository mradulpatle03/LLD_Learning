#include<bits/stdc++.h>
using namespace std;

class Engine{
    public:
    virtual void start()=0;
}; 

class Car{
    public:
    Engine* engine;
    Car(Engine* eng){
        engine=eng;
    }
    virtual void drive()=0;
};

class PetrolEngine: public Engine{
    public:
    void start(){
        cout<<"Petrol Engine Started"<<endl;
    }
};
class DieselEngine: public Engine{
    public:
    void start(){
        cout<<"Diesel Engine Started"<<endl;
    }
};  

class SportsCar: public Car{
    public:
    SportsCar(Engine* eng): Car(eng){}
    void drive(){
        engine->start();
        cout<<"Sports Car is driving"<<endl;
    }
};

class SUV: public Car{
    public:
    SUV(Engine* eng): Car(eng){}
    void drive(){
        engine->start();
        cout<<"SUV is driving"<<endl;
    }
};

int main(){
    Engine* petrolEngine = new PetrolEngine();
    Engine* dieselEngine = new DieselEngine();

    Car* sportsCar = new SportsCar(petrolEngine);
    Car* suv = new SUV(dieselEngine);

    sportsCar->drive();
    suv->drive();

    delete petrolEngine;
    delete dieselEngine;
    delete sportsCar;
    delete suv;

    return 0;
}