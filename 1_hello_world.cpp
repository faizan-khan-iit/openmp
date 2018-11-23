#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void solve(int n){
	cout << "Hello " << n << " World " << n << endl;
	return;
}

int main(){
	int n;
	
	#pragma omp parallel
	{
	n = omp_get_thread_num();
	solve(n);
	}
	
    return(0);
}
