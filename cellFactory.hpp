#pragma once
#include "cell.hpp"
#include <string>
class CellFactory
{
public:
	static Cell* createCell(const std::string& input);
};

