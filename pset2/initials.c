#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s = get_string();
    if (s != NULL)
    {
        //Print first initial if first character is not a space
        if (isalpha(s[0]))
        {
            printf("%c",toupper(s[0]));
        }
        
        //Look for letters following spaces, and print them if found
        int n = strlen(s);
        for (int i=1; i < n; i++)
        {
            if (s[i-1] == ' ' && isalpha(s[i]))
            {
                printf("%c",toupper(s[i]));
            }
        }
    }
    printf("\n");
}