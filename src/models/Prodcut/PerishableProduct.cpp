#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include "Product.h"
#include "../../interface/IShippable.h"

class PerishableProduct : public Product, public IShippable
{
private:
    time_t expirationDate;
    double weight; // in kg

public:
    PerishableProduct(const std::string &name, double price, int quantity,
                      bool requiresShipping, time_t expirationDate, double weight = 0.0)
        : Product(name, price, quantity, requiresShipping), expirationDate(expirationDate), weight(weight) {}

    bool isExpired() const override
    {
        return time(0) > expirationDate;
    }

    // IShippable interface implementation
    std::string getName() const override { return name; }
    double getWeight() const override { return weight; }
};
