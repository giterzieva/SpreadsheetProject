# SpreadsheetProject
# Console Spreadsheet Engine (C++)

A console-based spreadsheet application built in C++ that replicates core features of MS Excel and Google Sheets. The program supports dynamic table resizing, multiple data types, CSV file handling, and real-time evaluation of mathematical formulas with cell references.

## Key Features

* **Dynamic Table Resizing:** Automatically expands rows and columns as new data is added.
* **Multiple Data Types:** Supports integers, floating-point numbers, character strings, and empty cells.
* **Real-Time Formula Evaluation:** Parses and calculates mathematical formulas (including references to other cells) on the fly whenever the table is printed, preventing stale or outdated values.
* **CSV File Support:** Reads and writes `.csv` files while properly handling whitespace and special characters.
* **Safe Console Menu:** Provides an interactive command-line menu with exception handling to prevent invalid user inputs from crashing the program.

## Architecture & Class Design

The project is built using Object-Oriented Programming (OOP) principles and manual memory management:

* **`cell` (Abstract Base Class):** Defines the core interface for all table cells and includes a virtual destructor for safe polymorphic cleanup. Derived classes implement specific data types and formulas.
* **`table`:** A dynamic 2D container that stores and manages cell pointers, automatically resizing when needed. Implements the **Rule of Four** (destructor, copy constructor, copy assignment operator, and default constructor) to ensure safe object lifecycle management.
* **`cellFactory`:** Detects the data type of user console input and instantiates the appropriate derived `cell` object.
* **`fileManager`:** Handles loading and saving `.csv` files, parsing delimiters, whitespace, and escape characters.
* **`CommandInterpreter`:** Manages the interactive console menu, validates commands, and handles exceptions safely.

## Project Structure

* `main.cpp` – Entry point of the application.
* `cell.hpp` / `cell.cpp` – Abstract base class for table cells.
* `cellTypes.hpp` / `cellTypes.cpp` – Derived classes for integers, floats, strings, and empty cells.
* `formulaCell.hpp` / `formulaCell.cpp` – Formula parsing and dynamic calculation logic.
* `cellFactory.hpp` / `cellFactory.cpp` – Factory class for creating cells from input.
* `table.hpp` / `table.cpp` – Dynamic 2D grid container.
* `fileManager.hpp` / `fileManager.cpp` – CSV file reader and writer.
* `commandInterpreter.hpp` / `commandInterpreter.cpp` – Console UI and error handling.
* `formulas.csv`, `test.csv`, `testOriginal.csv` – Sample spreadsheets for testing.

## How to Run

1. Clone or download this repository.
2. Open the project in **Visual Studio** (or compile all `.cpp` files using a C++ compiler such as `g++`):
   ```bash
   g++ *.cpp -o spreadsheet
   ./spreadsheet
   ```
3. Use the console menu to open one of the included sample files (e.g., `formulas.csv` or `test.csv`) and interact with the table.
