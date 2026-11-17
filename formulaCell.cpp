#include "formulaCell.hpp"
#include "table.hpp"
#include <iostream>

formulaCell::formulaCell(const std::string& text) : formulaText(text){}

void formulaCell::print(std::ostream& os)const {
	os << formulaText;
}
Cell* formulaCell::clone()const {
	return new formulaCell(*this);
}

bool formulaCell::isDigit(char c) const {
	return c >= '0' && c <= '9';
}

double formulaCell::parseOperand(const std::string& token, const Table& tableContext) const {
	if (token.empty())
	{
		return 0.0;
	}
	if ((token[0] == 'R' || token[0] == 'r'))
	{
		size_t charPosition = token.find('C');
		if (charPosition != std::string::npos) //npos - from <string> library
		{
			int row = 0;
			for (size_t i = 1; i < charPosition; ++i)
			{
				if (isDigit(token[i]))
				{
					row = row * 10 + (token[i] - '0');
				}
			}
			int col = 0;
			for (size_t i = charPosition + 1; i < token.length(); ++i)
			{
				if (isDigit(token[i]))
				{
					col = col * 10 + (token[i] - '0');
				}
			}
			const Cell* cell = tableContext.getCell(row, col);
			if (cell)
				return cell->getValue(tableContext);
			else
				return 0.0;
			//grid starts from 0 so we subtract 1
		}
	}
	double val = 0.0;
	double divisor = 10.0;
	bool foundDot = false;
	size_t start = (token[0] == '-' || token[0] == '+') ? 1 : 0;

	for (size_t i = start; i < token.length(); ++i)
	{
		if (token[i] == '.')
		{
			foundDot = true;
			continue;
		}
		if (!foundDot)
		{
			val = val * 10 + (token[i] - '0');
		}
		else
		{
			val = val + (token[i] - '0') / divisor;
			divisor *= 10.0;
		}
	}
	if (token[0] == '-')
		val = -val;
	return val;
}
double formulaCell::getValue(const Table& tableContext)const {
	std::string expr = formulaText.substr(1);

	std::string cleanExpr = "";
	for (size_t i = 0; i < expr.length(); ++i)
	{
		if (expr[i]!= ' ')
		{
			cleanExpr += expr[i];
		}
	}
	char op = ' '; //op - operator
	size_t opPosition = std::string::npos;
	char operators[] = { '+','-','*','/' };

	for (size_t i = 0; i < 4; ++i)
	{
		size_t position = cleanExpr.find(operators[i]);
		if (position != std::string::npos && position>0)
		{
			op = operators[i];
			opPosition = position;
			break;
		}
	}
	if (opPosition == std::string::npos)
	{
		return parseOperand(cleanExpr, tableContext);
	}
	std::string leftToken = cleanExpr.substr(0, opPosition);
	std::string rightToken = cleanExpr.substr(opPosition + 1);

	double leftVal = parseOperand(leftToken, tableContext);
	double rightVal = parseOperand(rightToken, tableContext);

	if (op=='+')
	{
		return leftVal + rightVal;
	}
	if (op == '-')
	{
		return leftVal - rightVal;
	}
	if (op == '*')
	{
		return leftVal * rightVal;
	}
	if (op == '/')
	{
		if (rightVal==0.0)
		{
			throw std::runtime_error("You can't devide by 0!");
		}
		return leftVal / rightVal;
	}
	return 0.0; //ensuring to return something if none match the given operations
}

std::string formulaCell::getRawText() const {
	return formulaText;
}