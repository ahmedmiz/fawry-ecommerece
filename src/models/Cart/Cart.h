#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>
#include "CartItem.h"
#include "../Prodcut/Product.h"
#include "../../interface/IShippable.h"

class Cart
{
private:
    std::vector<CartItem> items;

public:
    void add(std::shared_ptr<Product> product, int quantity);
    bool isEmpty() const;
    double getSubtotal() const;
    std::vector<std::shared_ptr<IShippable>> getShippableItems() const;
    std::map<std::string, int> getItemQuantities() const;
    const std::vector<CartItem> &getItems() const;
    void clear();
    bool validateCart() const;
    void updateProductQuantities();
};