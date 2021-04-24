#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for name
    string name = get_string("What is your name?\n");
    
    // Replies to user
    printf("Hello, %s! I hope you have a great day :D\n", name);
}