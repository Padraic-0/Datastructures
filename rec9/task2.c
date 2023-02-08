#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * return true (1) if n is happy, false (0) otherwise
 */
bool isHappy (int n){
	/*
	 * FIXME:
	 */
	
	int map[1000]={0};
	int run = 1;
	while(run){
		//break n into digits
		int i = 3;
		int digits[4] ={0};
		while(n){
			
			digits[i]=n%10;
			n = n - digits[i];
			n /=10;
			i--;

		}
		int sum = digits[0]*digits[0] + digits[1]*digits[1] + digits[2]*digits[2] + digits[3]*digits[3];
		n = sum;
		if(sum == 1){
			return 1;
		}
		for(int i = 0; i < 1000; i++){
			if(sum == map[i]){
				return 0;
			}
		}
		map[sum] = sum;
	}

	return 0;
}



/*
 * Below are testing functions... DO NOT MODIFY!!!
 */

void show_result(int e, int r){
	printf("Expected: %d\nActual: %d...", e, r);
	if (r != e) 
        printf("FAIL\n\n\n");
    else 
        printf("OK\n\n\n");
}



int main()
{
	printf("\nTEST 1...19\n");
	show_result(1, isHappy(19));

	printf("\nTEST 2...2\n");
	show_result(0, isHappy(2));

	printf("\nTEST 3...7\n");
	show_result(1, isHappy(7));

	printf("\nTEST 4...176\n");
	show_result(1, isHappy(176));

	printf("\nTEST 5...36\n");
	show_result(0, isHappy(36));

	

	return 0;
}
