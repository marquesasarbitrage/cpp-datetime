#pragma once 
#include "datetime.hpp"

enum class TenorType {DAYS, WEEKS, MONTHS, YEARS};

enum class DayCountConvention {ACTUAL_360 = 360, ACTUAL_365 = 365, ACTUAL_364 = 364};

class Tenor
{
    public:
        Tenor(int value, const TenorType& tenor_type);
        ~Tenor(){};

        int getValue() const;
        TenorType getTenorType() const;
        std::string asString() const;
        TimeDelta getRawTimeDelta() const;

        bool operator==(const Tenor& other) const;
        bool operator<(const Tenor& other) const;
        bool operator<=(const Tenor& other) const;
        bool operator!=(const Tenor& other) const;
        bool operator>(const Tenor& other) const;
        bool operator>=(const Tenor& other) const;
        Tenor operator*(int n) const;
        double operator/(const Tenor& other) const;

    private: 
        int value_; 
        TenorType tenor_type_;
};
