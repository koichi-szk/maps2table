DROP TABLE IF EXISTS maps;
CREATE TABLE maps
(
 test_label	text,	/* Label for a test case */
 hostname	text,	/* Hostname */
 pid		int,	/* pid */
 chunk_size	bigint,
 start_addr	text,
 end_addr	text,
 perms		text,
 offset_val	text,
 dev		text,
 inode		text,
 pathname	text
);

