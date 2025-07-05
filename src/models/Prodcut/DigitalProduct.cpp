#include "DigitalProduct.h"

DigitalProduct::DigitalProduct(const std::string &name, double price, int quantity)
    : Product(name, price, quantity, false) {}