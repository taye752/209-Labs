/*
 * 209Lab.c
 *
 * Created: 4/08/2026 4:29:31 PM
 * Author : taye752
 */ 

#include <avr/io.h>


int main(void)
{
    //create an array of all prime numbers up to 300
	int j = 0;
	int primeArray[100];
	for (int i = 2; i < 301; i++) {
		int notPrime = 0;
		for (int dividor = 2; dividor < i; dividor++) {
			if (i % dividor == 0) { //checking if prime
			notPrime = 1;
			break;
			}
		}
		
		if (notPrime == 0) {
			primeArray[j] = i;
			j++;
		}
	}
	
    while (1) 
    {
    }
}


