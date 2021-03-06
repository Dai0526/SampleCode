#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int Shift(char c)
{
    // TODO
    return (int)(c - 'a'); 
}

int main(int argc, string argv[])
{
    // valid argc 
    if (argc != 2)
    {
        printf("%s\n", "Usage: ./vigenere keyword");
        return 1;
    }
    
    // valid argv, non numeric
    int keyLen = strlen(argv[1]);    
    char key[keyLen + 1]; // create an array, length is keylength + 1, such that it is end with '\0' character
    for(int i = 0; i < keyLen; ++i) // initizlize all values of this array with null character.
    {
        key[i] = '\0';
    }
    
    // convert to lower case, and validate
    for (int i = 0; i < keyLen; ++i)
    {       
        char temp = tolower(argv[1][i]);
        
        // if it is not word, then return error
        if(temp < 97 || temp > 122)
        {
            printf("%s\n", "Usage: ./vigenere keyword");
            return 1;
        }   
        
        key[i] = temp;               
    }
    
    // get user input for plaintext
    string plainText = get_string("plaintext: ");
    int textLen = strlen(plainText);
    
    // save answer to cupherText
    char cipherText[textLen + 1]; 
    cipherText[textLen] = '\0';
        
    // loop over the plaintext to encrypt
    int keyIdx = 0; // we need a keyIdx variable to record the progress, since in some case the key won't move.
    
    for (int i = 0; i < keyLen; ++i)
    {    
        // Split steps 
        keyIdx = keyIdx % keyLen;   // get key index by length if circular needed 
        char keyChar = key[keyIdx]; // get char from key by the index we just got
        int numShift = Shift(keyChar); // get number of shift        
        char target = plainText[i]; // get the character need to be encoded
        
        //Upper case
        if (target >= 65 && target <= 90)
        {
            cipherText[i] = (char)(((target - 'A' + numShift) % 26) + 'A');
            ++ keyIdx;
        }
        else if (target >= 97 && target <= 122) // lower case
        {
            cipherText[i] = (char)(((target - 'a' + numShift) % 26) + 'a');
            ++ keyIdx;
        }
        else // handle illegal character
        {
            cipherText[i] = target;// if it is illegal, don't do any thing and put it into our array.
        }
        
    }
   
    // print output
    printf("ciphertext: %s\n", cipherText);
    
    return 0;
    
}
