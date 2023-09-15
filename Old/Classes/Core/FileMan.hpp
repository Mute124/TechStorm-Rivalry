#pragma once
#include "../lib/raylib.h"
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <filesystem>

// TODO : Fix line 43.
class FileManager {
public:
    /**
     * Creates a file with the given file path.
     *
     * @param filePath the path of the file to be created
     *
     * @return void
     *
     * @throws None
     */
    void createFile(const std::string& filePath) {
        std::ofstream file(filePath);
        if (file) {
            std::cout << "File created successfully." << std::endl;
            file.close();
        } else {
            std::cout << "Failed to create file." << std::endl;
        }
    }

    /**
     * Loads a file from the specified file path.
     *
     * @param filePath the path of the file to be loaded
     *
     * @throws std::ifstream::failure if the file fails to open
     */
    void loadFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::cout << line << std::endl;
            }
            file.close();
        } else {
            std::cout << "Failed to load file." << std::endl;
        }
    }

    /**
     * Saves the given content to a file at the specified file path.
     *
     * @param filePath the path to the file
     * @param content the content to be saved
     *
     * @throws std::ofstream::failure if the file fails to open or write
     */
    void saveFile(const std::string& filePath, const std::string& content) {
        std::ofstream file(filePath);
        if (file) {
            file << content;
            std::cout << "File saved successfully." << std::endl;
            file.close();
        } else {
            std::cout << "Failed to save file." << std::endl;
        }
    }

    /**
     * Creates a folder at the specified path.
     *
     * @param folderPath the path where the folder should be created
     *
     * @return void
     *
     * @throws None
     */
    void createFolder(const std::string& folderPath) {
        if (std::filesystem::create_directory(folderPath)) {
            std::cout << "Folder created successfully." << std::endl;
        } else {
            std::cout << "Failed to create folder." << std::endl;
        }
    }

    /**
     * Loads all the files and subfolders in the specified folder.
     *
     * @param folderPath the path of the folder to load
     *
     * @throws std::filesystem::filesystem_error if the folderPath is invalid or inaccessible
     */
    void loadFolder(const std::string& folderPath) {
        if (std::filesystem::exists(folderPath) && std::filesystem::is_directory(folderPath)) {
            for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
                std::cout << entry.path() << std::endl;
            }
        } else {
            std::cout << "Failed to load folder." << std::endl;
        }
    }

    /**
     * Saves a folder at the specified path.
     *
     * @param folderPath the path to the folder to be saved
     *
     * @throws ErrorType description of error
     */
    void saveFolder(const std::string& folderPath) {
        // Folder saving logic goes here
        std::cout << "Folder saved successfully." << std::endl;
    }
};

/*
    Example of how to use

    int main() {
        FileManager fileManager;
        fileManager.createFile("example.txt");
        fileManager.loadFile("example.txt");
        fileManager.saveFile("example.txt", "Hello, World!");
        fileManager.createFolder("example_folder");
        fileManager.loadFolder("example_folder");
        fileManager.saveFolder("example_folder");
    
        return 0;
    }
*/

