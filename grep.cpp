#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <ctype.h>
#define NO_OF_CHARS 256

std::vector<std::string > InputString;

void badCharHeuristic(std::string str, int size, int badchar[NO_OF_CHARS])
{
	int i;
	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;
	for (i = 0; i < size; i++)
		badchar[(int) str[i]] = i;
}

int search(std::string txt, std::string pat)
{
	int m = pat.size();
	int n = txt.size();
	int count = 0;
	int badchar[NO_OF_CHARS];

	badCharHeuristic(pat, m, badchar);

	int s = 0;

	while (s <= (n - m))
	{
		int j = m - 1;

		while (j >= 0 && pat[j] == txt[s + j])
			j--;
		if (j < 0)
		{
			count++;
			s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

		}
		else
			s = s + std::max(1, j - badchar[txt[s + j]]);
	}

	return count;
}

bool ReadFile(std::string FileName)
{
	std::ifstream f;
	std::string line;
	bool opened;
	f.open(FileName.c_str());
	if (f.is_open())
		opened = true;
	else
		return false;
	while (!f.eof())
	{
		getline(f, line);
		InputString.push_back(line);
	}

	f.close();
	return opened;
}

std::vector<std::string > check_flag(char *arg[])
{
	std::vector<std::string > flags;
	int i = 1, k = 1;
	while (arg[i])
	{
		char ch = arg[i][0];
		if (ch == '-')
		{
			flags.insert(flags.begin(), arg[i]);
		}
		else
		{
			flags.push_back(arg[i]);
		}

		i++;
	}

	return flags;
}

void NO_flag(std::string FindWord)
{
	int i = 0;
	while (i < InputString.size())
	{
		if (search(InputString[i], FindWord) > 0)
		{
			std::cout << InputString[i] << std::endl;
		}

		i++;
	}
}

bool LineSearch(std::string line, std::string FindWord, std::string flags)
{
	int visit = 0;
	bool present = false;
	if (flags.find("i") != std::string::npos)
	{
		transform(FindWord.begin(), FindWord.end(), FindWord.begin(), ::tolower);
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		if (search(line, FindWord) > 0)
		{
			present = true;
		}

		visit = 1;
	}

	if (flags.find("w") != std::string::npos)
	{
		size_t i_pos = line.find(FindWord);
		if (i_pos != std::string::npos && isspace(line[i_pos + FindWord.length()]) && isspace(line[(i_pos - 1 > -1) ? (i_pos - 1) : i_pos + FindWord.length()]))
		{
			present = true;
		}

		visit = 1;
	}

	if (visit == 1)
		return present;
	else
		return (search(line, FindWord) > 0) ? true : false;
}

void operation(std::vector<std::string > flags)
{
	int count = 0, i = 0;
	std::string line;
	if (flags[0][0] == '-')
	{
		if (flags.size() == 3)
		{
			while (i < InputString.size())
			{
				if (LineSearch(InputString[i], flags[1], flags[0]))
				{
					if (flags[0].find("c") != std::string::npos)
					{
						i++;
						count++;
						continue;
					}

					if (flags[0].find("n") != std::string::npos)
					{
						std::cout << i << ":" << InputString[i] << std::endl;
						i++;
						continue;
					}

					std::cout << InputString[i] << std::endl;
				}

				i++;
			}

			if (count > 0)
			{
				std::cout << count;
			}
		}
		else
		{
			getline(std::cin, line);
			if (search(line, flags[1]) > 0)
				std::cout << line << std::endl;
		}
	}
	else
	{
		NO_flag(flags[0]);
	}
}

int main(int argc, char *argv[])
{
	std::vector<std::string > flags;
	flags = check_flag(argv);
	ReadFile(flags[flags.size() - 1]);
	operation(flags);

}