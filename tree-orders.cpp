#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {
	public:
		void read()
		{
			cin >> n;
			key.resize(n);
			left.resize(n);
			right.resize(n);
			for (int i = 0; i < n; i++) {
				cin >> key[i] >> left[i] >> right[i];
			}
		}

		void in_order_recursive(int node, vector<int> *result)
		{
			if (node < 0) return;
			in_order_recursive(left[node], result);
			result->push_back(key[node]);
			in_order_recursive(right[node], result);
		}

		vector <int> in_order()
		{
			vector<int> result;

			in_order_recursive(0, &result);

			return result;
		}

		void pre_order_recursive(int node, vector<int> *result)
		{
			if (node < 0) return;
			result->push_back(key[node]);
			pre_order_recursive(left[node], result);
			pre_order_recursive(right[node], result);
		}

		vector <int> pre_order()
		{
			vector<int> result;    

			pre_order_recursive(0, &result);

			return result;
		}

		void post_order_recursive(int node, vector<int> *result)
		{
			if (node < 0) return;
			post_order_recursive(left[node], result);
			post_order_recursive(right[node], result);
			result->push_back(key[node]);
		}

		vector <int> post_order()
		{
			vector<int> result;

			post_order_recursive(0, &result);

			return result;
		}

	private:
		int n;
		vector <int> key;
		vector <int> left;
		vector <int> right;
};

void print(vector <int> a)
{
	for (size_t i = 0; i < a.size(); i++) {
		if (i > 0) {
			cout << ' ';
		}
		cout << a[i];
	}
	cout << '\n';
}

int main_with_large_stack_space()
{
	ios_base::sync_with_stdio(0);
	TreeOrders t;
	t.read();
	print(t.in_order());
	print(t.pre_order());
	print(t.post_order());
	return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				cerr << "setrlimit returned result = " << result << endl;
			}
		}
	}
#endif

	return main_with_large_stack_space();
}

