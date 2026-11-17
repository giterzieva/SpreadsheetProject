#include "cellTypes.hpp"
#include <cstdlib>
#include <stdexcept>

intCell:: intCell (int val) : value (val){}

void intCell::print(std::ostream& os) const {
	os << value;
}
double intCell::getValue(const Table& tableContext) const {
	return static_cast <double> (value);
}
Cell* intCell::clone() const {
	return new intCell(*this);
}

std::string intCell::getRawText() const {
	return std::to_string(value);
}

void emptyCell::print(std::ostream& os) const {
	os << "";
}
double emptyCell::getValue(const Table& tableContext)const {
	return 0.0;
}
Cell* emptyCell::clone()const {
	return new emptyCell(*this);
}

std::string emptyCell::getRawText() const {
	return "";
}

doubleCell::doubleCell(double val) : value(val) {}

void doubleCell::print(std::ostream& os) const {
	os << value;
}
double doubleCell::getValue(const Table& tableContext) const {
	return value;
}
Cell* doubleCell::clone() const {
	return new doubleCell(*this);
}
std::string doubleCell::getRawText() const {
	return std::to_string(value);
}

stringCell::stringCell(const std::string& txt): text(txt){}

void stringCell::print(std::ostream& os) const {
	os << text;
}
double stringCell::getValue(const Table& tableContext) const {
	try {
		return std::stod(text);
	}
	catch (...) {
		return 0.0;
	}	
}
Cell* stringCell::clone()const {
	return new stringCell(*this);
}
std::string stringCell::getRawText() const {
	if (text.size() >=2 && text.front()=='"'&& text.back()=='"')
	{
		return text;
	}
	return "\"" + text + "\"";
}