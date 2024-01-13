// Include everything necessary here 
#include "functions.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

double generate_random(double min, double max)
{
    // implement a function to return a value between min and max

    // Generate a random number between 0 and 1
    double random_value = (double)rand() / RAND_MAX;

    // Scale and shift the random number to fit within the desired range
    double scaled_random = random_value * (max - min) + min;

    return scaled_random;
}

unsigned int generate_int()
{
    // implement the function to return a random integer value

    // Generate a random unsigned integer value
    unsigned int random_value = rand();

    return random_value;
}

// Function to initialize a random population
void generate_population(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES])
{
    // randomly initialize for all values in "population[i][j]""
    
    for (int i = 0; i < POPULATION_SIZE; i++) 
    {
        for (int j = 0; j < NUM_VARIABLES; j++) 
        {
            population[i][j] = generate_random(Lbound[j], Ubound[j]);
        }
    }
}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{

    /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */

    for (int i = 0; i < POPULATION_SIZE; i++) 
    {
        fitness[i] = Objective_function(NUM_VARIABLES, population[i]);
    }
}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/

    // Calculate selection probabilities
    double fitness_probs[POPULATION_SIZE];
    double total_fitness = 0.0;

    for (int i = 0; i < POPULATION_SIZE; i++) 
    {
        total_fitness += fitness[i];
    }

    for (int i = 0; i < POPULATION_SIZE; i++) 
    {
        fitness_probs[i] = fitness[i] / total_fitness;
    }

    for (int i = 0; i < POPULATION_SIZE; i++) 
    {
        double random_value = generate_random(0.0, 1.0);
        double cumulative_prob = 0.0;

        // Select parents based on fitness probabilities
        int parent1 = -1;
        int parent2 = -1;

        for (int j = 0; j < POPULATION_SIZE; j++) 
        {
            cumulative_prob += fitness_probs[j];
            if (random_value <= cumulative_prob) 
            {
                if (parent1 == -1) 
                {
                    parent1 = j;
                } 
                else 
                {
                    parent2 = j;
                    break;
                }
            }
        }

        // Apply crossover based on crossover_rate
        if (generate_random(0.0, 1.0) <= crossover_rate) 
        {
            double crossover_point = generate_random(0, NUM_VARIABLES - 1);

            for (int j = 0; j < NUM_VARIABLES; j++) 
            {
                if (j < crossover_point) 
                {
                    new_population[i][j] = population[parent1][j];
                } 
                else 
                {
                    new_population[i][j] = population[parent2][j];
                }
            }
        } 
        else 
        {
            // If no crossover, copy one of the parents as-is
            for (int j = 0; j < NUM_VARIABLES; j++) 
            {
                new_population[i][j] = population[parent1][j];
            }
        }
    }
}

void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate)
{
    /*Implement the logic of mutation on "new_population" and then copy everything into "population"*/

    for (int i = 0; i < POPULATION_SIZE; i++) 
    {
        for (int j = 0; j < NUM_VARIABLES; j++) 
        {
            if (generate_random(0.0, 1.0) <= mutate_rate) 
            {
                // Apply mutation by generating a new random value within bounds
                new_population[i][j] = generate_random(Lbound[j], Ubound[j]);
            }
        }
    }

    // Copy new_population into population
    for (int i = 0; i < POPULATION_SIZE; i++) 
    {
        for (int j = 0; j < NUM_VARIABLES; j++) 
        {
            population[i][j] = new_population[i][j];
        }
    }
}
