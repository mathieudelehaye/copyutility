//
//  copier.hpp
//  c021-file_copy
//
//  Created by Mathieu Delehaye on 11/08/2021.
//

#ifndef copier_hpp
#define copier_hpp

#include <stdio.h>
#include <string>
#include <filesystem>

using namespace std;
using namespace filesystem;

class Copier {
public:
    int processPathAndCopy(const path & sourcePath, const path & destPath);
    int copyFile(const string & source, const string & dest);
};

#endif /* copier_hpp */
