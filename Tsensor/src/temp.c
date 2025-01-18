// temp.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep()
#include "temp.h"


// Function to convert Fahrenheit to Celsius
double fahrenheit_to_celsius(double fahrenheit) {
    return (fahrenheit - 32) * 5.0 / 9.0;
}

#define TEMP_LOG_FILE "logs/temperature_log.txt"

void process_temperature_log()
{
    FILE *temp_file = fopen(TEMP_LOG_FILE, "r");
    if (!temp_file)
    {
        perror("Error opening temperature log file");
        return;
    }

    char temp1_ptr[256];
    while (fgets(temp1_ptr, sizeof(temp1_ptr), temp_file))
    {
        int temp_f;
        if (sscanf(temp1_ptr, "%*s %*s - Temperature: %d°F", &temp_f) == 1)
        {
            double temp_c = fahrenheit_to_celsius(temp_f);
            printf("Temperature: %d°F (%.2f°C)\n", temp_f, temp_c);
            sleep(1); // Delay of 1 second between processing each line
        }
    }

    fclose(temp_file);
}


