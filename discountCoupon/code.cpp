#include<bits/stdc++.h>
using namespace std;

class Product{
    private:
        string name;
        string category;
        double price;
    public:
        Product(string name, string category,double price){
            this->name = name;
            this->category = category;
            this->price = price;
        }
        string getName(){
            return name;
        }
        string getCategory(){
            return category;
        }
        double getPrice(){
            return price;
        }
};

class CartItem{
    private:
        Product* product;
        int quantity;
    public:
        CartItem(Product* product, int quantity){
            this->product = product;
            this->quantity = quantity;
        }
        double getTotalPrice(){
            return product->getPrice() * quantity;
        }
        Product* getProduct(){
            return product;
        }
        int getQuantity(){
            return quantity;
        }
};  

class Cart{
    private:
        vector<CartItem*> items;
        bool loyaltyMember;
        double initialTotal;
        double finalTotal;
        string paymentBank;
    public:
        Cart(){
            loyaltyMember = false;
            initialTotal = 0.0;
            finalTotal = 0.0;
            paymentBank = "";
        }

        void addItem(Product* product, int quantity){
            CartItem* item = new CartItem(product, quantity);
            items.push_back(item);
            initialTotal += item->getTotalPrice();
            finalTotal += item->getTotalPrice();
        }
        void applyDiscount(double amount){
            finalTotal -= amount;
            if(finalTotal < 0) finalTotal = 0;
        }

        void setLoyaltyMember(bool status){
            loyaltyMember = status;
        }
        bool isLoyaltyMember(){
            return loyaltyMember;
        }
        void setPaymentBank(string bank){
            paymentBank = bank;
        }
        string getPaymentBank(){
            return paymentBank;
        }
        double getInitialTotal(){
            return initialTotal;
        }
        double getFinalTotal(){
            return finalTotal;
        }
        vector<CartItem*> getItems(){
            return items;
        }
};

class DiscountStrategy{
    public:
        virtual double calculateDiscount(double total) = 0;
};

class PercentageDiscount : public DiscountStrategy{
    private:
        double percentage;
    public:
        PercentageDiscount(double percentage){
            this->percentage = percentage;
        }
        double calculateDiscount(double total){
            return total * (percentage / 100.0);
        }
};

class FlatDiscount : public DiscountStrategy{
    private:
        double amount;
    public:
        FlatDiscount(double amount){
            this->amount = amount;
        }
        double calculateDiscount(double total){
            int final = total-amount;
            if(final > 0) return final;
            return 0;
        }
};

class PercentageDiscountWithCap : public DiscountStrategy{
    private:
        double percentage;
        double cap;
    public:
        PercentageDiscountWithCap(double percentage, double cap){
            this->percentage = percentage;
            this->cap = cap;
        }
        double calculateDiscount(double total){
            double discount = total * (percentage / 100.0);
            return min(discount, cap);
        }
};

enum DiscountType{
    PERCENTAGE,
    FLAT,
    PERCENTAGE_WITH_CAP
};

class DiscountStrategyFactory{
    private:
        DiscountStrategyFactory() {}
        static DiscountStrategyFactory* instance;
    public:
        static DiscountStrategyFactory* getInstance(){
            if(instance == nullptr){
                instance = new DiscountStrategyFactory();
            }
            return instance;
        }
        DiscountStrategy* createDiscountStrategy(DiscountType type, double value, double cap = 0){
            switch(type){
                case DiscountType::PERCENTAGE:
                    return new PercentageDiscount(value);
                case DiscountType::FLAT:
                    return new FlatDiscount(value);
                case DiscountType::PERCENTAGE_WITH_CAP:
                    return new PercentageDiscountWithCap(value, cap);
                default:
                    return nullptr;
            }
        }
};

DiscountStrategyFactory* DiscountStrategyFactory::instance = nullptr;

class Coupon{
    private:
        Coupon* next;
    public:
        Coupon(){
            next = nullptr;
        }
        Coupon* getNext(){
            return next;
        }
        void setNext(Coupon* coupon){
            next = coupon;
        }

        virtual void applyDiscount(Cart* cart){
            if(isApplicable(cart)){
                double discountAmount = getDiscountAmount(cart);
                cart->applyDiscount(discountAmount);
                if(!isCombinable()){
                    return ;
                }
            }
            if(next != nullptr){
                next->applyDiscount(cart);
            }
        }

        virtual bool isApplicable(Cart* cart) = 0;
        virtual double getDiscountAmount(Cart* cart) = 0;
        virtual bool isCombinable() {
            return true;
        }
        virtual string name() = 0;
};

class SeasonalCoupon : public Coupon{
    private:
        double percent;
        string category;
        DiscountStrategy* discountStrategy;
    public:
        SeasonalCoupon(double percent, string category){
            this->percent = percent;
            this->category = category;
            this->discountStrategy = DiscountStrategyFactory::getInstance()->createDiscountStrategy(DiscountType::PERCENTAGE, percent);
        }
        bool isApplicable(Cart* cart){
            for(CartItem* item : cart->getItems()){
                if(item->getProduct()->getCategory() == category){
                    return true;
                }
            }
            return false;
        }
        double getDiscountAmount(Cart* cart){
            double total = 0;
            for(CartItem* item : cart->getItems()){
                if(item->getProduct()->getCategory() == category){
                    total += item->getTotalPrice();
                }
            }
            return discountStrategy->calculateDiscount(total);
        }
        bool isCombinable(){
            return true;
        }
        string name(){
            return "Seasonal Offer " + to_string((int)percent) + " % off " + category;
        }
};

