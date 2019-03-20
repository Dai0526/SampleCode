#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool validateKey(char *str)
{
    int argvLen = strlen(str);  
    // check each digits, bacause atoi is really bad for validation
    bool isValid = true;
    for (int i = 0; i < argvLen; ++i)
    {
        if ((str[i]) >= 48 && (str[i]) <= 57)
        {
            continue;
        } 
        else
        {
            return false;
        }
    } 
    return true;
}

int main(int argc, string argv[])
{
    // check argument number
    if (argc != 2)
    {
        printf("%s", "Usage: ./caesar key\n");
        return 1;
    }
    
    // validate key 
    int key = atoi(argv[1]); // 0 if it is not a inteager  
    if (key < 1 || validateKey(argv[1]) == false)
    {
        printf("%s\n", "Usage: ./caesar key");
        return 1;
    }
    
    // take user input as the plain text
    string plainText = get_string("plaintest: ");
    
    // encryption as key
    int textLen = strlen(plainText);
    
    // create an array to store the output
    char output[textLen + 1];
    output[textLen] = '\0';
    
    for (int i = 0; i < textLen; ++i)
    {
        char c = plainText[i];
        
        //Upper case
        if (c >= 65 && c <= 90)
        {
            output[i] = (char)(((c - 'A' + key) % 26) + 'A');
        }
        else if (c >= 97 && c <= 122)
        {
            output[i] = (char)(((c - 'a' + key) % 26) + 'a');
        }
        else
        {
            //printf("%s", "Not a valid string input");
            // if it is not a valid text, then keep it
            output[i] = c;
        }
    }
    
    printf("ciphertext: %s\n", output);
    return 0;
}