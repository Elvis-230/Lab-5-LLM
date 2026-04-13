#include "CosDistance.h"
#include <iostream>
#include <cmath>

bool almostEqual(double a, double b, double eps = 1e-6) {
    return std::fabs(a - b) < eps;
}

int main() {
    CosDistanceCalculator calc;

    std::vector<double> v1 = {1.0, 0.0};
    std::vector<double> v2 = {1.0, 0.0};
    std::vector<double> v3 = {0.0, 1.0};
    std::vector<double> v4 = {1.0, 1.0};

    if (!almostEqual(calc.dotProduct(v1, v2), 1.0)) {
        std::cout << "dotProduct test failed\n";
        return 1;
    }

    if (!almostEqual(calc.magnitude(v4), std::sqrt(2.0))) {
        std::cout << "magnitude test failed\n";
        return 1;
    }

    if (!almostEqual(calc.cosineSimilarity(v1, v2), 1.0)) {
        std::cout << "cosineSimilarity identical vectors test failed\n";
        return 1;
    }

    if (!almostEqual(calc.cosineSimilarity(v1, v3), 0.0)) {
        std::cout << "cosineSimilarity orthogonal vectors test failed\n";
        return 1;
    }

    if (!almostEqual(calc.cosineDistance(v1, v2), 0.0)) {
        std::cout << "cosineDistance identical vectors test failed\n";
        return 1;
    }

    if (!almostEqual(calc.cosineDistance(v1, v3), 1.0)) {
        std::cout << "cosineDistance orthogonal vectors test failed\n";
        return 1;
    }

    std::vector<std::vector<double>> vectors = {
        {1.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0}
    };

    std::vector<VectorPairResult> results = calc.computeAllPairwiseDistances(vectors);

    if (results.empty()) {
        std::cout << "pairwise computation test failed\n";
        return 1;
    }

    if (!(results[0].index1 == 0 && results[0].index2 == 1 && almostEqual(results[0].cosineDistance, 0.0))) {
        std::cout << "sorting by closeness test failed\n";
        return 1;
    }

    std::cout << "All tests passed\n";
    return 0;
}