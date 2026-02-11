#ifndef PAYMENT_STRATEGY_H
#define PAYMENT_STRATEGY_H

#include <bits/stdc++.h>
using namespace std;

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() {}
};

#endif