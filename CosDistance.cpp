#include "CosDistance.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

std::vector<std::vector<double>> CosDistanceCalculator::readVectorsFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open input file.");
    }

    std::vector<std::vector<double>> vectors;
    std::string line;
    std::size_t expectedSize = 0;

    while (std::getline(infile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::vector<double> vec;
        double value;

        while (ss >> value) {
            vec.push_back(value);
        }

        if (vec.size() < 2) {
            throw std::runtime_error("Each vector must have dimension at least 2.");
        }

        if (expectedSize == 0) {
            expectedSize = vec.size();
        } else if (vec.size() != expectedSize) {
            throw std::runtime_error("All vectors in the file must have the same size.");
        }

        vectors.push_back(vec);
    }

    if (vectors.size() < 2) {
        throw std::runtime_error("Need at least two vectors.");
    }

    return vectors;
}

double CosDistanceCalculator::dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::runtime_error("Vectors must have the same dimension.");
    }

    double sum = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

double CosDistanceCalculator::magnitude(const std::vector<double>& v) {
    double sum = 0.0;
    for (double x : v) {
        sum += x * x;
    }
    return std::sqrt(sum);
}

double CosDistanceCalculator::cosineSimilarity(const std::vector<double>& a, const std::vector<double>& b) {
    double magA = magnitude(a);
    double magB = magnitude(b);

    if (magA == 0.0 || magB == 0.0) {
        throw std::runtime_error("Zero vector encountered; cosine similarity is undefined.");
    }

    return dotProduct(a, b) / (magA * magB);
}

double CosDistanceCalculator::cosineDistance(const std::vector<double>& a, const std::vector<double>& b) {
    return 1.0 - cosineSimilarity(a, b);
}

std::vector<VectorPairResult> CosDistanceCalculator::computeAllPairwiseDistances(const std::vector<std::vector<double>>& vectors) {
    std::vector<VectorPairResult> results;

    for (std::size_t i = 0; i < vectors.size(); ++i) {
        for (std::size_t j = i + 1; j < vectors.size(); ++j) {
            double sim = cosineSimilarity(vectors[i], vectors[j]);
            double dist = 1.0 - sim;

            results.push_back({static_cast<int>(i), static_cast<int>(j), sim, dist});
        }
    }

    std::sort(results.begin(), results.end(), [](const VectorPairResult& a, const VectorPairResult& b) {
        return a.cosineDistance < b.cosineDistance;
    });

    return results;
}