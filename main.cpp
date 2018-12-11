#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

template <class T>
void makeIteration(vector<T>& universe) {
	random_device rd;
	mt19937 gen(rd());

	int combinationSum = 0;
	int firstRandom = gen() % universe.size();
	int secondRandom = gen() % universe.size();

	while (firstRandom == secondRandom)
		secondRandom = gen() % universe.size();

	combinationSum += universe[firstRandom] + universe[secondRandom];

	universe.push_back(combinationSum);
}

template <class T>
void dataHandler(vector<T>& sumUniverse, vector<vector<int>>& data) {
	int count = 1;

	sort(sumUniverse.begin(), sumUniverse.end()); // from algorithm

	for (int i = 1; i < sumUniverse.size(); i++) {
		if (sumUniverse[i] == sumUniverse[i - 1])
			count++;
		else {
			vector<int> new_item;
			new_item.push_back(sumUniverse[i - 1]);
			new_item.push_back(count);
			data.push_back(new_item);
			count = 1;
		}
	}

	vector<int> new_item;
	new_item.push_back(sumUniverse[sumUniverse.size() - 1]);
	new_item.push_back(count);

	data.push_back(new_item);
}

int main() {
	int n = 100;
	int depth = 1;

	vector<int> universe(4);
	vector<int> defaultUniverse(4);
	vector<int> sumUniverse;
	vector<vector<int>> data;

	for (int i = 0; i < universe.size(); i++)
		defaultUniverse[i] = i + 1;
	for (int i = 0; i < n; i++) {
		universe = defaultUniverse;

		for (int j = 0; j < depth; j++)
			makeIteration(universe);

		int sum = 10; // 1 + 2 + 3 + 4
		for (int j = 4; j < universe.size(); j++)
			sum += universe[j];

		sumUniverse.push_back(sum);
	}

	dataHandler(sumUniverse, data);

	cout << "n: " << n << endl;
	for (auto& el : data) {
		cout << el[0] << ": " << (double)el[1] / n << endl;
	}

	system("pause");
}