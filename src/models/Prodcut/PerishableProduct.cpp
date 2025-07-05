#include "PerishableProduct.h"

PerishableProduct::PerishableProduct(const std::string &name, double price, int quantity,
                                     bool requiresShipping, time_t expirationDate, double weight)
    : Product(name, price, quantity, requiresShipping), expirationDate(expirationDate), weight(weight) {}

bool PerishableProduct::isExpired() const
{
    return time(0) > expirationDate;
}

std::string PerishableProduct::getName() const { return name; }
double PerishableProduct::getWeight() const { return weight; }
