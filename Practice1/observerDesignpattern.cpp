#include<bits/stdc++.h>
using namespace std;    

class Iobserver{
public:
    virtual void update() = 0;
    virtual ~Iobserver(){};
};
class Iobservable{
public:
    virtual void subscribe(Iobserver* observer) = 0;
    virtual void unsubscribe(Iobserver* observer) = 0;
    virtual void notify() = 0;
    virtual ~Iobservable(){};
};

class ConcreteObservable : public Iobservable{
private:
    vector<Iobserver*> observers; // list of subscribed observers
    string name;
    string newVideo;
public:
    ConcreteObservable(string name){
        this->name = name;
    }
    void subscribe(Iobserver* observer) override{
        if (find(observers.begin(), observers.end(), observer) == observers.end()) {
            observers.push_back(observer);
        }
    }
    void unsubscribe(Iobserver* observer) override{
        auto it = find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }
    void notify() override{
        for( Iobserver* observer : observers){
            observer->update();
        }
    }

    void uploadVideo(string videoName){
        newVideo = videoName;
        cout << "New video uploaded: " << newVideo << endl;
        notify();
    }

    string getData(){
        return newVideo;
    }

};

class ConcreteObserver : public Iobserver{
private:
    string name;
    ConcreteObservable* observable;
public:
    ConcreteObserver(string name, ConcreteObservable* observable){
        this->name = name;
        this->observable = observable;
    }

    void update() override{
        cout << "Observer " << name << " is notified" << endl;
    }
};

int main(){
    ConcreteObservable* observable = new ConcreteObservable("Youtube");
    ConcreteObserver* observer1 = new ConcreteObserver("Observer 1", observable);
    ConcreteObserver* observer2 = new ConcreteObserver("Observer 2", observable);
    observable->subscribe(observer1);
    observable->subscribe(observer2);
    observable->uploadVideo("Video 1");
    observable->unsubscribe(observer1);
    observable->uploadVideo("Video 2");
    return 0;
}