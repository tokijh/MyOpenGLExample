//
//  AssetsManager.mm
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#include <Foundation/Foundation.h>
#include "AssetsManager.h"

AssetsManager& AssetsManager::getInstance()
{
    static AssetsManager *assetsManager = NULL;
    
    if (assetsManager == NULL) {
        assetsManager = new AssetsManager();
    }
    
    return *assetsManager;
}

void AssetsManager::destroy()
{
    AssetsManager *assetsManager = &getInstance();
    
    if (assetsManager != NULL) {
        delete assetsManager;
    }
}

std::string AssetsManager::readFile(std::string filename)
{
    
    NSString *file = [[NSString alloc] initWithUTF8String:filename.c_str()];
    
    NSArray* list = [file componentsSeparatedByString:@"."];
    
    NSError *error = nil;
    NSString *filePath = [[NSBundle mainBundle] pathForResource:list[0] ofType:list[1]];
    NSString *result = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:&error];
    
    return [result UTF8String];
}
