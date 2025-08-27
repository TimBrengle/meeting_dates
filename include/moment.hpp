#pragma once

#include <string>
#include <ctime>
#include <stdexcept>
#include <xlnt/xlnt.hpp>
#include "excel_utilities.hpp"

using namespace ExcelUtilities;

namespace mtgs
{

const std::string DateFmt == "%m/%d/%Y %H:%M";

class Moment
{
public:
    std::time_t point{0};
    std::tm parsed{0};
    std::string date_str{""};
    std::string calref{""};
    excel_serial serial{0};

    Moment()
    : point(0)
    {}

    explicit Moment(const std::time_t& p)
    : point(p)
    {
	localtime_r(t, parsed);
	date_str = to_string(parsed);
	calref = mkref(parsed);
	serial = mkserial(point);
    }

    explicit Moment(const std::tm& t)
    : parsed(t)
    {
	point = mktime(&parsed);
	date_str = to_string(&parsed);
	calref = mkref(&parsed);
	serial = mkserial(point);
    }

    explicit Moment(const std::string& str)
    {
        // Format time from Calendar cell
        if (strptime(
		str.c_str(),
		DateFmt,
		&parsed))
        {
            point = mktime(&parsed);
	    date_str = to_string(&parsed);
	    calref = mkref(&parsed);
	    excel = mkserial(point);
        }
        else
        {
            throw std::runtime_error(
		"Unsupported date string format: "
		+ str);
        }
    }

    explicit Moment(const excel_serial& s)
    {
        // Excel's serial date handling
	// (1900-based, includes leap year bug)
	
	// 1899-12-31 UTC
        const time_t excel_epoch = -2209161600;
        point = excel_epoch
	    + static_cast<time_t>(serial * 86400);
    }

    std::time_t value() const
    {
	 return point;
    }

    std::string to_string() const
    {
        char buf[32];
        localtime_r(&point, &parsed);
        strftime(buf,
		 sizeof(buf),
		 DateFmt,
		 &parsed);
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
};

static const std::string month_abbr[] =
{
    // Excel uses January = 0
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Map date -> calref
inline std::string to_calref(const std::time_t& t)
{
    // Convert to calendar date
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
