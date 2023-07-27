/********************************************************/
select
	test_label
   	hostname,
	pid,
	lpad(TO_CHAR(sum(chunk_size), 'FM999,999,999,999'), 15) as total_heap_and_stack
from
	maps
where
	pid in (select pid from maps where pathname like '%post%') and
	(pathname = '[stack]' or pathname = '[heap]')
group by
	test_label,
	hostname,
	pid
order by
	sum(chunk_size) desc,
	test_label,
	hostname,
	pid;

/********************************************************/
select
	pathname,
	lpad(TO_CHAR(sum(chunk_size), 'FM999,999,999,999'), 15) as total_size
from
	maps
where
	pid=3446181
group by
	pathname
order by
	sum(chunk_size) desc;

/********************************************************/
select
	test_label,
	hostname,
	pid,
	lpad(TO_CHAR(sum(chunk_size), 'FM999,999,999,999'), 15) as total_size
from
	maps
where
	pid in (select pid from maps where pathname like '%post%') and
	(pathname = '[stack]' or pathname = '[heap]')
group by
	test_label,
	hostname,
	pid
order by
	sum(chunk_size) desc,
	test_label,
	hostname,
	pid;


/********************************************************/
select
	test_label,
	hostname,
	lpad(TO_CHAR(sum(chunk_size) as total_size
from
	maps
where
	pid in (select pid from maps where pathname like '%post%') and
	(pathname = '[stack]' or pathname = '[heap]')
group by
	test_label,
	hostname
order by
	total_size desc,
	test_label,
	hostname;


