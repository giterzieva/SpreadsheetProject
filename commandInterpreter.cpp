#include "commandInterpreter.hpp"
#include "cellFactory.hpp"
#include <iostream>
#include <stdexcept>

CommandInterpreter::CommandInterpreter() : isRunning(true) {}

void CommandInterpreter::run()
{
    std::string input;
    std::cout << "Welcome to the Spreadsheet App!\n";
    std::cout << "Available commands: open <file>, save, saveas <file>, print, edit <row> <col> <value>, exit\n\n";

    while (isRunning)
    {
        std::cout << "> ";
        if (!std::getline(std::cin, input))
        {
            break;
        }

        if (input.empty()) {
            continue;
        }

        size_t spacePos = input.find(' ');
        std::string command;
        std::string arguments;

        if (spacePos == std::string::npos)
        {
            command = input;
            arguments = "";
        }
        else
        {
            command = input.substr(0, spacePos);
            arguments = input.substr(spacePos + 1);
        }

        try
        {
            if (command == "open")
            {
                handleOpen(arguments);
            }
            else if (command == "save")
            {
                handleSave();
            }
            else if (command == "saveas")
            {
                handleSaveAs(arguments);
            }
            else if (command == "print")
            {
                handlePrint();
            }
            else if (command == "edit")
            {
                handleEdit(arguments);
            }
            else if (command == "exit")
            {
                std::cout << "Exiting program. Goodbye!\n";
                isRunning = false;
            }
            else
            {
                std::cout << "Unknown command: " << command << "\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

void CommandInterpreter::handleOpen(const std::string& arguments)
{
    if (arguments.empty())
    {
        std::cout << "Usage: open <filepath>\n";
        return;
    }
    manager.loadFromFile(arguments, table);
}

void CommandInterpreter::handleSave()
{
    manager.saveToFile(table);
}

void CommandInterpreter::handleSaveAs(const std::string& arguments)
{
    if (arguments.empty())
    {
        std::cout << "Usage: saveas <filepath>\n";
        return;
    }
    manager.saveAsToFile(arguments, table);
}

void CommandInterpreter::handlePrint()
{
    table.printTable(std::cout);
}

void CommandInterpreter::handleEdit(const std::string& arguments)
{
    if (arguments.empty())
    {
        std::cout << "Usage: edit <row> <col> <value>\n";
        return;
    }

    size_t firstSpace = arguments.find(' ');
    if (firstSpace == std::string::npos)
    {
        std::cout << "Invalid edit arguments!\n";
        return;
    }

    std::string rowStr = arguments.substr(0, firstSpace);
    std::string rest = arguments.substr(firstSpace + 1);

    size_t secondSpace = rest.find(' ');
    std::string colStr = (secondSpace == std::string::npos) ? rest : rest.substr(0, secondSpace);
    std::string valueStr = (secondSpace == std::string::npos) ? "" : rest.substr(secondSpace + 1);

    try {
        int r = std::stoi(rowStr);
        int c = std::stoi(colStr);

        if (r < 0 || c < 0) {
            std::cout << "Error: Row and column indices cannot be negative!\n";
            return;
        }

        Cell* newCell = CellFactory::createCell(valueStr);
        table.setCell(static_cast<size_t>(r), static_cast<size_t>(c), newCell);
        std::cout << "Cell updated successfully!\n";
    }
    catch (const std::invalid_argument&) {
        std::cout << "Error: Row and column must be valid integers!\n";
    }
}