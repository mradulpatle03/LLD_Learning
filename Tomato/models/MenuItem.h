#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include<bits/stdc++.h>
using namespace std;

class MenuItem{
    private:
        string name;
        string code;
        int price;
    public:
        MenuItem(const string& code,const string& name, int price){
            this->name = name;
            this->code = code;
            this->price = price;            
        }

        string getName() const {
            return name;
        }

        string getCode() const{
            return code;
        }

        int getPrice() const {
            return price;
        }
        void setName(const string& name){
            this->name = name;
        }

        void setCode(const string &code){
            this->code = code;
        }
        void setPrice(int price){
            this->price = price;
        }
};

#endif