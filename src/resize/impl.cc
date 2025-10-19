#include "impls.h"
#include <iostream>


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;

    cv::Mat img = input;

    

    // IMPLEMENT YOUR CODE HERE
    int h = input.rows, w = input.cols;
    int new_h = h * scale, new_w = w * scale;
    cv::Mat out(new_h, new_w, input.type());


    float x,y;
    int x1,y1,x2,y2;
    float r,g,b;
    for(int i=1;i<=new_h;i++){
    
        for(int j=1;j<=new_w;j++){
            
            x = j/scale;//原图坐标
            y = i/scale;
            
            x1 = static_cast<int>(x);
            y1 = static_cast<int>(y);
            
            if(x+1 <= w && y+1 <= h){
                x2 = x1+1;
                y2 = y1+1;
            }else if(x+1 <= w && y+1 > h){
                x2 = x1+1;
                y2 = y1;
            }else if(x+1 > w && y+1 <= h){
                x2 = x1;
                y2 = y1+1;
            }else{
                x2 = x1;
                y2 = y1;
            }//p1(x1,y2)  p2(x2,y2)  p3(x1,y1)  p4(x2,y1)
        


            float r_p1,g_p1,b_p1,r_p2,g_p2,b_p2,r_p3,g_p3,b_p3,r_p4,g_p4,b_p4;
            cv::Vec3b p1,p2,p3,p4;
            p1 = input.at<cv::Vec3b>(y2-1,x1-1);
            p2 = input.at<cv::Vec3b>(y2-1,x2-1);
            p3 = input.at<cv::Vec3b>(y1-1,x1-1);
            p4 = input.at<cv::Vec3b>(y1-1,x2-1);
            b_p1 = p1[0]; 
            g_p1 = p1[1];
            r_p1 = p1[2];
            b_p2 = p2[0]; 
            g_p2 = p2[1];
            r_p2 = p2[2];
            b_p3 = p3[0]; 
            g_p3 = p3[1];
            r_p3 = p3[2];
            b_p4 = p4[0]; 
            g_p4 = p4[1];
            r_p4 = p4[2];


            
            //dx = x - x1, dy = y - y1
            //Q = P1 * (1 - dx)(1 - dy) + P2 * dx(1 - dy) + P3 * (1 - dx)dy + P4 * dxdy
            float dx,dy;
            dx = x-x1;
            dy = y-y1;
            float r,g,b;
            r = r_p1 * (1-dx)*(1-dy) + r_p2 * dx*(1-dy) + r_p3 * (1-dx)*dy + r_p4 *dx*dy;
            g = g_p1 * (1-dx)*(1-dy) + g_p2 * dx*(1-dy) + g_p3 * (1-dx)*dy + g_p4 *dx*dy;
            b = b_p1 * (1-dx)*(1-dy) + b_p2 * dx*(1-dy) + b_p3 * (1-dx)*dy + b_p4 *dx*dy;
            

            out.at<cv::Vec3b>(i-1,j-1)[0] = b;
            out.at<cv::Vec3b>(i-1,j-1)[1] = g;
            out.at<cv::Vec3b>(i-1,j-1)[2] = r;
        }

    }
    // return cv::Mat::zeros(new_rows, new_cols, input.type());
    return out;
}