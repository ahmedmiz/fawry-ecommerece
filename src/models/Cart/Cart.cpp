#include "Cart.h"

void Cart::add(std::shared_ptr<Product> product, int quantity)
{
    // Check if product already exists in cart
    for (auto &item : items)
    {
        if (item.getProduct() == product)
        {
            item.setQuantity(item.getQuantity() + quantity);
            return;
        }
    }

    // Add new item
    items.emplace_back(product, quantity);
}

bool Cart::isEmpty() const
{
    return items.empty();
}

double Cart::getSubtotal() const
{
    double subtotal = 0.0;
    for (const auto &item : items)
    {
        subtotal += item.getTotalPrice();
    }
    return subtotal;
}

std::vector<std::shared_ptr<IShippable>> Cart::getShippableItems() const
{
    std::vector<std::shared_ptr<IShippable>> shippableItems;

    for (const auto &item : items)
    {
        auto product = item.getProduct();
        if (product->getRequiresShipping())
        {
            // Cast to IShippable if possible
            auto shippable = std::dynamic_pointer_cast<IShippable>(product);
            if (shippable)
            {
                shippableItems.push_back(shippable);
            }
        }
    }

    return shippableItems;
}

std::map<std::string, int> Cart::getItemQuantities() const
{
    std::map<std::string, int> quantities;

    for (const auto &item : items)
    {
        quantities[item.getProduct()->getName()] = item.getQuantity();
    }

    return quantities;
}

const std::vector<CartItem> &Cart::getItems() const
{
    return items;
}

void Cart::clear()
{
    items.clear();
}

// Validate cart before checkout
bool Cart::validateCart() const
{
    for (const auto &item : items)
    {
        auto product = item.getProduct();
        if (!product->isAvailable(item.getQuantity()))
        {
            return false;
        }
    }
    return true;
}

// Update product quantities after successful checkout
void Cart::updateProductQuantities()
{
    for (const auto &item : items)
    {
        item.getProduct()->reduceQuantity(item.getQuantity());
    }
}
