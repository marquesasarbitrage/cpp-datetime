#include <iostream>
#include "../include/cpp-datetime/utils.hpp"

DateTimeUtils::DateTimeUtils(const bool adjust_business_day, const HolidayCalendar& holiday_calendar, const DayCountConvention& day_count_convention):
adjust_business_day_(adjust_business_day), holiday_calendar_(holiday_calendar), day_count_convention_(day_count_convention){};

DateTimeUtils::DateTimeUtils():adjust_business_day_(false), holiday_calendar_(HolidayCalendar::NONE), day_count_convention_(DayCountConvention::ACTUAL_360){};

void DateTimeUtils::setDayCountConvention(const DayCountConvention& day_count_convention){day_count_convention_=day_count_convention;}
void DateTimeUtils::setHolidayCalendar(const HolidayCalendar& holiday_calendar){holiday_calendar_=holiday_calendar;}
void DateTimeUtils::setAdjustBusinessDay(bool adjust_business_day){adjust_business_day_=adjust_business_day;}

DayCountConvention DateTimeUtils::getDayCountConvention(){return day_count_convention_;}
HolidayCalendar DateTimeUtils::getHolidayCalendar(){return holiday_calendar_;}
bool DateTimeUtils::getAdjustBusinessDay(){return adjust_business_day_;}

bool DateTimeUtils::isWeekEnd(const DateTime& reference_date)
{
    std::tm time_info = reference_date.getCTimeObject();
    if (time_info.tm_wday==0){return true;}
    if (time_info.tm_wday==6){return true;}
    return false;
}

DateTime DateTimeUtils::getNextBusinessDay(const DateTime& reference_date)
{
    switch (holiday_calendar_)
    {
    case HolidayCalendar::NONE: return getNextBusinessDayNone(reference_date); 
    default: 
        std::cout << UndefinedHolidayCalendarError().what() << std::endl; 
        return getNextBusinessDayNone(reference_date); 
    }
}

DateTime DateTimeUtils::getNextBusinessDayNone(const DateTime& reference_date)
{
    DateTime outDate = DateTime(reference_date.getTimestamp(), reference_date.getTimestampType());
    if (isWeekEnd(reference_date)){
        int day_of_week = outDate.getCTimeObject().tm_wday;
        if (day_of_week == 6) {outDate += TimeDelta(2,0,0,0,0,0,0);};
        if (day_of_week == 0) {outDate += TimeDelta(1,0,0,0,0,0,0);};
    };
    return outDate;
}

double DateTimeUtils::getYearFraction(const DateTime& start, const DateTime& end)
{
    if (start>end) throw EndDateBeforeStartDateError();    
    return double((end-start).getTotalNanoSeconds())/(static_cast<double>(day_count_convention_)*static_cast<double>(EpochTimestampType::NANOSECONDS)*24.0*60.0*60.0);
}

DateTime DateTimeUtils::getForwardDateTime(const DateTime& reference_date, const Tenor& tenor)
{
    std::tm t = reference_date.getCTimeObject();
    switch (tenor.getTenorType()){
        case TenorType::DAYS: {t.tm_mday += tenor.getValue();}; break;
        case TenorType::WEEKS: {t.tm_mday += 7*tenor.getValue();}; break;
        case TenorType::MONTHS: {t.tm_mon += tenor.getValue();}; break;
        case TenorType::YEARS: {t.tm_year += tenor.getValue();}; break;
    }
    DateTime forwardDate = DateTime(static_cast<long long int>(mktime(&t)), EpochTimestampType::SECONDS);
    return adjust_business_day_ ? getNextBusinessDay(forwardDate) : forwardDate;
}

std::vector<DateTime> DateTimeUtils::getDateTimeSequence(const DateTime& start, const Tenor& frequence, const Tenor& maturity)
{
    DateTime reference_date = adjust_business_day_ ? getNextBusinessDay(start): start;
    DateTime maturity_date = getForwardDateTime(start, maturity);
    int n = static_cast<int>(round(maturity/frequence));
    std::vector<DateTime> dateSequence = {reference_date}; 
    for (int i = 0; i<n-1; i++)
    {
        reference_date = getForwardDateTime(reference_date, frequence);
        dateSequence.push_back(reference_date);
    }
    dateSequence.push_back(maturity_date);
    return dateSequence;
}
