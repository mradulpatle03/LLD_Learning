#ifndef UPI_PAYMENT_STRATEGY_H
#define UPI_PAYMENT_STRATEGY_H

#include "PaymentStrategy.h"
#include <bits/stdc++.h>
using namespace std;

class UpiPaymentStrategy : public PaymentStrategy {
private:
    string mobile;
public:
    UpiPaymentStrategy(const string& mob) {
        mobile = mob;
    }

    void pay(double amount) override {
        cout << "Paid ₹" << amount << " using UPI (" << mobile << ")" << endl;
    }
};

#endif