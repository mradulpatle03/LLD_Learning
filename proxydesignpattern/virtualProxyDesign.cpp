#include<bits/stdc++.h>
using namespace std;

class IImage{
    public:
        virtual void display()=0;
};

class RealImage:public IImage{
    string filename;
    public:
        RealImage(string filename){
            this->filename=filename;
            loadFromDisk();
        }
        void loadFromDisk(){
            cout<<"Loading "<<filename<<endl;
        }
        void display() override {
            cout<<"Displaying "<<filename<<endl;
        }
};

class ProxyImage:public IImage{
    string filename;
    RealImage* realImage;
    public:
        ProxyImage(string filename){
            this->filename=filename;
            realImage=nullptr;
        }
        void display() override {
            if(realImage==nullptr){
                realImage=new RealImage(filename);
            }
            realImage->display();
        }
};

int main(){
    ProxyImage* image=new ProxyImage("test_image.jpg");
    // Image will be loaded from disk
    image->display();
    // Image will not be loaded from disk
    image->display();
    delete image;
    return 0;
}
