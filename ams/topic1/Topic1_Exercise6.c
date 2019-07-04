#include <stdio.h>
#include <ctype.h>

void word_count()
{
    int lines = 0, words = 0, characters = 0;
    char character1, character2; // Varibles
    // for (size_t count = 0; (text = getchar()) != EOF; count++) // Loop starts
    while (character1 != EOF)
    {
        character2 = character1;
        character1 = getchar();
        if (isalpha(character1)) // Checks for letters
        {
            characters++;
        }
        if (isspace(character1))
        {
            characters++;
        }
        if ((isalpha(character1) && isspace(character2)) || (isalpha(character2) && character1 == EOF))
        {
            words++;
            // printf("\nCharacter 1: %c\nCharacter 2: %c\n", character1, character2); // Debuging code
        }
        if (iscntrl(character1) &! isspace(character2) ) // Finds line feeds
        {
            // printf("\nNew Line found\n"); // debuging code
            lines++;
        }
        if (ispunct(character2) && character1 == EOF)
        {
            characters++;
            words++;
        }
    }
    printf("Document contents: %i lines; %i words; %i characters.\n", lines, words, characters); // out put to the user of how many line, words and charcters are in the text4
}

int main()
{
    word_count();
    return 0;
}