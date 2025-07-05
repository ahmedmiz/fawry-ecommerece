#pragma once

#include "Product.h"                    // Base class declaration
#include "../../interface/IShippable.h" // Interface declaration

// NonPerishableProduct class definition
class NonPerishableProduct : public Product, public IShippable
{
private:
    double weight; // in kg

public:
    NonPerishableProduct(const std::string &name, double price, int quantity,
                         bool requiresShipping, double weight = 0.0);

    // IShippable interface implementation
    std::string getName() const override;
    double getWeight() const override;
};
