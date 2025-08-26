#pragma once

#include <string>
#include <vector>
#include <xlnt/xlnt.hpp>

// Utility functions for working with Excel files using xlnt
namespace ExcelUtilities
{
    // Open a workbook from a file
    inline xlnt::workbook openWorkbook(const std::string &filename)
    {
        xlnt::workbook wb;
        wb.load(filename);
        return wb;
    }

    // Save a workbook to a file
    inline void saveWorkbook(xlnt::workbook &wb, const std::string &filename)
    {
        wb.save(filename);
    }

    // Get a worksheet by name
    inline xlnt::worksheet getSheet(xlnt::workbook &wb, const std::string &sheetName)
    {
        return wb.sheet_by_title(sheetName);
    }

    // Read a cell value as string
    inline std::string readCell(xlnt::worksheet &ws, const std::string &cellRef)
    {
        auto cell = ws[cellRef];
        if (cell.has_value())
        {
            return cell.to_string();
        }
        return "";
    }

    // Write a string value into a cell
    inline void writeCell(xlnt::worksheet &ws, const std::string &cellRef, const std::string &value)
    {
        ws[cellRef].value(value);
    }

    // Write an integer value into a cell
    inline void writeCell(xlnt::worksheet &ws, const std::string &cellRef, int value)
    {
        ws[cellRef].value(value);
    }

    // Write a double value into a cell
    inline void writeCell(xlnt::worksheet &ws, const std::string &cellRef, double value)
    {
        ws[cellRef].value(value);
    }

    // Find the first cell in a worksheet that matches a string
    inline std::string findCell(xlnt::worksheet &ws, const std::string &text)
    {
        for (auto row : ws.rows(false))
        {
            for (auto cell : row)
            {
                if (cell.has_value() && cell.to_string() == text)
                {
                    return cell.reference().to_string();
                }
            }
        }
        return "";
    }

    // Get all values from a column as strings
    inline std::vector<std::string> readColumn(xlnt::worksheet &ws, const std::string &colLetter)
    {
        std::vector<std::string> values;
        for (auto row : ws.rows(false))
        {
            auto cell = row.front();
            if (cell.column().column_string() == colLetter && cell.has_value())
            {
                values.push_back(cell.to_string());
            }
        }
        return values;
    }

    // Get all values from a row as strings
    inline std::vector<std::string> readRow(xlnt::worksheet &ws, int rowIndex)
    {
        std::vector<std::string> values;
        for (auto cell : ws[rowIndex])
        {
            if (cell.has_value())
            {
                values.push_back(cell.to_string());
            }
        }
        return values;
    }
}
