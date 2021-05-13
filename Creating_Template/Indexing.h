#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

void createIndexing(std::string fileName, std::string RowDelimeter, std::string IndexFilename) noexcept
{
	std::ifstream file;
	file.open(fileName);
	int pos = 0, RecordNo = 0, LastCallValue = 0;
	size_t lenght = 0;
	std::string s;
	std::ofstream Indexing;
	Indexing.open(IndexFilename, std::ios::out);
	while (getline(file, s) && RowDelimeter != "")
	{
		pos = 0;
		while (s[pos] != '\0')
		{
			lenght = s.find(RowDelimeter, pos);
			Indexing << RecordNo << ";" << pos + LastCallValue << ";" << (lenght + LastCallValue) - 1 << ";" << std::endl;
			RecordNo++;
			pos = lenght + RowDelimeter.length();
		}

		LastCallValue = LastCallValue + pos + 2;

	}

	file.close();
	Indexing.close();
}

void CreateTemplate(std::string TemplateFileName, std::string FileName, std::string ColumnDelimeter, std::string IndexFileName) noexcept
{
	std::fstream DatabaseFile, Indexfile;
	std::ifstream TemplatefileIn;
	std::ofstream TemplateFileOut;
	int initial = 0, k = 0;
	std::smatch match;
	std::regex r("(##)(.*?)(##)");
	std::string header;
	std::map<int, std::vector<std::string>> DataHeader;
	std::map<int, std::vector < int>> IndexHeader;
	std::vector<std::string > TemplateHeader;
	DatabaseFile.open(FileName);
	Indexfile.open(IndexFileName);

	//Extracting The Data from csv with the help of indexfile 

	while (getline(Indexfile, header) && ColumnDelimeter != "")
	{
		initial = 0;
		while (header[initial] != '\0')
		{
			size_t len = header.find(';', initial);
			IndexHeader[k].push_back(std::stoi(header.substr(initial, (len - initial))));
			initial = len + 1;
		}

		DatabaseFile.seekg(IndexHeader[k][1], std::ios::beg);
		char *ReadData = new char[(IndexHeader[k][2] - IndexHeader[k][1]) + 2];
		DatabaseFile.read(ReadData, (IndexHeader[k][2] - IndexHeader[k][1]) + 1);
		ReadData[(IndexHeader[k][2] - IndexHeader[k][1]) + 1] = '\0';
		header.assign(ReadData);
		header.append(ColumnDelimeter);
		initial = 0;
		while (header[initial] != '\0')
		{
			size_t len = header.find(ColumnDelimeter, initial);
			DataHeader[k].push_back(header.substr(initial, (len - initial)));
			initial = len + ColumnDelimeter.length();
		}

		k++;
		delete[] ReadData;
	}
	DatabaseFile.close();
	Indexfile.close();

	// Creating Template using template.txt
	TemplatefileIn.open(TemplateFileName);
	std::vector<std::string > HeaderData = DataHeader[0];
	DataHeader.erase(0);
	while (getline(TemplatefileIn, header))
	{
		TemplateHeader.push_back(header);
	}
	TemplatefileIn.close();

	for (auto x: DataHeader)
	{
		TemplateFileOut.open("C:\\Users\\sancheet_patil\\Desktop\\Indexing_of_file\\Generated_Template\\Record_" + x.second[0] + ".txt");
		for (auto t: TemplateHeader)
		{
			while (regex_search(t, match, r))
			{
				for (k = 0; k < HeaderData.size(); k++)
				{
					if (match.str(2) == HeaderData[k])
					{
						t.replace(match.position(0),match.str(0).length() , x.second[k]);
					}
				}
			}

			TemplateFileOut << t << std::endl;
		}

		TemplateFileOut.close();
	}
}