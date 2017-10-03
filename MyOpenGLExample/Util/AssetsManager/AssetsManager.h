//
//  AssetsManager.h
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#ifndef AssetsManager_h
#define AssetsManager_h

#include <stdlib.h>
#include <string>
#include "Logger.h"

class AssetsManager {
public:
    static AssetsManager &getInstance();
    
    static void destroy();
    
    std::string readFile(std::string filename);
};

#endif /* AssetsManager_h */

