#include <vector>
#include <array>
#include <cmath>
#include "types.h"
#include "random_generators.h"

#ifndef XY_H
#define XY_H

struct ModelSettings {
    double temperature;
    int grid_size;
    double anisotropy;
    double external_field;
    double colormap_angle;
};


class XYModel {
    public:
        ModelSettings* settings;
        Grid grid;
        XYModel(ModelSettings&);
        void initialize();
        void step();
        void mc_step();
    protected:
        const static std::array<Point, 4> neighbors;
        float local_energy_diff(Point, float);
        float local_energy(Point);
        float local_energy(Point, float);
        RandomRealGenerator angle_generator;
        RandomRealGenerator prob_generator;
        RandomPointGenerator point_generator;
};


XYModel::XYModel(ModelSettings& settings)
    : settings(&settings),
      grid(settings.grid_size, std::vector<float>(settings.grid_size)),
      angle_generator(2 * M_PI),
      prob_generator(1),
      point_generator(settings.grid_size) {
    
    initialize();
}

void XYModel::initialize() {
    for (int i = 0; i < settings->grid_size; i++) {
        for (int j = 0; j < settings->grid_size; j++) {
            grid[i][j] = angle_generator.generate();
        }
    }
}

void XYModel::step() {
    for (int i = 0; i < pow(settings->grid_size, 2); i++) {
        mc_step();
    }
}

void XYModel::mc_step() {
    Point point = point_generator.generate();
    float new_angle = angle_generator.generate();
    float energy_diff = local_energy_diff(point, new_angle);
    if (energy_diff < 0 || 
        prob_generator.generate() < exp(-energy_diff / settings->temperature)) {
        grid[point.second][point.first] = new_angle;
    }
}

const std::array<Point, 4> XYModel::neighbors = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

float XYModel::local_energy_diff(Point point, float new_angle) {
    return local_energy(point, new_angle) - local_energy(point);
}

float XYModel::local_energy(Point point) {
    return local_energy(point, grid[point.second][point.first]);
}

float XYModel::local_energy(Point point, float angle) {
    float energy = settings->anisotropy * (pow(cos(angle), 2) - pow(sin(angle), 2)) + 
                  settings->external_field * sin(angle);
    int x, y;
    for (Point neighbor : neighbors) {
        x = (point.first + neighbor.first + settings->grid_size) % settings->grid_size;
        y = (point.second + neighbor.second + settings->grid_size) % settings->grid_size;
        energy -= cos(grid[y][x] - angle);
    }
    return energy;
}

#endif
