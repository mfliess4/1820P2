/*	Project:    Frankenmap
	Name:       Michael Fliess
    Partner:    PARTNER'S NAME IF ANY
    Class:      example: CSC 1820 - MF Section
*/

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

class Node
{
  public:
	Node()
	{
		frequency = 1;
	}

	int frequency;
	vector<int> appears_on_lines;
};

//Main starts

int main(int argc, char *argv[])
{

	//checks for filename entry
	char *tester = nullptr;
	tester = argv[1];

	if (argc < 2)
	{
		cout << "Must provide name of input file." << endl;
		return 1;
	}

	//string filenametest = "words.txt";

	//checks for opening
	ifstream instream;

	instream.open(tester);

	if (!instream.is_open())
	{
		cout << "Unable to open " << tester << endl;
		return 1;
	}
	else if (instream.is_open())
	{
		//cout << tester << " opened successfully. " << endl;
	}

	//Mapping start

	map<string, Node> entryMap;
	string wordToEnter = "";
	Node defaultNode;
	int lineNumber = 1;
	vector<int> lineNums;
	pair<string, Node> entryPair;
	Node entryNode;

	while (!instream.eof())
	{
		instream >> wordToEnter;
		auto iter = entryMap.find(wordToEnter);

		if (iter == entryMap.end())
		{
			entryMap.emplace(wordToEnter, defaultNode);
			entryNode = entryMap.at(wordToEnter);
			//cout << "word placed" << endl;
			//cout << lineNumber << endl;

			lineNums = entryNode.appears_on_lines;
			lineNums.push_back(lineNumber);
			entryNode.appears_on_lines = lineNums;

			entryMap.at(wordToEnter) = entryNode;
			//cout << (entryMap.at(wordToEnter))->first; //Will not work becasue the string is hash key
		}
		else if (iter != entryMap.end())
		{
			entryNode = entryMap.at(wordToEnter);
			entryNode.frequency++;

			lineNums = entryNode.appears_on_lines;
			lineNums.push_back(lineNumber);
			entryNode.appears_on_lines = lineNums;

			entryMap.at(wordToEnter) = entryNode;
		}

		lineNumber++;
	}

	//Map searching start

	string searcher = "";
	vector<int> outputVector;

	while (7 != 4) //intentionally creates infine loop
	{
		cout << "Enter a word (case sensitive): ";
		getline(cin, searcher);
		//cout << endl;
		auto iter2 = entryMap.find(searcher);

		if (iter2 == entryMap.end())
		{
			cout << "Could not locate: " << searcher << endl;
		}
		else
		{
			cout << searcher << " found " << entryMap.at(searcher).frequency << " times on lines: " << endl;
			outputVector = entryMap.at(searcher).appears_on_lines;

			for (unsigned int i = 0; i < outputVector.size(); i++)
			{
				cout << outputVector.at(i) << ",";
			}
		}

		cout << endl;
	}

	// This causes the program to pause at its completion.
	{
		char c;
		cout << "Hit enter to exit:";
		cin.get(c);
	}
	return 0;
}