#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
	Bracket(char type, int position):
		type(type),
		position(position)
	{}

	bool Matchc(char c)
	{
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;
};

static int error_position_of_brackets(const string &text)
{
	stack<Bracket> opening_brackets_stack;

	for (int position = 0; position < text.length(); ++position) {
		char next = text[position];

		if (next == '(' || next == '[' || next == '{') {
			opening_brackets_stack.push(Bracket(next, position));
		} else if (next == ')' || next == ']' || next == '}') {
			if (opening_brackets_stack.empty()) {
				return position;
			}

			Bracket top_bracket = opening_brackets_stack.top();

			opening_brackets_stack.pop();

			if (!top_bracket.Matchc(next)) {
				return position;
			}
		}
	}

	if (!opening_brackets_stack.empty()) {
		Bracket top_bracket = opening_brackets_stack.top();

		return top_bracket.position;
	}

	return -1;
}

int main()
{
	string text;
	getline(cin, text);

	int pos = error_position_of_brackets(text);

	if (pos == -1) {
		cout << "Success" << endl;
	} else {
		cout << pos + 1 << endl;
	}

	return 0;
}
