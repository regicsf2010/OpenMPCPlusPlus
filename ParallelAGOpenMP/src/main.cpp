#include <iostream>
#include <chrono>
using namespace std;
#include "auxiliaries/Configuration.h"
#include "ag/MoonSlow.h"
#include "ag/Population.h"

int main(void) {
	for (int i = 0; i < 10; i++) {
		MoonSlow ml(Ackley::ID);
		auto start = chrono::steady_clock::now();
		Population *p = ml.run();
		auto finish = chrono::steady_clock::now();

		double elapsed = chrono::duration_cast<chrono::duration<double>>(finish - start).count();

		cout << flush << elapsed << ", ";
	}
	cout << "--END MOONSLOW--" << endl;
	return 0;
}


