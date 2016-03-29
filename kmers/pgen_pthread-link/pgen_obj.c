/* --- UPCR system headers --- */ 
#include "upcr.h" 
#include "whirl2c.h"
#include "upcr_proxy.h"
/*******************************************************
 * C file translated from WHIRL Tue Mar 29 14:09:30 2016
 *******************************************************/

/* UPC Runtime specification expected: 3.6 */
#define UPCR_WANT_MAJOR 3
#define UPCR_WANT_MINOR 6
/* UPC translator version: release 2.22.0, built on Oct 30 2015 at 14:53:24, host edison05 linux-x86_64/64, gcc v4.3.4 [gcc-4_3-branch revision 152973] */
/* Included code from the initialization script */
#include</global/common/edison/ftg/upc/2.22.0/PrgEnv-gnu-5.2.56-5.2.0/runtime/inst/opt/include/upcr_config.h>
#include</global/common/edison/ftg/upc/2.22.0/PrgEnv-gnu-5.2.56-5.2.0/runtime/inst/opt/include/portable_platform.h>
#include "upcr_geninclude/stdio.h"
#include "upcr_geninclude/string.h"
#include "upcr_geninclude/stdlib.h"
#include</usr/include/sys/time.h>
#include "upcr_geninclude/math.h"
#include "upcr_geninclude/time.h"
#include</global/common/edison/ftg/upc/2.22.0/PrgEnv-gnu-5.2.56-5.2.0/runtime/inst/opt/include/upcr_preinclude/upc_types.h>
#include "upcr_geninclude/stddef.h"
#include</global/common/edison/ftg/upc/2.22.0/PrgEnv-gnu-5.2.56-5.2.0/runtime/inst/opt/include/upcr_preinclude/upc_bits.h>
#include "upcr_geninclude/stdlib.h"
#include "upcr_geninclude/inttypes.h"
#include</global/u1/b/belletti/para3/kmers/packingDNAseq.h>
#include "upcr_geninclude/stdio.h"
#include "upcr_geninclude/stdlib.h"
#include "upcr_geninclude/math.h"
#include "upcr_geninclude/string.h"
#include</global/u1/b/belletti/para3/kmers/dist_generation.h>
#line 1 "pgen.w2c.h"
/* Include builtin types and operators */

#ifndef UPCR_TRANS_EXTRA_INCL
#define UPCR_TRANS_EXTRA_INCL
extern int upcrt_gcd (int _a, int _b);
extern int _upcrt_forall_start(int _start_thread, int _step, int _lo, int _scale);
#define upcrt_forall_start(start_thread, step, lo, scale)  \
       _upcrt_forall_start(start_thread, step, lo, scale)
