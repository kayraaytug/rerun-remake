#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <Eigen/Dense>

struct ImageData {
    std::string fileName;
    std::string path;
    uint32_t width, height;
    int mipmaps;
};

struct ColmapImage {
    struct Proj {
		Eigen::Vector2f p;
		uint32_t idPoint;
	};
	uint32_t ID; // ID of the image
	Eigen::Quaterniond q; // rotation
	Eigen::Vector3d t; // translation
    uint32_t idCamera; // ID of the associated camera
    std::string fileName;
    std::vector<Proj> projs;
};

struct ColmapCamera {
    uint32_t ID;                // ID of the camera
    std::string model;          // Camera model name
    uint32_t width, height;     // Camera resolution
    double f, cx, cy, k;        // Camera parameters
};

struct ColmapPoint3D {
    uint32_t ID;
    double x, y, z;
    uint16_t r, g, b;
    double error;
};