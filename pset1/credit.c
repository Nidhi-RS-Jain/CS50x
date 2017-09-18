#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void){
    long long card;
    
    printf("Number: ");
    card = get_long_long();
    int sum = 0, arr[15], iter, power;
    
    for(iter = 0, power = 14; iter < 15; iter++, power--){    
        arr[iter] = card / (long long)pow(10, power) ;
        card -= ((card / (long long)pow(10, power)) * (long long)pow(10, power));
        //printf("%lld\n", card);
    }
    
    for(iter = 14; iter > -1; iter--){
        if(iter % 2 == 0) sum += arr[iter];
        else sum += (2 * arr[iter])/10 + (2 * arr[iter]) % 10;
    }
    
    if(sum % 10 == 0) printf("AMEX\n");
    else if(arr[0] >= 51 && arr[0] <= 55) printf("MASTERCARD\n");
    else if((arr[0] >= 40 && arr[0] <= 49) || arr[2] == 4) printf("VISA\n");
    else printf("INVALID\n");
    
    return 0;
}