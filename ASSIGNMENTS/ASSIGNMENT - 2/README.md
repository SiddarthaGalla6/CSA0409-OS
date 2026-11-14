# Assignment 02 C Programs – C Programs

This ZIP contains the C programs extracted from the corresponding Operating Systems assignment report.

## File format
Each `.c` file contains:
- The complete C source code.
- An `Input:` section in a C comment.
- An `Output (reference/sample):` section in a C comment.

The Input and Output sections are comments, so the file can still be compiled as a normal C program.

## Programs
- `Q1_process_states.c` — Q1 – Processes and Process States
- `Q2_round_robin.c` — Q2 – CPU Scheduling
- `Q3_camera_threads.c` — Q3 – Threads
- `Q4_pipe_ipc.c` — Q4 – Inter-Process Communication
- `Q5_producer_consumer.c` — Q5 – Synchronisation
- `Q6_bankers_algorithm.c` — Q6 – Deadlock Handling and Banker’s Algorithm

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
