#include <iostream>
#include "../../include/cpp-datetime/errors.hpp"

EndDateBeforeStartDateError::EndDateBeforeStartDateError(): message_(getMessageAsString()){}
const char* EndDateBeforeStartDateError::what() const noexcept {return message_.c_str();}
std::string EndDateBeforeStartDateError::getMessageAsString() const{return "The end date cannot be before the start date when compputing year fraction.";}

NegativeEpochTimestampError::NegativeEpochTimestampError(): message_(getMessageAsString()){};
const char* NegativeEpochTimestampError::what() const noexcept {return message_.c_str();};
std::string NegativeEpochTimestampError::getMessageAsString() const{return "The epoch timestamp cannot be negative.";}

UndefinedHolidayCalendarError::UndefinedHolidayCalendarError(): message_(getMessageAsString()){};
const char* UndefinedHolidayCalendarError::what() const noexcept {return message_.c_str();};
std::string UndefinedHolidayCalendarError::getMessageAsString() const{return "The holiday calendar has no method mapped. Method NONE is used.";}