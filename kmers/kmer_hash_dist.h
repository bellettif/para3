#ifndef KMER_HASH_H
#define KMER_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h> 
#include <string.h>
#include "dist_generation.h"

/* Auxiliary function for computing hash values */
int64_t hashseq(char *seq, int size)
{
   unsigned long hashval;
   hashval = 5381;
   for(int i = 0; i < size; i++) {
      hashval = seq[i] +  (hashval << 5) + hashval;
   }

   return hashval % (HASH_SIZE * THREADS);
}

/* Returns the hash value of a kmer */
int64_t hashkmer(char *seq)
{
   return hashseq(seq, KMER_PACKED_LENGTH);
}

/* Looks up a kmer in the hash table and returns a pointer to that entry */
shared kmer_t* lookup_kmer(shared bucket_t *buckets, shared kmer_t *heap, const unsigned char *kmer)
{

   char packedKmer[KMER_PACKED_LENGTH];
   packSequence(kmer, (unsigned char*) packedKmer, KMER_LENGTH);
   int64_t hashval = hashkmer((char*) packedKmer);
   bucket_t cur_bucket;
   shared kmer_t *result;

   //upc_memget_nb(&cur_bucket, buckets + hashval, sizeof(bucket_t));
   cur_bucket = buckets[hashval];

   result = heap + cur_bucket.head;

   kmer_t other;

   for (; result!=NULL; ) {

	  //upc_memget_nb(&other, result, sizeof(kmer_t));
      other = *result;

      if ( memcmp(packedKmer, other.kmer, KMER_PACKED_LENGTH * sizeof(char)) == 0 ) {
         return result;
      }
      result = heap + result->next;

   }
   return NULL;
}

/* Adds a kmer and its extensions in the hash table (note that a memory heap should be preallocated. ) */
int add_kmer(shared bucket_t *buckets, shared kmer_t *heap, int pos, const unsigned char *kmer, char left_ext, char right_ext)
{
   /* Pack a k-mer sequence appropriately */
   char packedKmer[KMER_PACKED_LENGTH];
   packSequence(kmer, (unsigned char*) packedKmer, KMER_LENGTH);
   int64_t hashval = hashkmer((char*) packedKmer);

   /* Add the contents to the appropriate kmer struct in the heap */
   kmer_t to_mod = heap[pos];
   //upc_memget_nb(&to_mod, heap + pos, sizeof(kmer_t));

   memcpy(to_mod.kmer, packedKmer, KMER_PACKED_LENGTH * sizeof(char));
   to_mod.l_ext = left_ext;
   to_mod.r_ext = right_ext;

   bucket_t target_bucket = buckets[hashval];
   //upc_memget_nb(&target_bucket, buckets + hashval, sizeof(bucket_t));

   /* Fix the next pointer to point to the appropriate kmer struct */
   to_mod.next = target_bucket.head;
   //upc_memput_nb(heap + pos, &to_mod, sizeof(kmer_t));
   heap[pos] = to_mod;

   /* Fix the head pointer of the appropriate bucket to point to the current kmer */
   target_bucket.head = pos;
   //upc_memput_nb(buckets + hashval, &target_bucket, sizeof(bucket_t));
   buckets[hashval] = target_bucket;

   return 0;
}

#endif // KMER_HASH_H