int32_t UPCR_TLD_DEFINE_TENTATIVE(upcrt_forall_control, 4, 4);
#define upcr_forall_control upcrt_forall_control
#ifndef UPCR_EXIT_FUNCTION
#define UPCR_EXIT_FUNCTION() ((void)0)
#endif
#if UPCR_RUNTIME_SPEC_MAJOR > 3 || (UPCR_RUNTIME_SPEC_MAJOR == 3 && UPCR_RUNTIME_SPEC_MINOR >= 8)
  #define UPCRT_STARTUP_SHALLOC(sptr, blockbytes, numblocks, mult_by_threads, elemsz, typestr) \
      { &(sptr), (blockbytes), (numblocks), (mult_by_threads), (elemsz), #sptr, (typestr) }
#else
  #define UPCRT_STARTUP_SHALLOC(sptr, blockbytes, numblocks, mult_by_threads, elemsz, typestr) \
      { &(sptr), (blockbytes), (numblocks), (mult_by_threads) }
#endif
#define UPCRT_STARTUP_PSHALLOC UPCRT_STARTUP_SHALLOC

/**** Autonb optimization ********/

extern void _upcrt_memput_nb(upcr_shared_ptr_t _dst, const void *_src, size_t _n);
#define upcrt_memput_nb(dst, src, n) \
       (upcri_srcpos(), _upcrt_memput_nb(dst, src, n))

#endif


/* Types */
/* File-level vars and routines */
extern long hashseq(char *, int);

extern long hashkmer(char *);

extern upcr_pshared_ptr_t lookup_kmer(upcr_pshared_ptr_t, upcr_pshared_ptr_t, const unsigned char *);

extern int add_kmer(upcr_pshared_ptr_t, upcr_pshared_ptr_t, int, const unsigned char *, char, char);

extern int user_main(int, char **);


#define UPCR_SHARED_SIZE_ 16
#define UPCR_PSHARED_SIZE_ 16
upcr_pshared_ptr_t heap;
upcr_pshared_ptr_t buckets;
upcr_pshared_ptr_t starts;
upcr_pshared_ptr_t pos = UPCR_INITIALIZED_PSHARED;
upcr_pshared_ptr_t n_starts = UPCR_INITIALIZED_PSHARED;
upcr_pshared_ptr_t UPCR_TLD_DEFINE_TENTATIVE(lookup, 16, 8);

void UPCRI_ALLOC_pgen_6953898206118(void) { 
UPCR_BEGIN_FUNCTION();
upcr_startup_pshalloc_t _bupc_pinfo[] = { 
UPCRT_STARTUP_PSHALLOC(heap, 12, 16777216, 1, 12, "A16777216H_R1_N6kmer_t"), 
UPCRT_STARTUP_PSHALLOC(buckets, 4, 4514197, 1, 4, "A4514197H_R1_N8bucket_t"), 
UPCRT_STARTUP_PSHALLOC(starts, 4, 16777216, 1, 4, "A16777216H_R1_i"), 
UPCRT_STARTUP_PSHALLOC(pos, 4, 1, 0, 4, "R1_i"), 
UPCRT_STARTUP_PSHALLOC(n_starts, 4, 1, 0, 4, "R1_i"), 
 };

UPCR_SET_SRCPOS("_pgen_6953898206118_ALLOC",0);
upcr_startup_pshalloc(_bupc_pinfo, sizeof(_bupc_pinfo) / sizeof(upcr_startup_pshalloc_t));
}

void UPCRI_INIT_pgen_6953898206118(void) { 
UPCR_BEGIN_FUNCTION();
int32_t _bupc_pos_val = 0;
int32_t _bupc_n_starts_val = 0;
UPCR_SET_SRCPOS("_pgen_6953898206118_INIT",0);
if (upcr_mythread()== 0) { 
upcr_put_pshared(pos, 0, &_bupc_pos_val, 4);
}
if (upcr_mythread()== 0) { 
upcr_put_pshared(n_starts, 0, &_bupc_n_starts_val, 4);
}
}

#line 13 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
extern long hashseq(
  char * seq,
  int size)
#line 13 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
{
#line 13 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  UPCR_BEGIN_FUNCTION();
  unsigned long hashval;
  int i;
  
#line 15 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  hashval = 5381ULL;
#line 16 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  i = 0;
#line 16 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  while(i < size)
#line 16 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  {
#line 17 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    hashval = hashval + ((_UINT64)((unsigned long) * (seq + i)) + _U8SHL(hashval, (_UINT64)(5)));
#line 18 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    _1 :;
#line 18 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    i = i + 1;
  }
#line 20 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  UPCR_EXIT_FUNCTION();
#line 20 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  return(_INT64)(hashval % (_UINT64)((((int) upcr_threads () ) * 4514197)));
} /* hashseq */


#line 25 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
extern long hashkmer(
  char * seq)
#line 25 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
{
#line 25 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  UPCR_BEGIN_FUNCTION();
  register _INT64 _bupc_comma;
  
#line 26 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_comma = hashseq(seq, (int) 5);
#line 26 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  UPCR_EXIT_FUNCTION();
#line 26 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  return _bupc_comma;
} /* hashkmer */


#line 31 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
extern upcr_pshared_ptr_t lookup_kmer(
  upcr_pshared_ptr_t _bupc_w2c_buckets0,
  upcr_pshared_ptr_t _bupc_w2c_heap0,
  const unsigned char * kmer)
