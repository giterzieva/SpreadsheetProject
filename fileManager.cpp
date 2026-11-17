#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

#include "table.hpp"       
#include "fileManager.hpp" 
#include "cellFactory.hpp" 

fileManager::fileManager() : currentFilePath("") {}

void fileManager::loadFromFile(const std::string& filePath, Table& tableContext) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("File cannot be open! " + filePath);
    }
    tableContext.clear();

    std::string line;
    int rowIndex = 0;

    while (std::getline(file, line)) {
        int colIndex = 0;
        size_t startPos = 0;

        while (startPos < line.length()) {
            size_t commaPos = line.find(',', startPos);
            std::string cellValue;

            if (commaPos != std::string::npos) {
                cellValue = line.substr(startPos, commaPos - startPos);
                startPos = commaPos + 1;
            }
            else {
                cellValue = line.substr(startPos);
                startPos = line.length();
            }

            if (!cellValue.empty()) {
                size_t first = cellValue.find_first_not_of(" \t");
                size_t last = cellValue.find_last_not_of(" \t");
                if (first != std::string::npos && last != std::string::npos) {
                    cellValue = cellValue.substr(first, (last - first + 1));
                }
                else {
                    cellValue = "";
                }
            }
            Cell* newCell = CellFactory::createCell(cellValue);
            tableContext.setCell(rowIndex, colIndex, newCell);

            colIndex++;
        }

        if (!line.empty() && line.back() == ',') {
            Cell* emptyCell = CellFactory::createCell("");
            tableContext.setCell(rowIndex, colIndex, emptyCell);
        }

        rowIndex++;
    }

    file.close();
    currentFilePath = filePath;
    std::cout << "File loaded successfully! " << filePath << "\n";
}

void fileManager::saveToFile(const Table& tableContext) {
    if (!hasOpenedFile()) {
        throw std::runtime_error("No opened file to save to! Use 'saveas' first.");
    }
    saveAsToFile(currentFilePath, tableContext);
}

void fileManager::saveAsToFile(const std::string& filePath, const Table& tableContext) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("File cannot be open for writing! " + filePath);
    }

    size_t maxRows = tableContext.getRows();
    size_t maxCols = tableContext.getCols();

    for (size_t i = 0; i < maxRows; ++i) {
        for (size_t j = 0; j < maxCols; ++j) {

            const Cell* currentCell = tableContext.getCell(i, j);

            if (currentCell != nullptr) {
                file << currentCell->getRawText();
            }

            if (j < maxCols - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
    currentFilePath = filePath;
    std::cout << "File saved successfully! " << filePath << "\n";
}

bool fileManager::hasOpenedFile() const {
    return !currentFilePath.empty();
}

std::string fileManager::getCurrentPath() const {
    return currentFilePath;
}