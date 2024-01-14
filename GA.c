// Include everything necessary here 
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "functions.h"
//#include "functions.c"
//#include "OF.c"

int main(int argc, char *argv[])
{
    // Handle the possible errors in input data given by the user and say how to execute the code
    if (argc != 6) {
        printf("Usage: ./GA <POPULATION SIZE> <MAX GENERATIONS> <crossover rate> <mutate rate> <stop criteria>\n");
        return 1;
    }

    // Assign all inputs given by the user argv[i] like
    // POPULATION_SIZE, MAX_GENERATIONS, crossover_rate, mutate_rate, stop_criteria
    int POPULATION_SIZE = atoi(argv[1]);
    int MAX_GENERATIONS = atoi(argv[2]);
    double crossover_rate = atof(argv[3]);
    double mutate_rate = atof(argv[4]);
    double stop_criteria = atof(argv[5]);

    // ###################################################################################
    // the number of variables
    int NUM_VARIABLES = 2;
    // the lower bounds of variables
    double Lbound[] = {-5.0, -5.0};
    // the upper bounds of variable
    double Ubound[] = {5.0, 5.0};
    // ###################################################################################


    // Here make all the initial print outs
    printf("Genetic Algorithm is initiated.\n");
    printf("------------------------------------------------\n");
    printf("The number of variables: %d\n", NUM_VARIABLES);
    printf("Lower bounds: [%.6lf, %.6lf]\n", Lbound[0], Lbound[1]);
    printf("Upper bounds: [%.6lf, %.6lf]\n\n", Ubound[0], Ubound[1]);
    printf("Population Size:   %d\n", POPULATION_SIZE);
    printf("Max Generations:   %d\n", MAX_GENERATIONS);
    printf("Crossover Rate:    %.6lf\n", crossover_rate);
    printf("Mutation Rate:     %.6lf\n", mutate_rate);
    printf("Stopping criteria: %.16lf\n", stop_criteria);
    printf("Results\n");
    printf("------------------------------------------------\n");

    // Timing
    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // Declare all the arrays you need here
    double population[POPULATION_SIZE][NUM_VARIABLES];
    double fitness[POPULATION_SIZE];
    double new_population[POPULATION_SIZE][NUM_VARIABLES];

    // Initialize best_fitness
    double best_fitness = 1.0; 

    // Initialize best_solution
    double best_solution[NUM_VARIABLES];

    srand((unsigned)time(NULL)); // Seed random number generator once

    // Call generate_population function to initialize the "population" like:
    // generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);
    generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);

    // iteration starts here. The loop continues until MAX_GENERATIONS is reached
    // Or stopping criteria is met
    for (int generation = 0; generation < MAX_GENERATIONS; generation++)
    {
        // Compute the fitness values using objective function for
        // each row in "population" (each set of variables) like:
        // compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);
        compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);

        // Here implement the logic of finding best solution with minimum fitness value
        // and the stopping criteria
        for (int i = 0; i < POPULATION_SIZE; i++) 
        {
            if (fitness[i] < best_fitness)  
            {
                best_fitness = fitness[i];
                for (int j = 0; j < NUM_VARIABLES; j++) 
                {
                    best_solution[j] = population[i][j];
                }
            }
        }
        // Check the stopping criteria
        if (best_fitness < stop_criteria) {
            printf("Stopping criteria met");
            break;
        }
        // Here call the crossover function
        crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);

        // Here call the mutation function
        mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);

        // Now you have the a new population, and it goes to the beginning of loop to re-compute all again
    }

    // Jump to this part of code if the stopping criteria is met before MAX_GENERATIONS is met

    // ###################################################################################
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time: %f seconds\n", cpu_time_used);
    // ###################################################################################

    // Here print out the best solution and objective function value for the best solution like the format
    printf("Best solution found: (");
    for (int j = 0; j < NUM_VARIABLES; j++) {
        printf("%.20lf", best_solution[j]);
        if (j < NUM_VARIABLES - 1) {
            printf(", ");
        }
    }
    printf(")\nBest fitness: %.20lf\n", best_fitness);

    return 0;
}