#line 31 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
{
#line 31 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  UPCR_BEGIN_FUNCTION();
  register _INT64 _bupc_comma;
  register _INT64 _bupc_reg8;
  register _INT32 _bupc_comma0;
  char packedKmer[5LL];
  long hashval;
  struct bucket_t cur_bucket;
  upcr_pshared_ptr_t result;
  struct kmer_t other;
  int _bupc__spilleq3;
  upcr_pshared_ptr_t _bupc_Mptra1;
  upcr_shared_ptr_t _bupc_Mstopcvt2;
  upcr_pshared_ptr_t _bupc_Mptra3;
  upcr_shared_ptr_t _bupc_Mstopcvt4;
  int _bupc_spillld5;
  upcr_pshared_ptr_t _bupc_Mptra6;
  _INT32 _bupc_Mptreq7;
  
#line 34 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  packSequence(kmer, (unsigned char *) packedKmer, (int) 19);
#line 35 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_comma = hashkmer(packedKmer);
#line 35 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  hashval = _bupc_comma;
#line 39 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mptra1 = UPCR_ADD_PSHARED1(_bupc_w2c_buckets0, 4ULL, hashval);
#line 39 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mstopcvt2 = UPCR_PSHARED_TO_SHARED(_bupc_Mptra1);
#line 39 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  upc_memget_nb(&cur_bucket, _bupc_Mstopcvt2, (unsigned long) 4ULL);
#line 41 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mptra3 = UPCR_ADD_PSHARED1(_bupc_w2c_heap0, 12ULL, (cur_bucket).head);
#line 41 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  result = _bupc_Mptra3;
#line 54 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_reg8 = UPCR_ISNULL_PSHARED(result);
  _bupc_Mptreq7 = !(_INT32) _bupc_reg8;
#line 45 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  while(_bupc_Mptreq7)
#line 45 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  {
#line 47 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    _bupc_Mstopcvt4 = UPCR_PSHARED_TO_SHARED(result);
#line 47 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    upc_memget_nb(&other, _bupc_Mstopcvt4, (unsigned long) 12ULL);
#line 49 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    _bupc_comma0 = memcmp(packedKmer, &other, (unsigned long) 5ULL);
#line 49 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    _bupc__spilleq3 = _bupc_comma0;
#line 49 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    if(_bupc__spilleq3 == 0)
#line 49 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    {
#line 50 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
      return (result);
    }
#line 52 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    UPCR_GET_PSHARED(&_bupc_spillld5, result, 8, 4);
#line 52 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    _bupc_Mptra6 = UPCR_ADD_PSHARED1(_bupc_w2c_heap0, 12ULL, _bupc_spillld5);
#line 52 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    result = _bupc_Mptra6;
#line 54 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    _1 :;
#line 54 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
    _bupc_reg8 = UPCR_ISNULL_PSHARED(result);
    _bupc_Mptreq7 = !(_INT32) _bupc_reg8;
  }
#line 55 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  return (upcr_null_pshared);
} /* lookup_kmer */


#line 60 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
extern int add_kmer(
  upcr_pshared_ptr_t _bupc_w2c_buckets0,
  upcr_pshared_ptr_t _bupc_w2c_heap0,
  int _bupc_w2c_pos0,
  const unsigned char * kmer,
  char left_ext,
  char right_ext)
