#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#include "papi.h"
#include "assert.h"

#define REPEAT 10000000

using namespace std;

typedef unsigned __int128 uint128_t;

int eval_prime(unsigned *map, char *word1, char *word2);
int eval_freq(char *word1, char *word2);
void display_usage() {
	printf("Usage: ./anagram_checker <word1> <word2>\n");
}
long_long get_time() {
	return PAPI_get_virt_usec();
}

int main(int argc, char **argv) {

	if (argc < 2) {
		display_usage();
		exit(1);
	}

	//////////////////// SETUP ///////////////////////
	char *word1 = argv[1];
	char *word2 = argv[2];

	unsigned primes[26] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
	unsigned order[26] = {2,17,10,12,1,18,16,15,4,25,21,9,14,7,5,13,26,3,8,6,11,22,20,23,19,24};

	// construct map
	unsigned map[26]; 
	for (int i=0;i<26;i++){
		map[i] = primes[order[i]-1];
	}
	//////////////////////////////////////////////////

	int isAnagram0, isAnagram1 ,isAnagram2;
	long_long t0,t1;

	///////////////////// Start timing different implementations ///////////////////////////

	// evaluate using the frequency-bin method
	t0 = get_time();
	for (int i=0;i<REPEAT;i++) {
		isAnagram0 = eval_freq(word1,word2);
	}
	t1 = get_time();
	printf("[FREQ] %f microseconds/evaluation\n",(t1-t0)/((float)REPEAT));

	// evaluate using the prime method (unordered primes)
	t0 = get_time();
	for (int i=0;i<REPEAT;i++) {
		isAnagram1 = eval_prime(primes,word1,word2);
	}
	t1 = get_time();
	printf("[PRIME] %f microseconds/evaluation\n",(t1-t0)/((float)REPEAT));
	
	// evaluate using the prime method (primes assigned by alphabet frequency in written language)
	t0 = get_time();
	for (int i=0;i<REPEAT;i++) {
		isAnagram2 = eval_prime(map,word1,word2);
	}
	t1 = get_time();
	printf("[PRIME-ORD] %f microseconds/evaluation\n",(t1-t0)/((float)REPEAT));

	assert(isAnagram0==isAnagram1); // sanity check
	assert(isAnagram0==isAnagram2); // sanity check

	if (isAnagram0) {
		printf("%s and %s are anagrams\n",word1,word2);
	} else {
		printf("%s and %s are NOT anagrams\n",word1,word2);
	}

	return 0;
}

int eval_prime(unsigned *map, char *word1, char *word2) {

	// compute prime mult of word 1
	uint128_t product1 = 1;
	for(int i=0;word1[i]!='\0';i++) {
		product1 *= map[(int)(word1[i])-97];
	}
	uint128_t product2 = 1;
	for(int i=0;word2[i]!='\0';i++) {
		product2 *= map[(int)(word2[i])-97];
	}

	return (product1 == product2);
}

int eval_freq(char *word1, char *word2) {

	int *freq1 = (int *)calloc(26,sizeof(int));
	int *freq2 = (int *)calloc(26,sizeof(int));
	int length1 = 0, length2 = 0;
	for (int i=0;word1[i]!='\0';i++) {
		freq1[(int)word1[i]-97]++;
		length1++;
	}
	for (int i=0;word2[i]!='\0';i++) {
		freq2[(int)word2[i]-97]++;
		length2++;
	}
	
	if (length1 != length2)
		return 0;

	for (int i=0;i<26;i++) {
		if (freq1[i] != freq2[i])
			return 0;
	}

	return 1;
}
