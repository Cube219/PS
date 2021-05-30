#include "hat.h"
#include <vector>
using namespace std;

int nn;

void init(int N)
{
	nn = N;
}

int call(vector<int> F, vector<int> B, int num)
{
	if(num == nn - 1) {
		int res = 0;
		for(int i = 0; i < F.size(); ++i) {
			res ^= F[i];
		}
		return res;
	}

	int res = B[nn - 1];
	for(int i = num + 1; i < nn - 1; ++i) {
		res ^= B[i];
	}
	for(int i = 0; i < num; ++i) {
		res ^= F[i];
	}
	return res;
}
