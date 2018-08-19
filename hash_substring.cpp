#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

template <class T>
static T mod(T a, T b)
{
	return ((a%b) + b)%b;
}

static bool AreEqual(const string &s1, int start1, int end1, const string &s2, int start2, int end2)
{
	int	len1 = end1 - start1 + 1;
	int	len2 = end2 - start2 + 1;

	if (len1 != len2) return false;

	for (int i = 0; i < len1; i++) {
		if (s1[start1 + i] != s2[start2 + i]) {
			return false;
		}
	}

	return true;
}

static long long PolyHash(const string &s, long long p, long long x)
{
	long long hash = 0;

	for (int i = (int)s.size() - 1; i >= 0; i--) {
		hash = mod(hash * x + s[i], p);
	}

	return hash;
}

static vector<long long> PrecomputeHashes(const string &text, int pattern_size, long long p, long long x)
{
	int text_size = (int)text.size();
	vector<long long> hashes(text_size - pattern_size + 1);
	string s = text.substr(text_size - pattern_size, pattern_size);
	long long y;

	hashes[text_size - pattern_size] = PolyHash(s, p, x);

	y = 1;
	for (int i = 1; i <= pattern_size; i++) {
		y = mod(y * x, p);
	}

	for (int i = text_size - pattern_size - 1; i >= 0; i--) {
		hashes[i] = mod(x * hashes[i+1] + text[i] - y * text[i+pattern_size], p);
	}

	return hashes;
}

static vector<int> RabinKarp(const string &text, const string &pattern)
{
	int pattern_size = (int)pattern.size();
	int text_size = (int)text.size();
	vector<int> result;

	long long p = 1000000007;
	default_random_engine generator;
	uniform_int_distribution<long long> distribution(1, p-1);
	long long x = distribution(generator);

	long long p_hash = PolyHash(pattern, p, x);
	vector<long long> hashes = PrecomputeHashes(text, pattern_size, p, x);

	for (int i = 0; i <= text_size - pattern_size; i++) {
		if (p_hash != hashes[i]) {
			continue;
		}
		if (AreEqual(text, i, i + pattern_size - 1, pattern, 0, pattern_size - 1)) {
			result.push_back(i);
		}
	}

	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);

	string pattern;
	string text;
	cin >> pattern >> text;

	vector<int> result = RabinKarp(text, pattern);

	for (size_t i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;

	return 0;
}
