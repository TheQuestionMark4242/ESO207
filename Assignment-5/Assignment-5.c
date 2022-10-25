#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
/*	
         ;,_            ,
                 _uP~"b          d"u,
                dP'   "b       ,d"  "o
               d"    , `b     d"'    "b
              l] [    " `l,  d"       lb
              Ol ?     "  "b`"=uoqo,_  "l
            ,dBb "b        "b,    `"~~TObup,_
          ,d" (db.`"         ""     "tbc,_ `~"Yuu,_
        .d" l`T'  '=                      ~     `""Yu,
      ,dO` gP,                           `u,   b,_  "b7
     d?' ,d" l,                           `"b,_ `~b  "1
   ,8i' dl   `l                 ,ggQOV",dbgq,._"  `l  lb
  .df' (O,    "             ,ggQY"~  , @@@@@d"bd~  `b "1
 .df'   `"           -=@QgpOY""     (b  @@@@P db    `Lp"b,
.d(                  _               "ko "=d_,Q`  ,_  "  "b,
Ql         .         `"qo,._          "tQo,_`""bo ;tb,    `"b,
qQ         |L           ~"QQQgggc,_.,dObc,opooO  `"~~";.   __,7,
qp         t\io,_           `~"TOOggQV""""        _,dg,_ =PIQHib.
`qp        `Q["tQQQo,_                          ,pl{QOP"'   7AFR`
  `         `tb  '""tQQQg,_             p" "b   `       .;-.`Vl'
             "Yb      `"tQOOo,__    _,edb    ` .__   /`/'|  |b;=;.__
                           `"tQQQOOOOP""`"\QV;qQObob"`-._`\_~~-._
                                """"    ._        /   | |oP"\_   ~\ ~\_~\
                                        `~"\ic,qggddOOP"|  |  ~\   `\~-._
                                          ,qP`"""|"   | `\ `;   `\   `\
                               _        _,p"     |    |   `\`;    |    |
       theQuestionMark4242        "boo,._dP"       `\_  `\    `\|   `\   ;
                                 `"7tY~'            `\  `\    `|_   |
                                                      `~\  |
                                           
                  ????????????????????????????????????
                  ?______THE_QUESTION_MARK_4242______?
                  ????????????????????????????????????          
*/
unsigned long long int mergeSortComparisons = 0;
int C[1000010];
void mergeSort(int* A, int l, int r){
	if(l >= r) return;
	int mid = l+(r-l)/2;
	mergeSort(A, l, mid);
	mergeSort(A, mid + 1, r);

	int i = l;
	int j = mid + 1;

	int k = 0;
	while(i <= mid && j <= r){
		if(A[i] > A[j]) C[k++] = A[j++];
		else C[k++] = A[i++];
		mergeSortComparisons++;
	}
	while(i <= mid) C[k++] = A[i++];
	while(j <= r) C[k++] = A[j++];
	for(int c = l; c <= r; c++) A[c] = C[c-l];
}

int D[1000010];
int M[1000010], Q[1000010];
void improvedMergeSort(int* A, int l, int r){
	//We use a unified buffer for the merge step
	//This should decrease the time taken for the repeated allocation of 
	//the C[r-l+1] buffer for each interval we picked
	if(l >= r) return;
	int mid = l+(r-l)/2;
	improvedMergeSort(A, l, mid);
	improvedMergeSort(A, mid + 1, r);

	int i = l;
	int j = mid + 1;

       	int k = 0;
	while(i <= mid && j <= r){
		if(A[i] > A[j]) D[k++] = A[j++];
		else D[k++] = A[i++];
		mergeSortComparisons++;
	}
	while(i <= mid) D[k++] = A[i++];
	while(j <= r) D[k++] = A[j++];
	for(int c = l; c <= r; c++) A[c] = D[c-l];
}

unsigned long long int quickSortComparisons = 0;
int partition(int* A, int l, int r){
	//Partition range by A[l]
	// and return the index of where we end up putting the pivot 
	if(l >= r) return 0;
	int pivot = A[l];
	int upper_bound = r + 1;
	int i = l + 1;
	while(upper_bound > i){
		if(A[i] >= pivot){
			int temp = A[upper_bound-1];
			A[upper_bound-1] = A[i];
			A[i] = temp;
			upper_bound--;
		} 
		else i++;
		quickSortComparisons++;
	}
	int temp = A[upper_bound-1];
	A[upper_bound-1] = A[l];
	A[l] = temp;
	return upper_bound - 1;
}

int RNG(){
	int MAX_RANGE = 1000000;
	return (int) (((double) rand()/(double)RAND_MAX)*MAX_RANGE);
}

void quickSort(int* A, int l, int r){
	if(l >= r) return;
	int p = partition(A, l, r);
	quickSort(A, l, p - 1);
	quickSort(A, p + 1, r);
}

