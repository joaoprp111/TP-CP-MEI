#!/bin/bash

ELEMENTS=1000000
BUCKETS=1000

MY=/home/pg47325/TP/SequentialBucketSort
module load papi/5.4.1

$MY/sequential_bucketSort $ELEMENTS $BUCKETS
