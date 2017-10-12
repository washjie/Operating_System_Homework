#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<iomanip>
#include<stdlib.h>

using namespace std;

int main() {
	cout << "FIFO---" << endl;
	cout << "size" << setw(15) << "miss_count" << setw(15) << "hit_count";
	cout << setw(20) << "page fault ratio" << endl; 
	for (int frame = 64; frame <= 512; frame *= 2) {
		
		string line, temp, victim;
		unsigned long int hit_count = 0, miss_count = 0;
		int index = 0;
		vector<string> arr;
		map<string, int> table;
		map<string, int>::iterator it, it_victim;
		ifstream myfile("trace.txt");

		if (!myfile.is_open())
			exit(EXIT_FAILURE);
		
		arr.resize(frame);
		while (getline(myfile, line)) {
			temp = line.substr(3, 5);
			it = table.find(temp);
			if (it == table.end()) {
				//doesn't exist, or simply just "miss"
				//fisrt, if there is no empty page, delete the victim page
				if (miss_count >= frame) {
					//means the vector is full
					//delete the string pointed by the index in the vector
					victim = arr[index];
					it_victim = table.find(victim);
					table.erase(it_victim);
				}
				//then replace the page
				table[temp] = index;
				arr[index] = temp;
				index++;
				index %= frame;//ex. assume frame = 64, if index = 64, it will return to 0

				miss_count++;
			}
			else {//exist
				hit_count++;
			}
		}
		double ratio = (double)miss_count / (double)hit_count;

		cout << setw(4) << frame << setw(15) << miss_count << setw(15) << hit_count;
		cout << setw(20) << fixed << setprecision(9) << ratio << endl;
		myfile.close();
	}
	cout << "LRU---" << endl;
	cout << "size" << setw(15) << "miss_count" << setw(15) << "hit_count";
	cout << setw(20) << "page fault ratio" << endl; 
	for (int frame = 64; frame <= 512; frame *= 2) {

		string line, temp, victim;
		unsigned long int hit_count = 0, miss_count = 0;
		int index = 0;
		vector<string> arr;
		map<string, int> table;
		map<string, int>::iterator it, it_victim;
		ifstream myfile("trace.txt");

		if (!myfile.is_open())
			exit(EXIT_FAILURE);

		arr.resize(frame);
		while (getline(myfile, line)) {
			temp = line.substr(3, 5);
			it = table.find(temp);
			if (it == table.end()) {
				//doesn't exist, or simply just "miss"
				//check whether there is empty page. 
				//if not, delete the victim page
				//then replace the page
				if (miss_count >= frame) {
					//means the vector is full
					//delete the string pointed by the index in the vector
					//in the LRU, we make index always points to the 0,
					//which means the top of the stack
					victim = arr[0];
					it_victim = table.find(victim);
					table.erase(it_victim);
					for (int i = 0; i < frame - 1; i++)
						arr[i] = arr[i + 1];
					//update the map and the vector
					//note that map has to update the index also
					table[temp] = frame - 1;//index
					arr[frame - 1] = temp;
					for (int i = 0; i < frame - 1; i++)
						table[arr[i]]--;
				}
				//if yes, just fill in the empty page
				else {
					//this is the ( 1st ~ frame'th ) operation program does
					//update the map and the vector
					table[temp] = index;
					arr[index] = temp;
					index++;
					//	cout << miss_count << endl;
					index %= frame;//ex. assume frame = 64, if index = 64, it will return to 0
				}

				miss_count++;
			}
			else {
				//exist, or simply just "hit"
				//according to the LRU, if the "stack" are full
				//we have to update the "stack"
				//to represent the actual use rate every page has
				//only update when needed
				int page_index = table[temp];
				int temp_size = table.size();

				for (int i = page_index; i < temp_size - 1; i++)
					arr[i] = arr[i + 1];

				arr[temp_size - 1] = temp;
				for (int i = page_index; i < temp_size - 1; i++)
					table[arr[i]]--;

				table[temp] = temp_size - 1;


				hit_count++;
			}

		}
		double ratio = (double)miss_count / (double)hit_count;

		cout << setw(4) << frame << setw(15) << miss_count << setw(15) << hit_count;
		cout << setw(20) << fixed <<  setprecision(9) << ratio << endl;
		myfile.close();
	}
	return 0;
}
