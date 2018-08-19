#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct Query {
	string	type;
	string	s;
	size_t	ind;
};

class QueryProcessor {
	public:
		QueryProcessor(int bucket_count) :
			m_bucket_count(bucket_count),
			m_hash_table()
		{
			m_hash_table.resize(bucket_count);
		}

		Query readQuery() const
		{
			Query query;
			cin >> query.type;

			if (query.type != "check") {
				cin >> query.s;
			} else {
				cin >> query.ind;
			}

			return query;
		}

		void writeSearchResult(bool was_found) const
		{
			cout << (was_found ? "yes\n" : "no\n");
		}

		void processQuery(const Query& query)
		{
			if (query.type == "check") {
				list<string> &elems = m_hash_table[query.ind];

				for (list<string>::iterator it = elems.begin(); it != elems.end(); ++it) {
					cout << *it << " ";
				}
				cout << endl;
			} else {
				list<string> &elems = m_hash_table[hash_func(query.s)];
				list<string>::iterator it = find(elems.begin(), elems.end(), query.s);

				if (query.type == "find") {
					writeSearchResult(it != elems.end());
				} else if (query.type == "add") {
					if (it == elems.end()) {
						elems.push_front(query.s);
					}
				} else if (query.type == "del") {
					if (it != elems.end()) {
						elems.erase(it);
					}
				}
			}
		}

		void processQueries()
		{
			int n;
			cin >> n;

			for (int i = 0; i < n; ++i) {
				processQuery(readQuery());
			}
		}

	private:
		size_t hash_func(const string& s) const
		{
			static const size_t multiplier = 263;
			static const size_t prime = 1000000007;
			unsigned long long hash = 0;

			for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i) {
				hash = (hash * multiplier + s[i]) % prime;
			}

			return hash % m_bucket_count;
		}

		int			m_bucket_count;
		vector<list<string> >	m_hash_table;
};

int main()
{
	ios_base::sync_with_stdio(false);
	int bucket_count;
	cin >> bucket_count;

	QueryProcessor proc(bucket_count);
	proc.processQueries();

	return 0;
}
