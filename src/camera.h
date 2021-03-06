/* 
Created by li on 22/8/2021.
Modified by Gu on 24/8/2021
 */

#ifndef XSTRACKING_CAMERA_H
#define XSTRACKING_CAMERA_H
#include "common.h"

class CameraFactory{
public:
    CameraFactory()=default;
    static std::shared_ptr<Camera> CreateCamera(CAMERA_TYPE cam_type, std::string path);
};

class UVC: public Camera{
public:
    UVC(int cam);
    UVC(std::string path);
    bool GetImg(Ximg &img);

    static int getUVCTimeNums; //静态成员，记录当前推送了几帧。

protected:
    cv::VideoCapture fb_;
    std::string path_; //视频地址
    std::vector<XSTime> UVC_TV; //保存时间戳的动态数组
    int totalTimeNUms; //一共有多少帧的时间戳
    
};

class XSCAM: public Camera{
public:
    XSCAM(std::string path);
    bool GetImg(Ximg &img);

    static int getXSTimeNums; //静态成员，记录当前推送了几帧。

protected:
    cv::VideoCapture rtspVC;
    std::string path_; //视频地址
    std::vector<XSTime> XSCAM_TV; //保存时间戳的动态数组
    int totalTimeNUms; //一共有多少帧的时间戳
};




#endif //XSTRACKING_CAMERA_H