class loyaltyCoupon : public Coupon{
    private:
        double percent;
        DiscountStrategy* discountStrategy;
    public:
        loyaltyCoupon(double percent){
            this->percent = percent;
            this->discountStrategy = DiscountStrategyFactory::getInstance()->createDiscountStrategy(DiscountType::PERCENTAGE, percent);
        }
        bool isApplicable(Cart* cart){
            return cart->isLoyaltyMember();
        }
        double getDiscountAmount(Cart* cart){
            return discountStrategy->calculateDiscount(cart->getFinalTotal());
        }
        string name(){
            return "Loyalty Discount " + to_string((int)percent) + "% off";
        }
};

class BulkCoupon : public Coupon{
    private:
        double threshold;
        double amount;
        DiscountStrategy* discountStrategy;
    public:
        BulkCoupon(double threshold,double amount){
            this->threshold = threshold;
            this->amount = amount;
            this->discountStrategy = DiscountStrategyFactory::getInstance()->createDiscountStrategy(DiscountType::FLAT, amount);
        }
        bool isApplicable(Cart* cart){
            return cart->getFinalTotal() >= threshold;
        }
        double getDiscountAmount(Cart* cart){
            return discountStrategy->calculateDiscount(cart->getFinalTotal());
        }
        string name(){
            return "Bulk Purchase Rs " + to_string((int)amount) + " off over "
            + to_string((int)threshold);
        }
};

class BankCoupon : public Coupon{
    private:
        string bank;
        double minSpend;
        double percent;
        double offCap;
        DiscountStrategy* discountStrategy;
    public:
        BankCoupon(string bank, double minSpend, double percent, double offCap){
            this->bank = bank;
            this->minSpend = minSpend;
            this->percent = percent;
            this->offCap = offCap;
            this->discountStrategy = DiscountStrategyFactory::getInstance()->createDiscountStrategy(DiscountType::PERCENTAGE_WITH_CAP, percent, offCap);
        }
        bool isApplicable(Cart* cart){
            return cart->getPaymentBank() == bank && cart->getFinalTotal() >= minSpend;
        }
        double getDiscountAmount(Cart* cart){
            return discountStrategy->calculateDiscount(cart->getFinalTotal());
        }
        string name(){
            return "Bank Offer " + to_string((int)percent) + "% off up to Rs " + to_string((int)offCap) + " on " + bank;
        }
};

class CouponManager {
private:
    static CouponManager* instance;
    Coupon* head;
    mutable mutex mtx;
    CouponManager() {
        head = nullptr;
    }
public:
    static CouponManager* getInstance() {
        if (!instance) {
            instance = new CouponManager();
        }
        return instance;
    }

    void registerCoupon(Coupon* coupon) {
        lock_guard<mutex> lock(mtx);
        if (!head) {
            head = coupon;
        } else {
            Coupon* cur = head;
            while (cur->getNext()) {
                cur = cur->getNext();
            }
            cur->setNext(coupon);
        }
    }

    vector<string> getApplicable(Cart* cart) const {
        lock_guard<mutex> lock(mtx);
        vector<string> res;
        Coupon* cur = head;
        while (cur) {
            if (cur->isApplicable(cart)) {
                res.push_back(cur->name());
            }
            cur = cur->getNext();
        }
        return res;
    }

    double applyAll(Cart* cart) {
        lock_guard<mutex> lock(mtx);
        if (head) {
            head->applyDiscount(cart);
        }
        return cart->getFinalTotal();
    }
};

CouponManager* CouponManager::instance = nullptr;

int main(){

    Product* product1 = new Product("Product 1", "Category 1", 10.0);
    Product* product2 = new Product("Product 2", "Category 2", 20.0);
    Product* product3 = new Product("Product 3", "Category 3", 30.0);
    Product* product4 = new Product("Product 4", "Category 4", 40.0);
    Product* product5 = new Product("Product 5", "Category 5", 50.0);

    Cart* cart = new Cart();
    cart->addItem(product1, 2);
    cart->addItem(product2, 1);
    cart->addItem(product3, 3);
    cart->addItem(product4, 1);
    cart->addItem(product5, 2);

    cart->setLoyaltyMember(true);
    cart->setPaymentBank("SBI");

    loyaltyCoupon* loyaltyDiscount = new loyaltyCoupon(10.0);
    BulkCoupon* bulkCoupon = new BulkCoupon(200.0, 50.0);
    BankCoupon* bankCoupon = new BankCoupon("SBI", 500.0, 5.0, 100.0);

    CouponManager* couponManager = CouponManager::getInstance();
    couponManager->registerCoupon(loyaltyDiscount);
    couponManager->registerCoupon(bulkCoupon);
    couponManager->registerCoupon(bankCoupon);

    double finalTotal = couponManager->applyAll(cart);
    vector<string> applicableCoupons = couponManager->getApplicable(cart);

    cout << "Final Total: " << finalTotal << endl;
    cout << "Applicable Coupons:" << endl;
    for (string coupon : applicableCoupons) {
        cout << " - " << coupon << endl;
    }

    return 0;
}