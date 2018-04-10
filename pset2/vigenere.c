#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define ERROR_MSG "Usage: ./vigenere k\n"

int main(int argc, string argv[])
{
    int l_k; // length of key
     
    // 2 command line arguments
    if (argc == 2)
    {
        l_k = strlen(argv[1]);
        
        // Check each character of 2nd command line argument for non-alphabetical character
        for (int i = 0; i < l_k; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf(ERROR_MSG);
                return 1;
            }
        }
    }
    else
    // No incorrect number of command line arguments
    {
        printf(ERROR_MSG);
        return 1;
    }
    
    // Generate numeric key from keyword
    int key[l_k];
    for (int i = 0; i < l_k; i++)
    {
        key[i] = toupper(argv[1][i]) - 'A';
    }
    
    // Get plaintext
    printf("plaintext: ");
    string plaintext = get_string();
    
    // Iterate over each character in plaintext and generate cyphertext
    int l_p = strlen(plaintext);
    char cyphertext[l_p + 1];
    cyphertext[l_p] = '\0';
    
    for (int i = 0, j = 0; i < l_p; i++)
    {
        // Check if current character is alphabetical
        if (isalpha(plaintext[i]))
        {
            // Convert to cipher letter
            int cur_char = plaintext[i] + key[j % l_k];
            j++;
            
            // Check for wrapping after 'z' or 'Z'
            if ((isupper(plaintext[i]) && !isupper(cur_char)) || (islower(plaintext[i]) && !islower(cur_char)))
                cur_char -= 26;
                
            // Append ciphered character
            cyphertext[i] = cur_char;
        }
        else
        // Append the character unchanged
        {
            cyphertext[i] = plaintext[i];
        }
    }
    
    printf("ciphertext: %s\n", cyphertext);
}