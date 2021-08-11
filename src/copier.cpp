//
//  copier.cpp
//  c021-file_copy
//
//  Created by Mathieu Delehaye on 11/08/2021.
//

#include "copier.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

int Copier::copyFile(const string & source, const string & dest) {
    
    int ret = 0;
   
    ifstream input;
   
    ofstream output;
    
    // Open files
    // Input
    if(!ret) {
        input.open(source, ios::binary | ios::in);
        
        if(!input) {
            cout<<"Source file cannot be opened: "<<source<<endl;
            ret = -2;
        }
    }
    
    // Check if output already exists
    if (!ret) {
        
        if(exists(dest)) {
            cout<<dest<<" already exists and cannot be overwritten.  Stopping."<<endl;
            ret = -3;
        }
    }
    
    // Output
    if(!ret) {
        output.open(dest, ios::binary | ios::out);
        
        if(!output) {
            cout<<"Destination file cannot be opened."<<endl;
            ret = -4;
        }
    }
    
    // Copy file
    if(!ret) {
        cout<<"Copying "<<source;
        
        const uint16_t buffSize = 100;
        char buffer[buffSize];
        
        uint32_t copiedBytes = 0;
        uint32_t totalBytesToCopy = static_cast<uint32_t>(file_size(source));
        
        while(copiedBytes < totalBytesToCopy) {
            
            uint32_t bytesToCopy = min(static_cast<uint32_t>(buffSize), totalBytesToCopy - copiedBytes);
                        
            input.read(buffer,bytesToCopy);
                    
            output.write(buffer,bytesToCopy);
            
            copiedBytes += bytesToCopy;
            
            cout<<".";
        }
        
        cout<<" Done!"<<endl;
                
        // Close files
        input.close();
        output.close();
    }
    
    return ret;
}

int Copier::processPathAndCopy(const filesystem::path & sourcePath, const filesystem::path & destPath) {
        
    int ret = 0;
            
    bool isSourceDir = false; // true if source is a directory path
    bool isDestDir = false;   // true if dest is a directory path
    
    // check paths
    if (sourcePath == destPath) {
        cout<<"Error: source and destination directories cannot be the same."<<endl;
        ret = -1;
    }
    
    if(!ret) {
        if(exists(sourcePath) && is_directory(sourcePath)) {
            isSourceDir = true;
        }
        
        if(exists(destPath)) {
            if(is_directory(destPath)) {
                isDestDir = true;
            }
        } else {
            if(isSourceDir) {
                // if source is a directory and destination does not exist, create the latter as a directory.
                create_directory(destPath);
                isDestDir = true;
            }
        }
        
        // not possible to copy a directory to a file
        if(isSourceDir && !isDestDir) {
            cout<<"Error: cannot copy directory: " << sourcePath << " to file: " << destPath << endl;
            ret = -2;
        }
    }
        
    // copy
    if(!ret) {
                
        if(isDestDir) {
            // copy to directory
            if(isSourceDir) {
                // copy all files from source directory to destination one
                path p1{sourcePath};  // path to directory
                
                for(auto const& dirEntry: directory_iterator{p1}) {
                    if (dirEntry.is_regular_file()) {
                        copyFile(dirEntry.path(), destPath / dirEntry.path().filename());
                        
                    }
                }
            } else {
                // copy file to directory
                copyFile(sourcePath, destPath / sourcePath.filename());
            }
        } else {
            // copy to file
            if (!isSourceDir) {
                // copy file
                copyFile(sourcePath, destPath);
            }
        }
    }
    
    return ret;
}
