#pragma once 
#include "tenor.hpp"

enum class HolidayCalendar {NONE};

class DateTimeUtils
{
    public: 
        DateTimeUtils(const bool adjust_business_day, const HolidayCalendar& holiday_calendar, const DayCountConvention& day_count_convention); 
        DateTimeUtils(); 

        void setDayCountConvention(const DayCountConvention& day_count_convention);
        void setHolidayCalendar(const HolidayCalendar& holiday_calendar);
        void setAdjustBusinessDay(bool adjust_business_day);

        DayCountConvention getDayCountConvention();
        HolidayCalendar getHolidayCalendar();
        bool getAdjustBusinessDay();

        bool isWeekEnd(const DateTime& reference_date);
        DateTime getNextBusinessDay(const DateTime& reference_date);
        double getYearFraction(const DateTime& start, const DateTime& end);
        DateTime getForwardDateTime(const DateTime& reference_date, const Tenor& tenor); 
        std::vector<DateTime> getDateTimeSequence(const DateTime& reference_date, const Tenor& frequence, const Tenor& maturity);

    private: 
        bool adjust_business_day_; 
        HolidayCalendar holiday_calendar_; 
        DayCountConvention day_count_convention_;

        DateTime getNextBusinessDayNone(const DateTime& reference_date);
};

