#include "DataManager.h"

void DataManager::LoadImages(std::vector<std::string> &paths)
{
    std::vector<std::string> filePaths = paths;
    std::sort(filePaths.begin(), filePaths.end());

    for (std::string &path : filePaths)
    {
        Image image = LoadImage(path.c_str());
        Texture2D texture = LoadTextureFromImage(image);
        ImageData imgData{getFileNameFromPath(path), path, static_cast<uint32_t>(image.width), static_cast<uint32_t>(image.height), image.mipmaps};
        textures.push_back(texture);
        images.push_back(imgData);
        UnloadImage(image);
    }
    Timeline_frameMax = textures.size() - 1;
}

void DataManager::LoadDepths(std::vector<std::string> &paths)
{
    std::vector<std::string> filePaths = paths;
    std::sort(filePaths.begin(), filePaths.end());

    for (std::string &path : filePaths)
    {
        Image image = LoadImage(path.c_str());
        Texture2D texture = LoadTextureFromImage(image);
        ImageData imgData{getFileNameFromPath(path), path, static_cast<uint32_t>(image.width), static_cast<uint32_t>(image.height), image.mipmaps};
        depthTextures.push_back(texture);
        UnloadImage(image);
    }
}

void DataManager::LoadImagesFolder(const std::string &folderPath){
    std::cout << "Enter LoadImagesFolder() with: " << folderPath << std::endl;
    std::vector<std::string> filePaths;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(folderPath)) {
        if (std::filesystem::is_regular_file(entry.path())) {
            std::cout << entry.path().string() << std::endl;
            filePaths.push_back(entry.path().string());
        }
    }
    LoadImages(filePaths);
}

void DataManager::LoadDepthFolder(const std::string &folderPath){
    std::cout << "Enter LoadDepthFolder() with: " << folderPath << std::endl;
    std::vector<std::string> filePaths;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(folderPath)) {
        if (std::filesystem::is_regular_file(entry.path())) {
            std::cout << entry.path().string() << std::endl;
            filePaths.push_back(entry.path().string());
        }
    }
    LoadDepths(filePaths);
}

bool DataManager::LoadImagesTXT(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') {
            continue;
        }

        ColmapImage image;
        std::istringstream iss(line);

        // Parse the first line of the image
        iss >> image.ID;
        double qw, qx, qy, qz;
        iss >> qw >> qx >> qy >> qz;
        image.q = Eigen::Quaterniond(qw, qx, qy, qz);

        double tx, ty, tz;
        iss >> tx >> ty >> tz;
        image.t = Eigen::Vector3d(tx, ty, tz);

        iss >> image.idCamera;
        iss >> image.fileName;

        // Parse the second line (POINTS2D)
        if (!std::getline(file, line) || line.empty()) {
            std::cerr << "Error parsing projections for image ID " << image.ID << std::endl;
            return false;
        }

        std::istringstream proj_iss(line);
        while (proj_iss) {
            float x, y;
            int pointID;
            proj_iss >> x >> y >> pointID;
            if (proj_iss.fail()) {
                break;
            }

            ColmapImage::Proj proj;
            proj.p = Eigen::Vector2f(x, y);
            proj.idPoint = pointID;
            image.projs.push_back(proj);
        }
        assert(image.idCamera > 0);
		    --image.idCamera;
            --image.ID;
        colmapImages.push_back(image);
    }
    std::sort(colmapImages.begin(), colmapImages.end(), [](const ColmapImage &a, const ColmapImage &b) {
        return a.idCamera < b.idCamera;
    });

    file.close();
    return true;
}

bool DataManager::LoadCamerasTXT(const std::string &filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        std::istringstream lineStream(line);
        ColmapCamera camera;
        lineStream >> camera.ID >> camera.model >> camera.width >> camera.height >> camera.f >> camera.cx >> camera.cy >> camera.k;
        if (camera.model != "SIMPLE_RADIAL")
        {
            std::cerr << "Error: Unsupported camera model. Only 'SIMPLE_RADIAL' is supported." << std::endl;
            return false;
        }

        if (lineStream.fail())
        {
            std::cerr << "Error: Failed to parse camera parameters." << std::endl;
            return false;
        }
        assert(camera.ID > 0);
		--camera.ID;

        cameras.push_back(camera);
    }

    return true;
}

bool DataManager::LoadPoints3DTXT(const std::string &filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        std::istringstream lineStream(line);
        ColmapPoint3D point;
        lineStream >> point.ID >> point.x >> point.y >> point.z >> point.r >> point.g >> point.b >> point.error;

        if (lineStream.fail())
        {
            std::cerr << "Error: Failed to parse points." << std::endl;
            return false;
        }
        assert(point.ID > 0);
        --point.ID;

        points3D.push_back(point);
    }

    return true;
}