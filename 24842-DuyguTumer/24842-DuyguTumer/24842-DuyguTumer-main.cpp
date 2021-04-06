#include "24842-DuyguTumer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	ifstream text, text2;
	string fileName, line, cityName, fileName2, line2;
	int x, y;
	float radius;
	
	/*cout << "Please enter file name: ";
	cin >> fileName;*/
	fileName = "cities.txt";

	text.open(fileName);

	while (text.fail())
	{
		cout << "Cannot find a file named " << fileName << endl;
		cout << "Please enter file name: ";
		cin >> fileName;
		text.open(fileName);
	}	

	quadTree duygu = quadTree();
	
	getline(text, line);
	istringstream input_file (line);

	input_file >> x;
	input_file >> y;

	duygu.setBoundary(x, y);

	while(getline(text, line))
	{
		//Point cityCoord;
		istringstream input_file (line); 
		
		// taking the values from the file
		input_file >> cityName;
		
		input_file >> x;
		
		input_file >> y;

		quadNode* temp = new quadNode();
		temp->cityName = cityName;
		temp->coo.x = x;
		temp->coo.y = y;

		duygu.insert(temp);
	}
	text.clear();
	text.seekg(0);

	duygu.pretty_print();
	cout << endl;

    /////////////////////////////////////////////////////////////////////////

	/*cout << "Please enter file name: ";
	cin >> fileName2;*/
	fileName2 = "queries.txt";

	text2.open(fileName2);

	while (text2.fail())
	{
		cout << "Cannot find a file named " << fileName2 << endl;
		cout << "Please enter file name: ";
		cin >> fileName2;
		text2.open(fileName2);
	}	

	string temp;
	// Get the line
	while(getline(text2, line2))
	{
		//inputfile2 has the whole line
		istringstream input_file2 (line2);

		getline(input_file2, temp, ','); // get the first element of the line
		x = stoi(temp);

		getline(input_file2, temp, ','); // get the second element of the line
		y = stoi(temp);

		getline(input_file2, temp, ','); // get the last element of the line
		radius = stof(temp);

		Point berk(x,y);
		duygu.search(berk, radius);
	}
	text2.clear();
	text2.seekg(0);

	text.close();	
	text2.close();	
	return 0;
}