#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include "models/Customer/Customer.h"
#include "models/Cart/Cart.h"
#include "models/Prodcut/Product.h"
#include "models/Prodcut/PerishableProduct.h"
#include "models/Prodcut/NonPerishableProduct.h"
#include "models/Prodcut/DigitalProduct.h"
#include "services/ShippingService.h"
#include "interface/IShippable.h"

void checkout(Customer &customer, Cart &cart)
{
    try
    {
        // Check if cart is empty
        if (cart.isEmpty())
        {
            throw std::runtime_error("Cart is empty");
        }

        // Validate cart (check stock and expiration)
        if (!cart.validateCart())
        {
            throw std::runtime_error("One or more products are out of stock or expired");
        }

        // Calculate subtotal
        double subtotal = cart.getSubtotal();

        // Get shippable items and calculate shipping
        auto shippableItems = cart.getShippableItems();
        auto quantities = cart.getItemQuantities();
        double shippingFee = 0.0;

        if (!shippableItems.empty())
        {
            shippingFee = ShippingService::calculateShippingFee(shippableItems);
        }

        double totalAmount = subtotal + shippingFee;

        // Check customer balance
        if (!customer.hasEnoughBalance(totalAmount))
        {
            throw std::runtime_error("Customer's balance is insufficient");
        }

        // Process shipment if there are shippable items
        if (!shippableItems.empty())
        {
            ShippingService::processShipment(shippableItems, quantities);
        }

        // Print checkout receipt
        std::cout << "** Checkout receipt **" << std::endl;

        for (const auto &item : cart.getItems())
        {
            std::cout << item.getQuantity() << "x " << item.getProduct()->getName()
                      << " " << std::fixed << std::setprecision(0) << item.getTotalPrice() << std::endl;
        }

        std::cout << "----------------------" << std::endl;
        std::cout << "Subtotal " << std::fixed << std::setprecision(0) << subtotal << std::endl;
        std::cout << "Shipping " << std::fixed << std::setprecision(0) << shippingFee << std::endl;
        std::cout << "Amount " << std::fixed << std::setprecision(0) << totalAmount << std::endl;

        // Process payment
        customer.deductBalance(totalAmount);
        cart.updateProductQuantities();

        std::cout << "Payment successful! Customer balance: $" << std::fixed << std::setprecision(2)
                  << customer.getBalance() << std::endl;

        // Clear cart after successful checkout
        cart.clear();
    }
    catch (const std::exception &e)
    {
        std::cout << "Checkout failed: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        // Create products
        time_t futureDate = time(0) + 86400 * 30; // 30 days from now
        time_t pastDate = time(0) - 86400;        // 1 day ago (expired)

        // Perishable products
        auto cheese = std::make_shared<PerishableProduct>("Cheese", 100.0, 10, true, futureDate, 0.2);
        auto biscuits = std::make_shared<PerishableProduct>("Biscuits", 150.0, 5, true, futureDate, 0.7);
        auto expiredMilk = std::make_shared<PerishableProduct>("Milk", 50.0, 3, true, pastDate, 0.5);

        // Non-perishable products
        auto tv = std::make_shared<NonPerishableProduct>("TV", 500.0, 2, true, 15.0);
        auto mobile = std::make_shared<NonPerishableProduct>("Mobile", 800.0, 1, true, 0.3);

        // Digital products
        auto scratchCard = std::make_shared<DigitalProduct>("Scratch Card", 10.0, 100);

        // Create customer
        Customer customer("Ahmed Saad", 2000.0);

        // Create cart
        Cart cart;

        std::cout << "=== E-COMMERCE SYSTEM DEMO ===" << std::endl
                  << std::endl;

        // Test Case 1: Successful checkout with mixed items
        std::cout << "Test Case 1: Successful checkout with mixed items" << std::endl;
        cart.add(cheese, 2);
        cart.add(biscuits, 1);
        cart.add(scratchCard, 1);
        checkout(customer, cart);
        std::cout << std::endl;

        // Test Case 2: Checkout with TV (heavy item)
        std::cout << "Test Case 2: Checkout with TV (heavy item)" << std::endl;
        cart.add(tv, 1);
        checkout(customer, cart);
        std::cout << std::endl;

        // Test Case 3: Empty cart
        std::cout << "Test Case 3: Empty cart checkout" << std::endl;
        Cart emptyCart;
        checkout(customer, emptyCart);
        std::cout << std::endl;

        // Test Case 4: Insufficient balance
        std::cout << "Test Case 4: Insufficient balance" << std::endl;
        Customer poorCustomer("Jane Doe", 50.0);
        cart.add(tv, 1);
        checkout(poorCustomer, cart);
        cart.clear();
        std::cout << std::endl;

        // Test Case 5: Expired product
        std::cout << "Test Case 5: Expired product" << std::endl;
        cart.add(expiredMilk, 1);
        checkout(customer, cart);
        cart.clear();
        std::cout << std::endl;

        // Test Case 6: Out of stock
        std::cout << "Test Case 6: Out of stock" << std::endl;
        cart.add(mobile, 5); // Only 1 available
        checkout(customer, cart);
        cart.clear();
        std::cout << std::endl;

        // Test Case 7: Only digital products (no shipping)
        std::cout << "Test Case 7: Only digital products (no shipping)" << std::endl;
        cart.add(scratchCard, 3);
        checkout(customer, cart);
        std::cout << std::endl;

        std::cout << "=== DEMO COMPLETE ===" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}