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
using namespace std::filesystem;

class Copier {
public:
    /**
     * @brief Copy binary file.
     * @param sourcePath path to source file
     * @param destPath path to destination file
     *
     */
    int copyBinaryFile(const path& sourcePath, const path& destPath);
    
    /**
     *@brief Copy text file.
     *@param sourcePath path to source file
     *@param destPath path to destination file
     */
    int copyTextFile(const path& sourcePath, const path& destPath);
    
    /**
     *@brief Process path to files and directory, then try to copy files in following.
     *@param sourcePath path to source file
     *@param destPath path to destination file
     *@param binary True to copy in binary mode.  False to do in text mode.
     */
    int processPathAndCopy(const path & sourcePath, const path & destPath, bool binary);
};

#endif /* copier_hpp */
