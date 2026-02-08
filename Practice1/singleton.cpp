#include<bits/stdc++.h>
using namespace std;

class Singleton{
private:
    static Singleton* inst;
    static mutex mt;
    Singleton(){
        cout<<"Singleton instance created"<<endl;
    }
public: 
    static Singleton* getInstance(){
        if(inst==nullptr){
            lock_guard<mutex> lock(mt);
            if(inst==nullptr){
                inst=new Singleton();
            }
        }
        return inst;
    }
};
Singleton* Singleton::inst=nullptr;
mutex Singleton::mt;

int main(){
    Singleton* s1=Singleton::getInstance();
    Singleton* s2=Singleton::getInstance();
    cout<<(s1==s2)<<endl;
    return 0;
}