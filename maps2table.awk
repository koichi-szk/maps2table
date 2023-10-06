#!/usr/bin/gawk
# Call sequence:
#
# gawk -f maps2table.awk test_label=xxx host_name=yyy pid=ppp <infile>
#
# This script reads /proc/*/maps file and convert this into SQL statement to import this to
# "maps" database table.
#
BEGIN {
# Initialize
	maps_tabname = "maps";
	begin_printed = 0;
}
{
	if (NF != 5 && NF != 6)
		next;
	if (begin_printed == 0)
	{
		print "BEGIN;";
		begin_printed = 1;
	}
	chunk_region = $1;
	perms = $2;
	offset = $3;
	dev = $4;
	inode = $5;
	if (NF == 6)
		pathname = "'" $6 "'";
	else
		pathname = "NULL";
	split(chunk_region, aa, "-");
	start_addr = aa[1];
	end_addr = aa[2];
	chunk_size = strtonum("0x" end_addr) - strtonum("0x" start_addr);

	printf "INSERT INTO %s VALUES ('%s', '%s', %d, %d, '%s', '%s', '%s', '%s', '%s', '%s', %s);\n",
		maps_tabname, test_label, host_name, pid,
		chunk_size, start_addr, end_addr, perms, offset, dev, inode, pathname;
}
END {
	if (begin_printed == 1)
		print "COMMIT;"
}
