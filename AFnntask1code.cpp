#include<fstream>
#include<string>
#include<iostream>
#include <algorithm>
#include<vector>

using namespace std;

void quickSort(vector<pair<pair<string, string>, int>> &array, int low, int high)
{
	int i = low;
	int j = high;
	pair<pair<string, string>, int> pivot = array[(i + j) / 2];
	pair<pair<string, string>, int> temp;

	while (i <= j)
	{
		while (array[i].first.second < pivot.first.second || (array[i].first.second == pivot.first.second && array[i].second < pivot.second))
			i++;
		while (array[j].first.second > pivot.first.second || (array[j].first.second == pivot.first.second && array[j].second > pivot.second))
			j--;
		if (i <= j)
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if (j > low)
		quickSort(array, low, j);
	if (i < high)
		quickSort(array, i, high);
}



int main(int argc, char** argv) {
	vector<string> graphs, untarcs;
	vector<pair<pair<string, string>, int>> arcs;
	string input, output, curr, v1, v2, n;
	bool f = 1;
	char cur;
	if (argc != 3) {
		cout << "Invalid input and/or output file direction";
		return -1;
	}
	input = argv[1];
	output = argv[2];
	if (output[0] == 'i') swap(input, output);
	if (input.substr(0, 7) != "input1=") {
		cout << "Invalid input and/or output file direction";
		return -1;
	}
	if (input.substr(input.find('.')) != ".txt") {
		cout << "Invalid input and/or output file direction";
		return -1;
	}
	if (output.substr(0, 8) != "output1=") {
		cout << "Invalid input and/or output file direction";
		return -1;
	}
	if (!(output.substr(output.find('.')) == ".json" || output.substr(output.find('.')) == ".xml")) {
		cout << "Invalid input and/or output file direction";
		return -1;
	}
	input = input.substr(7);
	output = output.substr(8);
	ifstream in(input);
	ofstream out(output);

	while (in >> cur) {
		curr += cur;
		if (curr[0] == '(' && curr[curr.size() - 1] == ')') {
			if (count(curr.begin(), curr.end(), ',') == 2 && curr[curr.size() - 2] <= '9' && curr[curr.size()-2] >= '0'){
				untarcs.push_back(curr);
				curr.clear();
				in >> cur;
			}
			else {
				cout << "Invalid input: the arc in position " << untarcs.size() + 1 << " is incorrect";
				return -2;
			}
		}
	}
	if (!curr.empty()) {
		cout << "Invalid input: unfinished last arc";
		return -2;
	}
	
	for (int i = 0; i < untarcs.size(); i++) {
		curr = untarcs[i].substr(1);
		v1 = curr.substr(0, curr.find(',')-1);
		for (int j = 0; j < graphs.size(); j++) if (graphs[j] == v1) f = 0;
		if (f) graphs.push_back(v1);
		f = 1;
		curr = curr.substr(curr.find(',') + 1);
		v2 = curr.substr(0, curr.find(',') - 1);
		for (int j = 0; j < graphs.size(); j++) if (graphs[j] == v2) f = 0;
		if (f) graphs.push_back(v2);
		f = 1;
		curr = curr.substr(curr.find(',') + 1);
		curr.pop_back();
		n = curr;
		arcs.push_back(make_pair(make_pair(v1, v2), stoi(n)));
	}
	quickSort(arcs, 0, arcs.size() - 1);
	out << "<graph>" << endl;
	for (int i = 0; i < graphs.size(); i++) out << "	<vertex>" << graphs[i] << "</vertex>" << endl;
	for (int i = 0; i < arcs.size(); i++) {
		out << "	<arc>" << endl;
		out << "		<from>" << arcs[i].first.first << "</from>" << endl;
		out << "		<to>" << arcs[i].first.second << "</to>" << endl;
		out << "		<order>" << arcs[i].second << "</order>" << endl;
		out << "	</arc>" << endl;
	}
	out << "</graph>";

	//---ещё работает---
	return 0;
}