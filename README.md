# maps2table
This is a tool to analyze memory map of processes in `/proc/<pid>/maps` file.

maps2table creates a table to store each lines of `maps` file into a table row.
You can just feed `/proc/<pid>/maps` file to maps2table with additional information
and it writes SQL statement to add them to `maps` table in a relational database,
preferably PostgreSQL.

This is at present a very quick hack and contains minimum amount of materials.

