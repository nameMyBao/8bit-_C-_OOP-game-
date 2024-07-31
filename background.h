#pragma once
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include<cctype>
#include<string>
#include<vector>
#include<sstream>
#include <iostream>
using namespace std;
using namespace sf;


void createbackground(const char* filename, std::vector<vector<Vector2i >> &bando)
{
	vector<Vector2i > tempMap;
	ifstream openfile(filename);
	bando.clear();
	if (openfile.is_open())
	{


		while (!openfile.eof())
		{
			string str, value;
			getline(openfile, str);
			stringstream stream(str);
			while (getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					string xx = value.substr(0, value.find(','));
					string yy = value.substr(value.find(',') + 1);

					int x, y, i, j;

					for (i = 0; i < xx.length(); i++)
					{
						if (!isdigit(xx[i])) {
							break;
						}
					}
					for (j = 0; j < yy.length(); j++)
					{
						if (!isdigit(yy[j])) {
							break;
						}
					}

					x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
					y = (j == yy.length()) ? atoi(yy.c_str()) : -1;
					tempMap.push_back(Vector2i(x, y));
				}
			}
			if (tempMap.size() > 0)
			{
				bando.push_back(tempMap);
				tempMap.clear();
			}
		}


	}

}


void setcoli(const char* filename, std::vector<vector<int >>& colmap)
{
	vector<int > tempMap;
	ifstream openfile(filename);
	colmap.clear();
	if (openfile.is_open())
	{
		while (!openfile.eof())
		{
			string str, value;
			getline(openfile, str);
			stringstream stream(str);
			while (getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					int a = atoi(value.c_str());
					tempMap.push_back(a);
					
					
				}
			}

			colmap.push_back(tempMap);
			tempMap.clear();
		}


	}

}
