#pragma once

class Menu
{
public:
	char option;
	int numberOfVertices;
	int **vertices;

	bool configGood;
	std::string filename;

	Menu();
	~Menu();

	int LoadFile(std::string &filename);
	int LoadFileTXT(std::string &filename);
	int LoadFileTSP(std::string &filename);
	int LoadFileATSP(std::string &filename);
	int GenerateMatrix(int numberOfVerts, bool sym);
};
