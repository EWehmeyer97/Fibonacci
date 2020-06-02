//Evan Wehmeyer
#include <stdio.h>


int stepOne(int i1, int i2);
void stepTwo(FILE *read, int total);
void stepThree(FILE *read);
void stepFour();

int main(int argc, char** argv) {

	int a;
	printf("Your command line: ");
	for(a = 0; a < argc; a++){
		printf("%s ", *(argv + a));
	}
	printf("\n");


	if (argc != 4)
		printf("ERROR: Incorrect number of inputs!\n");
	else if (**(argv + 2) != '+')
		printf("ERROR: Did not find +!\n");
	else {
		short int x = 0;
		short int i;
		for(i = 0; *(*(argv + 1)+ i) != '\0'; i++) {
			if (*(*(argv + 1)+ i) < '0' || *(*(argv + 1)+ i) > '9')
				x = 1;
		}
		for(i = 0; *(*(argv + 3)+ i) != '\0'; i++) {
			if (*(*(argv + 3)+ i) < '0' || *(*(argv + 3)+ i) > '9')
				x = 1;
		}
		if (x)
			printf("ERROR: Invalid Arguments!\n");
		else {
			unsigned int i1 = atoi(*(argv + 1));
			unsigned int i2 = atoi(*(argv + 3));
			if (i1 + i2 < 3)
				printf("ERROR: Invalid Arguments!\n");
			else {				
				int total = stepOne(i1, i2);

				FILE *read = fopen("Fibonacci", "r");

				printf("\n2. The Fibonacci median: ");

				stepTwo(read, total);

				printf("\n3. Even and Odd Separation:\n");
				rewind(read);
			
				stepThree(read);

				fclose(read);
				
				stepFour();
				
			}
		}
	}
}

int stepOne(int i1, int i2) {
	unsigned int sum = i1 + i2;
	printf("Calculating %u Fibonacci numbers\n", sum);
	printf("\n1. File Fibonacci content:\n");
	FILE *out = fopen("Fibonacci", "w");

	unsigned long long int f1 = 1, f2 = 1;
	printf("	1	1");
	fprintf(out, "	1	1");
	int total = 2;
	sum -= 2;
				
	while (sum--) {
		unsigned long long int temp = f2;
		f2 += f1;
		f1 = temp;
		if (f2 < f1) {
			printf("\nERROR: Number is too larger!\n");
			break;
		}
		else {
			printf("	%llu", f2);
			fprintf(out, "	%llu", f2);
			total++;
			if (!(total % 4)) {
				printf("\n");	
				fprintf(out, "\n");
			}			
		}
	}
	if (total % 4) {
		printf("\n");
		fprintf(out, "\n");
	}
	printf("\nTotal: %d numbers in Fibonacci\n", total);
	fprintf(out, "\nTotal: %d numbers in Fibonacci\n", total);
	fclose(out); //STEP ONE DONE
	return total;
}

void stepTwo(FILE *read, int total) {
	int num;
	if (total % 2) {
		unsigned long long int median;
		for(num = 0; num < (total/2); num++)
			fscanf(read, "%llu", &median);
		fscanf(read, "%llu", &median);
		printf("%llu.00\n", median); //.00 added for same look between totals
	} else {
		unsigned long long int m1, m2;
		for(num = 0; num < (total/2); num++)
			fscanf(read, "%llu", &m1);
		fscanf(read, "%llu", &m2);
		double m3 = m1;
		m3 = (m3 + m2) / 2;
		printf("%.2lf\n", m3);
	}
	
}

void stepThree(FILE *read) {
	unsigned long long int num;
	int oCount = 0, eCount = 0;
	FILE *odd = fopen("Fibonacci.odd", "w");
	FILE *even = fopen("Fibonacci.even", "w");
	int check = fscanf(read, "%llu", &num);
	while(check == 1){
		
		if(num % 2) {
			fprintf(odd, "	%llu", num);
			oCount++;
			if(!(oCount % 4))
				fprintf(odd, "\n");
		} else {
			fprintf(even, "	%llu", num);
			eCount++;
			if(!(eCount % 4))
				fprintf(even, "\n");
		}
		check = fscanf(read, "%llu", &num);
	}
	fclose(odd);
	fclose(even);
	printf("%d numbers in Fibonacci.even\n", eCount);
	printf("%d numbers in Fibonacci.odd\n", oCount);

	FILE *eRead = fopen("Fibonacci.even", "r");
	FILE *oRead = fopen("Fibonacci.odd", "r");

	printf("Fibonacci.even medium: ");
	stepTwo(eRead, eCount);
	printf("Fibonacci.odd medium: ");
	stepTwo(oRead, oCount);
}

void stepFour() {
	printf("\n4. Total count in Fibonacci.odd: ");
	FILE *oRead = fopen("Fibonacci.odd", "r");
	FILE *oAppend = fopen("Fibonacci.odd", "a");
	FILE *eRead = fopen("Fibonacci.even", "r");
	int total = 0;
	unsigned long long int x;
	int check = fscanf(oRead, "%llu", &x);
	while(check == 1) {
		total++;
		check = fscanf(oRead, "%llu", &x);
		x = 0;
	}
	rewind(oRead);
	check = fscanf(eRead, "%llu", &x);
	while(check == 1) {
		total++;
		fprintf(oAppend, "	%llu", x);
		if(!(total % 6))
			fprintf(oAppend, "\n");
		check = fscanf(eRead, "%llu", &x);
	}
	printf("%d\n", total);
	fclose(eRead);
	fclose(oAppend);
	int count = 0;
	while(total--){
		fscanf(oRead, "%llu", &x);
		printf("	%llu", x);
		count++;
		if(!(count % 5))
			printf("\n");
	}

	printf("\n");


}




