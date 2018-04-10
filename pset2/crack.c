#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

void check_key(string key, string salt, string hash);

int main(int argc, string argv[])
{
    //Check for valid command line input
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    // Salt is first 2 characters of hash
    char salt[] = {argv[1][0], argv[1][1]};
    
    // Setup library of possible characters in password
    char lib[] = {  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                    'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                    'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    int len = sizeof(lib) / sizeof(char);
    
    //Generate and test all possible permutations of up to 5-letter keys
    char guess1[2], guess2[3], guess3[4], guess4[5], guess5[6];
    guess1[1] = '\0';
    guess2[2] = '\0';
    guess3[3] = '\0';
    guess4[4] = '\0';
    guess5[5] = '\0';
    
    for (int i = 0; i < len; i++)
    {
        // Generate 1st letter
        guess1[0] = lib[i];
        guess2[0] = lib[i];
        guess3[0] = lib[i];
        guess4[0] = lib[i];
        guess5[0] = lib[i];
        
        // Run comparison function
        check_key(guess1, salt, argv[1]);
                    
        // Iterate over 2-letter guesses
        for (int j = 0; j < len; j++)
        {
            // Generate 2nd letter
            guess2[1] = lib[j];
            guess3[1] = lib[j];
            guess4[1] = lib[j];
            guess5[1] = lib[j];
            
            // Run comparison function
            check_key(guess2, salt, argv[1]);
                        
            // Iterate over 3-letter guesses
            for (int k = 0; k < len; k++)
            {
                // Generate 3rd letter
                guess3[2] = lib[k];
                guess4[2] = lib[k];
                guess5[2] = lib[k];
                
                // Run comparison function
                check_key(guess3, salt, argv[1]);
                            
                // Iterate over 4-letter guesses
                for (int l = 0; l < len; l++)
                {
                    // Generate 4th letter
                    guess4[3] = lib[l];
                    guess5[3] = lib[l];
                    
                    // Run comparison function
                    check_key(guess4, salt, argv[1]);
                    
                    // Iterate over 5-letter guesses
                    for (int m = 0; m < len; m++)
                    {
                        // Generate 5th letter
                        guess5[4] = lib[m];
                        
                        // Run comparison function
                        check_key(guess5, salt, argv[1]);
                    }
                }
            }
        }
    }
}

void check_key(string key, string salt, string hash)
{
    // Compare guessed hash with actual hash
    int match = strcmp(crypt(key, salt), hash);
    
    // Stop program if password cracked
    if (match == 0)
    {
        printf("%s\n", key);
        exit(0);
    }
}


