#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

struct Node {
	Node() : key(0), parent(NULL), children() {}

	void setParent(Node *theParent)
	{
		parent = theParent;
		parent->children.push_back(this);
	}

	int		key;
	Node		*parent;
	vector<Node *>	children;
};

int tree_height(Node *node)
{
	if (!node) return 0;

	vector<Node *> &children = node->children;
	int max_height = 0;

	for (size_t i = 0; i < children.size(); i++) {
		Node *child = children[i];
		int height = tree_height(child);

		if (height > max_height) {
			max_height = height;
		}
	}

	return 1 + max_height;
}

int main_with_large_stack_space()
{
	Node *root = NULL;
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	vector<Node> nodes(n);

	for (int child_index = 0; child_index < n; child_index++) {
		int parent_index;

		cin >> parent_index;
		if (parent_index >= 0) {
			nodes[child_index].setParent(&nodes[parent_index]);
		} else {
			root = &nodes[child_index];
		}
		nodes[child_index].key = child_index;
	}

	cout << tree_height(root) << endl;

	return 0;
}

int main(int argc, char **argv)
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

