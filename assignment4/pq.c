/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Padraic Bergin
 * Email: berginp@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* da;
};
//struct to allow the da to hold a element with data and priority
struct element{
	void* data;
	int priority;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* newPQ = malloc(sizeof(struct pq));
	newPQ->da = dynarray_create();
	return newPQ;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->da);
	free(pq);
	/*
	 * FIXME: 
	 */
	return;
}
//print pq for tests
void print_pq(struct pq* pq){
	int size = dynarray_size(pq->da);
	printf("\n Here is the array: (");
	for (int i = 0; i < size; i++){
		struct element* temp = dynarray_get(pq->da,i);
		printf("%d,", temp->priority);
	}
	printf(")\n");
}

/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	//if null return empty
	if(pq->da == NULL){
		return 1;
	}
	if(dynarray_size(pq->da) <= 0){//if size is 0 then its empty
		return 1;
	}
	else{
		return 0;
	}
	/*
	 * FIXME: 
	 */
	//return 1;
}

/*
helper function to perculate the given element up
*/
void perc_up(struct pq* pq, int index){
	//printf("\nIndex is: %d\n", index);
	if ((index-1)/2 < 0){//if parent is out of bounds then return
		return;
	}
	
	else{
		//printf("\nParent Index is: %d\n", (index-1)/2);
		struct element* parent = dynarray_get(pq->da,(index-1)/2);//get parent of current
		//printf("\nhere %d\n", parent->priority);
		struct element* curr = dynarray_get(pq->da,index);//get current
		if(parent->priority > curr->priority){//swap if the parent is more then the current
			
			struct element* temp = parent;//temp for replacement
			//pq->da[(index-1)/2] = pq->da[index];
			dynarray_set(pq->da,(index-1)/2,curr);//replace parent with current
			//pq->da[index] = temp;
			dynarray_set(pq->da,index,temp);//replace current with parent
			perc_up(pq,(index-1)/2);//recursivily call until the parent is smaller then current
		}
		else{
			return;//stop when parent is smaller
		}
		
	}

}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	/*
	 * FIXME: 
	 */

	struct element* new = malloc(sizeof(struct element));
	new->priority = priority;
	new->data = value;
	dynarray_insert(pq->da, new);
	//printf("\nInserting: %d\n",priority);
	if(dynarray_size(pq->da) > 0){
		perc_up(pq, dynarray_size(pq->da)-1);//perc up the element until the parents are less using perc_up helper function
	}
	//print_pq(pq); print for testing
	return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	struct element* first = dynarray_get(pq->da,0);
	return first->data;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	struct element* first = dynarray_get(pq->da,0);
	return first->priority;
}

//perc down
void perc_down(struct pq* pq, int index){
	struct element* curr = dynarray_get(pq->da, index);
	struct element* left;
	struct element* right;
	if((index*2)+1 <= dynarray_size(pq->da)-1){//checking for left child
		left = dynarray_get(pq->da, (index*2)+1);//set left
	}
	else{
		return;//no need to perc down if index is out of bounds
	}
	if((index*2)+2 <= dynarray_size(pq->da)-1){//checjing for right child
		right = dynarray_get(pq->da, (index*2)+2);
	}
	else{
		if(curr->priority > left->priority){//if no right child and left child is smaller then current priotity then swap them and return
			dynarray_set(pq->da,index,left);
			dynarray_set(pq->da,(index*2)+1,curr);
			
		}
		return;
	}
	if(left->priority < right->priority){//checking if right path is larger then left path
		if(curr->priority > left->priority){// swaps current with left child if left child is smaller then curr and the right child
			//swap
			//call perc down again
			dynarray_set(pq->da,index,left);
			dynarray_set(pq->da,(index*2)+1,curr);
			perc_down(pq,(index*2)+1);
		}
		else{
			return;//return no swap because the smallest child is still larger then current prioty, so no swap
		}
	}else{
		if(curr->priority > right->priority){//swap right child
			dynarray_set(pq->da,index,right);
			dynarray_set(pq->da,(index*2)+2,curr);
			perc_down(pq,(index*2)+2);

		}else{
			return;
		}
	}


}
/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	//print_pq(pq);
	void* first = pq_first(pq);//hold first element then delete it
	free(dynarray_get(pq->da,0));
	struct element* last = dynarray_get(pq->da, dynarray_size(pq->da)-1);
	
	if(dynarray_size(pq->da)!= 1){
		dynarray_set(pq->da,0,last);//bring last up to front
		dynarray_remove(pq->da,dynarray_size(pq->da)-1);//remove the last
		perc_down(pq,0);//perc down to proper order
		
	}else{//last element so no need to perc down
		dynarray_remove(pq->da,0);//remove it
		//dynarray_remove(pq->da,0);
	}
	
	//print_pq(pq);
	return first;
}
