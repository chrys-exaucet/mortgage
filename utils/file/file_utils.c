//
// Created by Roy on 12/02/2021.
//

#include <stdio.h>
#include "file_utils.h"

int fileExists(char filename [])
{
    FILE *f = fopen(filename, "r");
    return f != NULL ? 0:-1;
}