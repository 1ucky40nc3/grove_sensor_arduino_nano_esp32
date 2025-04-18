#pragma once

#include <string>
#include <cstdint>
#include <memory> // For smart pointers

using namespace std;

class AbstractData
{
public:
    virtual ~AbstractData() = default; // Important for proper cleanup with pointers
    virtual string toJson() = 0;
};

class HM330XData : public AbstractData
{
private:
    uint8_t pm_010_spm;
    uint8_t pm_025_spm;
    uint8_t pm_100_spm;
    uint8_t pm_010_ae;
    uint8_t pm_025_ae;
    uint8_t pm_100_ae;

public:
    HM330XData(uint8_t pm010_spm, uint8_t pm025_spm, uint8_t pm100_spm,
               uint8_t pm010_ae, uint8_t pm025_ae, uint8_t pm100_ae);
    string toJson() override; // It's good practice to use 'override' in C++11 and later
};

class AbstractMeasurement
{
public:
    string sensor;
    string version;
    unique_ptr<AbstractData> data; // Using a smart pointer for memory management
    virtual string toJson() = 0;

protected:
    AbstractMeasurement(string sensor, string version, unique_ptr<AbstractData> data);
};

class HM33XMeasurement : public AbstractMeasurement
{
public:
    HM33XMeasurement(string sensor, string version, unique_ptr<HM330XData> data);
    string toJson() override;
};