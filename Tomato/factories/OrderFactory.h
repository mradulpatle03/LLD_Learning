#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include <bits/stdc++.h>
#include "../models/Order.h"
#include "../models/Cart.h"
#include "../models/Restaurant.h"
#include "../strategies/PaymentStrategy.h"
using namespace std;

class OrderFactory {
public:
    virtual Order* createOrder(User* user, Cart* cart, Restaurant* restaurant, const vector<MenuItem>& menuItems,
                                PaymentStrategy* paymentStrategy, double totalCost, const string& orderType) = 0;
    virtual ~OrderFactory() {}
};

#endif