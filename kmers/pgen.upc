#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <upc.h>

#include "packingDNAseq.h"
#include "kmer_hash_dist.h"

shared [16] kmer_t heap [THREADS * 1024];
shared [16] bucket_t buckets [THREADS * 1024];
shared [16] kmer_t starts [THREADS * 1024]; 

shared int pos = 0;
shared int n_starts = 0;

int main(int argc, char *argv[]){

	/** Declarations **/
	double inputTime=0.0, constrTime=0.0, traversalTime=0.0;

	/** Read input **/
	upc_barrier;
	inputTime -= gettime();

	///////////////////////////////////////////
	// Your code for input file reading here //
	///////////////////////////////////////////         
	if(MYTHREAD == 0){

	time_t start, end;
   	double constrTime, traversalTime;
   	char cur_contig[MAXIMUM_CONTIG_SIZE], unpackedKmer[KMER_LENGTH+1], left_ext, right_ext, *input_UFX_name;
   	int64_t posInContig, contigID = 0, totBases = 0, ptr = 0, nKmers, cur_chars_read, total_chars_to_read;
   	unpackedKmer[KMER_LENGTH] = '\0';
   	kmer_t *cur_kmer_ptr;
   	start_kmer_t *startKmersList = NULL, *curStartNode;
   	unsigned char *working_buffer;
   	FILE *inputFile, *serialOutputFile;
   	/* Read the input file name */
   	input_UFX_name = argv[1];
	nKmers = getNumKmersInUFX(input_UFX_name);
	total_chars_to_read = nKmers * LINE_SIZE;
	inputFile = fopen(input_UFX_name, "r");
   	cur_chars_read = fread(working_buffer, sizeof(unsigned char),total_chars_to_read , inputFile);
   	fclose(inputFile);

	while (ptr < cur_chars_read) {
	/* working_buffer[ptr] is the start of the current k-mer                */
	/* so current left extension is at working_buffer[ptr+KMER_LENGTH+1]    */
	/* and current right extension is at working_buffer[ptr+KMER_LENGTH+2]  */

	left_ext = (char) working_buffer[ptr+KMER_LENGTH+1];
	right_ext = (char) working_buffer[ptr+KMER_LENGTH+2];

	add_kmer(buckets, heap, pos, &working_buffer[ptr], left_ext, right_ext);
	
	if (left_ext == 'F') {
        	kmer_t temp;
        	upc_memget_nb(&temp, heap + pos, sizeof(kmer_t));	
		upc_memput_nb(starts + n_starts, &temp, sizeof(kmer_t));
        	++n_starts;
	}
	
	++pos;

	}

	}

	upc_barrier;
	inputTime += gettime();

	/** Graph construction **/
	constrTime -= gettime();
	///////////////////////////////////////////
	// Your code for graph construction here //
	///////////////////////////////////////////
	upc_barrier;
	constrTime += gettime();

	/** Graph traversal **/
	traversalTime -= gettime();
	////////////////////////////////////////////////////////////
	// Your code for graph traversal and output printing here //
	// Save your output to "pgen.out"                         //
	////////////////////////////////////////////////////////////
	upc_barrier;
	traversalTime += gettime();

	/** Print timing and output info **/
	/***** DO NOT CHANGE THIS PART ****/
	if(MYTHREAD==0){
		printf("%s: Input set: %s\n", argv[0], argv[1]);
		printf("Number of UPC threads: %d\n", THREADS);
		printf("Input reading time: %f seconds\n", inputTime);
		printf("Graph construction time: %f seconds\n", constrTime);
		printf("Graph traversal time: %f seconds\n", traversalTime);
	}
	return 0;
}
