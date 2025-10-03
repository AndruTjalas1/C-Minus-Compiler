#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>
#include <sys/time.h>

typedef struct {
    double cpu_time;
    double wall_time;
    long memory_usage;
    long peak_memory;
} BenchmarkResult;

// Platform-specific memory measurement
long get_memory_usage();

// Benchmark functions
BenchmarkResult* start_benchmark();
void end_benchmark(BenchmarkResult* result, const char* phase);

#endif
