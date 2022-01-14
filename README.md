# Ant Algorithm using Hybrid Programming
An ant colony algorithm implemented with MPI and multithreads

### Compilation
mpiicc -no-multibyte-chars -o ant ant.c -lpthread

### Execution
mpiexec -n (# of processors) ant

### What have you done
Created multiprocessors and then within the processors created multithreads, and the threads are id'd from 0->(number of colonies\*ants per colony) with no repeating ids


#### List of Variables Created and their Scopes
##### Global Variables: 
READ/WRITE:
**TGlobal**: city_path\[city_num\]\[city_num\] 

READ ONLY:
**n**: (number of cities) city_num 
**m**: (ants per colony) ants_per_colony

#### Local Variables:
**pheromone matrix τ**: pheromone\[city_num\]\[ants_per_colony\] 
**TLocal**

### Analysis on your result
No results yet

### Any difficulties?
The algorithm in general, parallelizing shouldn't be too hard because my thought is I could just use MPIGather/MPIPack and MPIScatter/Unpack for collecting different colonies's results and the pthreads were the ants and they can be parallelized with mutexes and barriers can be cond variables
