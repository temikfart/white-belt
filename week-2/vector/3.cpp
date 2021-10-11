#include <vector>
#include <string>
#include <iostream>

using namespace std;

void dump(vector<string>& tasks) {
	bool flag = true;
	cout << tasks.size() << " ";
	for (auto x : tasks) {
		if (flag) {
			cout << x;
			flag = false;
			continue;
		}
		cout << " " << x;
	}
	cout << endl;
}

void next(vector<int>& months, vector<vector<string>>& days, int& cur_m) {
//	cout << "cur month: " << cur_m << endl;
	cur_m = (cur_m + 1) % 12;
//	cout << "next month: " << cur_m << endl;
	
	int d_sz = days.size();
	int next_m_sz = months[cur_m];
	int delta_sz = d_sz - next_m_sz;
	
	// Next month is bigger than current
	if (delta_sz < 1) {
		days.resize(next_m_sz);
		return;
	}
	
	// Next month is smaller than than current
	// 1. Copy tasks from unnecessary days 
	//    to the last day in the next month;
	// 2. Pop unnecessary days.
	for (int i = next_m_sz; i < d_sz; i++) {
		days[next_m_sz-1].insert(end(days[next_m_sz-1]), 
						begin(days[i]), 
						end(days[i]));
	}
	for (int i = 0; i < delta_sz; i++) {
		days.pop_back();
	}
}

int main() {
	int q;
	cin >> q;

	vector<int> months = {31, 28, 31, 30,
				31, 30, 31, 31,
				30, 31, 30, 31};
	int cur_m = 0;
	int cur_m_sz = months[cur_m];
	string cmd;
	// vector with cur_month elements
	// which contains tasks for day
	vector<vector<string>> days(cur_m_sz);

	int day;
	string task;

	for (int k = 0; k < q; k++) {
		cin >> cmd;
		if (cmd == "ADD") {
			cin >> day >> task;
			
			days[day-1].push_back(task);
//			cout << "ADD <" << days[day-1][0] << "> on the " 
//				<< day << " day." << endl;
		}
		if (cmd == "DUMP") {
			cin >> day;
			
//			cout << "days.size() = " << days.size() << endl;
			dump(days[day-1]);
		}
		if (cmd == "NEXT") {
			next(months, days, cur_m);
		}
	}	

	return 0;
}
