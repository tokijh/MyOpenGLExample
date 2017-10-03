//
//  ChapterTableViewCell.swift
//  MyOpenGLExample
//
//  Created by 윤중현 on 2017. 10. 2..
//  Copyright © 2017년 윤중현. All rights reserved.
//

import UIKit

let MAX_TOUCH_COUNT: Int = 5

class ChapterTableViewCell: UITableViewCell {

    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var subTitleLabel: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        
        self.selectionStyle = .none
    }
    
    func set(_ chapter: Chapter) {
        self.titleLabel.text = chapter.title
        self.subTitleLabel.text = chapter.subTitle
    }
}
