#include<bits/stdc++.h>
using namespace std;

class Product{
    private:
        int sku;
        string name;
        double price;
    public:
        Product(int s, string n, double p){
            sku = s;
            name = n;
            price = p;
        }
        int getSku(){
            return sku;
        }
        string getName(){
            return name;
        }
        double getPrice(){
            return price;
        }
};

class Productfactory{
    
    public:
        static Product* createProduct(int sku){
            //create a product
            string name;
            double price;
            if(sku == 1){
                name = "Product A";
                price = 10.0;
            }
            else if(sku == 2){
                name = "Product B";
                price = 20.0;
            }
            else{
                name = "Product C";
                price = 30.0;
            }
            return new Product(sku, name, price);
        }
};

class InventoryStore{
    public:
        virtual void addProduct(Product* product,int quantity) = 0;
        virtual void removeProduct(int sku,int quantity) = 0;
        virtual int checkStock(int sku) = 0;
        virtual vector<Product*> getProducts() = 0;
};

class DBInventoryStore: public InventoryStore{
    private:
        map<int,int> stock;
        map<int,Product*> products;
    public:
        void addProduct(Product* product,int quantity){
            int sku = product->getSku();
            stock[sku] += quantity;
            products[sku] = product;
        }
        void removeProduct(int sku,int quantity){
            if(stock.find(sku) == stock.end()) return;
            stock[sku] -= quantity;
            if(stock[sku] <= 0){
                stock.erase(sku);
                products.erase(sku);
            }
        }
        int checkStock(int sku){
            if(stock.find(sku) != stock.end()){
                return stock[sku];
            }
            return 0;
        }
        vector<Product*> getProducts(){
            vector<Product*> result;
            for(auto it = products.begin(); it != products.end(); it++){
                if(stock[it->first] > 0){
                    result.push_back(it->second);
                }
            }
            return result;
        }
};

class InventoryManager{
    private:
        InventoryStore* store;
    public:
        InventoryManager(InventoryStore* s){
            store = s;
        }
        void addStock(int sku,int quantity){
            Product* product =Productfactory::createProduct(sku);
            store->addProduct(product,quantity);
        }

        void removeStock(int sku,int quantity){
            store->removeProduct(sku,quantity);
        }

        int checkStock(int sku){
            return store->checkStock(sku);
        }
        vector<Product*> getProducts(){
            return store->getProducts();
        }
};

class ReplenishmentSystem{
    public:
        virtual void replenish(InventoryManager* manager, map<int,int> stockToReplenish)=0;
};

class ThresholdReplenishmentSystem: public ReplenishmentSystem{
    private:
        int threshold;
    public:
        ThresholdReplenishmentSystem(int t){
            threshold = t;
        }
        void replenish(InventoryManager* manager, map<int,int> stockToReplenish){
            for(auto it = stockToReplenish.begin(); it != stockToReplenish.end(); it++){
                int sku = it->first;
                int quantity = it->second;
                if(manager->checkStock(sku) < threshold){
                    manager->addStock(sku,quantity);
                }
            }
            cout<<"Replenishment completed based on threshold."<<endl;
        }
};

class WeeklyReplenishmentSystem: public ReplenishmentSystem{
    public:
        void replenish(InventoryManager* manager, map<int,int> stockToReplenish){
            cout<<"Replenishment completed weekly."<<endl;
        }
};

class DarkStore{
    private:
        string name;
        double x,y;
        InventoryManager* manager;
        ReplenishmentSystem* replenishmentSystem;
    public:
        DarkStore(string n, double x, double y){
            name = n;
            this->x = x;
            this->y = y;
            manager = new InventoryManager(new DBInventoryStore());
        }

        void addStock(int sku,int quantity){
            manager->addStock(sku,quantity);
        }
        void removeStock(int sku,int quantity){
            manager->removeStock(sku,quantity);
        }
        int checkStock(int sku){
            return manager->checkStock(sku);
        }
        vector<Product*> getProducts(){
            return manager->getProducts();
        }
        void setReplenishmentSystem(ReplenishmentSystem* rs){
            replenishmentSystem = rs;
        }
        void replenishStock(map<int,int> stockToReplenish){
            if(replenishmentSystem != NULL){
                replenishmentSystem->replenish(manager,stockToReplenish);
            }
        }
        double getDistance(double x1, double y1){
            return sqrt((x1-x)*(x1-x) + (y1-y)*(y1-y));
        }
        string getName(){
            return name;
        }
        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        InventoryManager* getManager(){
            return manager;
        }
};

int main(){
    return 0;
}