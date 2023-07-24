#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>

namespace fs = std::filesystem;

void splitData(const fs::path& dataDir, double trainPercentage) {
    if (!fs::exists(dataDir) || !fs::is_directory(dataDir)) {
        std::cerr << "Error: Data directory does not exist or is not a directory." << std::endl;
        return;
    }

    if (trainPercentage < 0.0 || trainPercentage > 1.0) {
        std::cerr << "Error: Invalid trainPercentage value. It should be between 0.0 and 1.0." << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    fs::path trainDir = dataDir / "train";
    fs::path valDir = dataDir / "val";

    fs::create_directory(trainDir);
    fs::create_directory(valDir);

    fs::path trainImagesDir = trainDir / "images";
    fs::path trainLabelsDir = trainDir / "labels";
    fs::create_directory(trainImagesDir);
    fs::create_directory(trainLabelsDir);

    fs::path valImagesDir = valDir / "images";
    fs::path valLabelsDir = valDir / "labels";
    fs::create_directory(valImagesDir);
    fs::create_directory(valLabelsDir);

    std::vector<fs::path> imageFiles;
    for (const auto& entry : fs::directory_iterator(dataDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".jpg") {
            imageFiles.push_back(entry.path());
        }
    }

    std::shuffle(imageFiles.begin(), imageFiles.end(), generator);

    size_t trainSize = static_cast<size_t>(trainPercentage * imageFiles.size());

    for (size_t i = 0; i < imageFiles.size(); ++i) {
        const fs::path& imageFile = imageFiles[i];
        const fs::path& imageName = imageFile.filename();

        fs::path txtFile = imageFile;
        txtFile.replace_extension(".txt");

        if (i < trainSize) {
            fs::copy_file(imageFile, trainImagesDir / imageName, fs::copy_options::overwrite_existing);
            if (fs::exists(txtFile))
                fs::copy_file(txtFile, trainLabelsDir / txtFile.filename(), fs::copy_options::overwrite_existing);
        } else {
            fs::copy_file(imageFile, valImagesDir / imageName, fs::copy_options::overwrite_existing);
            if (fs::exists(txtFile))
                fs::copy_file(txtFile, valLabelsDir / txtFile.filename(), fs::copy_options::overwrite_existing);
        }
    }

    // Remove the copied files
    for (const auto& imageFile : imageFiles) {
        fs::path txtFile = imageFile;
        txtFile.replace_extension(".txt");

        if (fs::exists(imageFile))
            fs::remove(imageFile);

        if (fs::exists(txtFile))
            fs::remove(txtFile);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <data_directory_path> <train_percentage>" << std::endl;
        return 1;
    }

    fs::path dataDir = argv[1];
    double trainPercentage = std::stod(argv[2]);

    splitData(dataDir, trainPercentage);

    std::cout << "Data split completed successfully." << std::endl;
    return 0;
}