#line 60 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
{
#line 60 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  UPCR_BEGIN_FUNCTION();
  register _INT64 _bupc_comma;
  char packedKmer[5LL];
  long hashval;
  struct kmer_t to_mod;
  struct bucket_t target_bucket;
  upcr_pshared_ptr_t _bupc_Mptra8;
  upcr_shared_ptr_t _bupc_Mstopcvt9;
  upcr_pshared_ptr_t _bupc_Mptra10;
  upcr_shared_ptr_t _bupc_Mstopcvt11;
  upcr_pshared_ptr_t _bupc_Mptra12;
  upcr_shared_ptr_t _bupc_Mstopcvt13;
  upcr_pshared_ptr_t _bupc_Mptra14;
  upcr_shared_ptr_t _bupc_Mstopcvt15;
  
#line 63 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  packSequence(kmer, (unsigned char *) packedKmer, (int) 19);
#line 64 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_comma = hashkmer(packedKmer);
#line 64 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  hashval = _bupc_comma;
#line 68 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mptra8 = UPCR_ADD_PSHARED1(_bupc_w2c_heap0, 12ULL, _bupc_w2c_pos0);
#line 68 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mstopcvt9 = UPCR_PSHARED_TO_SHARED(_bupc_Mptra8);
#line 68 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  upc_memget_nb(&to_mod, _bupc_Mstopcvt9, (unsigned long) 12ULL);
#line 70 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  memcpy(&to_mod, (const void *)(packedKmer), (unsigned long) 5ULL);
#line 71 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  to_mod.l_ext = left_ext;
#line 72 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  to_mod.r_ext = right_ext;
#line 75 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mptra10 = UPCR_ADD_PSHARED1(_bupc_w2c_buckets0, 4ULL, hashval);
#line 75 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mstopcvt11 = UPCR_PSHARED_TO_SHARED(_bupc_Mptra10);
#line 75 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  upc_memget_nb(&target_bucket, _bupc_Mstopcvt11, (unsigned long) 4ULL);
#line 78 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  to_mod.next = (target_bucket).head;
#line 79 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mptra12 = UPCR_ADD_PSHARED1(_bupc_w2c_heap0, 12ULL, _bupc_w2c_pos0);
#line 79 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mstopcvt13 = UPCR_PSHARED_TO_SHARED(_bupc_Mptra12);
#line 79 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  upc_memput_nb(_bupc_Mstopcvt13, &to_mod, (unsigned long) 12ULL);
#line 82 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  target_bucket.head = _bupc_w2c_pos0;
#line 83 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mptra14 = UPCR_ADD_PSHARED1(_bupc_w2c_buckets0, 4ULL, hashval);
#line 83 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  _bupc_Mstopcvt15 = UPCR_PSHARED_TO_SHARED(_bupc_Mptra14);
#line 83 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  upc_memput_nb(_bupc_Mstopcvt15, &target_bucket, (unsigned long) 4ULL);
#line 85 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  UPCR_EXIT_FUNCTION();
#line 85 "/global/u1/b/belletti/para3/kmers/kmer_hash_dist.h"
  return 0;
} /* add_kmer */


#line 22 "pgen.upc"
extern int user_main(
  int argc,
  char ** argv)
