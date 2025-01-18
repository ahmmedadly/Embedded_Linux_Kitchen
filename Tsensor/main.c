
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "pressure.h"

int main()
{
    printf("Processing temperature log file:\n");
    process_temperature_log();

    printf("\nProcessing pressure log file:\n");
    process_pressure_log();

    return 0;
}
