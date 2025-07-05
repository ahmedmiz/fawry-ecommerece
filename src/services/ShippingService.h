#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>
#include "../interface/IShippable.h"

class ShippingService
{
public:
    static double calculateShippingFee(const std::vector<std::shared_ptr<IShippable>> &items);

    static void processShipment(
        const std::vector<std::shared_ptr<IShippable>> &items,
        const std::map<std::string, int> &quantities);
};
