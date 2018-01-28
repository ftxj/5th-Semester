#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <stdbool.h>
#include <utility>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char const *argv[])
{

	string ss(argv[1]);
	int kk = 0,pp = 1;
	for(int i = ss.size()-1;i>=0;i--)
	{
		kk+=(ss[i]-'0')*pp;
		pp*=10;
	}
	srand(time(NULL));
	for (int i = 0; i < kk; ++i)
	{
		int k = rand();
		k = k%10;
		if(k == 0)
			continue;
		cout << k << endl;
		for (int j = 0; j < k; ++j)
		{
			int w1 = rand(),w2 = rand();
			w1 = w1%10;w2 = w2%10;
			if(w1 == w2)
			{
				j--;
				continue;
			}
			if(w1<w2)
			{
				cout << w1 << " " << w2 << endl;
			}
			else
			{
				cout << w2 << " " << w1 << endl;
			}
		}
	}
	return 0;
}
