#include <bits/stdc++.h>
using namespace std;

class Prototype
{
public:
    virtual Prototype *clone() = 0;
    virtual ~Prototype() {}
};

class ConcretePrototype : public Prototype
{
public:
    string name;
    int health;
    int attack;
    int defense;
    ConcretePrototype(string name, int health, int attack, int defense)
    {
        // let this be a expensive creation
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        cout << "Creating " << name << endl;
    }
    ConcretePrototype(const ConcretePrototype &other)
    {
        name = other.name;
        health = other.health;
        attack = other.attack;
        defense = other.defense;
        cout << "Cloning done" << endl;
    }
    Prototype *clone()
    {
        return new ConcretePrototype(*this);
    }

    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "Defense: " << defense << endl;
    }

    // setters for attributes which can be changed after creation
    void setName(string name)
    {
        this->name = name;
    }
    void setHealth(int health)
    {
        this->health = health;
    }
    void setAttack(int attack)
    {
        this->attack = attack;
    }
    void setDefense(int defense)
    {
        this->defense = defense;
    }
};

int main()
{

    ConcretePrototype *hero = new ConcretePrototype("Hero", 100, 10, 5);
    hero->display();
    // type casting is necessary because clone() returns a pointer to the base class
    ConcretePrototype *hero2 = dynamic_cast<ConcretePrototype *>(hero->clone());
    hero2->setName("Hero 2");
    hero2->setHealth(200);
    hero2->display();
    return 0;
}