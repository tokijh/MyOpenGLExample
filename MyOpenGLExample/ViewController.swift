//
//  ViewController.swift
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 2..
//  Copyright © 2017년 윤중현. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var tableView: UITableView!
    
    let chapterList: [Chapter] = [
        Chapter(title: "Chapter1", subTitle: "HelloTriangle", storyBoardName: "HelloTriangle"),
        Chapter(title: "Chapter2", subTitle: "HelloTriangleColor", storyBoardName: "HelloTriangleColor"),
        Chapter(title: "Chapter3", subTitle: "HelloTriangleAdvanceColor", storyBoardName: "HelloTriangleAdvanceColor"),
        Chapter(title: "Chapter4", subTitle: "HelloTriangleAdvanceColor - MapBuffers", storyBoardName: "HelloTriangleAdvanceColor_MapBuffers"),
        Chapter(title: "Chapter5", subTitle: "HelloTriangleAdvanceColor - VertexArrayObjects", storyBoardName: "HelloTriangleAdvanceColor_VertexArrayObjects")
    ]
    
}

extension ViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        
        initTableView()
    }
    
    func initTableView() {
        tableView.rowHeight = UITableViewAutomaticDimension
        tableView.estimatedRowHeight = 44
    }
}

extension ViewController: UITableViewDelegate {
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        let chapter = chapterList[indexPath.row]
        let storyboard = UIStoryboard(name: chapter.storyBoardName, bundle: nil)
        guard let viewController = storyboard.instantiateInitialViewController() else {
            return
        }
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}

extension ViewController: UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return chapterList.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let chapterCell = tableView.dequeueReusableCell(withIdentifier: "ChapterCell", for: indexPath) as! ChapterTableViewCell
        chapterCell.set(chapterList[indexPath.row])
        return chapterCell
    }
}

struct Chapter {
    var title: String
    var subTitle: String
    var storyBoardName: String
}
