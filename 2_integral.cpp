#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define N 10000 
#define PAD 16

double step;
static long num_steps = 100000000;

// Find integral of the function
double integral(int id, int num_threads){
	double x, pi, sum=0.0;

	step = 1.0/(double) num_steps;

	int start_i = (id*num_steps)/num_threads;
	int end_i = ((id+1)*num_steps)/num_threads;
	for(int i=start_i; i<end_i; i++){
		x = (i+0.5) * step;
		sum += (4.0/ (1.0 + (x*x)));
	}

	pi = step * sum;
	return(pi);
}

// Aggregate value from all threads
double get_ans(double ans[N][PAD], int actual_threads){
	double res = 0.0;
	for(int i=0; i<actual_threads; i++){
		res += ans[i][0];
	}
	return(res);
}

// Fork-Join parallelism
int main(){
	int n;
	
	double arr[N] = {0}; // on heap, visible to all threads
	int num_threads_i;
	double ans[N][PAD]={0};
	double time_i1, time_i2;

	// Try for different number of threads
	for(int num_threads = 1; num_threads <= 10; num_threads++){
		omp_set_num_threads(num_threads); // Override OMP_NUM_THREADS
		time_i1 = omp_get_wtime();
		
		#pragma omp parallel
		{	
			int actual_threads = omp_get_num_threads();
			int ID = omp_get_thread_num(); // private to thread
			ans[ID][0] = integral(ID, actual_threads);
			// Copy actual number of created threads to master thread
			if(ID == 0){
				num_threads_i = actual_threads;
			}
		}

		time_i2 = omp_get_wtime();
		cout << get_ans(ans, num_threads_i) << " :||: ";
		cout << "Threads : " << num_threads_i << " || ";
		cout << "Time : "  << time_i2 - time_i1 <<endl;
	}
	
	return(0);
}
