#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <chrono>
#include <math.h>
#include <cmath>
#include <windows.h>
#include <shellapi.h>
#include <string>
#include "MinHeap.h"
#include "OrderedMap.h"

#define degreesToRadians (M_PI / 180.0)
#define locationWidth 25
#define distWidth 20
#define addywidth 60
#define webwidth 50

using namespace std;
void print(string input, const int& width)
{
	cout << left << setw(width) << setfill(' ') << input;
}

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
	cout << "1. Build Table using Min Heap" << endl;
	cout << "2. Build Table using Ordered Map" << endl;
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
			cout << endl;
			cout << "Ok, thank you for using Vaccinapp! The app will now close" << endl;
			return 0;
		}
	}
	// Find locations using MinHeap
	if (selection == 1) {
		ifstream data;
		data.open("data/data.csv");
		if (!data.is_open()) {
			cout << endl;
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
		cout << endl;
		cout << "Sorting all of the nearest Vaccine locations in the United States into a Min Heap ... this may take a few minutes" << endl;
		while (getline(data, cellInfo))
		{
			bool error = false;
			string in = "";
			stringstream lineStream(cellInfo);
			string cell;
			getline(lineStream, cell, ',');
			string subLat = cell.substr(2);

			try {
				lon1 = stof(subLat);
			}
			catch (exception& e) {
				lon1 = 0.0;
				error = true;
			}

			getline(lineStream, cell, ',');

			if (cell.size() > 2) {
				cell.pop_back();
				cell.pop_back();
			}

			try {
				lat1 = stof(cell);
			}
			catch (exception& e) {
				lat1 = 0.0;
				error = true;
			}

			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(",");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(",");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(" ");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			if (!error)
				r->insert(make_pair(distance(latitude, longitude, lat1, lon1), in));
		}
		float distance;
		string name, address, website;
		cout << endl;
		print("Distance (miles)", distWidth);
		print("Location Name", locationWidth);
		print("Address", addywidth);
		print("Website (to schedule appointments)", webwidth);
		cout << endl;
		cout << endl;
		int amt = 100;
	Loop:
		for (int i = 0; i < 100; i++) {
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
			print(to_string(distance), distWidth);
			print(name, locationWidth);
			print(address, addywidth);
			print(website, webwidth);
			cout << endl;
		}
		cout << endl;
		cout << "You just viewed " << amt << " locations. Would you like to see more?" << endl;
		string choice;
		cin >> choice;
		transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		if (choice == "yes" || choice == "1") {
			cout << endl;
			amt += 100;
			goto Loop;
		}
		cout << endl;
	}
	// Find locations using Ordered Map
	else if (selection == 2) {
		ifstream data;
		data.open("data/data.csv");
		if (!data.is_open()) {
			cout << endl;
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
		cout << endl;
		cout << "Sorting all of the nearest Vaccine locations in the United States into an Ordered Map ... this may take a few minutes" << endl;
		while (getline(data, cellInfo))
		{
			bool error = false;
			string in = "";
			stringstream lineStream(cellInfo);
			string cell;
			getline(lineStream, cell, ',');
			string subLat = cell.substr(2);

			try {
				lon1 = stof(subLat);
			}
			catch (exception& e) {
				lon1 = 0.0;
				error = true;
			}

			getline(lineStream, cell, ',');

			if (cell.size() > 2) {
				cell.pop_back();
				cell.pop_back();
			}

			try {
				lat1 = stof(cell);
			}
			catch (exception& e) {
				lat1 = 0.0;
				error = true;
			}

			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(",");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(",");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(" ");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			if (!error)
				r->insert(distance(latitude, longitude, lat1, lon1), in);
		}
		vector<Node*> vect = r->inorderVector();
		float distance;
		string name, address, website;
		cout << endl;
		print("Distance (miles)", distWidth);
		print("Location Name", locationWidth);
		print("Address", addywidth);
		print("Website", webwidth);
		cout << endl;
		cout << endl;
		int start = 0;
		int amt = 100;
	MapLoop:
		for (int i = start; i <= amt; i++) {
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
				print(to_string(distance), distWidth);
				print(name, locationWidth);
				print(address, addywidth);
				print(website, webwidth);
			}
			cout << endl;
		}
		cout << endl;
		cout << "You just viewed " << amt << " locations. Would you like to see more?" << endl;
		string choice;
		cin >> choice;
		transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		if (choice == "yes" || choice == "1") {
			cout << endl;
			if (start == 0)
				start += 1;
			start += 100;
			amt += 100;
			goto MapLoop;
		}
		cout << endl;

	}
	// Comparing the two data structures
	else if (selection == 3) {
		ifstream data;
		data.open("data/data.csv");
		if (!data.is_open()) {
			cout << endl;
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
		cout << endl;
		cout << "Beginning to time construction of Min Heap. Please Stand by..." << endl;
		cout << endl;
		auto begin_time_ = chrono::high_resolution_clock::now();
		// Minheap
		while (getline(data, cellInfo))
		{
			bool error = false;
			string in = "";
			stringstream lineStream(cellInfo);
			string cell;
			getline(lineStream, cell, ',');
			string subLat = cell.substr(2);

			try {
				lon1 = stof(subLat);
			}
			catch (exception& e) {
				lon1 = 0.0;
				error = true;
			}

			getline(lineStream, cell, ',');
			cell.pop_back();
			cell.pop_back();

			try {
				lat1 = stof(cell);
			}
			catch (exception& e) {
				lat1 = 0.0;
				error = true;
			}

			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(",");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(",");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(" ");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			if (!error)
				r->insert(make_pair(distance(latitude, longitude, lat1, lon1), in));
		}
		auto stop_time_ = chrono::high_resolution_clock::now();
		cout << "Finished timing construction of Min Heap ... moving on to Ordered Map" << endl;
		cout << endl;
		auto time_difference_nano_MinHeap = chrono::duration_cast<chrono::nanoseconds>(stop_time_ - begin_time_).count();
		auto time_difference_milli_MinHeap = chrono::duration_cast<chrono::milliseconds>(stop_time_ - begin_time_).count();
		auto time_difference_sec_MinHeap = chrono::duration_cast<chrono::seconds>(stop_time_ - begin_time_).count();
		data.close();

		data.open("data/data.csv");
		if (!data.is_open()) {
			cout << endl;
			cout << "File not found. Cannot create Ordered Map. Returning to menu." << endl;
			cout << endl;
			goto Start;
		}

		getline(data, throwaway);
		cout << endl;
		cout << "Beginning to time construction of Ordered Map. Please Stand by..." << endl;
		cout << endl;
		begin_time_ = chrono::high_resolution_clock::now();
		// Ordered Map
		while (getline(data, cellInfo))
		{
			bool error = false;
			string in = "";
			stringstream lineStream(cellInfo);
			string cell;
			getline(lineStream, cell, ',');
			string subLat = cell.substr(2);

			try {
				lon1 = stof(subLat);
			}
			catch (exception& e) {
				lon1 = 0.0;
				error = true;
			}

			getline(lineStream, cell, ',');
			cell.pop_back();
			cell.pop_back();

			try {
				lat1 = stof(cell);
			}
			catch (exception& e) {
				lat1 = 0.0;
				error = true;
			}

			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(",");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(",");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append(" ");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			getline(lineStream, cell, ',');
			in.append(cell);
			in.append("#");
			if (!error)
				s->insert(distance(latitude, longitude, lat1, lon1), in);
		}
		stop_time_ = chrono::high_resolution_clock::now();
		cout << "Finished timing construction of Ordered Map ... showing results" << endl;
		cout << endl;
		auto time_difference_nano_OrderedMap = chrono::duration_cast<chrono::nanoseconds>(stop_time_ - begin_time_).count();
		auto time_difference_milli_OrderedMap = chrono::duration_cast<chrono::milliseconds>(stop_time_ - begin_time_).count();
		auto time_difference_sec_OrderedMap = chrono::duration_cast<chrono::seconds>(stop_time_ - begin_time_).count();

		cout << "Time to insert values in MinHeap: " << time_difference_nano_MinHeap <<" nanoseconds (or "<< time_difference_milli_MinHeap << " milliseconds"<< " or "<< time_difference_sec_MinHeap<<" seconds)."<<endl;
		cout << "Time to insert values into Ordered Map: " << time_difference_nano_OrderedMap << " nanoseconds (or " << time_difference_milli_OrderedMap << " milliseconds" << " or " << time_difference_sec_OrderedMap << " seconds)." << endl;
		long long diff_nano;
		long long diff_milli;
		long long diff_sec;
		if (time_difference_nano_MinHeap > time_difference_nano_OrderedMap) {
			diff_nano = time_difference_nano_MinHeap - time_difference_nano_OrderedMap;
			diff_milli = time_difference_milli_MinHeap - time_difference_milli_OrderedMap;
			diff_sec = time_difference_sec_MinHeap - time_difference_sec_OrderedMap;
		}
		else {
			diff_nano = time_difference_nano_OrderedMap - time_difference_nano_MinHeap;
			diff_milli = time_difference_milli_OrderedMap - time_difference_milli_MinHeap;
			diff_sec = time_difference_sec_OrderedMap - time_difference_sec_MinHeap;
		}

		cout << "Difference between two data structures: " << diff_nano <<" nanoseconds (or " << diff_milli << " milliseconds" << " or " << diff_sec << " seconds)." << endl;
		cout << endl;

	}
	// Print Latitude and Longitude
	else if (selection == 4) {
		cout << endl;
		cout << "Latitude: " << latitude << endl;
		cout << "Longitude: " << longitude << endl;
		cout << endl;
	}
	// Edit Latitude and Longitude
	else if (selection == 5) {
		cout << endl;
		cout << "Input Latitude: ";
		float lat;
		cin >> lat;
		latitude = lat;
		cout << endl;
		cout << "Input Longitude: ";
		float lon;
		cin >> lon;
		longitude = lon;
		cout << endl;
	}
	// Open about Page (README)
	else if (selection == 6) {
	cout << endl;
	cout << "Opening information about the app..." << endl;
		ShellExecuteA(GetDesktopWindow(), "open", "About\\README.md", NULL, NULL, SW_SHOWNORMAL);
	}
	// Open documentation
	else if (selection == 7) {
		cout << endl;
		cout << "Opening Documentation..." << endl;
		ShellExecuteA(GetDesktopWindow(), "open", "About\\Documentation.pdf", NULL, NULL, SW_SHOWNORMAL);
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
		cout << endl;
		cout << "Ok, thank you for using Vaccinapp! The app will now close" << endl;
		return 0;
	}

}
