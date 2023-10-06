#!/bin/bash
id="$1"
host="$2"
for i in maps-*
do
gawk test_table="$id" host_name="$host" pid=${i##maps-} -f `which maps_table.awk` $i
done
