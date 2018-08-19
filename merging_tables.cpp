#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement {
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
		size(size),
		parent(parent),
		rank(rank)
	{}

	int	size;
	int	parent;
	int	rank;
};

struct DisjointSets {
	DisjointSets(int size) :
		size(size),
		max_table_size(0),
		sets(size)
	{
		for (int i = 0; i < size; i++) {
			sets[i].parent = i;
		}
	}

	int getParent(int table)
	{
		if (table != sets[table].parent) {
			sets[table].parent = getParent(sets[table].parent);
		}

		return sets[table].parent;
	}

	void merge(int trg, int src)
	{
		int trg_id = getParent(trg);
		int src_id = getParent(src);

		if (trg_id == src_id) return;

		if (sets[trg_id].rank <= sets[src_id].rank) {
			swap(trg_id, src_id);
		} else if (sets[trg_id].rank == sets[src_id].rank) {
			sets[trg_id].rank++;
		}
		sets[src_id].parent = sets[trg_id].parent;
		sets[trg_id].size += sets[src_id].size;
		sets[src_id].size = 0;
		max_table_size = max(max_table_size, sets[trg_id].size);
	}

	int 	size;
	int	max_table_size;
	vector <DisjointSetsElement> sets;
};

int main()
{
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int dest, src;
		cin >> dest >> src;

		tables.merge(dest - 1, src - 1);
		cout << tables.max_table_size << endl;
	}

	return 0;
}
