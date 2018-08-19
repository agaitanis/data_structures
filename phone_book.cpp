#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Query {
	string	type;
	string	name;
	int	number;
};

static vector<Query> read_queries()
{
	int n;
	cin >> n;

	vector<Query> queries(n);

	for (int i = 0; i < n; ++i) {
		cin >> queries[i].type;
		if (queries[i].type == "add") {
			cin >> queries[i].number >> queries[i].name;
		} else {
			cin >> queries[i].number;
		}
	}

	return queries;
}

static void write_responses(const vector<string>& result)
{
	for (size_t i = 0; i < result.size(); ++i) {
		std::cout << result[i] << "\n";
	}
}

static vector<string> process_queries(const vector<Query>& queries)
{
	vector<string> result;
	unordered_map<int, string> contacts;

	for (size_t i = 0; i < queries.size(); ++i) {
		if (queries[i].type == "add") {
			contacts[queries[i].number] = queries[i].name;
		} else if (queries[i].type == "del") {
			contacts.erase(queries[i].number);
		} else {
			unordered_map<int, string>::iterator it = contacts.find(queries[i].number);

			if (it != contacts.end()) {
				result.push_back(it->second);
			} else {
				result.push_back("not found");
			}
		}
	}

	return result;
}

int main()
{
	write_responses(process_queries(read_queries()));

	return 0;
}
