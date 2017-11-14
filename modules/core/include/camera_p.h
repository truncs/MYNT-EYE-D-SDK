#ifndef MYNTEYE_CORE_CAMERA_P_H_
#define MYNTEYE_CORE_CAMERA_P_H_
#pragma once

#include "camera.h"

#include "eSPDI.h"

namespace mynteye {

class CameraPrivate {
public:
    CameraPrivate(Camera *q);
    /*
    CameraPrivate(const CameraPrivate &other);
    CameraPrivate(CameraPrivate &&other);
    CameraPrivate &operator=(const CameraPrivate &other);
    */
    ~CameraPrivate();

    void GetDevices(std::vector<DeviceInfo> &dev_infos);
    void GetResolutions(const std::int32_t &dev_index,
        std::vector<StreamInfo> &color_infos, std::vector<StreamInfo> &depth_infos);

    ErrorCode SetAutoExposureEnabled(bool enabled);
    ErrorCode SetAutoWhiteBalanceEnabled(bool enabled);

    ErrorCode Open(const InitParams &params);

    bool IsOpened();

    ErrorCode RetrieveImage(cv::Mat &color, cv::Mat &depth);
    //ErrorCode RetrieveImage(cv::Mat &mat, const View &view);

    void Close();

    /** q-ptr that points to the API class */
    Camera *q_ptr;

private:
    //ErrorCode RetrieveColorImage(cv::Mat &mat);
    //ErrorCode RetrieveDepthImage(cv::Mat &mat);

    void ReleaseBuf();

    void *etron_di_;

    DEVSELINFO dev_sel_info_;
    int depth_data_type_;

    PETRONDI_STREAM_INFO stream_color_info_ptr_;
    PETRONDI_STREAM_INFO stream_depth_info_ptr_;
    int color_res_index_;
    int depth_res_index_;
    DEPTH_TRANSFER_CTRL dtc_;
    int framerate_;

    std::int32_t stream_info_dev_index_;

    int color_serial_number_;
    int depth_serial_number_;
    unsigned long int color_image_size_;
    unsigned long int depth_image_size_;
    unsigned char *color_img_buf_;
    unsigned char *depth_img_buf_;
};

}  // namespace mynteye

#endif  // MYNTEYE_CORE_CAMERA_P_H_
