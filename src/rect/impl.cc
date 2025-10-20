#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    std::vector<std::vector<cv::Point>> res1;

    std::vector<cv::Vec4i> hierarchy;

    // IMPLEMENT YOUR CODE HERE
    cv::Mat grey,dst;
    cv::cvtColor(input,grey,cv::COLOR_RGB2GRAY);
    cv::threshold(grey,dst,254,255,cv::THRESH_BINARY);
    cv::findContours(dst,res1,hierarchy,3, 2);
    //std::cout << res1;
    //cv::Rect r1(res1[0][0],res1[0][2]);   
    
    cv::Rect r1;
    cv::RotatedRect r2;

    for (int i=0;i<hierarchy.size();i++){
        if (res1[i].size()<5) continue;
        r2 = cv::minAreaRect(res1[i]);
        r1 = cv::boundingRect(res1[i]);
        break;
    }


    res.first = r1;
    res.second = r2;

    


    return res;
}