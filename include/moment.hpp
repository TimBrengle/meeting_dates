#if 1
#pragma once
#include <ctime>
#include <string>

class Moment
{
public:
    // Construct a Moment representing "now"
    Moment();

    // Construct from a specific time_t value
    explicit Moment(std::time_t t);

    // Return formatted string (e.g., "%Y-%m-%d %H:%M:%S")
    std::string to_string(const char* format = "%Y-%m-%d %H:%M:%S") const;

    // Return number of full days since a given time_t
    static int days_since(std::time_t past);

    // Parse from string into Moment (throws on failure)
    static Moment parse(const std::string& str, const char* format = "%Y-%m-%d %H:%M:%S");

    // Access internal tm struct (read-only)
    const std::tm& get_tm() const;

    // Convert to raw time_t
    std::time_t to_time_t() const;

private:
    std::tm timeInfo{};
};
#else
#pragma once

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

class Moment
{
public:
    Moment()
    {
        std::time_t now = std::time(nullptr);
        localtime_r(&now, &timeInfo);
    }

    explicit Moment(std::time_t t)
    {
        localtime_r(&t, &timeInfo);
    }

    // Return formatted date/time as string
    std::string to_string(const char* format = "%Y-%m-%d %H:%M:%S") const
    {
        char buffer[64];
        std::strftime(buffer, sizeof(buffer), format, &timeInfo);
        return std::string(buffer);
    }

    // Return days since given timestamp
    static int days_since(std::time_t past)
    {
        std::time_t now = std::time(nullptr);
        return static_cast<int>((now - past) / (60 * 60 * 24));
    }

    // Parse a string into a Moment using given format
    static Moment parse(const std::string& str, const char* format = "%Y-%m-%d %H:%M:%S")
    {
        std::tm parsed{};  // not const — must be mutable
        std::istringstream ss(str);
        ss >> std::get_time(&parsed, format);
        std::time_t point = std::mktime(&parsed);

        return Moment(point);
    }

    // Access raw tm
    const std::tm& get_tm() const
    {
        return timeInfo;
    }

    std::time_t to_time_t() const
    {
        return std::mktime(const_cast<std::tm*>(&timeInfo));
    }

private:
    std::tm timeInfo{};
};
#endif