#line 22 "pgen.upc"
{
#line 22 "pgen.upc"
  UPCR_BEGIN_FUNCTION();
  register _IEEE64 _bupc_comma;
  register _INT64 _bupc_comma0;
  register _UINT64 _bupc_comma1;
  register _IEEE64 _bupc_comma2;
  register _IEEE64 _bupc_comma3;
  register _UINT64 _bupc_comma4;
  register _IEEE64 _bupc_comma5;
  register _IEEE64 _bupc_comma6;
  register _IEEE64 _bupc_comma7;
  _IEEE64 inputTime;
  _IEEE64 constrTime;
  _IEEE64 traversalTime;
  long contigID;
  long totBases;
  long ptr;
  char unpackedKmer[20LL];
  struct start_kmer_t * startKmersList;
  char * input_UFX_name;
  long nKmers;
  long total_chars_to_read;
  unsigned char * _bupc__casttmp4;
  unsigned char * working_buffer;
  struct _IO_FILE * inputFile;
  long cur_chars_read;
  char left_ext;
  char right_ext;
  struct kmer_t temp;
  char packedKmer[5LL];
  int i;
  _INT32 _bupc_Mspillpost5;
  char filename[80LL];
  struct _IO_FILE * serialOutputFile;
  int _bupc_w2c_i0;
  struct kmer_t current_start;
  struct kmer_t * cur_kmer_ptr;
  char cur_contig[100000LL];
  long posInContig;
  void * _bupc_call16;
  struct _IO_FILE * _bupc_call17;
  upcr_pshared_ptr_t _bupc_call18;
  struct _IO_FILE * _bupc_call19;
  upcr_pshared_ptr_t _bupc_call20;
  int _bupc_spillld21;
  upcr_shared_ptr_t _bupc_Mstopcvt22;
  int _bupc_spillld23;
  int _bupc_spillld24;
  upcr_pshared_ptr_t _bupc_Mptra25;
  int _bupc_spillld26;
  int _bupc_spillld27;
  int _bupc_spillld28;
  int _bupc_spillld29;
  int _bupc_spillld30;
  upcr_pshared_ptr_t _bupc_Mptra31;
  int _bupc_spillld32;
  upcr_pshared_ptr_t _bupc_Mptra33;
  upcr_shared_ptr_t _bupc_Mstopcvt34;
  upcr_shared_ptr_t _bupc_Mstopcvt35;
  
#line 25 "pgen.upc"
  inputTime = 0.0;
#line 25 "pgen.upc"
  constrTime = 0.0;
#line 25 "pgen.upc"
  traversalTime = 0.0;
#line 28 "pgen.upc"
  upcr_barrier(346153894, 1);
#line 29 "pgen.upc"
  _bupc_comma = gettime();
#line 29 "pgen.upc"
  inputTime = inputTime - _bupc_comma;
#line 37 "pgen.upc"
  contigID = 0LL;
#line 37 "pgen.upc"
  totBases = 0LL;
#line 37 "pgen.upc"
  ptr = 0LL;
#line 38 "pgen.upc"
  (unpackedKmer)[19] = 0;
#line 40 "pgen.upc"
  startKmersList = (struct start_kmer_t *)(0ULL);
#line 45 "pgen.upc"
  init_LookupTable();
#line 47 "pgen.upc"
  if(((int) upcr_mythread () ) == 0)
#line 47 "pgen.upc"
  {
#line 48 "pgen.upc"
    input_UFX_name = *(argv + 1LL);
#line 50 "pgen.upc"
    _bupc_comma0 = getNumKmersInUFX(input_UFX_name);
#line 50 "pgen.upc"
    nKmers = _bupc_comma0;
#line 53 "pgen.upc"
    total_chars_to_read = nKmers * 23LL;
#line 54 "pgen.upc"
    _bupc_call16 = malloc((unsigned long)(_UINT64)(total_chars_to_read));
#line 54 "pgen.upc"
    _bupc__casttmp4 = _bupc_call16;
#line 54 "pgen.upc"
    working_buffer = _bupc__casttmp4;
#line 55 "pgen.upc"
    _bupc_call17 = fopen((const char *)(input_UFX_name), (const char *)("r"));
#line 55 "pgen.upc"
    inputFile = _bupc_call17;
#line 56 "pgen.upc"
    _bupc_comma1 = fread(working_buffer, (unsigned long) 1ULL, (unsigned long)(_UINT64)(total_chars_to_read), inputFile);
#line 56 "pgen.upc"
    cur_chars_read = (_INT64)(_bupc_comma1);
#line 57 "pgen.upc"
    fclose(inputFile);
#line 100 "pgen.upc"
    UPCR_GET_PSHARED(&_bupc_spillld27, pos, 0, 4);
#line 62 "pgen.upc"
    while((_INT32)((ptr < cur_chars_read)) && (_INT32)((_bupc_spillld27 <= 16777215)))
#line 62 "pgen.upc"
    {
#line 67 "pgen.upc"
      left_ext = (char) * ((working_buffer + (ptr + 19LL)) + 1LL);
#line 68 "pgen.upc"
      right_ext = (char) * ((working_buffer + (ptr + 19LL)) + 2LL);
#line 72 "pgen.upc"
      UPCR_GET_PSHARED(&_bupc_spillld21, pos, 0, 4);
#line 72 "pgen.upc"
      add_kmer(buckets, heap, _bupc_spillld21, working_buffer + ptr, left_ext, right_ext);
#line 79 "pgen.upc"
      _bupc_call18 = lookup_kmer(buckets, heap, working_buffer + ptr);
#line 79 "pgen.upc"
      (*((upcr_pshared_ptr_t *) UPCR_TLD_ADDR( lookup ))) = _bupc_call18;
#line 81 "pgen.upc"
      _bupc_Mstopcvt22 = UPCR_PSHARED_TO_SHARED((*((upcr_pshared_ptr_t *) UPCR_TLD_ADDR( lookup ))));
#line 81 "pgen.upc"
      upc_memget_nb(&temp, _bupc_Mstopcvt22, (unsigned long) 12ULL);
#line 84 "pgen.upc"
      packSequence(working_buffer + ptr, (unsigned char *) packedKmer, (int) 19);
#line 86 "pgen.upc"
      i = 0;
#line 86 "pgen.upc"
      while(i <= 4)
#line 86 "pgen.upc"
      {
#line 87 "pgen.upc"
        if((_INT32)((packedKmer)[i]) == (_INT32)(temp.kmer[i]))
#line 87 "pgen.upc"
        {
          0;
        }
        else
#line 87 "pgen.upc"
        {
#line 87 "pgen.upc"
          __assert_fail("packedKmer[i] == temp.kmer[i]", "pgen.upc", (unsigned int) 87U, "main");
        }
#line 88 "pgen.upc"
        _1 :;
#line 88 "pgen.upc"
        i = i + 1;
      }
#line 93 "pgen.upc"
      if((_INT32)(left_ext) == 70)
#line 93 "pgen.upc"
      {
#line 94 "pgen.upc"
        UPCR_GET_PSHARED(&_bupc_spillld23, n_starts, 0, 4);
#line 94 "pgen.upc"
        _bupc_Mspillpost5 = _bupc_spillld23;
#line 94 "pgen.upc"
        UPCR_PUT_PSHARED_VAL(n_starts, 0, _bupc_Mspillpost5 + 1, 4);
#line 94 "pgen.upc"
        _bupc_Mptra25 = UPCR_ADD_PSHARED1(starts, 4ULL, _bupc_Mspillpost5);
#line 94 "pgen.upc"
        UPCR_GET_PSHARED(&_bupc_spillld24, pos, 0, 4);
#line 94 "pgen.upc"
        UPCR_PUT_PSHARED_VAL(_bupc_Mptra25, 0, _bupc_spillld24, 4);
      }
#line 99 "pgen.upc"
      ptr = ptr + 23LL;
#line 100 "pgen.upc"
      UPCR_GET_PSHARED(&_bupc_spillld26, pos, 0, 4);
#line 100 "pgen.upc"
      UPCR_PUT_PSHARED_VAL(pos, 0, _bupc_spillld26 + 1, 4);
#line 100 "pgen.upc"
      UPCR_GET_PSHARED(&_bupc_spillld27, pos, 0, 4);
    }
#line 103 "pgen.upc"
    UPCR_GET_PSHARED(&_bupc_spillld28, pos, 0, 4);
#line 103 "pgen.upc"
    UPCR_GET_PSHARED(&_bupc_spillld29, n_starts, 0, 4);
#line 103 "pgen.upc"
    printf((const char *)("Initialized hash table with %d elements and got %d start positions\n"), _bupc_spillld28, _bupc_spillld29);
  }
#line 107 "pgen.upc"
  upcr_barrier(346153895, 1);
#line 108 "pgen.upc"
  _bupc_comma2 = gettime();
#line 108 "pgen.upc"
  inputTime = inputTime + _bupc_comma2;
#line 111 "pgen.upc"
  _bupc_comma3 = gettime();
#line 111 "pgen.upc"
  constrTime = constrTime - _bupc_comma3;
#line 118 "pgen.upc"
  sprintf(filename, (const char *)("pgen_%d.out"), ((int) upcr_mythread () ));
#line 120 "pgen.upc"
  _bupc_call19 = fopen((const char *)(filename), (const char *)("w"));
#line 120 "pgen.upc"
  serialOutputFile = _bupc_call19;
#line 122 "pgen.upc"
  UPCR_GET_PSHARED(&_bupc_spillld30, n_starts, 0, 4);
#line 122 "pgen.upc"
  _bupc_w2c_i0 = _bupc_spillld30 + -1;
#line 122 "pgen.upc"
  while(_bupc_w2c_i0 >= 0)
#line 122 "pgen.upc"
  {
#line 124 "pgen.upc"
    if((_bupc_w2c_i0 % ((int) upcr_threads () )) == ((int) upcr_mythread () ))
#line 124 "pgen.upc"
    {
#line 125 "pgen.upc"
      _bupc_Mptra31 = UPCR_ADD_PSHARED1(starts, 4ULL, _bupc_w2c_i0);
#line 125 "pgen.upc"
      UPCR_GET_PSHARED(&_bupc_spillld32, _bupc_Mptra31, 0, 4);
#line 125 "pgen.upc"
      _bupc_Mptra33 = UPCR_ADD_PSHARED1(heap, 12ULL, _bupc_spillld32);
#line 125 "pgen.upc"
      _bupc_Mstopcvt34 = UPCR_PSHARED_TO_SHARED(_bupc_Mptra33);
#line 125 "pgen.upc"
      upc_memget_nb(&current_start, _bupc_Mstopcvt34, (unsigned long) 12ULL);
#line 126 "pgen.upc"
      cur_kmer_ptr = &current_start;
#line 127 "pgen.upc"
      unpackSequence((const unsigned char *) & current_start, (unsigned char *) unpackedKmer, (int) 19);
#line 131 "pgen.upc"
      memcpy(cur_contig, (const void *)(unpackedKmer), (unsigned long) 19ULL);
#line 132 "pgen.upc"
      posInContig = 19LL;
#line 133 "pgen.upc"
      right_ext = (current_start).r_ext;
#line 136 "pgen.upc"
      while((_INT32)(right_ext) != 70)
#line 136 "pgen.upc"
      {
#line 137 "pgen.upc"
        (cur_contig)[posInContig] = right_ext;
#line 138 "pgen.upc"
        posInContig = posInContig + 1LL;
#line 140 "pgen.upc"
        _bupc_call20 = lookup_kmer(buckets, heap, (const unsigned char *)((char *)(((char *) & cur_contig) + -19LL) + posInContig));
#line 140 "pgen.upc"
        (*((upcr_pshared_ptr_t *) UPCR_TLD_ADDR( lookup ))) = _bupc_call20;
#line 141 "pgen.upc"
        _bupc_Mstopcvt35 = UPCR_PSHARED_TO_SHARED((*((upcr_pshared_ptr_t *) UPCR_TLD_ADDR( lookup ))));
#line 141 "pgen.upc"
        upc_memget_nb(cur_kmer_ptr, _bupc_Mstopcvt35, (unsigned long) 12ULL);
#line 142 "pgen.upc"
        right_ext = (cur_kmer_ptr) -> r_ext;
      }
#line 146 "pgen.upc"
      (cur_contig)[posInContig] = 0;
#line 147 "pgen.upc"
      fprintf(serialOutputFile, (const char *)("%s\n"), cur_contig);
#line 148 "pgen.upc"
      contigID = contigID + 1LL;
#line 149 "pgen.upc"
      _bupc_comma4 = strlen(cur_contig);
#line 149 "pgen.upc"
      totBases = (_INT64)(_bupc_comma4 + (_UINT64)(totBases));
    }
#line 153 "pgen.upc"
    _2 :;
#line 153 "pgen.upc"
    _bupc_w2c_i0 = _bupc_w2c_i0 + -1;
  }
#line 155 "pgen.upc"
  upcr_barrier(346153896, 1);
#line 156 "pgen.upc"
  _bupc_comma5 = gettime();
#line 156 "pgen.upc"
  constrTime = constrTime + _bupc_comma5;
#line 159 "pgen.upc"
  _bupc_comma6 = gettime();
#line 159 "pgen.upc"
  traversalTime = traversalTime - _bupc_comma6;
#line 164 "pgen.upc"
  upcr_barrier(346153897, 1);
#line 165 "pgen.upc"
  _bupc_comma7 = gettime();
#line 165 "pgen.upc"
  traversalTime = traversalTime + _bupc_comma7;
#line 169 "pgen.upc"
  if(((int) upcr_mythread () ) == 0)
#line 169 "pgen.upc"
  {
#line 170 "pgen.upc"
    printf((const char *)("%s: Input set: %s\n"), *argv, *(argv + 1LL));
#line 171 "pgen.upc"
    printf((const char *)("Number of UPC threads: %d\n"), ((int) upcr_threads () ));
#line 172 "pgen.upc"
    printf((const char *)("Input reading time: %f seconds\n"), inputTime);
#line 173 "pgen.upc"
    printf((const char *)("Graph construction time: %f seconds\n"), constrTime);
#line 174 "pgen.upc"
    printf((const char *)("Graph traversal time: %f seconds\n"), traversalTime);
  }
#line 176 "pgen.upc"
  UPCR_EXIT_FUNCTION();
#line 176 "pgen.upc"
  return 0;
} /* user_main */

