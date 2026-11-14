# CSA04 Operating Systems - Assignment 3 (CO3): program files

Student name: ____________   Register number: ____________

Compile every program with: gcc -std=c11 -Wall -Wextra -O2 file.c -o file
Extra flags used: -static (Q1 bank_static), -fPIC -shared (libenc.so), -ldl (dlopen programs), -lm (Q6 raid_calc).
Tested on Ubuntu 24.04, gcc 13.3.0. Some programs need Linux and root (Q1 shared_pages, Q6 swap, Q7 mlockall).

Q1: libenc.c/.h, bank.c, dl_demo.c, maps_demo.c, bank_lazy.c, bench.c, shared_pages.c
    gcc -static bank.c libenc.c -o bank_static
    gcc -fPIC -shared libenc.c -o libenc.so ; gcc bank.c -L. -lenc -Wl,-rpath,'$ORIGIN' -o bank_dyn
Q2: paging.c (TODO 1 completed), paging_2048.c, pt_size.c, eat.c, frag.c, boundary.c, touch.c, mytime.c
Q3: seg_translate.c, segv_demo.c, seg_maps.c, frag_seg.c, tables.c
Q4: eat_pf.c, alloc.c, vm_sim.c, cow.c, ref_frames.c, ws.c
Q5: replace.c (TODO 1 completed), trace.c, experiment.c, belady.c
Q6: raid_calc.c (-lm), raid5_demo.c
Q7: mlock_demo.c, rt_loop.c, mem_sim.c
