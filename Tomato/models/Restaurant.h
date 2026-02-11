#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<bits/stdc++.h>
#include "MenuItem.h"
using namespace std;

class Restaurant {
    private:
        static int idCounter;
        int id; 
        string name;
        string location;
        vector<MenuItem> menuItems;
    public:
        Restaurant(const string name,const string& location) {
            this->name = name;
            this->location = location;
            this->id = ++idCounter;
        }


        string getName() const {
            return name;
        }

        void setName(const string& name) {
            this->name = name;
        }

        string getLocation() const {
            return location;
        }

        void setLocation(const string& location) {
            this->location = location;
        }

        const vector<MenuItem>& getMenuItems() const {
            return menuItems;
        }

        void addMenuItem(const MenuItem& menuItem) {
            menuItems.push_back(menuItem);
        }

        ~Restaurant() {
            // Destructor logic if needed
            cout << "Destructor called for Restaurant " << name << endl;
            menuItems.clear();
        }
};      

int Restaurant::idCounter = 0;

#endif