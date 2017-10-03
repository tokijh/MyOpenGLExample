//
//  DataManager.hpp
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <unordered_map>
#include <string>
#include "AssetsManager.h"
#include "Logger.h"

class DataManager {
private:
    
    std::unordered_map<std::string, std::string> _data;
    
    ~DataManager();
    
public:
    
    static DataManager &getInstance();
    static void destroy();
    
    std::string get(std::string fileName);
};

#endif /* DataManager_hpp */
