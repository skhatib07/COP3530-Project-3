#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <chrono>
#include <math.h>
#include <cmath>
#include <windows.h>
#include <shellapi.h>
#include "MinHeap.h"
#include "OrderedMap.h"

#define degreesToRadians (M_PI / 180.0)

using namespace std;
float distance(float latitude1, float longitude1, float latitude2, float longitude2)
{
	float latitudeDistance = (latitude2 - latitude1) * degreesToRadians;
	float longitudeDistance = (longitude2 - longitude1) * degreesToRadians;

	float sideOne = pow(sin(latitudeDistance / 2.0), 2) + cos(latitude1 * degreesToRadians) * cos(latitude2 * degreesToRadians) * pow(sin(longitudeDistance / 2.0), 2);
	float sideTwo = 2 * atan2(sqrt(sideOne), sqrt(1 - sideOne));
	float dist = 3956 * sideTwo;

	return dist;
}

using namespace std;
int main() {
	float latitude = 29.6317805;
	float longitude = -82.37750439999999;
	int selection;
	cout << "Welcome to Vaccinapp!" << endl;
Start:
	cout << "Please Select from the Options Below:" << endl;
	cout << "1. Build Graph using Min Heap" << endl;
	cout << "2. Build Graph using Ordered Map" << endl;
	cout << "3. Compare Execution time for Min Heap vs. Ordered Map" << endl;
	cout << "4. Get User Coordinates" << endl;
	cout << "5. Edit Location" << endl;
	cout << "6. About the App" << endl;
	cout << "7. Documentation" << endl;
	cout << "8. Exit" << endl;
	cout << endl;

	cin >> selection;
	if (selection < 1 || selection > 8) {
		cout << "Your selection did not match one of the options provided." << endl;
		cout << "Would you like us to list them again?" << endl;
		string choice;
		cin >> choice;
		transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		if (choice == "yes" || choice == "1") {
			cout << endl;
			goto Start;
		}
		else {
			cout << "Ok, thank you for using Vaccinapp! The app will now close" << endl;
			return 0;
		}
	}
	// Find locations using MinHeap
	if (selection == 1) {
		ifstream data;
		data.open("data/FLVaccines.csv");
		if (!data.is_open()) {
			cout << "File not found, returning to menu." << endl;
			cout << endl;
			goto Start;
		}
		MinHeap* r = new MinHeap();

		string throwaway;
		getline(data, throwaway);
		string cellInfo;
		float lat1;
		float lon1;
		while (getline(data, cellInfo))
		{
			string in = "";
			stringstream lineStream(cellInfo);
			string cell;
			getline(lineStream, cell, '\t');
			lat1 = stof(cell);
			getline(lineStream, cell, '\t');
			lon1 = stof(cell);
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			r->insert(make_pair(distance(latitude, longitude, lat1, lon1), in));
		}
		float distance;
		string name, address, website;
		printf("|%5s|%5s|%5s|%5s|", "Distance", "Location Name", "Address", "Website");
		cout << endl;
		while (!r->isEmpty()) {
			pair<float, string> l = r->pop();
			distance = l.first;
			size_t found = l.second.find("#");
			name = l.second.substr(0, found);
			l.second = l.second.substr(found + 1);
			found = l.second.find("#");
			address = l.second.substr(0, found);
			l.second = l.second.substr(found + 1);
			found = l.second.find("#");
			website = l.second.substr(0, found);
			l.second = l.second.substr(found + 1);
			printf("|%5s|%5s|%5s|%5s|", distance, name, address, website);
			cout << endl;
		}
		cout << endl;

	}
	// Find locations using Ordered Map
	else if (selection == 2) {
		ifstream data;
		data.open("data/FLVaccines.csv");
		if (!data.is_open()) {
			cout << "File not found, returning to menu." << endl;
			cout << endl;
			goto Start;
		}
		OrderedMap* r = new OrderedMap();

		string throwaway;
		getline(data, throwaway);
		string cellInfo;
		float lat1;
		float lon1;
		while (getline(data, cellInfo))
		{
			string in = "";
			stringstream lineStream(cellInfo);
			string cell;
			getline(lineStream, cell, '\t');
			lat1 = stof(cell);
			getline(lineStream, cell, '\t');
			lon1 = stof(cell);
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			r->insert(distance(latitude, longitude, lat1, lon1), in);
		}
		vector<Node*> vect = r->inorderVector();
		float distance;
		string name, address, website;
		printf("|%5s|%5s|%5s|%5s|", "Distance", "Location Name", "Address", "Website");
		cout << endl;
		for (int i = 0; i < vect.size(); i++) {
			Node* l = vect.at(i);
			for (int i = 0; i < l->size(); i++) {
				distance = l->at(i).first;
				string sec = l->at(i).second;
				size_t found = sec.find("#");
				name = sec.substr(0, found);
				sec = sec.substr(found + 1);
				found = sec.find("#");
				address = sec.substr(0, found);
				sec = sec.substr(found + 1);
				found = sec.find("#");
				website = sec.substr(0, found);
				sec = sec.substr(found + 1);
				printf("|%5s|%5s|%5s|%5s|", distance, name, address, website);
			}
			cout << endl;
		}
		cout << endl;

	}
	// Comparing the two data structures
	else if (selection == 3) {
		ifstream data;
		data.open("data/FLVaccines.csv");
		if (!data.is_open()) {
			cout << "File not found. Cannot create Min Heap. Returning to menu." << endl;
			cout << endl;
			goto Start;
		}
		MinHeap* r = new MinHeap();
		OrderedMap* s = new OrderedMap();

		string throwaway;
		getline(data, throwaway);
		string cellInfo;
		float lat1;
		float lon1;
		auto begin_time_ = chrono::high_resolution_clock::now();
		// Minheap
		while (getline(data, cellInfo))
		{
			string in = "";
			stringstream lineStream(cellInfo);
			string cell;
			getline(lineStream, cell, '\t');
			lat1 = stof(cell);
			getline(lineStream, cell, '\t');
			lon1 = stof(cell);
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			r->insert(make_pair(distance(latitude, longitude, lat1, lon1), in));
		}
		auto stop_time_ = chrono::high_resolution_clock::now();
		auto time_difference_MinHeap = chrono::duration_cast<chrono::nanoseconds>(stop_time_ - begin_time_).count();
		data.close();

		data.open("data/FLVaccines.csv");
		if (!data.is_open()) {
			cout << "File not found. Cannot create Ordered Map. Returning to menu." << endl;
			cout << endl;
			goto Start;
		}

		getline(data, throwaway);
		begin_time_ = chrono::high_resolution_clock::now();
		// Ordered Map
		while (getline(data, cellInfo))
		{
			string in = "";
			stringstream lineStream(cellInfo);
			string cell;
			getline(lineStream, cell, '\t');
			lat1 = stof(cell);
			getline(lineStream, cell, '\t');
			lon1 = stof(cell);
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, '\t');
			in.append(cell);
			in.append("#");
			s->insert(distance(latitude, longitude, lat1, lon1), in);
		}
		stop_time_ = chrono::high_resolution_clock::now();
		auto time_difference_OrderedMap = chrono::duration_cast<chrono::nanoseconds>(stop_time_ - begin_time_).count();

		cout << "Time to insert values in MinHeap: " << time_difference_MinHeap << endl;
		cout << "Time to insert values into Ordered Map: " << time_difference_OrderedMap << endl;
		long long diff;
		if (time_difference_MinHeap > time_difference_OrderedMap)
			diff = time_difference_MinHeap - time_difference_OrderedMap;
		else
			diff = time_difference_OrderedMap - time_difference_MinHeap;

		cout << "Difference between two data structures: " << diff << endl;
		cout << endl;

	}
	// Print Latitude and Longitude
	else if (selection == 4) {
		cout << "Latitude: " << latitude << endl;
		cout << "Longitude: " << longitude << endl;
		cout << endl;
	}
	// Edit Latitude and Longitude
	else if (selection == 5) {
		cout << "Imput Latitude: ";
		float lat;
		cin >> lat;
		latitude = lat;
		cout << endl;
		cout << "Imput Longitude: ";
		float lon;
		cin >> lon;
		longitude = lon;
		cout << endl;
	}
	// Open about Page (README)
	else if (selection == 6) {
		ShellExecuteA(GetDesktopWindow(), "open", ".github\\README.md", NULL, NULL, SW_SHOWNORMAL);
	}
	// Open documentation
	else if (selection == 7) {
		ShellExecuteA(GetDesktopWindow(), "open", ".github\\Documentation.pdf", NULL, NULL, SW_SHOWNORMAL);
	}
	// Exit
	else if (selection == 8) {
		cout << endl;
		cout << "Ok, thank you for using Vaccinapp! The app will now close" << endl;
		return 0;
	}

	cout << endl;
	cout << "Would you like to select another option?" << endl;
	string choice;
	cin >> choice;
	transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
	if (choice == "yes" || choice == "1") {
		cout << endl;
		goto Start;
	}
	else {
		cout << "Ok, thank you for using Vaccinapp! The app will now close" << endl;
		return 0;
	}

}
