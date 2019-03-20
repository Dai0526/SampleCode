#include <cs50.h>
#include <stdio.h>

int main(void)
{ 
    // get user input
    int height = get_int("Height:");
    
    // check height 
    while (height < 1 || height > 8)
    {
        height = get_int("Height:");
    }
    
    // get row and col
    const int mid = height; 
        
    // paint from top to bottom, row by row
    for (int row = 0; row < height; ++row)
    {
        int base = height + 2 + row + 1;
        for (int col = 0; col < base; ++col)
        {
            
            // get left and right boundary for space
            int leftBoundary = mid - row - 1;
            int rightBoundary = mid + row + 2;
            
            if (col == mid || col == mid + 1 || col < leftBoundary || col > rightBoundary)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }      
            
        }
        printf("\n");  // new line after finish painting one row
    }
    
    return 0; 
}