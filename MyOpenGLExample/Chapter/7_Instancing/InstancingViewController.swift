//
//  InstancingViewController.swift
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 2..
//  Copyright © 2017년 윤중현. All rights reserved.
//

import GLKit

class InstancingViewController: GLKViewController {

    var glkView: GLKView!
    var context: EAGLContext!
    
    var engine: InstancingEngineWrapper!
    
    var timer: Timer!
    var preTime: TimeInterval = 0.0
    
    var isCreated: Bool = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        context = EAGLContext(api: .openGLES3)
        if context == nil {
            return
        }
        
        engine = InstancingEngineWrapper()
        
        initView()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        
        if self.isViewLoaded && self.view.window != nil {
            self.view = nil
            
            EAGLContext.setCurrent(self.context)
            
            engine.onDestroy()
            
            if EAGLContext.current() === self.context {
                EAGLContext.setCurrent(nil)
            }
            self.context = nil
        }
    }
    
    func initView() {
        EAGLContext.setCurrent(self.context)
        self.glkView = self.view as! GLKView!
        self.glkView.context = self.context!
        self.glkView.drawableDepthFormat = .format24
        
        self.delegate = self
    }
    
    func setEngine() {
        engine.onCreate()
        setDeviceWindow()
    }
    
    func setDeviceWindow() {
        let bounds = glkView.bounds
        let width = bounds.size.width
        let height = bounds.size.height
        engine.onChanged(Int32(width), Int32(height))
    }
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        if !isCreated {
            setEngine()
            isCreated = true
        }
        engine.onDraw()
    }
    
    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        // UIDevice.current.orientation.isLandscape // 화면 가로 세로 확인
        if engine != nil {
            setDeviceWindow()
        }
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touchEvent = UnsafeMutablePointer<UnsafeMutablePointer<Int32>?>.allocate(capacity: touches.count)
        
        var i = 0
        for touch in touches {
            let point = touch.location(in: glkView)
            let info = UnsafeMutablePointer<Int32>.allocate(capacity: 4)
            info[0] = Int32(i)
            info[1] = 0
            info[2] = Int32(point.x)
            info[3] = Int32(point.y)
            touchEvent[i] = info
            i += 1
            if MAX_TOUCH_COUNT <= i {
                break
            }
        }
        engine.onTouch(Int32(i), touchEvent)
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touchEvent = UnsafeMutablePointer<UnsafeMutablePointer<Int32>?>.allocate(capacity: touches.count)
        
        var i = 0
        for touch in touches {
            let point = touch.location(in: glkView)
            let info = UnsafeMutablePointer<Int32>.allocate(capacity: 4)
            info[0] = Int32(i)
            info[1] = 2
            info[2] = Int32(point.x)
            info[3] = Int32(point.y)
            touchEvent[i] = info
            i += 1
            if MAX_TOUCH_COUNT <= i {
                break
            }
        }
        engine.onTouch(Int32(i), touchEvent)
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        let touchEvent = UnsafeMutablePointer<UnsafeMutablePointer<Int32>?>.allocate(capacity: touches.count)
        
        var i = 0
        for touch in touches {
            let point = touch.location(in: glkView)
            let info = UnsafeMutablePointer<Int32>.allocate(capacity: 4)
            info[0] = Int32(i)
            info[1] = 1
            info[2] = Int32(point.x)
            info[3] = Int32(point.y)
            touchEvent[i] = info
            i += 1
            if MAX_TOUCH_COUNT <= i {
                break
            }
        }
        engine.onTouch(Int32(i), touchEvent)
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        engine.onViewWillAppear()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        engine.onViewWillDisAppear()
    }
    
    deinit {
        engine.onDestroy()
        
        if EAGLContext.current() === self.context {
            EAGLContext.setCurrent(nil)
        }
    }
}

extension InstancingViewController: GLKViewControllerDelegate {
    func glkViewControllerUpdate(_ controller: GLKViewController) {
        if isCreated {
            self.engine.onUpdate(Float(timeSinceLastUpdate))
        }
    }
}
