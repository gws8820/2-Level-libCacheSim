#include "../../include/libCacheSim/cache.h"
#include "../../include/libCacheSim/reader.h"
#include "../../utils/include/mymath.h"
#include "../../utils/include/mystr.h"
#include "../../utils/include/mysys.h"

#ifdef __cplusplus
#endif

void print_head_requests(request_t *req, uint64_t req_cnt) {
  if (req_cnt < 2) {
    print_request(req, INFO_LEVEL);
  } else if (req_cnt < 10) {
    print_request(req, DEBUG_LEVEL);
  }
}

void simulate(reader_t *reader, cache_t **caches, int n_algo_pair,
              int report_interval, int warmup_sec, const char *ofilepath,
              bool ignore_obj_size, bool print_head_req) {
    request_t *req = new_request();
    uint64_t total_req_cnt = 0, l2_req_cnt = 0;
    uint64_t l1_miss_cnt = 0, l2_miss_cnt = 0;

    read_one_req(reader, req);
    uint64_t start_ts = (uint64_t)req->clock_time;
    uint64_t last_report_ts = warmup_sec;

    double start_time = gettime();

    printf("\nStarting Simulation...\n");

    while (req->valid) {
        if (print_head_req) {
            print_head_requests(req, total_req_cnt);
        }

        req->clock_time -= start_ts;

        if (req->clock_time <= warmup_sec) {
            for (int i = 0; i < n_algo_pair; i++) {
                caches[i]->get(caches[i], req);
            }
            read_one_req(reader, req);
            continue;
        } else total_req_cnt++;

        bool hit = false;
        if (caches[0]->get(caches[0], req)) hit = true;
        else {
            l1_miss_cnt++;
            l2_req_cnt++;
            
            if (n_algo_pair > 1 && caches[1]->get(caches[1], req)) hit = true;
            else l2_miss_cnt++;
        }

        if (req->clock_time - last_report_ts >= report_interval &&
            req->clock_time != 0) {
            printf("Total  %llu Requests, Miss Ratio: %.4lf\n", total_req_cnt, (double)l2_miss_cnt / total_req_cnt);
            printf("L1     %llu Requests, Miss Ratio: %.4lf\n", total_req_cnt, (double)l1_miss_cnt / total_req_cnt);
            printf("L2     %llu Requests, Miss Ratio: %.4lf\n", l2_req_cnt, l2_req_cnt > 0 ? (double)l2_miss_cnt / l2_req_cnt : 0.0);   
            last_report_ts = req->clock_time;
        }

        read_one_req(reader, req);
    }

    double runtime = gettime() - start_time;
    printf("\nSimulation Complete: %.2lf MQPS\n",
           (double)total_req_cnt / 1000000.0 / runtime);

    if (total_req_cnt > 0) {
        printf("Total  %llu Requests, Miss Ratio: %.4lf\n", total_req_cnt, (double)l2_miss_cnt / total_req_cnt);
        printf("L1     %llu Requests, Miss Ratio: %.4lf\n", total_req_cnt, (double)l1_miss_cnt / total_req_cnt);
        printf("L2     %llu Requests, Miss Ratio: %.4lf\n", l2_req_cnt, l2_req_cnt > 0 ? (double)l2_miss_cnt / l2_req_cnt : 0.0);   
    } else {
        printf("No requests processed, unable to calculate miss ratio.");
    }

    free_request(req);
}