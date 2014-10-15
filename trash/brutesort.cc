#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

template <typename T>
bool brutesortOK(const vector<T> &v)
{
	return is_sorted(v.begin(), v.end());
}

template <typename T>
void bruteplace(vector<T> &v)
{
	int t;
	vector<T> v2 (v.size());
	vector<bool> r (v2.size());
	random_device rnd;
		
	for (auto i : r)
		r.at(i) = false;

	for (int i = 0; i < v2.size(); i++) {
		
		do
			t = rnd() % v.size();
		while (r.at(t) != false);

		v2.at(t) = v.at(i);
		r.at(t) = true;
	}
		
	v = v2;
}

template <typename T>
void brutesort(vector<T> &v)
{
	while (!brutesortOK(v))
		bruteplace(v);
}

template <typename T>
void print(const vector<T> &v)
{
	for (int i = 0; i < v.size(); i++)
		cout << v.at(i) << ' ';
	cout << endl;
}

int main(void)
{
	int d;
	vector<int> v;

	while (cin >> d)
		v.push_back(d);

	auto begin = chrono::high_resolution_clock::now();

	brutesort(v);
	
	auto end = chrono::high_resolution_clock::now();
	cout << "Brutesorting took " 
		 << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
		 << " seconds." << endl;

	print(v);
}
