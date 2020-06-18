#ifndef CARGO_H
#define CARGO_H

#include <iostream>
#include <vector>

class Cargo
{
public:
    Cargo()
    {
        name = "default";
        weight = 0;
        volume = 0;
    }
    Cargo(std::string aName, float aWeight, float aVolume)
    {
        name = aName;
        weight = aWeight;
        volume = aVolume;
    }

    //ACCESSORS
    std::string gettName() const
    {
        return name;
    }

    float getWeight() const
    {
        return weight;
    }

    float getVolume() const
    {
        return volume;
    }

    //MODIFIERS

private:
    std::string name;
    float weight;
    float volume;
};

#endif