#line 1 "_SYSTEM"
/**************************************************************************/
/* upcc-generated strings for configuration consistency checks            */

GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_GASNetConfig_gen, 
 "$GASNetConfig: (/tmp/upcc-belletti-61116-1459285769/pgen.trans.c) RELEASE=1.26.0,SPEC=1.8,CONDUIT=ARIES(ARIES-0.3/ARIES-0.3),THREADMODEL=PAR,SEGMENT=FAST,PTR=64bit,noalign,pshm,nodebug,notrace,nostats,nodebugmalloc,nosrclines,timers_native,membars_native,atomics_native,atomic32_native,atomic64_native $");
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_UPCRConfig_gen,
 "$UPCRConfig: (/tmp/upcc-belletti-61116-1459285769/pgen.trans.c) VERSION=2.22.0,PLATFORMENV=shared-distributed,SHMEM=pthreads/pshm,SHAREDPTRREP=struct/p32:t32:a64,TRANS=berkeleyupc,nodebug,nogasp,notv,dynamicthreads $");
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_translatetime, 
 "$UPCTranslateTime: (pgen.o) Tue Mar 29 14:09:30 2016 $");
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_GASNetConfig_obj, 
 "$GASNetConfig: (pgen.o) " GASNET_CONFIG_STRING " $");
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_UPCRConfig_obj,
 "$UPCRConfig: (pgen.o) " UPCR_CONFIG_STRING UPCRI_THREADCONFIG_STR " $");
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_translator, 
 "$UPCTranslator: (pgen.o) /usr/common/ftg/upc/2.22.0/translator/install/targ (edison05) $");
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_upcver, 
 "$UPCVersion: (pgen.o) 2.22.0 $");
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_compileline, 
 "$UPCCompileLine: (pgen.o) /global/common/edison/ftg/upc/2.22.0/PrgEnv-gnu-5.2.56-5.2.0/runtime/inst/opt/bin/upcc.pl -pthreads -Wc,-O3  -o pgen pgen.upc -DKMER_LENGTH=19 -DKMER_PACKED_LENGTH=5 $");
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_compiletime, 
 "$UPCCompileTime: (pgen.o) " __DATE__ " " __TIME__ " $");
