#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include "../interface/IShippable.h"

class ShippingService
{
public:
    static double calculateShippingFee(const std::vector<std::shared_ptr<IShippable>> &items)
    {
        double totalWeight = 0.0;
        for (const auto &item : items)
        {
            totalWeight += item->getWeight();
        }

        // Shipping fee calculation: $10 per kg + $5 base fee
        return totalWeight * 10.0 + 5.0;
    }
    static void processShipment(const std::vector<std::shared_ptr<IShippable>> &items,
                                const std::map<std::string, int> &quantities)
    {
        if (items.empty())
            return;

        std::cout << "** Shipment notice **" << std::endl;

        double totalWeight = 0.0;
        for (const auto &item : items)
        {
            int qty = quantities.at(item->getName());
            double itemWeight = item->getWeight() * qty;
            totalWeight += itemWeight;

            std::cout << qty << "x " << item->getName() << " "
                      << std::fixed << std::setprecision(0) << (itemWeight * 1000) << "g" << std::endl;
        }

        std::cout << "Total package weight " << std::fixed << std::setprecision(1)
                  << totalWeight << "kg" << std::endl;
    }
};
