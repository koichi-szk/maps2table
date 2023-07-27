select
	test_label,
	hostname,
	sum(chunk_size) as total_size
from
	maps
where
	pid in (select pid from maps where pathname like '%post%') and
	(pathname = '[stack]' or pathname = '[heap]')
group by
	test_label,
	hostname
order by
	test_label,
	hostname
	;

