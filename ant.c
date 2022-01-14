#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <pthread.h>

#define ThreadPerProcess 5

void *func(void *arg);
void Send_tour(tour_t tour, int dest);
void Recieve_tour(tour_t tour, int src);

typedef struct {
    int *cities; //cities in partial tour
    int count; // number of cities in partial tour
    int cost; // cost of partial tour
} tour_struct;

typedef tour_struct* tour_t;

int main(int argc, char *argv[])
{
    int pid, comm_sz;

    // Set of cities TGlobal
    int city_path[17][17] = {
        {0, 633, 257,  91, 412, 150,  80, 134, 259, 505, 353, 324,  70, 211, 268, 246, 121},
        {633,   0, 390, 661, 227, 488, 572, 530, 555, 289, 282, 638, 567, 466, 420, 745, 518},
        {257, 390,   0, 228, 169, 112, 196, 154, 372, 262, 110, 437, 191,  74,  53, 472, 142},
        {91, 661, 228,   0, 383, 120,  77, 105, 175, 476, 324, 240,  27, 182, 239, 237,  84},
        {412, 227, 169, 383,   0, 267, 351, 309, 338, 196,  61, 421, 346, 243, 199, 528, 297},
        {150, 488, 112, 120, 267,   0,  63,  34, 264, 360, 208, 329,  83, 105, 123, 364,  35},
        {80, 572, 196,  77, 351,  63,   0,  29, 232, 444, 292, 297,  47, 150, 207, 332,  29},
        {134, 530, 154, 105, 309,  34,  29,   0, 249, 402, 250, 314,  68, 108, 165, 349,  36},
        {259, 555, 372, 175, 338, 264, 232, 249,   0, 495, 352,  95, 189, 326, 383, 202, 236},
        {505, 289, 262, 476, 196, 360, 444, 402, 495,   0, 154, 578, 439, 336, 240, 685, 390},
        {353, 282, 110, 324,  61, 208, 292, 250, 352, 154,   0, 435, 287, 184, 140, 542, 238},
        {324, 638, 437, 240, 421, 329, 297, 314,  95, 578, 435,   0, 254, 391, 448, 157, 301},
        {70, 567, 191,  27, 346,  83,  47,  68, 189, 439, 287, 254,   0, 145, 202, 289,  55},
        {211, 466,  74, 182, 243, 105, 150, 108, 326, 336, 184, 391, 145,   0,  57, 426,  96},
        {268, 420,  53, 239, 199, 123, 207, 165, 383, 240, 140, 448, 202,  57,   0, 483, 153},
        {246, 745, 472, 237, 528, 364, 332, 349, 202, 685, 542, 157, 289, 426, 483, 0, 336},
        {121, 518, 142,  84, 297,  35,  29,  36, 236, 390, 238, 301,  55,  96, 153, 336,   0}};
    
    int completed[17] = {0};

    int city_num = 17; //n
    int ants_per_colony = 2; //m
    
    // MPI Multiprocessors
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Status status;

    // Pthreads multithreads
    pthread_t tid[ThreadPerProcess];
    int id[ThreadPerProcess];

    //printf("Hello world from %d of %d\n", my_rank, comm_sz);

    int i;
    for(i=0; i<ThreadPerProcess; i++)
    {
        id[i] = (ThreadPerProcess*pid) + i;
        pthread_create(&tid[i], NULL, func, &id[i]);
    }

    for(i =0; i<ThreadPerProcess; i++)
    {
        pthread_join(tid[i], NULL);
    }


    MPI_Finalize();

    return 0;
}

void *func(void *arg)
{
    int id = *((int*)arg);
    int nc = 17;
    int city_num = 17;
    int ants_per_colony = 2;
    //int pheromone[city_num][ants_per_colony];
    //printf("My id is: %d\n", id);
    for(int t=1; t<nc; t++)
    {
        for(int i=1; i<city_num; i++)
        {
            for(int k=1; k<ants_per_colony; k++)
            {
                // choose next city j according to the transition rule
            }
        }

        for(int k=1; k<ants_per_colony; k++)
        {
            // Calculate tour distance Lk for ant k
            if(/*an improved tour is found*/)
            {
                //Update T* and L*
            }

            if(/*this is an exchange cycle*/)
            {
                if(/* L* < LGlobal */)
                {
                    // CRITICAL SECTION -> can use mutex to implement
                    //TGlobal = T*
                    //LGlobal = L*
                    // END CRITICAL SECTION -> mutex unlock
                }
                // SYNCHRONISATION BARRIER -> cond variables
                // T* = TGlobal (UPDATE LOCAL VARIABLES WITH NEW GLOBAL VARIABLE)
            }

        }
        // Update pheromone matrix t
    }
    

    return 0;
}

void Send_tour(tour_t tour, int dest)
{
    int position = 0;
    MPI_Pack(tour->cities, n+1, MPI_INT, contig_buf, LARGE, &position, MPI_COMM_WORLD);
    MPI_Pack(tour->count, n+1, MPI_INT, contig_buf, LARGE, &position, MPI_COMM_WORLD);
MPI_Pack(tour->cost, n+1, MPI_INT, contig_buf, LARGE, &position, MPI_COMM_WORLD);

    MPI_Send(contig_buf, position, MPI_PACKED, dest, 0, MPI_COMM_WORLD);
}

void Recieve_tour(tour_t tour, int src)
{
    int position = 0;

    MPI_Recv(contig_buf, LARGE, MPI_PACKED, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Unpack(contig_buf, LARGE, &position, &tour->cities, n+1, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(contig_buf, LARGE, &position, &tour->count, n+1, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(contig_buf, LARGE, &position, &tour->cost, n+1, MPI_INT, MPI_COMM_WORLD);

}
