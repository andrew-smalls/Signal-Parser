#include <stdio.h>  //Remove in the future
#include <string.h>
#include <stdlib.h>

#include "parser.h"

// reserve a place for '\0' in the matrix

FILE* check_file(char* filename)
{
    FILE* file = fopen(filename, "rb");
    if(file == NULL)
    {
        fclose(file);
        return NULL; 
    }
    else
        return file;
    
    
}


int check_result(STATE_MACHINE_RETURN_VALUE result, FILE* file)
{
    if(result == STATE_MACHINE_NOT_READY)
    {
        //printf("STATE_MACHINE_NOT_READY\n");
        return 1;
    }
    else if(result == STATE_MACHINE_READY_OK)
    {
        printf("Final result: STATE_MACHINE_READY_OK\n");
        fclose(file);
        return 0;
    }
    else if(result == STATE_MACHINE_READY_WITH_ERROR)
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

    return 0;
}
   

int main(int argc, char *argv[])
{
    if(argc != ARGC_LENGTH)
    {
        perror("Usage <program> <file_to_read>\n");
        perror("Helpful hand: gcc -Wall -o program main.c parser.c\n");
        exit(-1);
    }
    
    int length = strlen(argv[1]);
    
    char filename[length];
    strcpy(filename, argv[1]);
    printf("Filename: %s\n", filename);
    
    FILE* file;
    if((file = check_file(filename)) == NULL)
    {
        printf("Error when opening file\n");
        exit(-2);
    }
    else
    {
        //printf("Ready to parse!\n");
        
        char c;
        char buffer[BUFFER_LENGTH];
        uint16_t read_bytes = 0;
        
        STATE_MACHINE_RETURN_VALUE result;
        int keepReading = 1;
        
        while((read_bytes = fread(buffer, 1, BUFFER_LENGTH, file)) > 0 && keepReading == 1)
        {
            printf("Read %d bytes\n", read_bytes);
            for(int i = 0; i < read_bytes; i++)
            {
                c = buffer[i];
                //printf("At char %d (%c)\n", c, c);
                result = at_command_parse(c);
                if((keepReading = check_result(result, file)) == 0) break;
            }
        }
        
        fclose(file);
    }  
     
    
    return 0;
}
