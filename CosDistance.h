#ifndef COS_DISTANCE_H
#define COS_DISTANCE_H

#include <vector>
#include <string>

struct VectorPairResult {
    int index1;
    int index2;
    double cosineSimilarity;
    double cosineDistance;
};

class CosDistanceCalculator {
public:
    std::vector<std::vector<double>> readVectorsFromFile(const std::string& filename);
    double dotProduct(const std::vector<double>& a, const std::vector<double>& b);
    double magnitude(const std::vector<double>& v);
    double cosineSimilarity(const std::vector<double>& a, const std::vector<double>& b);
    double cosineDistance(const std::vector<double>& a, const std::vector<double>& b);
    std::vector<VectorPairResult> computeAllPairwiseDistances(const std::vector<std::vector<double>>& vectors);
};

#endif