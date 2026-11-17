#include "table.hpp"
#include "cellTypes.hpp"

void Table::freeMemory() {
	if (grid!= nullptr)
	{
		for (size_t i = 0; i < rows; ++i)
		{
			if (grid[i]!=nullptr)
			{
				for (size_t j = 0; j < cols; ++j)
				{
					delete grid[i][j];
				}
				delete[] grid[i];
			}
		}
		delete[] grid;
	}
	grid = nullptr;
	rows = 0;
	cols = 0;
}

void Table::copyFrom(const Table& other) {
	rows = other.rows;
	cols = other.cols;

	if (rows==0||cols==0)
	{
		grid = nullptr;
		return;
	}
	grid = new Cell** [rows];
	for (size_t i = 0; i < rows; ++i)
	{
		grid[i] = new Cell * [cols];
		for (size_t j = 0; j < cols; ++j)
		{
			if (other.grid[i][j]!=nullptr)
			{
				grid[i][j] = other.grid[i][j]->clone();
			}
			else
			{
				grid[i][j] = new emptyCell();
			}
		}
	}
 }

Table::Table() :grid(nullptr), rows(0), cols(0) {
	resize(3, 3);
}
Table ::~Table() {
	freeMemory();
}
Table::Table(const Table& other) :grid(nullptr), rows(0), cols(0) {
	copyFrom(other);
}
Table& Table::operator=(const Table& other) {
	if (this != &other) { 
		freeMemory();     
		copyFrom(other);  
	}
	return *this;
}
void Table::setCell(size_t  r, size_t c, Cell* newCell) {
	if (r>=rows||c>=cols)
	{
		size_t newRows = (r >= rows) ? r + 1 : rows;
		size_t newCols = (c >= cols) ? c + 1 : cols;
		resize(newRows, newCols);
	}
	delete grid[r][c];
	grid[r][c] = newCell;
}
const Cell* Table::getCell(size_t r, size_t c) const
{
	if (r>=rows||c>=cols)
	{
		return nullptr;
	}
	return grid[r][c];
}
void Table::resize(size_t newRows, size_t newCols) {
	Cell*** newGrid = new Cell * *[newRows];
	for (size_t i = 0; i < newRows; ++i)
	{
		newGrid[i] = new Cell * [newCols];
		for (size_t j = 0; j < newCols; ++j)
		{
			if (i<rows&&j<cols)
			{
				newGrid[i][j] = grid[i][j];
			}
			else
			{
				newGrid[i][j] = new emptyCell();
			}
		}
	}
	if (grid!= nullptr)
	{
		for (size_t i = 0; i < rows; ++i)
		{
			delete[] grid[i];
		}
		delete[]grid;
	}
	grid = newGrid;
	rows = newRows;
	cols = newCols;
}
void Table::printTable(std::ostream& os)const {
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			if (grid[i][j] != nullptr)
			{
				std::string raw = grid[i][j]->getRawText();
				if (!raw.empty() && raw[0] == '=') {
					os << grid[i][j]->getValue(*this);
				}
				else {
					grid[i][j]->print(os);
				}
			}
			else
			{
				os << "";
			}
			if (j < cols - 1) {
				os << "\t| ";
			}
		}
		os << "\n";
	}
}

void Table::clear() {
	freeMemory();
	rows = 0;
	cols = 0;
}

size_t Table::getRows() const
{
	return rows;
}

size_t Table::getCols() const
{
	return cols;
}