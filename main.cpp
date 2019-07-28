
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

struct Option
{

	std::string Name;
	int NextLine;

};

struct Line
{

	std::string Text;
	std::vector<Option> Options;

};

int main()
{

	std::vector<Line> Lines = std::vector<Line>();

	std::ifstream File("game.txt");

	if (File.is_open())
	{

		std::string TextLine;

		while (std::getline(File, TextLine))
		{

			Line NewLine;
			NewLine.Options = std::vector<Option>();

			int Split = TextLine.find('|');

			if (Split > 0)
			{

				NewLine.Text = TextLine.substr(0, Split);
				
				std::string Ops = TextLine.substr(Split + 1);

				std::istringstream iss(Ops);
				std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

				for (std::string o : results)
				{

					Split = o.find(":");

					if (Split > 0)
					{

						NewLine.Options.push_back((Option) {o.substr(0, Split), std::stoi(o.substr(Split + 1)) - 1});

					}

				}

			}
			else
			{

				NewLine.Text = TextLine;

			}

			Lines.push_back(NewLine);

		}

		File.close();

	}

	bool GameOn = true;
	int CurrentLine = 0;

	while (GameOn)
	{

		if (Lines[CurrentLine].Options.size() == 0)
		{

			std::cout << Lines[CurrentLine].Text << std::endl;
			GameOn = false;

		}
		else
		{

			std::string OutString = Lines[CurrentLine].Text + " (";
			bool FirstLine = true;

			for (Option o : Lines[CurrentLine].Options)
			{

				if (FirstLine)
				{

					OutString += o.Name;
					FirstLine = false;

				}
				else
				{

					OutString += "/" + o.Name;

				}

			}

			OutString += "): ";
			std::string InString;

			std::cout << OutString;
			std::getline(std::cin, InString);

			for (Option o : Lines[CurrentLine].Options)
			{

				if (InString == o.Name) CurrentLine = o.NextLine;

			}

		}

	}

	return 0;

}
