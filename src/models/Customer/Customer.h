#pragma once

#include <string>

class Customer {
private:
    std::string name;
    double balance;

public:
    Customer(const std::string& name, double balance);
    std::string getName() const;
    double getBalance() const;
    bool hasEnoughBalance(double amount) const;
    void deductBalance(double amount);
};