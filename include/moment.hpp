#pragma once

#include <string>
#include <ctime>
#include <stdexcept>
#include <xlnt/xlnt.hpp>
#include "excel_utilities.hpp"

namespace mtgs
{

const std::string DateFmt == "%m/%d/%Y %H:%M";

class Moment
{
public:
    std::time_t point;
    std::tm parsed;
    std::string date_str;
    std::string calref;

    Moment()
    : point(0)
    {}

    explicit Moment(std::time_t t)
    : point(t)
    {}

    explicit Moment(const std::string &str)
    {
        struct tm tm{};
        // Format of time in Calendar cell
        if (strptime(str.c_str(), DateFmt, &tm))
        {
            point = mktime(&tm);
        }
        else
        {
            throw std::runtime_error(
		"Unsupported date string format: "
		+ str);
        }
    }

    explicit Moment(double excel_serial)
    {
        // Excel's serial date handling
	// (1900-based, includes leap year bug)
	
	// 1899-12-31 UTC
        const time_t excel_epoch = -2209161600;
        point = excel_epoch
	    + static_cast<time_t>(
		excel_serial * 86400);
    }

    time_t value() const
    {
	 return point;
    }

    std::string to_string() const
    {
        char buf[32];
        struct tm tm{};
        localtime_r(&point, &tm);
        strftime(buf, sizeof(buf), DateFmt, &tm);
        return buf;
    }

    // --- static helpers ---

    static Moment from_cell(
		const xlnt::cell &cell)
    {
        switch (cell.data_type())
	{
	    case xlnt::cell_type::date:
            	auto dt =
		    cell.value<xlnt::datetime>();
            	std::tm tm{};
            	tm.tm_year = dt.year - 1900;
            	tm.tm_mon = dt.month - 1;
            	tm.tm_mday = dt.day;
            	tm.tm_hour = dt.hour;
            	tm.tm_min = dt.minute;
            	tm.tm_sec = dt.second;
            	time_t t = mktime(&tm);
            	return Moment(t);
	    case xlnt::cell_type::number:
                return Moment(
		    cell.value<double>());
	    case xlnt::cell_type::string:
                return Moment(
		    cell.value<std::string>());
	    default:
                throw std::runtime_error("Unsupported cell type for Moment");
        }
    }

private:
    time_t point;
};

static const std::string month_abbr[] =
{
    // Excel uses January = 0
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Map date -> calref
inline std::string to_calref(time_t t)
{
    // Convert to calendar date
    struct tm tm{};
    localtime_r(&t, &tm);

    // Map day-of-month to Excel row reference
    std::string row = itos(tm.tm_mday) + 1;

    // Map month to Excel column
    char col = 'B' + tm.tm_mon;
    std::string ref =
	    static_cast<std::string>(col) +
	    row;

    return ref;
}
