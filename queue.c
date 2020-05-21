/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
	queue_t *q =  malloc(sizeof(queue_t));
	/* What if malloc returned NULL? */
	if(q == NULL)
		return NULL;

	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

/* free all storage used by queue */
void q_free(queue_t *q)
{
	/* how about freeing the list elements and the strings? */
	/* free queue structure */
	if(q != NULL){
		list_ele_t *curr;
		list_ele_t *prev;
		curr = q->head;

		while(curr != NULL){
			prev = curr;
			curr = curr->next;
			free(prev->value);
			free(prev);
		}
		/* end 02 */
		free(q);
	}
}

/*
   attempt to insert element at head of queue.
   return true if successful.
   return false if q is NULL or could not allocate space.
   argument s points to the string to be stored.
   the function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
	list_ele_t *newh;
	/* what should you do if the q is NULL? */
	if(q == NULL)
		return false;
	/* don't forget to allocate space for the string and copy it */
	/* what if either call to malloc returns NULL? */
	newh = malloc(sizeof(list_ele_t));
	if(newh == NULL){
		return false;
	}
	newh->value = (char *) malloc(sizeof(char)*(strlen(s) + 1));
	if(newh->value == NULL){
		free(newh);
		return false;
	}
	strcpy(newh->value, s);
	newh->next = NULL;

	if(q->head == NULL){
		q->head = newh;
		q->tail = newh;
	}else{
		newh->next = q->head;
		q->head = newh;
	}
	q->size += 1;

	return true;
}


/*
   attempt to insert element at tail of queue.
   return true if successful.
   return false if q is NULL or could not allocate space.
   argument s points to the string to be stored.
   the function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
	/* you need to write the complete code for this function */
	/* remember: it should operate in o(1) time */
	if(q == NULL)
		return false;

	list_ele_t *new_tail;
	new_tail = malloc(sizeof(list_ele_t));
	if (new_tail == NULL){
		return false;
	}
	new_tail->value = (char *)  malloc(sizeof(char)*(strlen(s) + 1));
	if(new_tail->value == NULL){
		free(new_tail);
		return false;
	}
	strcpy(new_tail->value, s);
	new_tail->next = NULL;

	q->tail->next = new_tail;
	q->tail = new_tail;

	q->size += 1;
	/* end 04 */
	return true;
}

/*
   attempt to remove element from head of queue.
   return true if successful.
   return false if queue is NULL or empty.
   if sp is non-NULL and an element is removed, copy the removed string to *sp
   (up to a maximum of bufsize-1 characters, plus a NULL terminator.)
   the space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
	/* you need to fix up this code. */
	list_ele_t *curr_head;

	if(q == NULL || q->head == NULL)
		return false;
        
	if(sp != NULL){
		strncpy(sp, q->head->value, bufsize - 1);
		sp[bufsize - 1] = 0;
	}

	free(q->head->value);

	curr_head = q->head;
	q->head = q->head->next;
	free(curr_head);

	q->size -= 1;
	/* end 05 */
	return true;
}

/*
   return number of elements in queue.
   return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
	/* you need to write the code for this function */
	/* remember: it should operate in o(1) time */
	if(q == NULL || q->head == NULL)
		return 0;
	return q->size;
	/* end 06 */
}

/*
   reverse elements in queue
   no effect if q is NULL or empty
   this function should not allocate or free any list elements
   (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
   it should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
	/* you need to write the code for this function */
	if(q == NULL || q->head == NULL){
		/* nothing to do */
	}else{
		list_ele_t *curr_node;
		list_ele_t *prev_node;
		list_ele_t *next_node;
		prev_node = NULL;
		curr_node = q->head;
		next_node = q->head->next;
		q->head->next = prev_node;

		while(next_node != NULL){
			prev_node = curr_node;
			curr_node = next_node;
			next_node = next_node->next;
			curr_node->next = prev_node;
		}
		q->tail = q->head;
		q->head = curr_node;
	}
	/* end 07 */
}

