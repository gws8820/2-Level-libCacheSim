#pragma once

#include <inttypes.h>

#include "../../include/libCacheSim/admissionAlgo.h"
#include "../../include/libCacheSim/cache.h"
#include "../../include/libCacheSim/enum.h"
#include "../../include/libCacheSim/evictionAlgo.h"
#include "../../include/libCacheSim/reader.h"

#ifdef __cplusplus
extern "C" {
#endif

#define N_ARGS 6
#define N_MAX_ALGO_CACHE 16
#define OFILEPATH_LEN 128

struct algo_cache_pair {
    char *algorithm;
    uint64_t cache_size;
};

/* This structure is used to communicate with parse_opt. */
struct arguments {
  /* argument from the user */
  char *args[N_ARGS];
  char *trace_path;
  struct algo_cache_pair algo_pair[N_MAX_ALGO_CACHE]; // Array of algorithm-cache pairs
  int n_algo_pair;
  char *admission_algo;
  char *prefetch_algo;
  int warmup_sec;

  char ofilepath[OFILEPATH_LEN];
  char *trace_type_str;
  trace_type_e trace_type;
  char *trace_type_params;
  char *eviction_params;
  char *admission_params;
  char *prefetch_params;
  double sample_ratio;
  int n_thread;
  int64_t n_req; /* number of requests to process */

  bool verbose;
  int report_interval;
  bool ignore_obj_size;
  bool consider_obj_metadata;
  bool use_ttl;
  bool print_head_req;

  /* arguments generated */
  reader_t *reader;
  cache_t *caches[N_MAX_ALGO_CACHE];
};

void parse_cmd(int argc, char *argv[], struct arguments *args);

void free_arg(struct arguments *args);

// internal.h
void simulate(reader_t *reader, cache_t *caches[], int n_algo_pair,
              int report_interval, int warmup_sec, char *ofilepath,
              bool ignore_obj_size, bool print_head_req);

void print_parsed_args(struct arguments *args);


#ifdef __cplusplus
}
#endif
