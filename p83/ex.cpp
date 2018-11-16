#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <chrono>
#include <functional>
#include <random>

using namespace std;
using namespace std::chrono;

class QueenSolution {
public:
	QueenSolution(int number) : m_number(number) {}

	int GetNumber() {
		return m_number;
	}

	void SetStepVegas(int step) {
		m_step = step;
	}

	void Solve() {
		while (!LesVegasSolve());
	}

private:
	bool LesVegasSolve() {
		// the set of columns occupied by existing queens
		set<int> cols;

		// the set of main diagonals occupied by existing queens
		set<int> diag45;

		// the set of minor diagonals occupied by existing queens
		set<int> diag135;

		// the index of row
		int k = 0;

		// the counter for open location of k-th queen
		int nb = 0;

		do {
			// the column where k-th queen should be placed
			int j = -1;

			// i is the index of column, loop to test if (k, i) is open
			for (int i = 0; i < m_number; i++) {
				if (cols.find(i) == cols.end() &&
					diag45.find(i - k) == diag45.end() &&
					diag135.find(i + k) == diag135.end())
				{
					nb = nb + 1;
					uniform_int_distribution<int> dist(1, nb);
					
					// maybe the k-th queen can be placed at column i
					if (dist(engine) == 1) {
						j = i;
					}
				}
			}

			// if any possible open location is found
			if (nb > 0) {
				cols.insert(j);
				diag45.insert(j - k);
				diag135.insert(j + k);
				k = k + 1;
			}
		} while (nb != 0 && k < m_step);

		// flag indicates whether solve this puzzel successfully
		bool success = false;

		// if m_step queens have been placed without confliction
		if (nb > 0) {
			success = Backtrace(k, cols, diag45, diag135);
		}

		return success;
	}

	bool Backtrace(int k, set<int>& cols, set<int>& diag45, set<int>& diag135) {

		// the lower bound of backtracing
		int lower = k;

		// the column selected, [0...size-1] --> [k...k+size-1]
		vector<int> stack;

		// the column where k-th queen to be placed
		int j = 0;

		while (k >= lower && k < m_number) {

			bool findOpenPosition = false;

			// i is the index of column, loop to test if (k, i) is open
			while (j < m_number) {
				if (cols.find(j) == cols.end() &&
					diag45.find(j - k) == diag45.end() &&
					diag135.find(j + k) == diag135.end()) {
					findOpenPosition = true;
					break;
				}
				j = j + 1;
			}

			if (findOpenPosition) {
				cols.insert(j);
				diag45.insert(j - k);
				diag135.insert(j + k);
				stack.push_back(j);
				k = k + 1;
				j = 0;
			}
			else {
				k = k - 1;
				if (k >= lower) {
					j = stack.back();
					stack.pop_back();
					cols.erase(j);
					diag45.erase(j - k);
					diag135.erase(j + k);
					j = j + 1;
				}
			}
		}

		return k == m_number;
	}

private:
	// The number of queens to be placed
	int m_number;

	// The threshold of random palced queens
	int m_step;

	// The engine to generate pseudo-random number
	default_random_engine engine;
};

double Timing(function<void(void)> target, int iterations) {
	double timeSpanSum = 0.0;

	high_resolution_clock::time_point begin = high_resolution_clock::now();
	for (int j = 0; j < iterations; j++) {
		target();
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	timeSpanSum = duration_cast<duration<double>>(end - begin).count();

	return timeSpanSum / iterations;
}

vector<double> RuntimeStat(QueenSolution& solution) {
	vector<double> stat;

	for (int i = 0; i < solution.GetNumber(); i++) {
		solution.SetStepVegas(i+1);
		double runtime = Timing([&]() { solution.Solve(); }, 50);
		stat.push_back(runtime);
	}

	return stat;
}

void PrintRuntimeStat(int number, vector<double> stat) {
	double min = numeric_limits<double>::max();
	int i = -1;
	for (int j = 0; j < stat.size(); j++) {
		if (stat[j] < min) {
			min = stat[j];
			i = j;
		}
		cout << stat[j] << ",";
	}
	cout << i << endl;
}

int main()
{
	for (int n = 12; n <= 20; n++) {
		QueenSolution solution(n);
		vector<double> stat = RuntimeStat(solution);
		PrintRuntimeStat(n, stat);
	}
}
