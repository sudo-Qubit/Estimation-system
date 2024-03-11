#include "Add_Noise.h"

#include <cmath>
//#include <fstream>

void plotCosineFunction(){
    const double duration = 10.0;   // Duration of 10 seconds
    const double sampleTime = 0.01;  // Sampling time of 0.1 seconds
    const int numSamples = static_cast<int>(duration / sampleTime); // Calculate number of samples

    std::ofstream dataFile("noisy_data.dat"); // Create a data file to store the cosine values
    
    std::ofstream csvFile("noisy_data.csv");
    csvFile << "Time , Value" << std::endl;

    // Loop over time
    for (int i = 0; i <= numSamples; ++i) {
        // Calculate time
        double time = i * sampleTime;

        // Calculate cosine value
        double cosineValue = cos(time);
        std::vector<double> cos_vect={cosineValue,cosineValue,cosineValue};
        double noisy_cos = AddNoise(cos_vect)[0];


        // Write time and cosine value to the data file
        dataFile << time << " " << noisy_cos << std::endl;
        
        // Write time and cosine value to the csv file
        csvFile << time << "," << noisy_cos << std::endl;

    }

    dataFile.close(); // Close the data file
}

int main() {
    // Call the function to plot the cosine function
    plotCosineFunction();

    // Use Gnuplot to plot the data
    system("gnuplot -persist -e \"plot 'noisy_data.dat' with lines\"");

    return 0;
}