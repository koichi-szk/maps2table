#!/bin/bash
gawk -v "test_label"="$1" -v "host_name"="$2" -v "pid"="$3" -f `which maps2table.awk`
