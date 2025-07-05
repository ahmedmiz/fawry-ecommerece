#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include "../Prodcut/Product.h"

class CartItem
{
private:
    std::shared_ptr<Product> product;
    int quantity;

public:
    CartItem(std::shared_ptr<Product> product, int quantity)
        : product(product), quantity(quantity) {}

    std::shared_ptr<Product> getProduct() const { return product; }
    int getQuantity() const { return quantity; }
    double getTotalPrice() const { return product->getPrice() * quantity; }

    void setQuantity(int quantity) { this->quantity = quantity; }
};