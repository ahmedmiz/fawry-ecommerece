#pragma once

#include <string>
#include <ctime>                  // For time_t
#include "Product.h"              // Base class declaration
#include "interface/IShippable.h" // Interface declaration

// PerishableProduct class definition
class PerishableProduct : public Product, public IShippable
{
private:
    time_t expirationDate;
    double weight; // in kg

public:
    PerishableProduct(const std::string &name, double price, int quantity,
                      bool requiresShipping, time_t expirationDate, double weight = 0.0);

    bool isExpired() const override;

    // IShippable interface implementation
    std::string getName() const override;
    double getWeight() const override;
};
