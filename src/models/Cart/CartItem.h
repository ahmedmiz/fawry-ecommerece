#pragma once

#include <memory>
#include "../Prodcut/Product.h"

class CartItem
{
private:
    std::shared_ptr<Product> product;
    int quantity;

public:
    CartItem(std::shared_ptr<Product> product, int quantity);
    std::shared_ptr<Product> getProduct() const;
    int getQuantity() const;
    double getTotalPrice() const;
    void setQuantity(int quantity);
};