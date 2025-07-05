#pragma once

#include <string>

// Product base class definition
class Product {
protected:
    std::string name;
    double price;
    int quantity;
    bool requiresShipping;

public:
    Product(const std::string& name, double price, int quantity, bool requiresShipping);
    virtual ~Product() = default;

    // Getters
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    bool getRequiresShipping() const;

    // Check if product is available
    virtual bool isAvailable(int requestedQuantity) const;

    // Check if product is expired (default: never expires)
    virtual bool isExpired() const;

    // Reduce quantity when purchased
    void reduceQuantity(int amount);

    // Virtual method to get weight (for shippable items)
    virtual double getWeight() const;
};
