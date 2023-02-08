/*
 * In this file, you will write the structures and functions needed to
 * implement a hash table.  Feel free to implement any helper functions
 * you need in this file to implement a hash table.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>

#include "dynarray.h"
#include "list.h"
#include "hash_table.h"


/*
 * This is the structure that represents a hash table.  You must define
 * this struct to contain the data needed to implement a hash table.
 */
struct ht{
    struct dynarray* da;
};

struct element{
    void* value;
    void* key;
};

/*
 * This function should allocate and initialize an empty hash table and
 * return a pointer to it.
 */
struct ht* ht_create(){
    struct ht* hash = malloc(sizeof(struct ht));
    hash->da=dynarray_create();
    return hash;
}

/*
 * This function should free the memory allocated to a given hash table.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the hash table.  That is the responsibility of the caller.
 *
 * Params:
 *   ht - the hash table to be destroyed.  May not be NULL.
 */
void ht_free(struct ht* ht){
    dynarray_free(ht->da);
    free(ht);
    return;
}

/*
 * This function should return 1 if the specified hash table is empty and
 * 0 otherwise.
 *
 * Params:
 *   ht - the hash table whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if ht is empty and 0 otherwise.
 */
int ht_isempty(struct ht* ht){
    if(dynarray_size(ht->da)==0){
        return 1;
    }
    return 0;
}


/*
 * This function returns the size of a given hash table (i.e. the number of
 * elements stored in it, not the capacity).
 */
int ht_size(struct ht* ht){
    
    return dynarray_size(ht->da);
}


/*
 * This function takes a key, maps it to an integer index value in the hash table,
 * and returns it. The hash algorithm is totally up to you. Make sure to consider
 * Determinism, Uniformity, and Speed when design the hash algorithm
 *
 * Params:
 *   ht - the hash table into which to store the element.  May not be NULL.
 *   key - the key of the element to be stored
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
int ht_hash_func(struct ht* ht, void* key, int (*convert)(void*)){
    //printf("\nhello%d\n",convert(key));
    //printf("%dhere\n",get_capacity(ht->da));
    return convert(key)%get_capacity(ht->da);
}


/*
 * This function should insert a given element into a hash table with a
 * specified key.  Note that you cannot have two same keys in one hash table. 
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * Resolution of collisions is requried, use either chaining or open addressing.
 * If using chaining, double the number of buckets when the load factor is >= 4
 * If using open addressing, double the array capacity when the load factor is >= 0.75
 * load factor = (number of elements) / (hash table capacity)
 *
 * Params:
 *   ht - the hash table into which to insert an element.  May not be NULL.
 *   key - the key of the element
 *   value - the value to be inserted into ht.
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */

void ht_insert(struct ht* ht, void* key, void* value, int (*convert)(void*)){
    
     if((float)get_size(ht->da)/get_capacity(ht->da) >= 0.75){
        struct ht* new1 = ht_create();
        _dynarray_resize(new1->da,get_capacity(ht->da)*2);
        printf("\nnew%d\n",get_capacity(new1->da));
        for(int r = 0; r < get_capacity(ht->da); r++){
            //printf("\nresize\n");
            void* k = dynarray_get(ht->da,r);
            if(k != NULL){
                struct element* n = (struct element*)k;
                int index = convert(n->key)%get_capacity(new1->da);
                while(dynarray_get(new1->da, index) != NULL){
                    index = (index +1)%get_capacity(new1->da);
                }
                dynarray_set(new1->da, index, dynarray_get(ht->da,r));
                //printf("\nresize\n");
            }
        }
        //dynarray_free(ht->da);
        //ht->da = new1->da;
        dynarray_clear(ht->da, new1->da);
        //dynarray_free(new1->da);
        //dynarray_free(new1->da);
        
        //resize and rehash
    }
    if(ht_lookup(ht,key,convert) != NULL){
        printf("\nThis:%d wasnt inserted\n", convert(key));
        return;

    }
    struct element* element = malloc(sizeof(struct element));
    element->value = value;
    element->key = key;
    int index = ht_hash_func(ht,key,convert);
    void* k = dynarray_get(ht->da,index);
    struct element* n = (struct element*)k;
    printf("\nTrying to insert: %d\n", convert(key));
    
    if(n==NULL){
        dynarray_set(ht->da,index,element);
        print_ht(ht);
        return;
        
    }
    if(convert(n->key) == convert(key)){
        return;
    }else{
            int i = index;
            while(dynarray_get(ht->da,i) != NULL){
                i++;
                if(i==index){
                    return;
                }
                if(i >= get_capacity(ht->da)-1){
                    i=0;
                }
            }
            dynarray_set(ht->da,i,element);
        
    }
    print_ht(ht);

    return;
}


