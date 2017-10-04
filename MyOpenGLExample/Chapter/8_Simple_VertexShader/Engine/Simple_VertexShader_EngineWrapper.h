//
//  Simple_VertexShader_EngineWrapper.h
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 3..
//  Copyright © 2017년 윤중현. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Simple_VertexShader_EngineWrapper : NSObject
- (void) onCreate;
- (void) onViewWillAppear;
- (void) onViewWillDisAppear;
- (void) onChanged:(int) width : (int) height;
- (void) onUpdate: (float) deltaTime;
- (void) onDraw;
- (void) onTouch:(int) eventsCount : (int **) touchInfo;
- (void) onDestroy;
@end
