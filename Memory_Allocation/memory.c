#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "oslabs.h"

/*
struct MEMORY_BLOCK {
    int start_address;
    int end_address;
    int segment_size;
    int process_id; //0 indicates a free block
}
*/

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int* map_count, int process_id) {
	struct MEMORY_BLOCK temp_memory_block;
	bool match = false;
	int memory_map_index = 0;
    int best_fit_segmant = 0;

	for (int i = 0; i < *map_count; i++) {
		if ((request_size == memory_map[i].segment_size) && (memory_map[i].process_id == 0)) {
			match = true;
			memory_map_index = i;
			best_fit_segmant = request_size;
			break;
		}
		else if ((memory_map[i].segment_size > request_size) && (memory_map[i].process_id == 0) && (match == false)) {
			match = true;
			memory_map_index = i;
			best_fit_segmant = memory_map[i].segment_size;
		}
		else if ((best_fit_segmant > memory_map[i].segment_size) && (memory_map[i].process_id == 0)) {
			memory_map_index = i;
			best_fit_segmant = memory_map[i].segment_size;
		}
	}

	if (match == true) {
		temp_memory_block = memory_map[memory_map_index];
		memory_map[memory_map_index].end_address = memory_map[memory_map_index].start_address + request_size - 1;
		memory_map[memory_map_index].segment_size = request_size;
		memory_map[memory_map_index].process_id = process_id;

		if (memory_map[memory_map_index].segment_size == temp_memory_block.segment_size) {
			return memory_map[memory_map_index];
		}

		*map_count = *map_count + 1;

		for (int i = *map_count - 1; i > memory_map_index; i--) {
			memory_map[i + 1] = memory_map[i];
		}

		memory_map[memory_map_index + 1].start_address = memory_map[memory_map_index].end_address + 1;
		memory_map[memory_map_index + 1].end_address = temp_memory_block.end_address;
		memory_map[memory_map_index + 1].segment_size = temp_memory_block.segment_size - request_size;
		memory_map[memory_map_index + 1].process_id = 0;

		return memory_map[memory_map_index];
	}
	else {
		temp_memory_block.start_address = 0;
		temp_memory_block.end_address = 0;
		temp_memory_block.segment_size = 0;
		temp_memory_block.process_id = 0;

		return temp_memory_block;
	}
}

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int* map_count, int process_id) {
	struct MEMORY_BLOCK temp_memory_block;
	bool match = false;
	int memory_map_index = 0;
    int best_fit_segmant = 0;

	for (int i = 0; i < *map_count; i++) {
		if ((request_size <= memory_map[i].segment_size)&&(memory_map[i].process_id == 0)) {
			match = true;
			memory_map_index = i;
			best_fit_segmant = request_size;
			break;
		}
	}

	if (match == true) {
		temp_memory_block = memory_map[memory_map_index];
		memory_map[memory_map_index].end_address = memory_map[memory_map_index].start_address + request_size - 1;
		memory_map[memory_map_index].segment_size = request_size;
		memory_map[memory_map_index].process_id = process_id;

		if (memory_map[memory_map_index].segment_size == temp_memory_block.segment_size) {
			return memory_map[memory_map_index];
		}

		*map_count = *map_count + 1;

		for (int i = *map_count - 1; i > memory_map_index; i--) {
			memory_map[i + 1] = memory_map[i];
		}

		memory_map[memory_map_index + 1].start_address = memory_map[memory_map_index].end_address + 1;
		memory_map[memory_map_index + 1].end_address = temp_memory_block.end_address;
		memory_map[memory_map_index + 1].segment_size = temp_memory_block.segment_size - request_size;
		memory_map[memory_map_index + 1].process_id = 0;

		return memory_map[memory_map_index];
	}
	else {
		temp_memory_block.start_address = 0;
		temp_memory_block.end_address = 0;
		temp_memory_block.segment_size = 0;
		temp_memory_block.process_id = 0;

		return temp_memory_block;
	}
}

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int* map_count, int process_id) {
	struct MEMORY_BLOCK temp_memory_block;
	bool match = false;
	int memory_map_index = 0;
    int worst_fit_segmant = 0;

	for (int i = 0; i < *map_count; i++) {
		if ((request_size == memory_map[i].segment_size) && (memory_map[i].process_id == 0)) {
			match = true;
			memory_map_index = i;
			worst_fit_segmant = request_size;
		}
		else if ((memory_map[i].segment_size > request_size) && (memory_map[i].process_id == 0) && (match == false)) {
			match = true;
			memory_map_index = i;
			worst_fit_segmant = memory_map[i].segment_size;
		}
		else if ((worst_fit_segmant < memory_map[i].segment_size) && (memory_map[i].process_id == 0)) {
			memory_map_index = i;
			worst_fit_segmant = memory_map[i].segment_size;
		}
	}

	if (match == true) {
		temp_memory_block = memory_map[memory_map_index];
		memory_map[memory_map_index].end_address = memory_map[memory_map_index].start_address + request_size - 1;
		memory_map[memory_map_index].segment_size = request_size;
		memory_map[memory_map_index].process_id = process_id;

		if (memory_map[memory_map_index].segment_size == temp_memory_block.segment_size) {
			return memory_map[memory_map_index];
		}

		*map_count = *map_count + 1;

		for (int i = *map_count - 1; i > memory_map_index; i--) {
			memory_map[i + 1] = memory_map[i];
		}

		memory_map[memory_map_index + 1].start_address = memory_map[memory_map_index].end_address + 1;
		memory_map[memory_map_index + 1].end_address = temp_memory_block.end_address;
		memory_map[memory_map_index + 1].segment_size = temp_memory_block.segment_size - request_size;
		memory_map[memory_map_index + 1].process_id = 0;

		return memory_map[memory_map_index];
	}
	else {
		temp_memory_block.start_address = 0;
		temp_memory_block.end_address = 0;
		temp_memory_block.segment_size = 0;
		temp_memory_block.process_id = 0;

		return temp_memory_block;
	}
}

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int* map_count, int process_id, int last_address) {
	struct MEMORY_BLOCK temp_memory_block;
	bool match = false;
	int memory_map_index = 0;
    int best_fit_segmant = 0;

	for (int i = last_address; i < *map_count; i++) {
		if ((request_size <= memory_map[i].segment_size) && (memory_map[i].process_id == 0)) {
			match = true;
			memory_map_index = i;
			best_fit_segmant = request_size;
			break;
		}
	}

	if (match == true) {
		temp_memory_block = memory_map[memory_map_index];
		memory_map[memory_map_index].end_address = memory_map[memory_map_index].start_address + request_size - 1;
		memory_map[memory_map_index].segment_size = request_size;
		memory_map[memory_map_index].process_id = process_id;

		if (memory_map[memory_map_index].segment_size == temp_memory_block.segment_size) {
			return memory_map[memory_map_index];
		}

		*map_count = *map_count + 1;

		for (int i = *map_count - 1; i > memory_map_index; i--) {
			memory_map[i + 1] = memory_map[i];
		}

		memory_map[memory_map_index + 1].start_address = memory_map[memory_map_index].end_address + 1;
		memory_map[memory_map_index + 1].end_address = temp_memory_block.end_address;
		memory_map[memory_map_index + 1].segment_size = temp_memory_block.segment_size - request_size;
		memory_map[memory_map_index + 1].process_id = 0;

		return memory_map[memory_map_index];
	}
	else {
		temp_memory_block.start_address = 0;
		temp_memory_block.end_address = 0;
		temp_memory_block.segment_size = 0;
		temp_memory_block.process_id = 0;

		return temp_memory_block;
	}
}

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX], int* map_count) {
	if ((*map_count == 1) && (memory_map[0].end_address == 0) && (memory_map[0].start_address == 0) && (memory_map[0].process_id == 0) && (memory_map[0].segment_size == 0)) {
		return;
	}
	else {
		for (int i = 0; i < *map_count; i++) {
			if ((freed_block.start_address == memory_map[i].start_address) && (freed_block.end_address == memory_map[i].end_address) && (freed_block.process_id == memory_map[i].process_id)) {
				if ((i > 0 && memory_map[i - 1].process_id == 0) && (i < *map_count - 1 && memory_map[i + 1].process_id == 0)) {
					memory_map[i - 1].end_address = memory_map[i + 1].end_address;
					memory_map[i - 1].segment_size = memory_map[i + 1].end_address - memory_map[i - 1].start_address + 1;
					memory_map[i - 1].process_id = 0;

					for (int index = i + 2; index < *map_count; index++) {
						memory_map[index - 2] = memory_map[index];
					}

					*map_count = *map_count - 2;

					break;
				}
				else if (i > 0 && memory_map[i - 1].process_id == 0) {
					memory_map[i - 1].end_address = memory_map[i].end_address;
					memory_map[i - 1].segment_size = memory_map[i].end_address - memory_map[i - 1].start_address + 1;
					memory_map[i - 1].process_id = 0;

					for (int index = i + 1; index < *map_count; index++) {
						memory_map[index - 1] = memory_map[index];
					}

					*map_count = *map_count - 1;

					break;
				}
				else if (i < *map_count - 1 && memory_map[i + 1].process_id == 0) {
					memory_map[i].end_address = memory_map[i + 1].end_address;
					memory_map[i].segment_size = memory_map[i].end_address - memory_map[i].start_address + 1;
					memory_map[i].process_id = 0;

					for (int index = i + 2; index < *map_count; index++) {
						memory_map[index - 1] = memory_map[index];
					}

					*map_count = *map_count - 1;

					break;
				}
				else {
					memory_map[i].process_id = 0;
					break;
				}
			}
		}
	}
}

