#include "CosDistance.h"
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./cos_distance <input_file>\n";
        return 1;
    }

    try {
        CosDistanceCalculator calculator;
        std::vector<std::vector<double>> vectors = calculator.readVectorsFromFile(argv[1]);
        std::vector<VectorPairResult> results = calculator.computeAllPairwiseDistances(vectors);

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Pairs ordered by cosine closeness (closest first):\n";

        for (const auto& result : results) {
            std::cout << "Vector " << result.index1
                      << " and Vector " << result.index2
                      << " | Cosine Similarity: " << result.cosineSimilarity
                      << " | Cosine Distance: " << result.cosineDistance
                      << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}