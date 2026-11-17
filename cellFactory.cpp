#include "cellFactory.hpp"
#include "cellTypes.hpp"
#include "cell.hpp"
#include "formulaCell.hpp"


Cell* CellFactory::createCell(const std::string& input) {
	if (input.empty())
	{
		return new emptyCell();
	}
	if (input[0] ==  '=')
	{
		return new formulaCell(input);
	}
	if (input.front()=='"'&& input.back()=='"')
	{
		std::string cleanText = input.substr(1, input.length() - 2);
		return new stringCell(cleanText);
	}
	bool hasDot = false;
	bool isNumeric = true;
	size_t start = (input[0] == '-' || input[0] == '+') ? 1 : 0;
	if (start == input.length()) {
		isNumeric = false;
	}
	
		for (size_t i = start; i < input.length(); ++i)
		{
			if (input [i]== '.')
			{
				if (hasDot)
				{
					isNumeric = false;
					break;
				}
				hasDot = true;
			}
			else if (input[i]<'0'||input[i]>'9')
			{
				isNumeric = false; 
				break;
			}

		}
		if (isNumeric)
		{
			if (hasDot)
			{
				double integerPart = 0.0;
				double fractionalPart = 0.0;
				double divisor = 10.0;
				bool foundDot = false;

				for (size_t i = start; i < input.length(); ++i)
				{
					if ((input[i] == '.'))
					{
						foundDot = true;
						continue;
					}
					if (!foundDot)
					{
						integerPart = integerPart * 10.0 + (input[i] - '0');
					}
					else
					{
						fractionalPart += (input[i] - '0') / divisor;
						divisor *= 10.0;
					}
				}
				double finalDouble = integerPart + fractionalPart;
				if (input[0]=='-')
				{
					finalDouble = -finalDouble;
				}
				return new doubleCell(finalDouble);
			}
			else
			{
				int finalInt = 0;
				for (size_t i = start; i < input.length(); ++i)
				{
					finalInt = finalInt * 10 + (input[i] - '0');
				}
				if (input[0]=='-')
				{
					finalInt = -finalInt;
				}
				return new intCell(finalInt);
			}
		}
		return new stringCell(input);
}