/*
 * This function should search for a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, return the corresponding value (void*) of the element,
 * otherwise, return NULL
 *
 * Params:
 *   ht - the hash table into which to loop up for an element.  May not be NULL.
 *   key - the key of the element to search for
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void* ht_lookup(struct ht* ht, void* key, int (*convert)(void*)){
    //print_ht(ht);
    int initIndex = ht_hash_func(ht,key,convert);
    int index = ht_hash_func(ht,key,convert);
    while(1){
        if(dynarray_get(ht->da,index) != NULL){
            void* k = dynarray_get(ht->da,index);
            if (k != NULL) {
                struct element* n = (struct element*)k;
                if (convert(n->key) == convert(key)){
                    return (n->value);

                }
            }
        }
        index = (index +1) % get_capacity(ht->da);
        if (index == initIndex) {
            return NULL;
        }
    }


    /*
    for(int i = index; i!=get_capacity(ht->da); i++ ){
        if(i+1 == get_capacity(ht->da)){
            i = 0;
        }
    }


    
    int index = ht_hash_func(ht,key,convert);
    int run = 1;
    int stop = index;
    while(run){
        //printf("\nhere %d\n",get_capacity(ht->da));
        void* k = dynarray_get(ht->da,index);
        struct element* n = (struct element*)k;
        if(n!=NULL){
        
            if(convert(n->key) == convert(key)){
                run = 0;
                return n->value;
            }
            index++;
            if(index == stop){
                run = 0;
                return NULL;
            }
            if(index == get_capacity(ht->da)){
                index=0;
            }
    }
    else{
        index++;
        if(index == stop){
            run = 0;
            return NULL;
        }
        if(index == get_capacity(ht->da)){
            index=0;
        }
    }
}
*/
}


/*
 * This function should remove a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, remove the element and return, otherwise, do nothing and return 
 *
 * Params:
 *   ht - the hash table into which to remove an element.  May not be NULL.
 *   key - the key of the element to remove
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void ht_remove(struct ht* ht, void* key, int (*convert)(void*)){

    int run =1;
    int index = ht_hash_func(ht,key,convert);
    while(run){
        void* k = dynarray_get(ht->da,index);
        struct element* n = (struct element*)k;
        if(n!=NULL && convert(n->key) == convert(key)){
            free_element(ht->da,index);
            lower_size(ht->da);
            return;
        }else{
            if(index == get_capacity(ht->da)-1){
                index=0;
            }else{
                index++;
            }
        }
    }
    //print_ht(ht);
    return;
} 

void print_ht(struct ht* ht){
    printf("\nList:");
    for(int i = 0; i<get_capacity(ht->da); i++){
        void* k = dynarray_get(ht->da,i);
        struct element* n = (struct element*)k;
        if(n!= NULL){
            
            void* f = (int*)n->key;
            int b = *(int*)f;
            if(b!=-1){
                printf("%d,",b);
            }else{
                printf("[],",b);
            }
        }
        if(n== NULL){
            printf("[],");
        }
    }
    printf("\n");
}