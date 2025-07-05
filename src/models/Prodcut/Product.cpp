#include "Product.h"

Product::Product(const std::string &name, double price, int quantity, bool requiresShipping)
    : name(name), price(price), quantity(quantity), requiresShipping(requiresShipping) {}

// Getters
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }
bool Product::getRequiresShipping() const { return requiresShipping; }

// Check if product is available
bool Product::isAvailable(int requestedQuantity) const
{
    return quantity >= requestedQuantity && !isExpired();
}

// Check if product is expired (default: never expires)
bool Product::isExpired() const { return false; }

// Reduce quantity when purchased
void Product::reduceQuantity(int amount)
{
    if (amount <= quantity)
    {
        quantity -= amount;
    }
}

// Virtual method to get weight (for shippable items)
double Product::getWeight() const { return 0.0; }
