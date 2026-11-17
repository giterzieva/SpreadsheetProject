#pragma once
#include "cell.hpp"
#include <string>
class formulaCell: public Cell
{
private:
	std::string formulaText;
	double parseOperand(const std::string& token, const Table& tableContext) const;
	bool isDigit(char c) const;

public:
	formulaCell(const std::string& text);

	virtual void print(std::ostream& os) const override;
	virtual double getValue(const Table& tableConstext) const override;
	virtual Cell* clone() const override;
	std::string getRawText() const override; 
};

