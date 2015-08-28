#ifndef FILE_H
#define FILE_H

#include "Definitions.h"
#include <fstream>

class CFile
{
	public:
	CFile();
	~CFile();

	int Open(string filename);
	int Close();
	string Read_Variable(string variable, int Secondary);
	string Read_All();
	void Write(string input);
	void Wipe_All();
	string fname;
	std::fstream File;
};

#endif // FILE_H