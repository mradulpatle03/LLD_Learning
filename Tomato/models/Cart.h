#ifndef CART_H
#define CART_H

#include<bits/stdc++.h>
#include "MenuItem.h"
#include "Restaurant.h"
using namespace std;

class Cart{
    private:
        vector<MenuItem> items;
        Restaurant* restaurant;
    public:
        Cart(){
            restaurant = nullptr;
        }
        void setRestaurant(Restaurant* restaurant){
            this->restaurant = restaurant;
        }

        Restaurant* getRestaurant() const {
            return restaurant;
        }
        void addItem(const MenuItem& item){
            if(restaurant == nullptr){
                cout<<"Please set the restaurant first"<<endl;
                return;
            }
            items.push_back(item);
        }
        double getTotalPrice() const {
            double total = 0.0;
            for(auto item: items){
                total += item.getPrice();
            }
            return total;
        }

        bool isEmpty(){
            return  ( restaurant == nullptr || items.empty());
        }

        void clearCart(){
            items.clear();
            restaurant = nullptr;
        }
    
        const vector<MenuItem>& getItems() const {
            return items;
        }
};

#endif