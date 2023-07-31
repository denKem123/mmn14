# C Project: 12-bit Assembler
## About
This project is an assignment in a C programming course at the open unvieristy (20465). The purpose of this project is to build an assembler for instructions in asssembly language, for an imaginary 12-bit CPU Computer.
This project was done by **Guy Michalovitz** and	**Alon Asher**.

## Modules
1. `assembler` - main function definition, argv & argc processing, single file processing.
1. `macro` - create new `*.am` file spreading existing macros.
2. `first_pass` - first run on asssembly instructions.
3. `second_pass` - second run on asssembly instructions.
9. `writefiles` - create all output files: `*.ob`, `*.ext` and `*.ent` 

## Sub Modules
4. `code` - contains useful function for processing code.
5. `instructions` - contains useful function for processing instruction.
6. `globals.h` - contains type and constant definitions.
7. `table` - contains definition of table-like linked list data structure.
8. `utils` - contains general-purposed, project-wide functions.

## Build Code
You may build with several tools:
1. Using `make` command (Makefile)
2. Manually (Not recommended): compile each `*.c` file to `*.o` and then compile all to a single executable using `CC`/`GCC`/`CLang` with `-g a.o b.o .... -o exe`

## Run Code
`./assembler file1 file2 file3 ...`
Will start the processing of each file (specify WITHOUT extension!). No support for double-quoting file names.


