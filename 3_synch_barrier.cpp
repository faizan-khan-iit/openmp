// Synchronization barrier

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define N 100000

int some_big_calc(int id){
	for(int i=0; i<N; i++){
		string s = "herping derping";
	}
	return(id);
}

// Barrier implementation
int main(){

	int A[100] = {0};
	int num_threads = 10;
	omp_set_num_threads(num_threads);

	#pragma omp parallel
	{	
		int ans1 = 0;
		int id = omp_get_thread_num();
		A[id] = some_big_calc(id);
		
		// Need barrier here to have identical values in A[]
		#pragma omp barrier

		// Use values in A[] with LOCAL variable
		for(int k=0; k<num_threads; k++){
			ans1 += A[k];
		}
		cout << ans1 << endl;
	}

	return(0);
}
