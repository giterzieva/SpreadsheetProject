#pragma once
#include <iostream>
#include <string>

class Table;

class Cell {
public:
	Cell() = default;
	virtual ~Cell() = default;

	virtual void print(std::ostream& os) const = 0;
	virtual double getValue(const Table& tableContext) const = 0;
	virtual Cell* clone() const = 0;
	virtual std::string getRawText() const = 0;
};