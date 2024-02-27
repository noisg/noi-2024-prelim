#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;


int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);
	int n = inf.readInt();
	int c = inf.readInt();
	const int x_max = 1<<20;
	vector<int> supply(x_max);
	int x_largest = 0;
	for(int i=0; i<n; i++) {
		int x = inf.readInt();
		supply[x] = 1;
		x_largest = max(x_largest, x);
	}
	for(int i=0; i<n; i++) {
		int x = inf.readInt();
		supply[x] = -1;
		x_largest = max(x_largest, x);
	}
	// compute answer
	int64_t correct_ans = 0;
	int prefix_sum = 0;
	for(int i=0; i<x_largest; i++) {
		prefix_sum += supply[i];
		int trips = (abs(prefix_sum) + c - 1) / c;
		correct_ans += trips;
	}
	int64_t contestant_ans = ouf.readInt();
	// simulate contestant answer to check that they match
	int on_truck = 0;
	int64_t cost = 0;
	int current_location = 0;
	for(int i=0; i<2*n; i++) {

		if(ouf.seekEof()) {
			if (contestant_ans == correct_ans) {
				quitp(0.5);
			} else {
				quitf(_wa, "cost is wrong\n");
			}
		}

		int x = ouf.readInt();
		if (x < 0 || x > 10000) {
			quitf(_wa, "invalid input\n");
		}
		if (on_truck) {
			cost += abs(current_location - x);
		}
		if(supply[x] == 1) {
			supply[x] = 0;
			on_truck += 1;
			if(on_truck > c) {
				quitf(_wa, "truck too full on operation %d", i);
			}
		} else if(supply[x] == -1) {
			supply[x] = 0;
			on_truck -= 1;
			if(on_truck < 0) {
				quitf(_wa, "no candy to unload on operation %d", i);
			}
		} else {
			quitf(_wa, "invalid load/unload at location %d", x);
		}

		current_location = x;
	}
	//cost += current_location; // last operation - return to base
	for(int i: supply) {
		if(i) {
			quitf(_wa, "supply/demand not satisfied");
		}
	}
	if(cost != contestant_ans) {
		quitf(_wa, "cost claimed by contestant does not match actual cost, %ld %ld %ld", cost, contestant_ans, correct_ans);
	}
	if(contestant_ans > correct_ans) {
		quitf(_wa, "contestant cost too high %ld %ld\n", contestant_ans, correct_ans);
	}
	if(cost < correct_ans) {
		quitf(_fail, "contestant finds better solution %ld %ld\n", cost, correct_ans);
	}
	quitf(_ok, "all correct");
	return 0;
}