/*
int main() {
	struct MEMORY_BLOCK memory_map[MAPMAX], new_memory_block;
	int count = 1;
	int* map_count;
	map_count = &count;
	memory_map[0].end_address = 1023;
	memory_map[0].start_address = 0;
	memory_map[0].process_id = 0;
	memory_map[0].segment_size = 1024;
	struct MEMORY_BLOCK free;

	new_memory_block = worst_fit_allocate(10, memory_map, map_count, 1);
	printArr(memory_map, map_count);
	printf("\n");

	new_memory_block = worst_fit_allocate(15, memory_map, map_count, 2);
	printArr(memory_map, map_count);
	printf("\n");

	new_memory_block = worst_fit_allocate(120, memory_map, map_count, 3);
	printArr(memory_map, map_count);
	printf("\n");

	new_memory_block = worst_fit_allocate(50, memory_map, map_count, 4);
	printArr(memory_map, map_count);
	printf("\n");

	new_memory_block = worst_fit_allocate(32, memory_map, map_count, 5);
	printArr(memory_map, map_count);
	printf("\n");

	free.start_address = 10;
	free.end_address = 24;
	free.segment_size = 15;
	free.process_id = 2;
	release_memory(free, memory_map, map_count);
    
	free.start_address = 25;
	free.end_address = 144;
	free.segment_size = 120;
	free.process_id = 3;
	release_memory(free, memory_map, map_count);
    
	free.start_address = 145;
	free.end_address = 194;
	free.segment_size = 50;
	free.process_id = 4;
	release_memory(free, memory_map, map_count);

	new_memory_block = worst_fit_allocate(15, memory_map, map_count, 6);
	printArr(memory_map, map_count);
	printf("\n");

	return 0;
}
*/