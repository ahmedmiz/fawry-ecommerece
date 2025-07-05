# Fawry E-Commerce (C++)

A simple, modular e-commerce system implemented in C++. This project demonstrates object-oriented design, product management, cart operations, customer balance handling, and shipping logic.

## How the Project Works

This project simulates an e-commerce checkout system. It supports different product types (perishable, non-perishable, digital), manages a shopping cart, calculates shipping, and processes customer payments. The main program runs a series of test cases to demonstrate the system's features and error handling.

### High-Level Flow

1. **Product Creation:** Several products (perishable, non-perishable, digital) are created with different properties.
2. **Customer Creation:** A customer is initialized with a name and balance.
3. **Cart Operations:** Products are added to the cart in various scenarios (valid, expired, out-of-stock, etc.).
4. **Checkout:** The system validates the cart, calculates totals and shipping, checks customer balance, and processes payment and shipment.
5. **Error Handling:** The system demonstrates handling of empty carts, insufficient balance, expired products, and out-of-stock situations.

### Main Components

- **Product (Base Class):** Represents a generic product. Subclasses include:
  - `PerishableProduct`: Has an expiration date and weight.
  - `NonPerishableProduct`: Has weight but does not expire.
  - `DigitalProduct`: No shipping or expiration.
- **CartItem:** Associates a product with a quantity in the cart.
- **Cart:** Manages a collection of `CartItem`s, calculates subtotal, and provides shippable items.
- **Customer:** Holds customer information and balance, and processes payments.
- **ShippingService:** Calculates shipping fees and simulates shipment for shippable products.
- **IShippable (Interface):** Implemented by products that can be shipped.

### Project Structure

```
src/
  main.cpp                # Entry point and demo/test cases
  models/
    Cart/
      Cart.h, Cart.cpp        # Cart logic
      CartItem.h, CartItem.cpp# Cart item logic
    Customer/
      Customer.h, Customer.cpp# Customer logic
    Prodcut/                  # (typo: should be 'Product')
      Product.h, Product.cpp  # Base product class
      PerishableProduct.*     # Perishable product logic
      NonPerishableProduct.*  # Non-perishable product logic
      DigitalProduct.*        # Digital product logic
  services/
    ShippingService.h, ShippingService.cpp # Shipping logic
  interface/
    IShippable.h             # Shippable interface
CMakeLists.txt            # CMake build configuration
build.sh                  # Build script
Dockerfile                # Docker build/run
.gitignore                # Git ignore rules
```

## Build Instructions

### Prerequisites

- CMake (>=3.10)
- C++17 compatible compiler (g++ or clang++)
- (Optional) Docker

### Build (Native)

```bash
./build.sh
```

### Run

```bash
./build_Debug/fawry-eCommerce
```

### Build & Run Tests

```bash
./build.sh Debug test
```

## Build & Run with Docker

1. Build the Docker image:
   ```bash
   docker build -t fawry-ecommerce .
   ```
2. Run the program:
   ```bash
   docker run --rm fawry-ecommerce
   ```

## Example Output

When you run the program, it will execute several test cases, such as:

- Successful checkout with mixed items
- Checkout with heavy items
- Empty cart checkout
- Insufficient balance
- Expired product
- Out of stock
- Only digital products (no shipping)

Each case demonstrates the system's logic and error handling.

## Documentation

- **[OOP_DESIGN.md](OOP_DESIGN.md)** - Detailed object-oriented design documentation with class diagrams and relationships
