#pragma once
#include <string>
#include "moment.hpp"

namespace ExcelUtilities
{
    std::string read_cell(const std::string& filename,
                          const std::string& sheet,
                          const std::string& cell);

    void write_cell(const std::string& filename,
                    const std::string& sheet,
                    const std::string& cell,
                    const std::string& value);

    void update_meeting_date(const std::string& filename,
                             const std::string& sheet,
                             const std::string& cell,
                             const Moment& when);
}
