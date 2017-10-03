//
//  HelloTriangleAdvanceColor_VertexArrayObjects_EngineWrapper.m
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#import "HelloTriangleAdvanceColor_VertexArrayObjects_EngineWrapper.h"
#include "HelloTriangleAdvanceColor_VertexArrayObjects_Engine.hpp"

@implementation HelloTriangleAdvanceColor_VertexArrayObjects_EngineWrapper {
    HelloTriangleAdvanceColor_VertexArrayObjects_Engine * engine;
}

-(id)init {
    self = [super init];
    engine = new HelloTriangleAdvanceColor_VertexArrayObjects_Engine();
    return self;
}

- (void)dealloc {
    delete engine;
}

- (void) onCreate {
    engine->onCreate();
}

- (void) onViewWillAppear {
    engine->onViewWillAppear();
}

- (void) onViewWillDisAppear {
    engine->onViewWillDisAppear();
}

- (void) onChanged : (int) width : (int) height {
    engine->onChanged(width, height);
}

- (void) onDraw {
    engine->onDraw();
}

- (void) onTouch : (int) eventsCount : (int **) touchInfo {
    engine->onTouch(eventsCount, touchInfo);
}

- (void) onDestroy {
    engine->onDestroy();
}

@end
