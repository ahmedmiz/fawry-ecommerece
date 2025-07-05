#include "Customer.h"

Customer::Customer(const std::string &name, double balance)
    : name(name), balance(balance) {}

std::string Customer::getName() const { return name; }
double Customer::getBalance() const { return balance; }

bool Customer::hasEnoughBalance(double amount) const
{
    return balance >= amount;
}

void Customer::deductBalance(double amount)
{
    if (hasEnoughBalance(amount))
    {
        balance -= amount;
    }
}