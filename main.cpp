#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <bits/stdc++.h>
#include "vehicle.h"
#include "cargo.h"
#include <fstream>
using namespace std;

/***********************************************************/
//  文件名称: main.cpp
//  简要描述: main file for transportation simulator
//   
//  当前版本:1.2
//  日期: 06/14/2020 
//  描述: 加入油量参数 加入限重机制
/***********************************************************/

long double
toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double
Distance(long double lat1, long double long1,
         long double lat2, long double long2)
{
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    long double R = 6371;

    ans = ans * R * 0.621371;

    return ans;
}

// Driver Code
int main()
{
    ofstream myfile;
    myfile.open("output4.txt");
    
    /***********************/
    //INPUT COORDINATES HERE 
    /***********************/

    myfile << "Route A.\n";
    //myfile << "Writing this to a file.\n";
    //location 1: San Diego, CA, United States of America
    //Lat, Long: 32.71533,-117.15726
    long double lat1 = 32.71533;
    long double long1 = -117.15726;

    //location 2: Albany Medical Center, 43 New Scotland Avenue,
    //Albany, NY 12208, United States of America
    //Lat, Long: 42.6537776,-73.7761384
    long double lat2 = 42.6537776;
    long double long2 = -73.7761384;

    // call the distance function
    myfile << "Start:      :" << lat1 << "," << long1 << endl;
    myfile << "Destination :" << lat2 << "," << long2 << endl;
    myfile << setprecision(15) << fixed;
    myfile << Distance(lat1, long1,
                       lat2, long2)
           << " Mile" << endl;

    /**************************/
    //INPUT CARGO SPECS HERE ->
    /**************************/

    //cargo specs: 3M N-95 masks (20 pack) – box 5.625 x 5.625 x 8”, 0.525 lbs.
    string cargo_name = "masks";
    float cargo_weight = 0.525;
    float cargo_volume = 5.625 * 5.625 * 8;
    Cargo m_cargo(cargo_name, cargo_weight, cargo_volume);
    

    /*
    //cargo specs: Hamilton C3 ventilator – box (without stand) 24” x 12” x 24”, 25 lbs.
    string cargo_name = "ventilator";
    float cargo_weight = 25;
    float cargo_volume = 24 * 12 * 24;
    Cargo m_cargo(cargo_name, cargo_weight, cargo_volume);
    */

    /****************************/
    //INPUT VEHICLE SPECS HERE ->
    /****************************/
    float weight_of_t150anduhaul = 5460 + 1920;
    float volume_t150anduhaul = (536.4 + 396) * 1728; //all volume in cu in
    long double gas_weight = 701;                     //unit in lb
    Vehicle T150andUhaul("T150&Uhaul", weight_of_t150anduhaul, 0, m_cargo, volume_t150anduhaul, gas_weight);

    myfile << "Input specs: " << endl;
    myfile << "     Cargo type:      " << m_cargo.gettName() << endl;
    myfile << "     Cargo volume:    " << m_cargo.getVolume() << endl;
    myfile << "     Cargo weight:    " << int(m_cargo.getWeight() * T150andUhaul.getCargoQuantity()) << endl;
    myfile << "     Gas   weight:    " << T150andUhaul.getCurrentGas() << endl;
    myfile << "     cargo quantity:  " << T150andUhaul.getCargoQuantity() << endl;
    myfile << "     Total weight:    " << T150andUhaul.getTotalWeight() << endl;

    bool weight_test = false;

    while (T150andUhaul.getTotalWeight() > (weight_of_t150anduhaul + 5690))
    {
        T150andUhaul.throw_cargo();
        if (T150andUhaul.getTotalWeight() < (weight_of_t150anduhaul + 5690))
        {
            weight_test = true;
            break;
        }
    }

    while ((T150andUhaul.getCargoQuantity() * m_cargo.getVolume()) > (volume_t150anduhaul))
    {
        cerr << "Error" << endl;
    }

    if (weight_test == false)
    {
        myfile << "Input specs are correct" << endl;
        myfile << "Begin simulation:" << endl;
    }
    else
    {
        myfile << "Too many " << m_cargo.gettName() << "!" << endl;
        myfile << "Automatic drop quantity: " << T150andUhaul.getThrowIndex() << endl;
        myfile << "Correction specs: " << endl;
        myfile << "     Cargo type:      " << m_cargo.gettName() << endl;
        myfile << "     Cargo volume:    " << m_cargo.getVolume() << endl;
        myfile << "     Cargo weight:    " << int(m_cargo.getWeight() * T150andUhaul.getCargoQuantity()) << endl;
        myfile << "     Gas   weight:    " << T150andUhaul.getCurrentGas() << endl;
        myfile << "     cargo quantity:  " << T150andUhaul.getCargoQuantity() << endl;
        myfile << "     Total weight:    " << T150andUhaul.getTotalWeight() << endl;
        myfile << "Begin simulation:" << endl;
    }

    //myfile << "Total weight:    " << T150andUhaul.getTotalWeight() << endl;

    //big loop
    int i = 0; //i is minute

    long double
        velocity = 65 * 0.0166667;

    long double
        distance = Distance(lat1, long1, lat2, long2);

    long double
        distance_traveled = 0;

    while (distance_traveled < distance)
    {
        distance_traveled += velocity * 1;
        T150andUhaul.comsume_gas();
        myfile << "Time: " << i << " min  "
               << "Distance traveled: " << distance_traveled << "  ";
        myfile << "Current Gas: " << T150andUhaul.getCurrentGas() << endl;
        i++;
    }
    cout << "Time: " << i << " min   " << distance_traveled << endl;
    myfile.close();
}
