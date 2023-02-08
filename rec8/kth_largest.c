#include <stdio.h>
#include <stdlib.h>

int* heap(int* nums, int numsSize){
    int *heapnums = malloc(sizeof(int)*numsSize);
    int myTemp;
    int parnt;
    int curr;
    heapnums[0] = nums[0];
    for (int i = 0 ; i < numsSize; i++) {
        heapnums[i] = nums[i];
        parnt = (i-1)/2;
        curr = i;
        while(heapnums[parnt] < heapnums[curr]) {
            myTemp = heapnums[curr];
            heapnums[curr] = heapnums[parnt];
            heapnums[parnt] = myTemp;
            if (parnt > 0) {
                curr = parnt;
                parnt = (parnt-1)/2;
            }
        }
    }
    return heapnums;
}
int findKthLargest(int* nums, int numsSize, int k)
{
    nums = heap(nums,numsSize);
    
    
    for (int i=0; i<numsSize;i++){
        int temp = nums[0];
        nums[0] = nums[numsSize-i-1];
        nums[numsSize-i-1] = temp;
        int curr = 0;
        int run = 1;
        while(run){
            if((curr*2)+2 <= numsSize-i-2){
                if(nums[curr] < nums[(curr*2)+1] || nums[curr] < nums[(curr*2)+2]){
                    if(nums[(curr*2)+1] >= nums[(curr*2)+2]){
                        
                        int temp = nums[curr];
                        int next = nums[(curr*2)+1];
                        nums[curr] = next;
                        nums[(curr*2)+1] = temp;
                        curr = (curr*2)+1;
                    }else if(nums[(curr*2)+1] < nums[(curr*2)+2]){
                        int temp = nums[curr];
                        int next = nums[(curr*2)+2];
                        nums[curr] = next;
                        nums[(curr*2)+2] = temp;
                        curr = (curr*2)+2;
                    }
                    }else{
                        run = 0;
                    }
            }
            else if((curr*2)+1 <= numsSize-i-2){
                if(nums[curr]>!nums[(curr*2)+1]){
                        int temp = nums[curr];
                        int next = nums[(curr*2)+1];
                        nums[curr] = next;
                        nums[(curr*2)+1] = temp;
                        curr = (curr*2)+1;
                    }else{
                        run = 0;
                    }
                }else{
                    run = 0;
                }
            }
        
            //if(nums[curr]<nums[(curr*2)+1] || nums[curr] < nums[(curr*2)+2])
            

        
        
    }
    return nums[numsSize-k];
}


int main(int argc, char **argv)
{
    
    printf("\nTest 1...\n");
    int num1[6] = {3,2,1,5,6,4};
    printf("2nd largest in [3 2 1 5 6 4]\n");
    printf("Expected: 5\n");
    printf("Actual: %d\n", findKthLargest(num1, 6, 2));

    printf("\nTest 2...\n");
    int num2[9] = {3,2,3,1,2,4,5,5,6};
    printf("4th largest in [3 2 3 1 2 4 5 5 6]\n");
    printf("Expected: 4\n");
    printf("Actual: %d\n", findKthLargest(num2, 9, 4));


    printf("\nTest 3...\n");
    int num3[5] = {10,10,10,10,10};
    printf("5th largest in [10 10 10 10 10]\n");
    printf("Expected: 10\n");
    printf("Actual: %d\n", findKthLargest(num3, 5, 5));

    printf("\nTest 4...\n");
    int num4[7] = {-10,10,-10,10,-10,10,0};
    printf("4th largest in [-10 10 -10 10 -10 10 0]\n");
    printf("Expected: 0\n");
    printf("Actual: %d\n", findKthLargest(num4, 7, 4));

    printf("\nTest 5...\n");
    int num5[10] = {10,9,8,7,6,5,4,3,2,1};
    printf("1st largest in [10 9 8 7 6 5 4 3 2 1]\n");
    printf("Expected: 10\n");
    printf("Actual: %d\n", findKthLargest(num5, 10, 1));


    return 0;
}