#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
	private:
		vector<int> data_;
		vector< pair<int, int> > swaps_;

		void WriteResponse() const {
			cout << swaps_.size() << "\n";
			for (int i = 0; i < swaps_.size(); ++i) {
				cout << swaps_[i].first << " " << swaps_[i].second << "\n";
			}
		}

		void ReadData() {
			int n;
			cin >> n;
			data_.resize(n);
			for(int i = 0; i < n; ++i) {
				cin >> data_[i];
			}
		}

		int LeftChild(int i) {
			return i*2 + 1;
		}

		int RightChild(int i) {
			return i*2 + 2;
		}

		void SiftDown(int i) {
			int n = (int)data_.size();
			int min_index = i;
			int l = LeftChild(i);
			int r = RightChild(i);

			if (l < n && data_[l] < data_[min_index]) {
				min_index = l;
			}
			if (r < n && data_[r] < data_[min_index]) {
				min_index = r;
			}
			if (min_index != i) {
				swap(data_[i], data_[min_index]);
				swaps_.push_back(make_pair(i, min_index));
				SiftDown(min_index);
			}
		}

		void GenerateSwaps() {
			int n = (int)data_.size();

			for (int i = n/2-1; i >= 0; i--) {
				SiftDown(i);
			}
		}

	public:
		void Solve() {
			ReadData();
			GenerateSwaps();
			WriteResponse();
		}
};

int main()
{
	ios_base::sync_with_stdio(false);
	HeapBuilder heap_builder;
	heap_builder.Solve();
	return 0;
}