void comparisonsTest(){
	int n = 10;
	int ITERATIONS = 500;
	FILE* fp;
	fp = fopen("./comparisonsTest.txt", "w");
	for(int e = 0; e < 5; e++){
		n *= 10;
		mergeSortComparisons = 0;
		quickSortComparisons = 0;
		for(int j = 0; j < ITERATIONS; j++){
			for(int i = 0; i < n; i++) M[i] = Q[i] = RNG();
			quickSort(Q, 0, n-1);
			mergeSort(M, 0, n-1);					
		}	
		int avgMergeSortComparisons = (double) mergeSortComparisons/(double) ITERATIONS;		
		int avgQuickSortComparisons = (double) quickSortComparisons/(double) ITERATIONS;		
		fprintf(fp, "%d\t%d\t%d\n", n, avgMergeSortComparisons, avgQuickSortComparisons);
	}
	fclose(fp);
}

void timeComplexityQuickSort(){
	int I[5] = {1e5, 3e5, 5e5, 7e5, 9e5};
	int ITERATIONS = 500;
	FILE* fp;
	fp = fopen("./timeComplexityQuickSort.txt", "w");
	for (int i = 0; i < 5; i++){
		int n = I[i];
		clock_t time_taken;
		clock_t t = clock();
		for(int j = 0; j < ITERATIONS; j++){
			for(int i = 0; i < n; i++) Q[i] = RNG();
			quickSort(Q, 0, n-1);					
		}	
		time_taken = clock() - t;
		int time_ms = ((double)time_taken*1000000)/((double)CLOCKS_PER_SEC*ITERATIONS);
		fprintf(fp, "%d\t%d\n", n, time_ms);
	}
	fclose(fp);
}

void timeComplexityBoth(){
	int n = 10;
	int ITERATIONS = 500;
	FILE* fp;
	fp = fopen("./timeComplexityBoth.txt", "w");
	clock_t t1;
	clock_t time_taken1;
	clock_t t2;
	clock_t time_taken2;
	double total_time1 = 0;
	double total_time2 = 0;
	for(int e = 0; e < 5; e++){
		n *= 10;
		unsigned long long int msWins = 0;
		for(int j = 0; j < ITERATIONS; j++){
			for(int i = 0; i < n; i++) M[i] = Q[i] = RNG();
			t1 = clock();
			quickSort(Q, 0, n-1);
			time_taken1 = clock() - t1; 
			total_time1 += (double) time_taken1;
			t2 = clock();
			mergeSort(M, 0, n-1);	
			time_taken2 = clock() - t2;
			total_time2 += (double) time_taken2;				
			if(time_taken2 < time_taken1) msWins++;
		}	
		
		int quicksort_time_ms = (total_time1*1000000)/((double)CLOCKS_PER_SEC*ITERATIONS);
		
		int mergesort_time_ms = (total_time2*1000000)/((double)CLOCKS_PER_SEC*ITERATIONS);
		fprintf(fp, "%d\t%d\t%d\t%lld\n", n, quicksort_time_ms, mergesort_time_ms, msWins);
	}
	fclose(fp);
}


void timeComplexityBothImproved(){
		int n = 10;
	int ITERATIONS = 500;
	FILE* fp;
	fp = fopen("./timeComplexityBothImproved.txt", "w");
	clock_t t1;
	clock_t time_taken1;
	clock_t t2;
	clock_t time_taken2;
	double total_time1 = 0;
	double total_time2 = 0;
	for(int e = 0; e < 5; e++){
		n *= 10;
		int msWins = 0;
		for(int j = 0; j < ITERATIONS; j++){
			for(int i = 0; i < n; i++) M[i] = Q[i] = RNG();
			t1 = clock();
			quickSort(Q, 0, n-1);
			time_taken1 = clock() - t1; 
			total_time1 += (double) time_taken1;
			t2 = clock();
			mergeSort(M, 0, n-1);	
			time_taken2 = clock() - t2;
			total_time2 += (double) time_taken2;				
			if(time_taken2 < time_taken1) msWins++;
		}	
		
		int quicksort_time_ms = (total_time1*1000000)/((double)CLOCKS_PER_SEC*ITERATIONS);
		
		int mergesort_time_ms = (total_time2*1000000)/((double)CLOCKS_PER_SEC*ITERATIONS);
		fprintf(fp, "%d\t%d\t%d\t%d\n", n, quicksort_time_ms, mergesort_time_ms, msWins);
	}
	fclose(fp);
}

void QuickSortReliability(){
	int n = 10;
	int ITERATIONS = 500;
	FILE* fp;
	fp = fopen("./quickSortReliabilityTest.txt", "w");
	clock_t t;
	clock_t time_taken;
	double total_time = 0;
	for(int e = 0; e < 5; e++){
		n *= 10;
		for(int j = 0; j < ITERATIONS; j++){
			for(int i = 0; i < n; i++) Q[i] = RNG();
			t = clock();
			quickSort(Q, 0, n-1);
			time_taken = clock() - t; 
			total_time = (double) time_taken;		
			int quicksort_time_ms = (total_time*1000000)/((double)CLOCKS_PER_SEC*ITERATIONS);
			fprintf(fp, "%d\t%d\n", n, quicksort_time_ms);
		}	
	}
	fclose(fp);
}

int main(){	
	srand((unsigned) time(NULL));
	
	comparisonsTest();
	//timeComplexityQuickSort();
	//timeComplexityBoth();
	//timeComplexityBothImproved();
	//QuickSortReliability();
	
	return 0;
}


