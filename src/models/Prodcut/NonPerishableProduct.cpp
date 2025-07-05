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
#include "NonPerishableProduct.h"

class NonPerishableProduct : public Product, public IShippable
{
private:
    double weight; // in kg

public:
    NonPerishableProduct(const std::string &name, double price, int quantity,
                         bool requiresShipping, double weight)
        : Product(name, price, quantity, requiresShipping), weight(weight) {}

    // IShippable interface implementation
    std::string getName() const { return name; }
    double getWeight() const { return weight; }
};

// Digital Product class (non-shippable items like scratch cards)
class DigitalProduct : public Product
{
public:
    DigitalProduct(const std::string &name, double price, int quantity)
        : Product(name, price, quantity, false) {}
};
