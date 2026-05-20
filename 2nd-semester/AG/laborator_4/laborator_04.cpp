#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

auto codificare_prufer(vector<int> t)
{
	vector<int> k;
	for (int q = 1; q < t.size(); ++q)
	{
		int fmin = -1;
		for (int i = 0; i < t.size() && fmin == -1; ++i)
			if (std::find(t.begin(), t.end(), i) == t.end())
				fmin = i;
		k.push_back(t[fmin]);
		t[fmin] = fmin;
	}
	return k;
}

int main(int argc, char** argv)
{
	int radacina;
	vector<int> parinti;

	ifstream fin(argv[1]);
	int N;
	fin >> N;

	parinti = vector<int>(N);
	for (int i = 0; i < N; ++i)
	{
		fin >> parinti[i];
		if (parinti[i] == -1)
		{
			radacina = i;
		}
	}
	fin.close();
	auto rezultat = codificare_prufer(parinti);
	
	ofstream fout(argv[2]);
	fout << rezultat.size() << '\n';
	for (const auto& elem : rezultat)
		fout << elem << ' ';
	fout.close();
	
	return 0;
}