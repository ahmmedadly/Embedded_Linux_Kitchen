// pressure.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep()
#include "pressure.h"

#define PRESSURE_LOG_FILE "logs/pressure_log.txt"

// Function to convert hPa to Pa
int hpa_to_pa(int hpa) {
    return hpa * 100;
}
void process_pressure_log()
{
    FILE *pressure_file = fopen(PRESSURE_LOG_FILE, "r");
    if (!pressure_file)
    {
        perror("Error opening pressure log file");
        return;
    }

    char temp2_ptr[256];
    while (fgets(temp2_ptr, sizeof(temp2_ptr), pressure_file))
    {
        int pressure_hpa;
        if (sscanf(temp2_ptr, "%*s %*s - Pressure: %d hPa", &pressure_hpa) == 1)
        {
            int pressure_pa = hpa_to_pa(pressure_hpa);
            printf("Pressure: %d hPa (%d Pa)\n", pressure_hpa, pressure_pa);
            sleep(1); // Delay of 1 second between processing each line
        }
    }

    fclose(pressure_file);
}

