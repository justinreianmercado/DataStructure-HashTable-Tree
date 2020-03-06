#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("Justin Mercado\n");
	int i = 0;
	int val = 0;
	float total = 0.0;
	printf("Enter 5 numbers and I will find the average (hit enter after each number)\n");

	while(i<5){
		scanf("%d",&val);
		total = total+val;
		printf("Summing: num %d\n",val);
		i++;
	}
	printf("Total is %f average is %f\n",total,total/5);
	exit(0);
}
