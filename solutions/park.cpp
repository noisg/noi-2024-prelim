#include <iostream>
#include <cassert>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXQ 200'000
#define MAXS 200'000

typedef long long ll;
typedef pair<ll,ll> pl;

const ll INF = 3e18;

struct STNode
{
	ll s, e, m, v;
	STNode *left, *right;	
	
	STNode (ll _s, ll _e)
	{
		s = _s;
		e = _e;
		m = (s + e) / 2;
		v = INF;
		
		if (s != e)
		{
			left = new STNode(s, m);
			right = new STNode(m+1, e);
		}
	}
	
	void update(ll _p, ll _v)
	{
		if (s == e)
		{
			v = _v;
			return;
		}
		
		if (_p <= m) left->update(_p, _v);
		else right->update(_p, _v);
		
		v = min(left->v, right->v);
	}
	
	ll getmin(ll _l, ll _r)
	{
		if (_r < s || e < _l) return INF;
		else if (_l <= s && e <= _r) return v;
		else return min(left->getmin(_l, _r), right->getmin(_l, _r));
	}
	
} *root;

ll Q, gcount, gsize[MAXQ+5];
ll gstate[MAXQ+5];        // the subset that each group is assigned
set <ll> subs[MAXS+5];    // subs[0]: can split, subs[i>0]: cannot split, size i; stores ID

void force_update(ll p)
{
	ll v = ( subs[p].empty() ? INF : *subs[p].begin() );
	root->update(p, v);
}

void join(ll s, ll w)
{
	ll i = ++gcount;
	gstate[i] = (w == 1) ? 0 : s;
	gsize[i] = s;
	
	subs[gstate[i]].insert(i);
	force_update(gstate[i]);
}

void leave(ll i)
{
	subs[gstate[i]].erase(i);
	force_update(gstate[i]);
}

void board(ll b)
{
	vector <pl> output;
	
	while (b > 0)
	{
		ll i = root->getmin(0, min(b, (ll)MAXS));
		
		if (i == INF) break;    // no more groups can be chosen
		
		// if unwilling to split (gstate[i] > 0), then min(b, gsize[i]) can be read as just gsize[i]
		ll subgroup = min(b, gsize[i]);
		output.emplace_back(i, subgroup);
		b -= subgroup;
		gsize[i] -= subgroup;
		if (gsize[i] == 0) leave(i);
	}
	
	cout << output.size() << '\n';
	
	for (pl o : output)
	{
		cout << o.first << ' ' << o.second << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> Q;
	gcount = 0;
	root = new STNode(0, MAXS+5);
	
	for (ll q = 1; q <= Q; q++)
	{
		ll qtype;
		cin >> qtype;
		
		if (qtype == 1)    // join
		{
			ll s, w;
			cin >> s >> w;
			join(s, w);
		}
		
		else if (qtype == 2)    // leave
		{
			ll i;
			cin >> i;
			leave(i);
		}
		
		else    // qtype == 3: board
		{
			ll b;
			cin >> b;
			board(b);
		}
	}
	
	return 0;
}










