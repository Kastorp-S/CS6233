#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "oslabs.h"

/*
struct RCB {
    int request_id;
    int arrival_timestamp;
    int cylinder;
    int address;
    int process_id;
}
*/

struct RCB null_rcb = {0, 0, 0, 0, 0};

int is_null_rcb(struct RCB rcb){
    if(rcb.request_id == 0 && rcb.arrival_timestamp == 0 && rcb.cylinder == 0 && rcb.address == 0 && rcb.process_id ==0) {
        return 1;
    }
    else {
        return 0;   
    } 
}

// Arrival FCFS
struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_count, struct RCB current_request, struct RCB new_request, int timestamp) {
    if(is_null_rcb(current_request)){
		return new_request;
	} else {
		request_queue[*queue_count] = new_request;
		(*queue_count) = (*queue_count) + 1;
		return current_request;
    }
}

// Completion FCFS
struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],int *queue_count) {
    if(*queue_count == 0){
		return null_rcb;
    }
	
	int first_arrival = 0;
	
	for (int i = 1; i < *queue_count; i++) {
		if (request_queue[i].arrival_timestamp < request_queue[first_arrival].arrival_timestamp) {
			first_arrival = i;
		}
	}

	struct RCB remove = request_queue[first_arrival];

	for (int i = first_arrival -1; i < *queue_count - 1; i++) {
		request_queue[i] = request_queue[i+1];
	}

	(*queue_count) = (*queue_count) - 1;
	return remove;	
}

// Arrival SSTF
struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],int *queue_count, struct RCB current_request, struct RCB new_request, int timestamp){
    if(is_null_rcb(current_request)){
		return new_request;
	} else {
		request_queue[*queue_count] = new_request;
		(*queue_count) = (*queue_count) + 1;
		return current_request;
    }
}

// Complettion SSTF
struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_count,int current_cylinder) {
    if(*queue_count == 0){
		return null_rcb;
    }

	struct relative_req {
		struct RCB queue_rcb;
		int distance;
		int close_cylinder;
	};
	
	struct relative_req rcq[*queue_count];
	
	int close_req;
	
	for (int i = 0; i < *queue_count; i++) {
		rcq[i].queue_rcb = request_queue[i];
		rcq[i].close_cylinder = 0;
		rcq[i].distance = (request_queue[i].cylinder - current_cylinder) * (request_queue[i].cylinder - current_cylinder);
		
        if (i == 0){
			close_req = rcq[i].distance;
        } else if (close_req > rcq[i].distance){
			close_req = rcq[i].distance;
        }
	}

	for (int i = 0; i < *queue_count; i++) {
		if (rcq[i].distance == close_req) {
			rcq[i].close_cylinder = 1;
        }
	}
	
	int first_request = 1;
	struct RCB next_rcb;
	int early_index;
	
	for (int i = 0; i < *queue_count; i++){
		if(first_request == 1 && rcq[i].close_cylinder == 1){
			next_rcb = rcq[i].queue_rcb;
			first_request = 0;
			early_index = i;
		} else if (rcq[i].close_cylinder == 1 && rcq[i].queue_rcb.arrival_timestamp < next_rcb.arrival_timestamp) {
			next_rcb = rcq[i].queue_rcb;
			early_index = i;
		}
		
		for (int i = early_index; i < *queue_count - 1; i++) {
			request_queue[i] = request_queue[i+1];
		}
	}

	*queue_count = *queue_count - 1;
	return next_rcb;
}

// Arrival LOOK
struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],int *queue_count, struct RCB current_request, struct RCB new_request, int timestamp){
    if(is_null_rcb(current_request)){
		return new_request;
	} else {
		request_queue[*queue_count] = new_request;
		(*queue_count) = (*queue_count) + 1;
		return current_request;
    }
}
// Completion LOOK
struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],int *queue_count, int current_cylinder, int scan_direction){
    if(*queue_count == 0) {
		return null_rcb;
    }
	
	int early = 1000;
	int early_index = 0;
	
	for (int i = 0; i < *queue_count; i++) {
		if(request_queue[i].cylinder == current_cylinder) {
			if(request_queue[i].arrival_timestamp < early) {
				early = request_queue[i].arrival_timestamp;
				early_index = i;
			}
		}
	}
	
	if (early != 1000) {
		struct RCB result = request_queue[early_index];
		request_queue[early_index] = request_queue[(*queue_count) - 1];
		(*queue_count)--;
		return result;
	}

	int closest = 1000;
	int closest_index = 0;	
	if(scan_direction == 1) {
		for (int i = 0; i < *queue_count; i++) {
			if(request_queue[i].cylinder > current_cylinder) {
				if(request_queue[i].cylinder - current_cylinder < closest) {
					closest = request_queue[i].cylinder - current_cylinder;
					closest_index = i;
				}
			}
		}
		
		if (closest != 1000) {
			struct RCB result = request_queue[closest_index];
			
			request_queue[closest_index] = request_queue[(*queue_count) -1];
			(*queue_count)--;
			
			return result;
		}
		
		closest = 1000;
		closest_index = 0;
		
		for (int i = 0; i < *queue_count; i++) {
			if(request_queue[i].cylinder - current_cylinder < closest) {
				closest = request_queue[i].cylinder - current_cylinder;
				closest_index = i;
			}
		}

		struct RCB result = request_queue[early_index];
		request_queue[early_index] = request_queue[(*queue_count) - 1];
		(*queue_count)--;
		
		return result;	
	}
	
	if (scan_direction == 0) {
		for (int i = 0; i < *queue_count; i++) {
			if(request_queue[i].cylinder < current_cylinder) {
				if(request_queue[i].cylinder < current_cylinder) {
					closest = request_queue[i].cylinder - current_cylinder;
					closest_index = i;
				}
			}
		}
		
		if (closest != 1000) {
			struct RCB result = request_queue[closest_index];
			request_queue[closest_index] = request_queue[(*queue_count) - 1];
			(*queue_count)--;
			
			return result;
		}
		
		for (int i = 0; i < *queue_count; i++){
			if(request_queue[i].cylinder - current_cylinder < closest) {
				closest = request_queue[i].cylinder - current_cylinder;
				closest_index = i;
			}
		}
		
		struct RCB result = request_queue[early_index];
		request_queue[early_index] = request_queue[(*queue_count) - 1];
		(*queue_count)--;
		
		return result;
	}
}