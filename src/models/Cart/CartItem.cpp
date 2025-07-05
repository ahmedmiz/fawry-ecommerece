#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include "CartItem.h"
#include "../Prodcut/Product.h"

CartItem::CartItem(std::shared_ptr<Product> product, int quantity)
    : product(product), quantity(quantity) {}

std::shared_ptr<Product> CartItem::getProduct() const
{
    return product;
}

int CartItem::getQuantity() const
{
    return quantity;
}

double CartItem::getTotalPrice() const
{
    return product->getPrice() * quantity;
}

void CartItem::setQuantity(int quantity)
{
    this->quantity = quantity;
}