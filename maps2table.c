#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct mem_chunk mem_chunk;

struct mem_chunk
{
	char	*test_label;
	char	*hostname;
	int		 pid;
	long	 size;
	char	*start_address;
	char	*end_address;
	char	*perms;
	char	*offset;
	char	*dev;
	char	*inode;
	char	*pathname;
};

static long hex2long(char *str);
static void build_statement(mem_chunk *chunk);
static mem_chunk *parse_line(char *line, char *test_label, char *hostname, int pid, mem_chunk *chunk_data);
static char *skip_sp(char *p);
static char *mark_end(char *line, char mark);



int main(int ac, char *av[])
{
	static mem_chunk	CHUNK;
	mem_chunk	*chunk;
	char	buff[2048];
	char	*line;
	char	*fname;
	FILE	*inf;

	char *test_label = av[1];
	char *hostname = av[2];
	int	pid = atoi(av[3]);
	
	fname = av[4];
	inf = fopen(fname, "r");

	while (line = fgets(buff, 2048, inf))
	{
		if ((chunk = parse_line(buff, test_label, hostname, pid, &CHUNK)) == NULL)
			continue;
		chunk->size = hex2long(chunk->end_address) - hex2long(chunk->start_address);
		build_statement(&CHUNK);
	}
	fclose(inf);
}

static long
hex2long(char *str)
{
	long rv = 0;

	while(*str == ' ' || *str == '\t')
		str++;
	while((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F'))
	{
		rv *= 16;
		if(*str >= '0' && *str <= '9')
			rv += *str - '0';
		else if(*str >= 'a' && *str <= 'f')
			rv += *str - 'a' + 10;
		else
			rv += *str - 'A' + 10;
		str++;
	}
	return rv;
}

static void
build_statement(mem_chunk *chunk)
{
	if (chunk->pathname)
	{
		printf("INSERT INTO MAPS VALUES ('%s', '%s', %d, %ld, '%s', '%s', '%s', '%s', '%s', '%s', '%s');\n",
				chunk->test_label, chunk->hostname, chunk->pid, chunk->size, chunk->start_address, chunk->end_address, chunk->perms, chunk->offset, chunk->inode, chunk->dev, chunk->pathname);
	}
	else
	{
		printf("INSERT INTO MAPS VALUES ('%s', '%s', %d, %ld, '%s', '%s', '%s', '%s', '%s', '%s', NULL);\n",
				chunk->test_label, chunk->hostname, chunk->pid, chunk->size, chunk->start_address, chunk->end_address, chunk->perms, chunk->offset, chunk->inode, chunk->dev);
	}
}

#define SKIP_SP(p) do{p = skip_sp(p); if (p == NULL) return NULL;}while(0)
#define MARK_END(p, m) do{p = mark_end(p, m); if (p == NULL) return NULL;}while(0)
#define NEXT_TOKEN(p, m)	do{MARK_END(p, m); SKIP_SP(p);}while (0)

static mem_chunk *
parse_line(char *line, char *test_label, char *hostname, int pid, mem_chunk *chunk_data)
{
	char	*ptr = line;

	chunk_data->test_label = test_label;
	chunk_data->hostname = hostname;
	chunk_data->pid = pid;
	/* Start_addr */
	SKIP_SP(ptr);
	chunk_data->start_address = ptr;
	NEXT_TOKEN(ptr, '-');
	chunk_data->end_address = ptr;
	NEXT_TOKEN(ptr, 0);
	chunk_data->perms = ptr;
	NEXT_TOKEN(ptr, 0);
	chunk_data->offset = ptr;
	NEXT_TOKEN(ptr, 0);
	chunk_data->dev = ptr;
	NEXT_TOKEN(ptr, 0);
	chunk_data->inode = ptr;
	MARK_END(ptr, 0);
	ptr = skip_sp(ptr);
	if (ptr)
	{
		chunk_data->pathname = ptr;
		mark_end(ptr, 0);
	}
	else
		chunk_data->pathname = NULL;
	return chunk_data;
}

static char *
skip_sp(char *p)
{
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == 0 || *p == '\n')
		return NULL;
	return p;
}

static char *
mark_end(char *line, char mark)
{
	char *p = line;
	bool numm_mark;

	if (mark)
	{
		while (*p && (*p != mark))
			p++;
		if (*p)
		{
			*p = 0;
			return (p+1);
		}
		else
			return NULL;
	}
	else
	{
		/* White space */
		while (*p && *p != ' ' && *p != '\t' && *p != '\n')
		   p++;
		if (*p == 0 || *p == '\n')
		{
			*p = 0;
			return NULL;
		}
		*p = 0;
		return (p+1);
	}
	return NULL;
}