#ifndef UPCRI_CC /* ensure backward compatilibity for http netcompile */
#define UPCRI_CC <unknown>
#endif
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_backendcompiler, 
 "$UPCRBackendCompiler: (pgen.o) " _STRINGIFY(UPCRI_CC) " $");

#ifdef GASNETT_CONFIGURE_MISMATCH
  GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_configuremismatch, 
   "$UPCRConfigureMismatch: (pgen.o) 1 $");
  GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_configuredcompiler, 
   "$UPCRConfigureCompiler: (pgen.o) " GASNETT_PLATFORM_COMPILER_IDSTR " $");
  GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_buildcompiler, 
   "$UPCRBuildCompiler: (pgen.o) " PLATFORM_COMPILER_IDSTR " $");
#endif

/**************************************************************************/
GASNETT_IDENT(UPCRI_IdentString_pgen_o_1459285770_transver_2,
 "$UPCTranslatorVersion: (pgen.o) 2.22.0, built on Oct 30 2015 at 14:53:24, host edison05 linux-x86_64/64, gcc v4.3.4 [gcc-4_3-branch revision 152973] $");
GASNETT_IDENT(UPCRI_IdentString_INIT_pgen_6953898206118,"$UPCRInitFn: (pgen.trans.c) UPCRI_INIT_pgen_6953898206118 $");
GASNETT_IDENT(UPCRI_IdentString_ALLOC_pgen_6953898206118,"$UPCRAllocFn: (pgen.trans.c) UPCRI_ALLOC_pgen_6953898206118 $");
