#pragma once
#include <string>

class IShippable
{
public:
    virtual std::string getName() const = 0;
    virtual double getWeight() const = 0;
    virtual ~IShippable() = default;
};
