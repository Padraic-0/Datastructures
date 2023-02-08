#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ll.h"

// struct node
// {
// 	int val;
// 	struct node *next;
// };



struct node* add_two_num (struct node* l1, struct node* l2)
{
	struct node* l3 = (struct node*) malloc(sizeof(struct node));
	l3->next = NULL;
	
	int l1_val = 0;
	int multiplier1 = 1;
	while (l1 != NULL){
		l1_val += l1->val * multiplier1;
		l1 = l1->next;
		multiplier1 = multiplier1 * 10;
		//printf("This is l1 value %d\n",l1_val);
	}
	int l2_val = 0;
	int multiplier2 = 1;
	while (l2 != NULL){
		l2_val += l2->val * multiplier2;
		l2 = l2->next;
		multiplier2 = multiplier2 * 10;
		//printf("This is l1 value %d\n",l1_val);
	}
	int sum = l2_val + l1_val;
	//printf("This is sum %d\n",sum);
	char stored_val[10];
	snprintf(stored_val,10,"%d", sum);
	//printf("%c\n",stored_val[3]);
	
	struct node* runner;
	runner = l3;
	int length = strlen(stored_val);
	//printf("This is length %d\n",length);
	//printf("This is sum as string %c\n",stored_val[2]);
	l3->val = stored_val[length-1] - '0';
	for (int i = 1; i < length; i++){
		struct node* t1 = (struct node*) malloc(sizeof(struct node));
		t1->val = stored_val[length - 1 - i] - '0';
		t1->next = NULL;
		while (runner->next != NULL){
			runner = runner->next;
		}
		runner->next = t1;
	}
	
	
	

	return l3;
}


