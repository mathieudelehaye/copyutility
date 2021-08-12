//
//  main.cpp
//  c021-file_copy
//
//  Created by Mathieu Delehaye on 08/08/2021.
//

#include <iostream>
#include "copier.hpp"

int main(int argc, const char * argv[]) {
    
    std::string sourcePath, destPath;
    
    Copier copier;
    
    if (argc != 3) {
        std::cout<<"Enter source path: ";
        std::cin >> sourcePath;
        
        std::cout<<"Enter destination path: ";
        std::cin >> destPath;
    } else {
        destPath = argv[1];
        sourcePath = argv[2];
    }
    
    return copier.processPathAndCopy(sourcePath, destPath, true);
}
