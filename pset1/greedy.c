#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void){
    float change;
    
    printf("O hai! ");
    
    do{
        printf("How much change is owed?\n");
        change = get_float();
    }while( change < 0.0 );
    
    change = round(change * 100.00);
    int money = change;
    int sum = 0 ;

    //printf("%d\n", money);
    
    sum += money / 25;
    money %= 25;
    
    sum += money / 10;
    money %= 10;

    sum += money / 5;
    money %= 5;

    sum += money; 
    
    printf("%d\n", sum);
    
    return 0;
}