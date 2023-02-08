/* CS261- Recitation 1 - Q.2
 * Solution description: call the function foo using "reference" to see the values before and after the function
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    /*Set b to half its original value*/
    *b = *b / 2;
    /*Assign a+b to c*/
    c = *a + *b;
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 7, 8, 9 respectively*/
    int x=7,y=8,z=9,num;
    /*Print the values of x, y and z*/
    printf("x= %d,y = %d, z = %d\n", x,y,z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    num = foo(&x,&y,z);
    /*Print the value returned by foo*/
    printf("Foo= %d\n", num);
    /*Print the values of x, y and z again*/
    printf("x= %d,y = %d, z = %d\n", x,y,z);
    /*Is the return value different than the value of z?  Why? */
    // The return value is unchanged, as z wasnt passed by refernce so while in the function the value of c changed, the pointer to c is still 
    // equal to 9
    return 0;
}