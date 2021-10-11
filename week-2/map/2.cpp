#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void ChangeCapital(map<string, string>& m, string& country, string& new_capital) {
	if (m.count(country) == 0) {
		m[country] = new_capital;
		cout << "Introduce new country " << country 
			<< " with capital " << new_capital << endl;
	} else {
		if (m[country] == new_capital) {
			cout << "Country " << country 
				<< " hasn't changed its capital" << endl;
		} else {
			string old_capital = m[country];
			cout << "Country " << country 
				<< " has changed its capital from " << old_capital 
				<< " to " << new_capital << endl;
			m[country] = new_capital;
		}
	}
}
void RenameCountry(map<string, string>& m, string& old_name, string& new_name) {
	bool same_names = old_name == new_name;
	bool not_exists = !(m.count(old_name));
	bool name_engaged = m.count(new_name);
	if (same_names || not_exists || name_engaged) {
		cout << "Incorrect rename, skip" << endl;
		return;
	}
	
	cout << "Country " << old_name << " with capital " 
		<< m[old_name] << " has been renamed to "
		<< new_name << endl;
	string capital = m[old_name];
	m.erase(old_name);
	m[new_name] = capital;
}
void About(map<string, string>& m, string& country) {
	if (m.count(country) == 0) {
		cout << "Country " << country << " doesn't exist" << endl;
		return;
	}
	cout << "Country " << country << " has capital " << m[country] << endl;
}
void Dump(map<string, string> m) {
	if (m.empty()) {
		cout << "There are no countries in the world" << endl;
		return;
	}
	for(const auto& [key, value] : m) {
		cout << key << "/" << value << " ";
	}
	cout << endl;
}


int main() {
	map<string, string> countries;

	int q;
	cin >> q;
	
	string cmd;
	string country, new_capital;
	string old_country_name, new_country_name;
	for (int i = 0; i < q; i++) {
		cin >> cmd;
		if (cmd == "CHANGE_CAPITAL") {
			cin >> country >> new_capital;
			
			ChangeCapital(countries, country, new_capital);
		}
		if (cmd == "RENAME") {
			cin >> old_country_name >> new_country_name;
			
			RenameCountry(countries, old_country_name, new_country_name);
		}
		if (cmd == "ABOUT") {
			cin >> country;
			
			About(countries, country);
		}
		if (cmd == "DUMP") {
			Dump(countries);
		}
	}

	return 0;
}
