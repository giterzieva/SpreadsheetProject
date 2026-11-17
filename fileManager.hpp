#pragma once
#include <string>

class Table;

class fileManager
{
private:

	std::string currentFilePath;

public:
	fileManager();
	void loadFromFile(const std::string& filePath, Table& tableContext);
	void saveToFile(const Table& tableContext);
	void saveAsToFile(const std::string& filePath, const Table& tableContext);
	bool hasOpenedFile() const;

	std::string getCurrentPath()const;
};

