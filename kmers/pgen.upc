#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <upc.h>

#include "packingDNAseq.h"
#include "kmer_hash_dist.h"

//#define CHECK_TABLE

shared kmer_t heap [HEAP_SIZE * THREADS];
shared bucket_t buckets [THREADS * HASH_SIZE];

int starts [HASH_SIZE];
int pos = 0;
int n_starts = 0;
kmer_t lookup;

int main(int argc, char *argv[]){

    /** Declarations **/
    double inputTime=0.0, constrTime=0.0, traversalTime=0.0;

    /** Read input **/
    upc_barrier;
    inputTime -= gettime();

    ///////////////////////////////////////////
    // Your code for input file reading here //
    ///////////////////////////////////////////

    time_t start, end;
    char cur_contig[MAXIMUM_CONTIG_SIZE], unpackedKmer[KMER_LENGTH+1], left_ext, right_ext, *input_UFX_name;
    int64_t posInContig, contigID = 0, totBases = 0, ptr = 0, nKmers, cur_chars_read, total_chars_to_read;
    unpackedKmer[KMER_LENGTH] = '\0';
    kmer_t cur_kmer;
    start_kmer_t *startKmersList = NULL, *curStartNode;
    unsigned char *working_buffer;
    FILE *inputFile;
    /* Read the input file name */

    init_LookupTable();


    input_UFX_name = argv[1];

    nKmers = getNumKmersInUFX(input_UFX_name);

    /* Read the kmers from the input file and store them in the working_buffer */
    total_chars_to_read = nKmers * LINE_SIZE;
    working_buffer = (unsigned char*) malloc(total_chars_to_read * sizeof(unsigned char));
    inputFile = fopen(input_UFX_name, "r");
    cur_chars_read = fread(working_buffer, sizeof(unsigned char),total_chars_to_read , inputFile);
    fclose(inputFile);

    upc_barrier;
    inputTime += gettime();


    /** Graph construction **/
    constrTime -= gettime();

    upc_lock_t **locks = malloc(HASH_SIZE *sizeof(upc_lock_t*));
    int i;
    for(i = 0; i < HASH_SIZE; ++i){
        locks[i] = upc_all_lock_alloc();
    }

    /* Process the working_buffer and store the k-mers in the hash table */
    /* Expected format: KMER LR ,i.e. first k characters that represent the kmer, then a tab and then two chatacers, one for the left (backward) extension and one for the right (forward) extension */
    ptr = MYTHREAD * LINE_SIZE;
    pos = MYTHREAD;

    upc_barrier;

    while ((ptr < cur_chars_read) && (pos < HEAP_SIZE)) {
        /* working_buffer[ptr] is the start of the current k-mer                */
        /* so current left extension is at working_buffer[ptr+KMER_LENGTH+1]    */
        /* and current right extension is at working_buffer[ptr+KMER_LENGTH+2]  */

        left_ext = (char) working_buffer[ptr + KMER_LENGTH + 1];
        right_ext = (char) working_buffer[ptr + KMER_LENGTH + 2];

        /* Add k-mer to hash table */
        //add_kmer(hashtable, &memory_heap, &working_buffer[ptr], left_ext, right_ext);
        add_kmer(buckets, heap, pos, &working_buffer[ptr], left_ext, right_ext, locks);

        /*
     * Check that if we lookup the kmer we find the appropriate result
     */
#ifdef CHECK_TABLE

        lookup = lookup_kmer(buckets, heap, &working_buffer[ptr]);
        kmer_t temp = lookup;

        char packedKmer[KMER_PACKED_LENGTH];
        packSequence(&working_buffer[ptr], (unsigned char *) packedKmer, KMER_LENGTH);

        for (int i = 0; i < KMER_PACKED_LENGTH; ++i) {
            assert(packedKmer[i] == temp.kmer[i]);
        }

#endif

        /* Create also a list with the "start" kmers: nodes with F as left (backward) extension */
        if (left_ext == 'F') {
            starts[n_starts] = pos;
            ++n_starts;
        }

        /* Move to the next k-mer in the input working_buffer */
        ptr += LINE_SIZE * THREADS;

        pos += THREADS;

    }
    upc_barrier;
    constrTime += gettime();

    printf("Initialized hash table with %d elements and got %d start positions\n", pos, n_starts);

    /** Graph traversal **/
    traversalTime -= gettime();
    ////////////////////////////////////////////////////////////
    // Your code for graph traversal and output printing here //
    // Save your output to "pgen.out"                         //
    ////////////////////////////////////////////////////////////
    char filename[80];
    FILE *serialOutputFile;
    sprintf(filename, "pgen_%d.out", MYTHREAD);

    serialOutputFile = fopen(filename, "w");
    kmer_t current_start;
    for(int i = n_starts - 1; i >= 0; --i){

        current_start = heap[starts[i]];
        cur_kmer = current_start;
        unpackSequence((unsigned char*) current_start.kmer,  (unsigned char*) unpackedKmer, KMER_LENGTH);

        /* Initialize current contig with the seed content */
        memcpy(cur_contig ,unpackedKmer, KMER_LENGTH * sizeof(char));
        posInContig = KMER_LENGTH;
        right_ext = current_start.r_ext;

        /* Keep adding bases while not finding a terminal node */
        while (right_ext != 'F') {
            cur_contig[posInContig] = right_ext;
            posInContig++;
            /* At position cur_contig[posInContig-KMER_LENGTH] starts the last k-mer in the current contig */
            lookup = lookup_kmer(buckets, heap, (const unsigned char *) &cur_contig[posInContig-KMER_LENGTH]);

            if(lookup.next == -1){
                exit(2);
            }

            cur_kmer = lookup;
            right_ext = cur_kmer.r_ext;
        }

        /* Print the contig since we have found the corresponding terminal node */
        cur_contig[posInContig] = '\0';
        fprintf(serialOutputFile,"%s\n", cur_contig);
        contigID++;
        totBases += strlen(cur_contig);

    }

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
