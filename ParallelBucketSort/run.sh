#!/bin/bash

ELEMENTS=1000000
BUCKETS=1000

MY=/home/pg47325/TP/ParallelBucketSort
module load papi/5.4.1

$MY/parallel_bucketSort $ELEMENTS $BUCKETS
