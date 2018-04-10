#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Minutes: ");
    int min = get_int();
    printf("Bottles: %f\n", min*1.5*128/16);
}