#!/bin/bash

# Log files for temperature and pressure
TEMP_LOG_FILE="temperature_log.txt"
PRESSURE_LOG_FILE="pressure_log.txt"

# Function to generate a random temperature in Fahrenheit
generate_temperature() 
{
  echo "$((RANDOM % 91 + 30))" # Generates a random temperature between 30°F and 120°F
}

# Function to generate a random pressure in psi
generate_pressure() 
{
echo "$((RANDOM % 51 + 990))" # Generates a random pressure between 990 hPa and 1040 hPa
}

# Simulate the sensor
echo "Starting temperature and pressure sensor simulation..."
echo "Logging temperature data to $TEMP_LOG_FILE"
echo "Logging pressure data to $PRESSURE_LOG_FILE"

# Loop for 50 iterations
for ((i = 1; i <= 50; i++)); do
  # Generate random temperature and pressure
  temperature=$(generate_temperature)
  pressure=$(generate_pressure)

  # Get the current timestamp
  timestamp=$(date '+%Y-%m-%d %H:%M:%S')

  # Log temperature with the timestamp
  echo "$timestamp - Temperature: ${temperature}°F" | tee -a "$TEMP_LOG_FILE"

# Log pressure with the correct unit (hPa)
echo "$timestamp - Pressure: ${pressure} hPa" | tee -a "$PRESSURE_LOG_FILE"

  # Wait for 1 second before generating the next reading
  sleep 1
done

echo "Simulation completed."
echo "Temperature data logged to $TEMP_LOG_FILE."
echo "Pressure data logged to $PRESSURE_LOG_FILE."
