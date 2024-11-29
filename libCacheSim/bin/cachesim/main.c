#ifdef __linux__
#include <sys/sysinfo.h>
#endif
#include <assert.h>
#include <libgen.h>

#include "../../include/libCacheSim/cache.h"
#include "../../include/libCacheSim/reader.h"
#include "../../include/libCacheSim/simulator.h"
#include "../../utils/include/mystr.h"
#include "../../utils/include/mysys.h"
#include "internal.h"

int main(int argc, char **argv) {
  struct arguments args;
  parse_cmd(argc, argv, &args);
  if (args.n_algo_pair == 0) {
    ERROR("no cache size found\n");
  }
  simulate(args.reader, args.caches, args.n_algo_pair, args.report_interval,
          args.warmup_sec, args.ofilepath, args.ignore_obj_size, args.print_head_req);

  free_arg(&args);
  return 0;
}