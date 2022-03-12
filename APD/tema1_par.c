#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "genetic_algorithm.h"

int main(int argc, char *argv[]) {
	// array with all the objects that can be placed in the sack
	sack_object *objects = NULL;

	// number of objects
	int object_count = 0;

	// maximum weight that can be carried in the sack
	int sack_capacity = 0;

	// number of generations
	int generations_count = 0;

	// number of Threads
	int P = 0;

	if (!read_input(&objects, &object_count, &sack_capacity, &generations_count, &P, argc, argv)) {
		return 0;
	}

	pthread_t threads[P];
	void *status;
	int i;
	int r;

	individual *current_generation = (individual*) calloc(object_count, sizeof(individual));
	individual *next_generation = (individual*) calloc(object_count, sizeof(individual));

	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, P);

	struct threadArgs args[P];

	for (i = 0; i < P; i++) {
		args[i].threadID = i;
		args[i].P = P;
		args[i].object_count = object_count;
		args[i].sack_capacity = sack_capacity;
		args[i].generations_count = generations_count;
		args[i].objects = objects;
		args[i].current_generation = current_generation;
		args[i].next_generation = next_generation;
		args[i].barrier = &barrier;

		r = pthread_create(&threads[i], NULL, run_genetic_algorithm, &args[i]);
		
		if (r) {
	  		printf("Eroare la crearea thread-ului %d\n", args->threadID);
	  		exit(-1);
		}
	}

	for (i = 0; i < P; i++) {
		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", args->threadID);
			exit(-1);
		}
	}

	pthread_barrier_destroy(&barrier);

	free(objects);

	free_generation(current_generation);
	free(current_generation);

	free_generation(next_generation);
	free(next_generation);

	return 0;
}
