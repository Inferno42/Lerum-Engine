#include "File.h"
#include <ostream>

CFile::CFile()
{

}

CFile::~CFile()
{

}

int CFile::Open(string filename)
{
	fname = filename;
	File.open(filename.c_str(),std::ios::in | std::ios::out | std::ios::app);

	
	if(File.bad())
	{
#ifdef _DEBUG
		DevError("Bad File exception.");
		_DevErrorInfo();
#endif // _DEBUG
	}

	if(File.fail())
	{
		#ifdef _DEBUG
DevError("Failed to open File.");
		_DevErrorInfo();
		DevInfo("No such file by name %s detected, creating file.",fname.c_str());
		File.open(fname.c_str(),std::ios::in | std::ios::out | std::ios::app);

#endif // _DEBUG
	}

	if(File == NULL)
	{
		#ifdef _DEBUG
DevError("Failed to read File, File NULL.");
		_DevErrorInfo();
#endif // _DEBUG
	}

	if(File.good() && File.is_open() && File != NULL)
	{
//		DevInfo("Loaded %s successfully!", filename.c_str());
	}
	return 0;
}

int CFile::Close()
{
	File.close();
	return 0;
}

string CFile::Read_All()
{
	string final;
	string tmp;
	if(File == NULL)
	{
		#ifdef _DEBUG
DevError("Failed to read file, file NULL.");
		_DevErrorInfo();
#endif // _DEBUG
	}

		while(!File.eof())
		{
			getline(File,tmp);
			
		}

	return tmp;
}

string CFile::Read_Variable( string variable, int Secondary )
{
	bool found_variable = false;
	string tmp;
	string final;
	int varcount = 0;

	while(!File.eof())
	{
		getline(File,tmp);
		std::istringstream parser(tmp, std::istringstream::in);
		
		for(int i = 0; i <= Secondary; ++i)
		{
			parser >> final;

			if(final == variable && found_variable == false)
			{
				found_variable = true;
			}
			else if(final != variable && found_variable == false)
			{
				break;
			}
		}
		if(found_variable == true)
		{
			Close();
			Open(fname);
			return final;
		}
	}
	return "0";
}

void CFile::Write(string input)
{
//	File.close();
//	File.open(fname);
//	File.getline(File,tmp);
	File.write(input.c_str(),input.size());
}

void CFile::Wipe_All()
{
	File.close();
	File.open(fname.c_str(), std::ios::out | std::ios::trunc);
	File.close();
	File.open(fname.c_str(), std::ios::in | std::ios::out | std::ios::app);
}