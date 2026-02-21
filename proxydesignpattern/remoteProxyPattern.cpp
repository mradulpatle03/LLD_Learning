#include<bits/stdc++.h>
using namespace std;

class IDatabase{
    public:
        virtual void query(string sql)=0;
};

class Database:public IDatabase{
    public:
        Database(){
            cout<<"Database::Database constructor"<<endl;
        }
        void query(string sql){
            cout<<"Database::query"<<endl;
        }
};

class DatabaseProxy:public IDatabase{
    Database* database;
    public:
        DatabaseProxy(){
            database=new Database();
        }
        void query(string sql) override {
            cout<<"DatabaseProxy::query"<<endl;
            database->query(sql);
        }
};

int main(){
    DatabaseProxy databaseProxy;
    databaseProxy.query("SELECT * FROM users");
    return 0;
}