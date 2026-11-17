#pragma once
#include "cell.hpp"
#include <string>

class emptyCell : public Cell {
public:
	emptyCell() = default;
	virtual ~emptyCell() override = default;
	virtual void print(std::ostream& os) const override;
	virtual double getValue(const Table& tableContext) const override;
	virtual Cell* clone()const override;
	virtual std::string getRawText() const override;
};

class intCell : public Cell {
private:
	int value;
public:
	intCell(int val);
	virtual ~intCell() override = default;
	virtual void print(std::ostream& os) const override;
	virtual double getValue(const Table& tableContext) const override;
	virtual Cell* clone() const override;
	virtual std::string getRawText() const override;
};
class doubleCell : public Cell {
private:
	double value;
public:
	doubleCell(double val);
	virtual ~doubleCell() override = default;
	virtual void print(std::ostream& os) const override;
	virtual double getValue(const Table& tableContext) const override;
	virtual Cell* clone() const override;
	virtual std::string getRawText() const override;
};

class stringCell : public Cell {
private:
	std::string text;
public:
	stringCell(const std::string & txt);
	virtual ~stringCell() override = default;
	virtual void print(std::ostream & os) const override;
	virtual double getValue(const Table & tableContext) const override;
	virtual Cell* clone() const override;
	virtual std::string getRawText() const override;
};
