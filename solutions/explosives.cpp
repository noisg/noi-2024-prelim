#include <vector>
#include <utility>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <cassert>
#define supply(i) get<1>(input[i])
#define loc(i) get<0>(input[i])
using namespace std;

int main() {
	int n,m,c; cin>>n>>c;
	m = n;
	vector<tuple<int,int>> input(n+m+1);
	for(int i=1; i<=n+m; i++) {
		// location, demand, id
		// 0 - location
		// 1 - supply (+ve for shop, -ve for house)
		cin>> get<0>(input[i]);
		supply(i) = (i>n ? -1 : 1);
	}
	sort(input.begin(), input.end());
	auto input_copy = input;
	// convert supply to prefix sum
	for(int i=1; i<=n+m; i++) {
		supply(i) += supply(i-1);
		//cout << i << " " << supply(i) << "\n";
	}
	assert(supply(m+n)==0);

	vector<int> ans;
	int on_truck = 0;
	bool updated = true;
	int cost = 0;
	int prev_location = 0;
	do {
        updated = false;
        for(int i=0; i<=n+m; i++) {
            int target = min(c, max(0, supply(i)));
            if(target != on_truck) {
                assert(abs(target - on_truck) == 1);
                ans.push_back(i);
            }
            on_truck = target;
            supply(i) -= on_truck;
            if (on_truck) {
                updated = true;
                cost += abs(loc(i+1) - loc(i));
                // if we carry explosives now, then we must carry it to i+1
            }
        }
	} while(updated);
	for(int i=0; i<=n+m; i++) {
        assert(supply(i)<=0);
	}
	assert(on_truck == 0);
	do {
        updated = false;
        for(int i=n+m; i>=0; i--) {
            int target = min(c, max(0, -supply(i)));
            if(target != on_truck) {
                ans.push_back(i+1);
            }
            on_truck = target;
            supply(i) += on_truck;
            if(on_truck) {
                updated = true;
                cost += abs(loc(i+1) - loc(i));
            }
        }
	} while(updated);
    assert(ans.size() == 2*n);
    assert(on_truck == 0);
    cout << cost << "\n";
    for(int i: ans) {
        cout << loc(i) << " ";
    }
    cout << "\n";
}
