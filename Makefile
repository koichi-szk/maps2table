
DESTINATION=$(HOME)/bin

maps2table: maps2table.c
	cc -g maps2table.c -o maps2table

install: maps2table
	install maps2table $(DESTINATION)
	install backup_maps $(DESTINATION)
	install maps2table_all $(DESTINATION)
