#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ITER 300
#define TOLERANCE 0.001
#define K 2
#define rows 6
#define columns 2

// A sample dataset
float X[][2] = {{1.0,2.0},
			    {1.5,1.8},
			    {5.0,8.0},
			    {8.0,8.0},
			    {1.0,0.6},
			    {9,11},
			  };

// Structure for storing centroid			  
struct centroid{
		int cluster_no;
		float centroids[K][2];	  // <-------Check over here too!
};

// Structure for storing clustering results
struct classification{
	struct classification* next;
	int featureset[][2];
};

struct centroid* init(){
	// Array to store initial centroids
	struct centroid *c = (struct centroid*)malloc(K * sizeof(struct centroid));
	return c;	
}

// Function to calculate distance between centroids and distance points
float* distance(float x, float y,int count){
	//printf("X: %f\n",x);
	//printf("Y: %f\n",y);
	int i,idx;
	float xs,ys,b;
	static float dis[rows*2];
	printf("COunt: %d\n",count);
	if(count == 0){
		printf("0 done");
		idx =0;
	}
	if(count == 1){
		printf("1 done");
		idx = (2*rows)/2;
		printf("Idx %d",idx);
	}
	
	for(i=0;i<rows;i++){
		printf("data: %f\n",X[i][0]);
		printf("data: %f\n",X[i][1]);
		xs = pow(x - X[i][0],2); // <---Check for change of value
		printf("XS: %f\n",xs);
		ys = pow(y - X[i][1],2);
		printf("YS: %f\n",ys);
		b = sqrt(xs+ys);
		printf("B: %f\n",b);
		dis[idx++] = b;
		printf("B: %f\n",dis[idx]);
	}
	for(i=0;i<12;i++){
		printf("Dis: %f\n",dis[i]);
	}
		return dis;
	
}
//<----------------MergeSort---------------->
void merge(int a[],int i1,int j1,int i2,int j2){
	int temp[j2-i1+1];
	int i,j,k;
	i=i1;
	j=i2;
	k=0;
	while(i<=j1 && j<=j2){
		if(a[i]<a[j]){
			temp[k++] = a[i++];
		}else{
			temp[k++] = a[j++];	
		}
	}
	while(i<=j1){
		temp[k++] = a[i++];
	}
	while(j<=j2){
		temp[k++] = a[j++];
	}
	
	for(i=i1,j=0;i<=j2;i++,j++){
		a[i] = temp[j];
	}
}

void mergesort(int a[],int i,int j){
	int mid;
	if(i<j){
		mid = (i+j)/2;
		mergesort(a,i,mid);
		mergesort(a,mid+1,j);
		merge(a,i,mid,mid+1,j);
	}
}
//<-------------------MergeSort Ends-------------->
// Function to train algorithm	
void fit(float X[][2], struct centroid* c){
	int i,j,k,count;
	float centre[columns][columns];
	float *p;
	for(i=0;i<K;i++){                  //<-----------//Look for K value over here 
		c[i].cluster_no = i;
		//printf("Cluster %d\n",c[i].cluster_no);
		for(j=0;j<columns;j++){
			c[i].centroids[i][j] = X[i][j];
			//printf("Centroids: %.1f\n",c[i].centroids[i][j]);
		}	
	}
	//printf("Hello %d\n",c[0].cluster_no);
	//printf("Centroids: %.1f\n",c[0].centroids[0][0]);
struct classification* classifications = (struct classification*)malloc(K * sizeof(struct classification));
for(i=0;i<K;i++){
	classifications[i].next= NULL;
}

for(i=0;i<K;i++){
	for(j=0;j<columns;j++){
		centre[i][j] = c[i].centroids[i][j];
	}
}
for(i=0,count=0;i<K;i++,count++){
	p = distance(centre[i][0],centre[i][1],i);
	/* for(k=0;k<rows*2;k++){
		printf("P: %f\n",p[k]);
	} */
}
mergesort(p,0,(rows*2)-1);
for(k=0;k<rows*2;k++){
	printf("Sorted array: %f\n",p[k]);
}
	
}
// Main function
int main(){
	int i;
	struct centroid* c = init();
	fit(X,c);
	printf("%d\n",c[1].cluster_no);
	printf("%d\n",c[1].centroids[0][0]);
	
}