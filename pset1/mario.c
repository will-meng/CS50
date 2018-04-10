#include <cs50.h>
#include <stdio.h>

void draw(string s, int n);

int main(void)
{
    int h;
    do 
    {
        printf("Height: ");
        h = get_int();
    } while (h > 23 || h < 0);
    
    
    for (int i = 0; i < h ; i++)
    {
        /* leading spaces */
        draw(" ", h-1-i);
        
        /* blocks and gap */
        draw("#",i+1);
        draw(" ",2);
        draw("#",i+1);
        printf("\n");
    }
    
}

void draw(string s, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s",s);
    }
}