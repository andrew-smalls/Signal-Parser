#include <stdio.h>  //Remove in the future
#include <string.h>
#include <stdlib.h>

#include "parser.h"

FILE* check_file(char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        return NULL;
    }
    else
        return file;
}


int check_result(STATE_MACHINE_RETURN_VALUE result, FILE* file)
{
    if (result == STATE_MACHINE_NOT_READY)
    {
        //printf("STATE_MACHINE_NOT_READY\n");
        return 1;
    }
    else if (result == STATE_MACHINE_READY_OK)
    {
        printf("Final result: STATE_MACHINE_READY_OK\n");
        fclose(file);
        return 0;
    }
    else if (result == STATE_MACHINE_READY_WITH_ERROR)
    {
        printf("Final result: STATE_MACHINE_READY_WITH_ERROR\n");
        fclose(file);
        return 0;
    }
    else
    {
        printf("\n\n\nwhat\n\n\n");
        return 0;
    }
}


int main(int argc, char* argv[])
{
    printf("1\n");
    if (argc != ARGC_LENGTH)
    {
        perror("Usage <program> <file_to_read>\n");
        perror("Helpful hand: gcc -Wall -o program main.c parser.c\n");
        exit(-1);
    }
    printf("2\n");
    size_t filname_length = strlen(argv[1]);
    if (filname_length > 255)
    {
        perror("Filename too long, max length is 255 characters\n");
        exit(-1);
	}
    printf("3\n");
	char* filename = (char*)malloc(filname_length + 1); // +1 for '\0'
    printf("4\n");
    if (filename == NULL)
    {
        perror("Memory allocation failed\n");
        exit(-1);
	}

    printf("5\n");
    strcpy_s(filename, filname_length + 1, argv[1]);
    printf("6\n");
    printf("Filename: %s\n", filename);
    FILE* file;
    if ((file = check_file(filename)) == NULL)
    {
        printf("Error when opening file\n");
        exit(-2);
    }
    else
    {
        //printf("Ready to parse!\n");

        char c;
        char buffer[BUFFER_LENGTH];
        size_t read_bytes = 0;

        STATE_MACHINE_RETURN_VALUE result;
        int keepReading = 1;

        while ((read_bytes = fread(buffer, 1, BUFFER_LENGTH, file)) > 0 && keepReading == 1)
        {
            printf("Read %d bytes\n", (unsigned int) read_bytes);
            for (unsigned int i = 0; i < read_bytes; i++)
            {
                c = buffer[i];
                // printf("At char %d (%c)\n", c, c);
                result = at_command_parse(c);
                if ((keepReading = check_result(result, file)) == 0) break;
            }
        }

        fclose(file);
    }

	free(filename);
    return 0;
}