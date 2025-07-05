# OOP Design: Fawry E-Commerce (C++)

This document describes the object-oriented design of the Fawry E-Commerce C++ project, including class relationships, inheritance, and key design patterns.

---

## Class Diagram

```mermaid
classDiagram
    class Product {
        <<abstract>>
        +string name
        +double price
        +int quantity
        +bool requiresShipping
        +getName() string
        +getPrice() double
        +getQuantity() int
        +getRequiresShipping() bool
        +isAvailable(int) bool
        +isExpired() bool
        +reduceQuantity(int) void
        +getWeight() double
    }

    class PerishableProduct {
        +time_t expirationDate
        +double weight
        +isExpired() bool
        +getWeight() double
    }

    class NonPerishableProduct {
        +double weight
        +getWeight() double
    }

    class DigitalProduct {
        +getWeight() double
    }

    class IShippable {
        <<interface>>
        +getWeight() double
        +getName() string
    }

    class CartItem {
        +shared_ptr~Product~ product
        +int quantity
        +getProduct() shared_ptr~Product~
        +getQuantity() int
        +getTotalPrice() double
        +setQuantity(int) void
    }

    class Cart {
        +vector~CartItem~ items
        +add(Product, int) void
        +isEmpty() bool
        +getSubtotal() double
        +getShippableItems() vector~IShippable~
        +getItemQuantities() map~string,int~
        +getItems() vector~CartItem~
        +clear() void
        +validateCart() bool
        +updateProductQuantities() void
    }

    class Customer {
        +string name
        +double balance
        +hasEnoughBalance(double) bool
        +deductBalance(double) void
        +getBalance() double
    }

    class ShippingService {
        <<static>>
        +calculateShippingFee(vector~IShippable~) double
        +processShipment(vector~IShippable~, map~string,int~) void
    }

    Product <|-- PerishableProduct
    Product <|-- NonPerishableProduct
    Product <|-- DigitalProduct
    PerishableProduct ..|> IShippable
    NonPerishableProduct ..|> IShippable
    CartItem --> Product
    Cart --> CartItem
    Cart --> IShippable
    Customer --> Cart
    ShippingService --> IShippable
```

---

## Class & Interface Descriptions

### Product (Abstract Base Class)

- **Fields:** name, price, quantity, requiresShipping
- **Methods:** getName, getPrice, getQuantity, getRequiresShipping, isAvailable, isExpired, reduceQuantity, getWeight
- **Purpose:** Base for all product types. Provides common interface and logic.

### PerishableProduct (Inherits Product, Implements IShippable)

- **Fields:** expirationDate, weight
- **Methods:** isExpired (override), getWeight (override)
- **Purpose:** Represents products that can expire and be shipped (e.g., food).

### NonPerishableProduct (Inherits Product, Implements IShippable)

- **Fields:** weight
- **Methods:** getWeight (override)
- **Purpose:** Represents durable goods that can be shipped (e.g., electronics).

### DigitalProduct (Inherits Product)

- **Purpose:** Represents digital goods (e.g., e-cards). No shipping or expiration.

### IShippable (Interface)

- **Methods:** getWeight, getName
- **Purpose:** Implemented by products that can be shipped. Used for shipping calculations.

### CartItem

- **Fields:** product (shared_ptr<Product>), quantity
- **Methods:** getProduct, getQuantity, getTotalPrice, setQuantity
- **Purpose:** Represents a product and its quantity in the cart.

### Cart

- **Fields:** items (vector<CartItem>)
- **Methods:** add, isEmpty, getSubtotal, getShippableItems, getItemQuantities, getItems, clear, validateCart, updateProductQuantities
- **Purpose:** Manages cart items, calculates totals, and provides shippable items.

### Customer

- **Fields:** name, balance
- **Methods:** hasEnoughBalance, deductBalance, getBalance
- **Purpose:** Represents a customer and their account balance.

### ShippingService

- **Static Methods:** calculateShippingFee, processShipment
- **Purpose:** Calculates shipping fees and simulates shipment for shippable products.

---

## Key OOP Concepts Used

- **Inheritance:**
  - Product is a base class for PerishableProduct, NonPerishableProduct, and DigitalProduct.
- **Interface Implementation:**
  - IShippable is implemented by PerishableProduct and NonPerishableProduct.
- **Composition:**
  - Cart contains CartItems, which contain Products.
  - Customer has a Cart.
- **Polymorphism:**
  - Cart and ShippingService use pointers/references to Product and IShippable, allowing for flexible product handling.

---

## Interactions

- **Cart** manages a collection of **CartItem**s, each referencing a **Product**.
- **Cart** provides a list of **IShippable** products for shipping calculations.
- **ShippingService** operates on **IShippable** products to calculate fees and process shipments.
- **Customer** interacts with **Cart** for checkout and payment.

---

This design enables easy extension (e.g., adding new product types), clear separation of concerns, and demonstrates core OOP principles in C++.
