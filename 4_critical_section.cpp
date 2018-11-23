// Critical section

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

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

// Fork-Join parallelism
int main(){
	int n;
	int num_threads_i;
	double ans=0;
	double time_i1, time_i2;

	// Try for different number of threads
	for(int num_threads = 1; num_threads <= 5; num_threads++){
		omp_set_num_threads(num_threads); // Override OMP_NUM_THREADS
		ans = 0;

		time_i1 = omp_get_wtime();
		
		#pragma omp parallel
		{	
			double this_ans;
			int actual_threads = omp_get_num_threads();
			int ID = omp_get_thread_num();

			if(ID == 0){
				num_threads_i = actual_threads;
			}

			// Ans for this thread
			this_ans = integral(ID, actual_threads);
			// Update "ans" one thread at a time
			// Can also use "omp atomic"
			#pragma omp critical
			{
				ans += this_ans;	
			}
			
		}

		time_i2 = omp_get_wtime();
		
		cout << ans << " :||: ";
		cout << "Threads : " << num_threads_i << " || ";
		cout << "Time : "  << time_i2 - time_i1 <<endl;
	}
	
	return(0);
}
