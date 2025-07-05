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

class Product
{
protected:
    std::string name;
    double price;
    int quantity;
    bool requiresShipping;

public:
    Product(const std::string &name, double price, int quantity, bool requiresShipping)
        : name(name), price(price), quantity(quantity), requiresShipping(requiresShipping) {}

    virtual ~Product() = default;

    // Getters
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    bool getRequiresShipping() const { return requiresShipping; }

    // Check if product is available
    virtual bool isAvailable(int requestedQuantity) const
    {
        return quantity >= requestedQuantity && !isExpired();
    }

    // Check if product is expired (default: never expires)
    virtual bool isExpired() const { return false; }

    // Reduce quantity when purchased
    void reduceQuantity(int amount)
    {
        if (amount <= quantity)
        {
            quantity -= amount;
        }
    }

    // Virtual method to get weight (for shippable items)
    virtual double getWeight() const { return 0.0; }
};
