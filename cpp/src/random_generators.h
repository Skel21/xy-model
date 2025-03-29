#include <random>

#ifndef RANDOM_H
#define RANDOM_H

class RandomRealGenerator {
    public:
        RandomRealGenerator(int max) {
            gen = std::mt19937(rd());
            dis = std::uniform_real_distribution<float>(0, max);
        }
        float generate() {
            return dis(gen);
        }
    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<float> dis;
};


class RandomPointGenerator {
    public:
        RandomPointGenerator(int grid_size) {
            gen = std::mt19937(rd());
            dis = std::uniform_int_distribution<int>(0, grid_size - 1);
        }
        std::pair<int, int> generate() {
            return std::make_pair(dis(gen), dis(gen));
        }
    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<int> dis;
};

#endif
