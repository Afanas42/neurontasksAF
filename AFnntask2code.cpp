#include<fstream>
#include<string>
#include<iostream>
#include <algorithm>
#include<vector>
#include<set>

using namespace std;


set<string> enter, exitt;

string idunno(string in, vector<pair<pair<string, string>, int>> mass, set<string> inn) {
	string zero;
	if (exitt.count(in) > 0) return in;
	if (inn.count(in) > 0) return zero;
	else {
		inn.insert(in);
		string ss = in + "(";
		for (int i = 0; i < mass.size(); i++) if (mass[i].first.second == in) {
			if (idunno(mass[i].first.first, mass, inn) == zero) return zero;
			ss += idunno(mass[i].first.first, mass, inn) + ",";
		}
		ss.pop_back();
		ss += ")";
		return ss;
	}
}



int main(int argc, char** argv) {
	vector<string> graphs, untarcs;
	vector<pair<pair<string, string>, int>> arcs;
	string input, output, curr, v1, v2, n, zero;
	set<string> inn;
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
	if (output.substr(output.find('.')) != ".txt") {
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
			if (count(curr.begin(), curr.end(), ',') == 2 && curr[curr.size() - 2] <= '9' && curr[curr.size() - 2] >= '0') {
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
		v1 = curr.substr(0, curr.find(','));
		for (int j = 0; j < graphs.size(); j++) if (graphs[j] == v1) f = 0;
		if (f) graphs.push_back(v1);
		f = 1;
		exitt.insert(v1);
		curr = curr.substr(curr.find(',') + 1);
		v2 = curr.substr(0, curr.find(','));
		for (int j = 0; j < graphs.size(); j++) if (graphs[j] == v2) f = 0;
		if (f) graphs.push_back(v2);
		f = 1;
		enter.insert(v2);
		curr = curr.substr(curr.find(',') + 1);
		curr.pop_back();
		n = curr;
		arcs.push_back(make_pair(make_pair(v1, v2), stoi(n)));
	}
	
	for (int i = 0; i < arcs.size(); i++) {
		exitt.erase(arcs[i].first.second);
		enter.erase(arcs[i].first.first);
	}
	if (enter.empty()) {
		cout << "No final points found";
		return 3;
	}
	for (auto i : enter) {
		if (idunno(i, arcs, inn) == zero) {
			cout << "Cycle is found, includes node " << i;
			return 3;
		}
		out << idunno(i, arcs, inn) << endl;
	}

	return 0;
}