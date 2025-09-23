#include <iostream>
#include "../../include/cpp-datetime/tenor.hpp"

Tenor::Tenor(int value, const TenorType& tenor_type): value_(abs(value)), tenor_type_(tenor_type){}

int Tenor::getValue() const {return value_;}
TenorType Tenor::getTenorType() const {return tenor_type_;}
std::string Tenor::asString() const
{
    if (value_ == 0) return "0D";
    else if (value_ == 1 and tenor_type_ == TenorType::DAYS) return "ON";
    else if (value_ == 2 and tenor_type_ == TenorType::DAYS) return "SN";
    else if (value_ == 3 and tenor_type_ == TenorType::DAYS) return "TN";
    else 
    {
        switch (tenor_type_)
        {
            case TenorType::DAYS: return std::to_string(value_) + "D";;
            case TenorType::WEEKS: return std::to_string(value_) + "W";
            case TenorType::MONTHS: return std::to_string(value_) + "M";
            case TenorType::YEARS: return std::to_string(value_) + "Y";
        }
    }
}

TimeDelta Tenor::getRawTimeDelta() const
{
    DateTime now = DateTime();
    std::tm t = now.getCTimeObject();
    switch (getTenorType()){
        case TenorType::DAYS: {t.tm_mday += getValue();}; break;
        case TenorType::WEEKS: {t.tm_mday += 7*getValue();}; break;
        case TenorType::MONTHS: {t.tm_mon += getValue();}; break;
        case TenorType::YEARS: {t.tm_year += getValue();}; break;
    }
    DateTime forwardDate = DateTime(static_cast<long long int>(mktime(&t)), EpochTimestampType::SECONDS);
    return forwardDate - now;

}

bool Tenor::operator==(const Tenor& other) const {return (getRawTimeDelta() == other.getRawTimeDelta()) ? true : false;}
bool Tenor::operator<(const Tenor& other) const {return (getRawTimeDelta() < other.getRawTimeDelta()) ? true : false;}
bool Tenor::operator<=(const Tenor& other) const {return (getRawTimeDelta() <= other.getRawTimeDelta()) ? true : false;}
bool Tenor::operator!=(const Tenor& other) const{return (!operator==(other));}
bool Tenor::operator>(const Tenor& other) const {return (!operator<=(other));}
bool Tenor::operator>=(const Tenor& other) const {return (!operator<(other));}
Tenor Tenor::operator*(int n) const{return Tenor(value_*abs(n), tenor_type_);}
double Tenor::operator/(const Tenor& other) const{return double(getRawTimeDelta().getTotalNanoSeconds())/double(other.getRawTimeDelta().getTotalNanoSeconds());}