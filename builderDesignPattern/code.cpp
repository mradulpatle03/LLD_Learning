#include <iostream>
using namespace std;

//  PRODUCT

class House {
public:
    int doors = 0;
    int windows = 0;
    bool garage = false;

    void show() {
        cout << "Doors: " << doors << endl;
        cout << "Windows: " << windows << endl;
        cout << "Garage: " << (garage ? "Yes" : "No") << endl;
        cout << endl;
    }
};

//  1. CLASSIC BUILDER

class SimpleHouseBuilder {
private:
    House house;

public:
    SimpleHouseBuilder& setDoors(int d) {
        house.doors = d;
        return *this;
    }

    SimpleHouseBuilder& setWindows(int w) {
        house.windows = w;
        return *this;
    }

    SimpleHouseBuilder& setGarage(bool g) {
        house.garage = g;
        return *this;
    }

    House build() {
        return house;
    }
};

// 2. BUILDER WITH DIRECTOR


class Builder {
public:
    virtual void buildDoors() = 0;
    virtual void buildWindows() = 0;
    virtual void buildGarage() = 0;
    virtual House getHouse() = 0;
};

class ConcreteBuilder : public Builder {
private:
    House house;

public:
    void buildDoors() {
        house.doors = 4;
    }

    void buildWindows() {
        house.windows = 6;
    }

    void buildGarage() {
        house.garage = true;
    }

    House getHouse() {
        return house;
    }
};

class Director {
private:
    Builder* builder;

public:
    Director(Builder* b) {
        builder = b;
    }

    House construct() {
        builder->buildDoors();
        builder->buildWindows();
        builder->buildGarage();
        return builder->getHouse();
    }
};


// 3. STEP BUILDER


class StepHouse {
public:
    int doors;
    int windows;
    bool garage;

    void show() {
        cout << "Step Builder House\n";
        cout << "Doors: " << doors << endl;
        cout << "Windows: " << windows << endl;
        cout << "Garage: " << (garage ? "Yes" : "No") << endl;
    }
};

class WindowStep;
class GarageStep;

class DoorStep {
public:
    virtual WindowStep* setDoors(int) = 0;
};

class WindowStep {
public:
    virtual GarageStep* setWindows(int) = 0;
};

class GarageStep {
public:
    virtual StepHouse build() = 0;
    virtual GarageStep* setGarage(bool) = 0;
};

class StepHouseBuilder : public DoorStep, public WindowStep, public GarageStep {

private:
    StepHouse house;

public:

    static DoorStep* create() {
        return new StepHouseBuilder();
    }

    WindowStep* setDoors(int d) {
        house.doors = d;
        return this;
    }

    GarageStep* setWindows(int w) {
        house.windows = w;
        return this;
    }

    GarageStep* setGarage(bool g) {
        house.garage = g;
        return this;
    }

    StepHouse build() {
        return house;
    }
};

// MAIN


int main() {

    cout << "Classic Builder Pattern\n";

    House h1 = SimpleHouseBuilder()
        .setDoors(2)
        .setWindows(4)
        .setGarage(true)
        .build();

    h1.show();


    cout << "Builder with Director\n";

    ConcreteBuilder builder;
    Director director(&builder);

    House h2 = director.construct();

    h2.show();


    cout << "Step Builder Pattern\n";

    StepHouse h3 = StepHouseBuilder::create()
        ->setDoors(3)
        ->setWindows(5)
        ->setGarage(true)
        ->build();

    h3.show();

}