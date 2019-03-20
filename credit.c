#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{   
    // get user input
    long num = get_long("Number:");
    
    // instantiate 2 int variable for the sum and one int for length
    int len = 0;
    int sum = 0;
    long temp = num;    
    
    // get and sum every second digits from the last
    while (temp !=0){
        ++len; // increase length   
        
        // set a carrier for the number need to be added
        int carrier = 0;
        if((len%2) != 0){// odd digits
            carrier = (temp%10);    
        }else{// even digits
            carrier = (temp%10) * 2; 
        }
        
        sum += carrier/10 + carrier%10; 
        
        
        // set new temp for next iteration
        temp = temp/10;      
    } 
    
    // validation
    if((sum % 10) != 0){
        printf("%s\n", "INVALID");
        return 0;
    }
    
    // Check for each credit provider
    int first2Digits = num / (long)pow(10, len-2);

    if(len == 15 && (first2Digits == 34 ||first2Digits == 37)){
        printf("%s\n", "AMEX");
        return 0;
    }
    
    if(len == 16 && (first2Digits >= 51 && first2Digits <= 55)){
        printf("%s\n", "MASTERCARD");
        return 0;
    }
    
    if((len == 13 || len == 16) && (first2Digits / 10 == 4)){
        printf("%s\n", "VISA");
        return 0;
    }
    
    // Non cretrias were met, print invalid and return -1
    printf("%s\n", "INVALID");
    return 0; 
}