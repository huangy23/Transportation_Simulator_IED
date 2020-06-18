#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <vector>
#include <fstream>
#include "cargo.h"
using namespace std;

class Vehicle
{
public:
    Vehicle(std::string aModel, float aWeight, float aCapacity, Cargo aCargo,
            float aTotal_volume, long double aCurrent_Gas)
    {
        model = aModel;
        weight = aWeight;
        capacity = aCapacity;
        cargo = aCargo;
        total_volume = aTotal_volume;
        current_gas = aCurrent_Gas;
        throw_index = 0;
    }

    //ACCESSORS
    std::string getModelName() const
    {
        return model;
    }

    float getVehicleWeight() const
    {
        return weight;
    }

    float getCapacity() const
    {
        return capacity;
    }
    
    int getCargoQuantity()
    {
        long double f_cargo_quantity = (total_volume / cargo.getVolume()) - throw_index;
        int total = (int)f_cargo_quantity;
        return total;
    }

    int getTotalWeight()
    {
        long double
            f_total_weight = (this->getCargoQuantity() * cargo.getWeight()) + current_gas + weight;

        int temp = (int)f_total_weight;
        return temp;
    }

    int getCurrentGas()
    {
        return current_gas;
    }

    int getThrowIndex()
    {
        return throw_index;
    }

    //MODIFIERS
    void comsume_gas()
    {
        long double
            current_MileperLb = ((weight) / (weight + current_gas + cargo.getWeight())) * (23 / 6.3);

        //speed of 65 is 1.083 mile per minute (65 * 0.0166667)
        long double
            current_GasConsumptionPerMin = 1.083 / current_MileperLb;

        current_gas -= current_GasConsumptionPerMin;
    }

    void throw_cargo()
    {
        throw_index += 1;
        //cout << "drop" << endl;
    }

private:
    std::string model;
    float weight;
    float capacity;
    Cargo cargo;
    float total_volume;
    long double current_gas;
    int throw_index;

    //long double f_cargo_quantity = total_volume / cargo.getVolume();
    //long double f_total_weight = f_cargo_quantity * cargo.getWeight();
};

#endif
