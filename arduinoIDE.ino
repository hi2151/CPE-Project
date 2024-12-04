#include <math.h>

#define SAMPLES 128               // Number of samples (must be a power of 2)
#define SAMPLING_FREQUENCY 100    // Sampling frequency in Hz (ensure Nyquist theorem holds)
#define ALPHA_LOW 8               // Alpha band lower frequency in Hz
#define ALPHA_HIGH 13             // Alpha band upper frequency in Hz

int sensorPin = A0;
double sensorData[SAMPLES];

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Step 1: Collect samples
  for (int i = 0; i < SAMPLES; i++) {
    int rawValue = analogRead(sensorPin); // Read raw sensor value
    sensorData[i] = rawValue;

    delayMicroseconds(1000000 / SAMPLING_FREQUENCY); // Delay to maintain the sampling rate
  }

  // Step 2: Perform DFT for alpha band (8-13 Hz)
  // Calculate the frequency corresponding to the current frequency bin (k)
  for (int k = 0; k < SAMPLES / 2; k++) {
    double frequency = k * (SAMPLING_FREQUENCY / (double)SAMPLES); // Calculate frequency bin
    double realPart = 0;
    double imagPart = 0;

      // DFT calculation for each frequency
      for (int n = 0; n < SAMPLES; n++) {
        double angle = 2.0 * M_PI * k * n / SAMPLES;
        realPart += sensorData[n] * cos(angle);
        imagPart -= sensorData[n] * sin(angle);
      }

     // If the calculated frequency is within the alpha band (8-13 Hz), compute the magnitude
    if (frequency >= ALPHA_LOW && frequency <= ALPHA_HIGH) {
      double magnitude = sqrt(realPart * realPart + imagPart * imagPart) / SAMPLES;


      // Print results
      Serial.println(magnitude);
    }
  }

  delay(1000); // Delay before the next reading
}
