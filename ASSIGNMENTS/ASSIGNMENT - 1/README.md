# Assignment 01 C Programs – C Programs

This ZIP contains the C programs extracted from the corresponding Operating Systems assignment report.

## File format
Each `.c` file contains:
- The complete C source code.
- An `Input:` section in a C comment.
- An `Output (reference/sample):` section in a C comment.

The Input and Output sections are comments, so the file can still be compiled as a normal C program.

## Programs
- `Q5_system_call_demo.c` — Task 5 – System Calls
- `Q6_file_copy.c` — Task 6 – Cost of System Calls
- `Q7_process_control.c` — Task 7 – Process Control System Calls
- `Q10_process_bench.c` — Task 10 – Process Benchmark
- `Q10_thread_bench.c` — Task 10 – Thread Benchmark

## Compilation and execution

Run these commands from a Linux terminal in the folder containing the source file.

General compilation:
```bash
gcc -std=c11 -Wall -Wextra source_file.c -o program
./program
```

For programs that use POSIX threads or semaphores, compile with:
```bash
gcc -std=c11 -Wall -Wextra -pthread source_file.c -o program
./program
```

Notes:
- `Q7_process_control.c` uses the external `expr` utility, which is normally available on Linux.
- `Q10_process_bench.c` and `Q10_thread_bench.c` create 1,000 workers and may take longer depending on system limits.
- Process IDs and scheduling order can vary between runs.
- The output comments are reference/sample outputs. Replace them with your own captured results if your assignment requires execution evidence.
