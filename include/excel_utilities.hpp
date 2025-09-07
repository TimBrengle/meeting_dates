#pragma once
#include <string>
#include <xlnt/xlnt.hpp>

// Read a cell from a workbook by sheet name and cell address
inline std::string read_cell(xlnt::workbook &wb, const std::string &sheet, const std::string &cell)
{
    auto ws = wb.sheet_by_title(sheet);
    return ws.cell(cell).to_string();
}

// Write a value to a cell
inline void write_cell(xlnt::workbook &wb, const std::string &sheet,
                       const std::string &cell, const std::string &value)
{
    auto ws = wb.sheet_by_title(sheet);
    ws.cell(cell).value(value);
}

// Insert value into a row/column position (0-based)
inline void write_cell(xlnt::workbook &wb, const std::string &sheet,
                       std::size_t row, std::size_t col, const std::string &value)
{
    auto ws = wb.sheet_by_title(sheet);
    ws.cell(row + 1, col + 1).value(value); // xlnt uses 1-based indexing
}
