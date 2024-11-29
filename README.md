# 2-Level libCacheSim

* a high-performance **cache simulator** for running cache simulations. 
* runs in 2-Level so can set different replacement algorithm and cache size for each level.

## Supported algorithms
libCachesim supports the following algorithms:
### Eviction algorithms
* [FIFO](/libCacheSim/cache/eviction/FIFO.c), [LRU](/libCacheSim/cache/eviction/LRU.c), [Clock](/libCacheSim/cache/eviction/Clock.c), [SLRU](/libCacheSim/cache/eviction/SLRU.c)
* [LFU](/libCacheSim/cache/eviction/LFU.c), [LFU with dynamic aging](/libCacheSim/cache/eviction/LFUDA.c)
* [ARC](/libCacheSim/cache/eviction/ARC.c), [TwoQ](/libCacheSim/cache/eviction/TwoQ.c)
* [Belady](/libCacheSim/cache/eviction/Belady.c), [BeladySize](/libCacheSim/cache/eviction/BeladySize.c)
* [GDSF](/libCacheSim/cache/eviction/cpp/GDSF.cpp)
* [Hyperbolic](/libCacheSim/cache/eviction/Hyperbolic.c)
* [LeCaR](/libCacheSim/cache/eviction/LeCaR.c)
* [Cacheus](/libCacheSim/cache/eviction/Cacheus.c)
* [LHD](/libCacheSim/cache/eviction/LHD/LHD_Interface.cpp)
* [LRB](/libCacheSim/cache/eviction/LRB/LRB_Interface.cpp)
* [GLCache](/libCacheSim/cache/eviction/GLCache/GLCache.c)
* [WTinyLFU](/libCacheSim/cache/eviction/WTinyLFU.c)
* [QD-LP](/libCacheSim/cache/eviction/QDLP.c)
* [S3-FIFO](/libCacheSim/cache/eviction/S3FIFO.c)
* [Sieve](/libCacheSim/cache/eviction/Sieve.c)
### Admission algorithms
* [Adaptsize](/libCacheSim/cache/admission/adaptsize.c)
* [Bloomfilter](/libCacheSim/cache/admission/bloomfilter.c)
* [Prob](/libCacheSim/cache/admission/prob.c)
* [Size](/libCacheSim/cache/admission/size.c)
### Prefetching algorithms
* [OBL](/libCacheSim/cache/prefetch/OBL.c)
* [Mithril](/libCacheSim/cache/prefetch/Mithril.c)
* [PG](/libCacheSim/cache/prefetch/PG.c)
---


## Build and Install
<!-- TOC --><a name="one-line-install"></a>
### One-line install
We provide some scripts for quick installation of libCacheSim. 
```bash
cd scripts && bash install_dependency.sh && bash install_libcachesim.sh
```


### Build libCacheSim
cmake recommends **out-of-source build**, so we do it in a new directory:
```bash
git clone https://github.com/gws8820/2-Level-libCacheSim
pushd libCacheSim
mkdir _build && cd _build
cmake .. && make -j
[sudo] make install
popd
```
---
## Usage
### cachesim (a high-performance cache simulator)
After building and installing libCacheSim, `cachesim` should be in the `_build/bin/` directory. 
#### basic usage
```
./bin/cachesim trace_path trace_type l1_eviction_algo l1_cache_size l2_eviction_algo l2_cache_size
```

use `./bin/cachesim --help` to get more information.

#### Run a 2-level cache simulation
```bash
# Note that no space between the cache size and the unit, and the unit is not case-sensitive
./bin/cachesim ../data/trace.vscsi vscsi lru 128mb fifo 1gb
```


## License
This project uses [libCacheSim](https://github.com/1a1a11a/libCacheSim) developed by [1a1a11a](https://github.com/1a1a11a).

See [LICENSE](LICENSE) for details.
