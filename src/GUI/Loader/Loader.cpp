#include "Loader.h"

void Loader::Update()
{
    if (IsFileDropped())
    {
        std::vector<std::string> imagePaths;
        std::string camerasPath;
        std::string points3DPath;
        std::string imagesTXTPath;
        std::string imagesFolderPath;
        std::string depthFolderPath;
        FilePathList droppedFiles = LoadDroppedFiles();

        // Reserve space for new paths
        imagePaths.reserve(imagePaths.size() + droppedFiles.count);

        // Add new paths
        for (unsigned int i = 0; i < droppedFiles.count; i++)
        {
            std::string path = droppedFiles.paths[i];
            if (path.ends_with("cameras.txt")){
                std::cout << "Found cameras.txt file " << path << std::endl;
                camerasPath = path;
            }
            else if (path.ends_with("images.txt")){
                std::cout << "Found images.txt file " << path << std::endl;
                imagesTXTPath = path;
            }
            else if (path.ends_with("points3D.txt")){
                std::cout << "Found points3D.txt file " << path << std::endl;
                points3DPath = path;
            }
            else if (path.ends_with("images")){
                std::cout << "Found images folder " << path << std::endl;
                imagesFolderPath = path;
            }
            else if (path.ends_with("depth")){
                std::cout << "Found depth folder " << path << std::endl;
                depthFolderPath = path;
            }
            else imagePaths.emplace_back(path);
        }

        UnloadDroppedFiles(droppedFiles);

        if (!imagePaths.empty()){
            dataManager.LoadImages(imagePaths);
        }
        if (!imagesFolderPath.empty()){
            dataManager.LoadImagesFolder(imagesFolderPath);
        }
        if (!depthFolderPath.empty()){
            dataManager.LoadDepthFolder(depthFolderPath);
        }
        if (!imagesTXTPath.empty()){
            dataManager.LoadImagesTXT(imagesTXTPath);
        }
        if (!camerasPath.empty()){
            dataManager.LoadCamerasTXT(camerasPath);
        }
        if (!points3DPath.empty()){
            dataManager.LoadPoints3DTXT(points3DPath);
        }
        
    }
}