//
// Created by @chrys on 2/11/2021.
//

//
// updated by @roy on  2/12/2021.
//

#include <stdio.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "stringUtils.h"

/*
 * https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
 *
 */
char** str_split(char* a_str,  char a_delim)
{
    char** result    ;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            //assert(idx < count);
            if (idx < count)
            {
                *(result + idx++) = strdup(token);
                token = strtok(0, delim);
            }

        }
        //assert(idx == count - 1);
        if(idx == count - 1)
            *(result + idx) = 0;
    }

    return result;
}


/*
 * https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16993-la-saisie-de-texte-securisee
 * */
void cleanBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int readString(char *string, int length)
{
    char *enterCharacterPosition = NULL;

    if (fgets(string, length, stdin) != NULL)
    {
        enterCharacterPosition = strchr(string, '\n');
        if (enterCharacterPosition != NULL)
        {
            *enterCharacterPosition = '\0';
        }
        else
        {
            cleanBuffer();
        }
        return 1;
    }
    else
    {
        cleanBuffer();
        return 0;
    }
}

void stringToLower(char *string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        string[i] = tolower(string[i]);
        i++;
    }
}