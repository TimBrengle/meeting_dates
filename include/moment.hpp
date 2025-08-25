#pragma once

#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

class moment
{
public:
    // Default constructor: now
    moment();

    // Construct from time_t
    explicit moment(const std::time_t& tp);

    // Construct from std::tm
    explicit moment(const std::tm& tm);

    // Return as std::tm
    std::tm to_tm() const;

    // Return as time_t
    std::time_t to_time_t() const;

    // Return formatted string (default: "%Y-%m-%d %H:%M:%S")
    std::string to_string(const std::string& fmt = "%Y-%m-%d %H:%M:%S") const;

private:
    std::time_t timepoint_;
};
