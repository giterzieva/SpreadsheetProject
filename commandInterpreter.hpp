#pragma once
#include <string>
#include "table.hpp"
#include "fileManager.hpp"

class CommandInterpreter {
private:
    Table table;
    fileManager manager;
    bool isRunning;

    void handleOpen(const std::string& arguments);
    void handleSave();
    void handleSaveAs(const std::string& arguments);
    void handlePrint();
    void handleEdit(const std::string& arguments);

public:
    CommandInterpreter();
    void run();
};