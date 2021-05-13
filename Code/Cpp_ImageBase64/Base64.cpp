#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

void ImageTobinary(std::string ImageName) noexcept(false);
void Base64ToImage() noexcept(false);
std::string Base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void ImageTobinary(std::string ImageName) noexcept(false)
{
	std::string binary, Base64_string;
	int i = 0, flag = 0;
	char c;
	std::ifstream f;
	std::ofstream g;
	f.open(ImageName, std::ios::binary);
	g.open("Base_64Encoded.txt");
	if (f.is_open() && g.is_open())
	{
		while (f.get(c))
		{
			binary = binary + std::bitset<8> (int(c)).to_string();
		}

		//std::cout<<binary;  
		if (binary.length() % 6 == 2)
		{
			binary.append("0000");
			flag = 2;
		}

		if (binary.length() % 6 == 4)
		{
			binary.append("00");
			flag = 1;
		}

		while (i < binary.length())
		{
			Base64_string = Base64_string + Base64[stoi(binary.substr(i, 6), 0, 2)];
			i = i + 6;
		}

		if (flag == 1)
		{
			Base64_string.append("=");
		}
		if (flag == 2)
		{
			Base64_string.append("==");
		}
		g << Base64_string;
		f.close();
		g.close();
	}
	else
	{
		throw std::string("unable to open file");
	}
}

void Base64ToImage() noexcept(false)
{
	std::ifstream g;
	std::ofstream f;
	std::string base64_file_binary, Image_char;
	char c;
	g.open("Base_64Encoded.txt");
	f.open("Decoded_Image.png", std::ios::binary);
	if (f.is_open() && g.is_open())
	{
		while (g.get(c))
		{
			if (c == '=')
				continue;
			base64_file_binary = base64_file_binary + std::bitset<6> (Base64.find(c)).to_string();
		}

		int i = 0;
		while (i < base64_file_binary.length())
		{
			Image_char = Image_char + char(stoi(base64_file_binary.substr(i, 8), 0, 2));
			i = i + 8;
		}

		f << Image_char;
	}
	else
	{
		throw std::string("Unable to open write file!!!");

	}

	f.close();
	g.close();
}

int main()
{
	std::string ImageName;
	std::cout<<"Enter Image Name:";
	std::cin>>ImageName;
	try
	{
		ImageTobinary(ImageName);
		Base64ToImage();
	}

	catch (std::string e)
	{
		std::cout << e;
	}
}