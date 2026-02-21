#include<bits/stdc++.h>
using namespace std;

class IDocumentReader{
    public:
        virtual void read(string path,string pass)=0;
};

class DocumentReader:public IDocumentReader{
    public:
        void read(string path,string pass) override {
            cout<<"Reading document from "<<path<<" with password "<<pass<<endl;
        }
};

class User{
    string username;
    string password;
    public:
        User(string username,string password){
            this->username=username;
            this->password=password;
        }
        string getUsername(){
            return username;
        }
        string getPassword(){
            return password;
        }
};

class DocumentReaderProxy:public IDocumentReader{
    DocumentReader* documentReader;
    User* user;
    public:
        DocumentReaderProxy(User* user){
            this->user=user;
            documentReader=new DocumentReader();
        }
        void read(string path,string pass) override {
            if(user->getPassword()==pass){
                documentReader->read(path,pass);
            }else{
                cout<<"Access denied for user "<<user->getUsername()<<endl;
            }
        }
};

int main(){
    User* user=new User("mradul","1234");
    IDocumentReader* documentReader=new DocumentReaderProxy(user);
    documentReader->read("document.txt","1234");
    return 0;
}