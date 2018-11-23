// Every position has different moves!!!
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
typedef long long ll;

int N;
int X[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
int Y[8] = {2, 2, 1, -1, -2, -2, -1, 1};

int total_tours = 0;

void print_sol(vector<vector<int>> &M){
	for(int i=1; i<=N; i++){
		for(int j=1; j<=N; j++){
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

bool in_bounds(int x, int y){
	return(x>=0 && y>=0 && x<N && y<N);
}

bool valid(int x, int y, vector<vector<int>> &M){
	return(
		in_bounds(x, y) &&
		M[x][y] == 0
		);
}

void print_tours(int x, int y, int num_pos, vector<vector<int>> &M){
	// cout << num_pos << " ";
	M[x][y] = num_pos;

	if(num_pos >= N*N){
		// print_sol(M);
		#pragma omp critical
		{
			total_tours++;
		}
		M[x][y] = 0;
		return;
	}

	int nx, ny;
	for(int i=0; i<8; i++){
		nx = x + X[i];
		ny = y + Y[i];

		if(valid(nx, ny, M)){
			print_tours(nx, ny, num_pos + 1, M);		
		}
	}

	M[x][y] = 0;
	return;
}


void print_tours_parallel(int x, int y, int num_threads){
	omp_set_num_threads(num_threads);
	
	total_tours = 0;
	#pragma omp parallel for
	for(int i=0; i<8; i++){
		{
			int nx, ny;
			int st = 2;
			int ID = omp_get_thread_num();
			nx = st + X[i];
			ny = st + Y[i];

			// #pragma omp critical
			// {
			// cout << ID << " :: " << i <<" || ";
			// cout << "(" << nx << ", " << ny << ")" << endl;
			// }		
			if(in_bounds(nx, ny)){
				
				vector<vector<int>> M;
				vector<int> row;
				for(int i=0; i<N; i++){
					row.push_back(0);
				}

				for(int i=0; i<N; i++){
					M.push_back(row);
				}
				M[st][st] = 1;
				print_tours(nx, ny, 2, M);
			}
		}
	}
	// cout << "total_tours :: " << total_tours << endl;
	return;
}


int main(){
	int n;
	cout << "Size of board :: ";
	cin >> n;
	N = n;

	double time1, time2;
	int num_trials = 10;
	double avg = 0;
	for(int num_threads = 1; num_threads <9; num_threads++){
		cout << "Num of threads :: " << num_threads << endl;
		vector<double> T;
		for (int i=0; i < num_trials; i++){
			time1 = omp_get_wtime();
			print_tours_parallel(2 ,2, num_threads);
			time2 = omp_get_wtime();
			// cout << time2 - time1 << endl;
			T.push_back(time2 - time1);
		}
		avg = 0.0;
		for (int i=0; i < num_trials; i++){
			avg += T[i];
		}
		cout << avg/num_trials << endl << endl;
	}
	
	return(0);
}
