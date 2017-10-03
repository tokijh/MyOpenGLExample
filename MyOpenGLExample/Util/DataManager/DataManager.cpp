//
//  DataManager.cpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include "DataManager.hpp"

DataManager::~DataManager()
{
    _data.clear();
}

DataManager &DataManager::getInstance()
{
    static DataManager *dataManager = NULL;
    if (dataManager == NULL) {
        dataManager = new DataManager();
    }
    return *dataManager;
}

void DataManager::destroy()
{
    AssetsManager::destroy();
    
    DataManager *dataManager = &getInstance();
    
    if (dataManager != NULL) {
        delete dataManager;
    }
}

std::string DataManager::get(std::string fileName)
{
    std::unordered_map<std::string, std::string>::const_iterator findIterator = _data.find(fileName);
    
    if (findIterator == _data.end()) {
        _data.insert(std::make_pair(fileName, AssetsManager::getInstance().readFile(fileName)));
        LOGD("%s is saved", fileName.c_str());
        findIterator = _data.find(fileName);
    }
    
    return findIterator->second;
}
