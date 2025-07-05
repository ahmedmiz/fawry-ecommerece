#pragma once

#include "Product.h"

class DigitalProduct : public Product
{
public:
    DigitalProduct(const std::string &name, double price, int quantity);
};
