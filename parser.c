#include "parser.h"

#include <stdio.h> //Remove in the future

STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t crt_char)
{
    static uint8_t state = 0;
    static uint8_t col_index = 0;
    //printf("State = %d\n", state);

    switch (state)
    {
    case 0:
    {
        // printf("Case 0\n");
        if (crt_char == '\r')
        {
            state = 1;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_NOT_READY;
        }
    }
    case 1:
    {
        //  printf("Case 1\n");
        if (crt_char == '\n')
        {
            state = 2;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 2:
    {
        // printf("Case 2\n");
        if (crt_char == 'O')
        {
            state = 3;
            return STATE_MACHINE_NOT_READY;
        }
        else if (crt_char == 'E')
        {
            state = 7;
            return STATE_MACHINE_NOT_READY;
        }
        else if (crt_char == '+')
        {
            state = 12;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 3:
    {
        // printf("Case 3\n");
        if (crt_char == 'K')
        {
            state = 4;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }

    }
    case 4:
    {
        // printf("Case 4\n");
        if (crt_char == '\r')
        {
            state = 5;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;;
        }
    }
    case 5:
    {
        //printf("Case 5\n");
        if (crt_char == '\n')
        {
            state = 6;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;;
        }
    }
    case 6:
    {
        //printf("Case 6\n");
        return STATE_MACHINE_READY_OK;
    }
    case 7:
    {
        //printf("Case 7\n");
        if (crt_char == 'R')
        {
            state = 8;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;;
        }
    }
    case 8:
    {
        //printf("Case 8\n");
        if (crt_char == 'R')
        {
            state = 9;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;;
        }
    }
    case 9:
    {
        //printf("Case 9\n");
        if (crt_char == 'O')
        {
            state = 10;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;;
        }
    }
    case 10:
    {
        //printf("Case 10\n");
        if (crt_char == 'R')
        {
            state = 11;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;;
        }
    }
    case 11:
    {
        //printf("Case 11\n");
        if (crt_char == '\r')
        {
            state = 5;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 12:
    {
        //printf("Case 12\n");
        //printf("Char passed in case 12: %d (%c)\n", crt_char, crt_char);
        if ((32 <= crt_char) && (crt_char <= 126))
        {
            state = 12;
            //if available bytes in matrix
            //    my_data.data[my_data.line_count][col_index] = crt_char;
            col_index++;
            return STATE_MACHINE_NOT_READY;
        }
        else if (crt_char == '\r')
        {
            state = 13;
            //if available bytes in matrix
            //    my_data.data[my_data.line_count][col_index] = '\0';
            col_index = 0;
            return STATE_MACHINE_NOT_READY;
        }/*
        else if(crt_char == '\n' && prev_char == '\r')
        {

            state = 12;
            if available bytes in matrix
               my_data.data[my_data.line_count][col_index] = '\0';
                col_index = 0;
            return STATE_MACHINE_NOT_READY;
        }*/
        else
        {

            return STATE_MACHINE_READY_WITH_ERROR;
        }
        //break;
    }
    case 13:
    {
        //printf("Case 13\n");
        if (crt_char == '\n')
        {
            state = 14;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;;
        }
    }
    case 14:
    {
        //printf("Case 14\n");
        if (crt_char == '\r')
        {
            state = 15;
            return STATE_MACHINE_NOT_READY;
        }
        if (crt_char == '+')
        {
            state = 12;
            //if available bytes in matrix
            my_data.line_count++;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 15:
    {
        //printf("Case 15\n");
        if (crt_char == '\n')
        {
            state = 16;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    case 16:
    {
        //printf("Case 16\n");
        if (crt_char == 'O')
        {
            state = 3;
            return STATE_MACHINE_NOT_READY;
        }
        else if (crt_char == 'E')
        {
            state = 7;
            return STATE_MACHINE_NOT_READY;
        }
        else
        {
            return STATE_MACHINE_READY_WITH_ERROR;
        }
    }
    default:
    {
        printf("Case default\n");
        return STATE_MACHINE_READY_WITH_ERROR;
    }
    }
}