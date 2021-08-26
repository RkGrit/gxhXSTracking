/* 
Created by li on 22/8/2021.
Modified by Gu on 24/8/2021
*/
#include "camera.h"

int UVC::getUVCTimeNums = 0;
int XSCAM::getXSTimeNums = 0;

std::shared_ptr<Camera> CameraFactory::CreateCamera(CAMERA_TYPE cam_type, std::string path) {
    switch(cam_type){
        case CAMERA_TYPE_UVC:
            return std::make_shared<UVC>(path);
            break;
        case CAMERA_TYPE_XSCAM:
            return std::make_shared<XSCAM>(path);
            break;
        default:
            std::cerr<<"camera type invalid!"<<std::endl;
    }
}

UVC::UVC(int cam) {
    cam_type_ = CAMERA_TYPE_UVC;
    fb_ = cv::VideoCapture(cam);
}

UVC::UVC(std::string path) {
    cam_type_ = CAMERA_TYPE_UVC;
    this->path_=path;
    fb_ = cv::VideoCapture(path);
    GetTimestampFromSei(path,UVC_TV);
    totalTimeNUms = UVC_TV.size();
}

bool UVC::GetImg(Ximg &img) {
    cv::Mat src;
    fb_ >> src;
    XSTime Img_time = this->UVC_TV[getUVCTimeNums];
    //img = Ximg(this,std::move(src));
    img = Ximg(this, std::move(src), Img_time,getUVCTimeNums);
    getUVCTimeNums++;
    return true;
}



XSCAM::XSCAM(std::string path) {
    cam_type_ = CAMERA_TYPE_XSCAM;
    this->path_=path;
    rtspVC = cv::VideoCapture(path);
    GetTimestampFromSei(path,XSCAM_TV);
    totalTimeNUms = XSCAM_TV.size();
}

bool XSCAM::GetImg(Ximg &img) {
    cv::Mat src;
    rtspVC >> src;
    XSTime Img_time = this->XSCAM_TV[getXSTimeNums];
    //img = Ximg(this,std::move(src));
    img = Ximg(this, std::move(src), Img_time,getXSTimeNums);
    getXSTimeNums++;
    return true;
}



