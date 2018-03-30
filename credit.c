#include <cs50.h>
#include <stdio.h>
#include <math.h>

int firstNDigits(long long int num, int digits, int n);
int sumDigits(int n);
int checksum(long long int n);

int main(void)
{   
    // Get Input
    printf("Number: ");
    long long int cc = get_long_long();
    
    // Check length and starting digits 
    int digits = floor(log10(cc)) + 1;
    int firstDigit = firstNDigits(cc,digits,1);
    int first2Digits = firstNDigits(cc,digits,2);
    //printf("%i %i %i %i\n",digits,firstDigit,first2Digits,checksum(cc)); //Debug
    
    if ((digits == 13 || digits == 16) && firstDigit == 4) {
        //Possible VISA
        if (checksum(cc)%10 == 0) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
        
    } else if (digits == 15 && (first2Digits == 34 || first2Digits == 37)) {
        //Possible AMEX
        if (checksum(cc)%10 == 0) {
            printf("AMEX\n");
        } else {
            printf("INVALID\n");
        }
    } else if (digits == 16 && first2Digits >= 50 && first2Digits <= 55) {
        //Possible MASTERCARD
        if (checksum(cc)%10 == 0) {   
            printf("MASTERCARD\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        //Invalid card
        printf("INVALID\n");
    }
    
}

int firstNDigits(long long int num, int digits, int n)
{
    return (int)(num / (long long int)pow(10,digits-n));
}

int sumDigits(int n)
{
    return n/10 + n%10;
}

int checksum(long long int n)
{
    int sum = 0, digit = 1;
    while (n > 0)
    {
        if (digit%2 == 0) {
            sum += sumDigits((n%10)*2);
        } else {
            sum += n%10;
        }
        n /= 10;
        digit++;
    }
    return sum;
}



