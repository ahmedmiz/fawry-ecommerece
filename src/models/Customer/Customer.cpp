#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include "../../interface/IShippable.h"

class Customer
{
private:
    std::string name;
    double balance;

public:
    Customer(const std::string &name, double balance)
        : name(name), balance(balance) {}

    std::string getName() const { return name; }
    double getBalance() const { return balance; }

    bool hasEnoughBalance(double amount) const
    {
        return balance >= amount;
    }

    void deductBalance(double amount)
    {
        if (hasEnoughBalance(amount))
        {
            balance -= amount;
        }
    }
};