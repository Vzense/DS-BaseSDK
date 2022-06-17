#ifndef VZENSEDS_API_H
#define VZENSEDS_API_H

/**
* @file VzenseDS_api.h
* @brief Vzense API header file.
* Copyright (c) 2019-2022 Vzense Interactive, Inc.
*/

/*! \mainpage VzenseDS API Documentation
*
* \section intro_sec Introduction
*
* Welcome to the VzenseDS API documentation. This documentation enables you to quickly get started in your development efforts to programmatically interact with the Vzense CW TOF Camera (eg:DS77).
*/

#include "VzenseDS77_define.h"

/**
* @brief         Initializes the API on the device. This function must be invoked before any other Vzense APIs.
* @return        ::VzRetOK if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_Initialize();

/**
* @brief         Shuts down the API on the device and clears all resources allocated by the API. After invoking this function, no other Vzense APIs can be invoked.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_Shutdown();

/**
* @brief         Gets the version of SDK.
* @return        Returns sdk version
*/
VZENSE_C_API_EXPORT const char* VZ_GetSDKVersion();

/**
* @brief         Returns the number of camera devices currently connected.
* @param[out]    pDeviceCount    Pointer to a 32-bit integer variable in which to return the device count.
* @return        ::VzRetOK       if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetDeviceCount(uint32_t* pDeviceCount);

/**
* @brief         Returns the info of the deviceIndex camera device.
* @param[in]     deviceIndex    The index of the device to open. Device indices range from 0 to device count - 1.
* @param[out]    pDevicesInfo       Pointer to a buffer in which to store the device info.
* @return        ::VzRetOK      if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetDeviceInfo(uint32_t deviceIndex, VzDeviceInfo* pDevicesInfo);

/**
* @brief         Returns the info lists of the deviceCount camera devices.
* @param[in]     deviceCount         the number of camera devices.
* @param[out]    pDevicesInfoList    Pointer to a buffer in which to store the devices list infos.
* @return        ::VzRetOK           if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetDeviceInfoList(uint32_t deviceCount, VzDeviceInfo* pDevicesInfoList);

/**
* @brief         Opens the device specified by <code>uri</code>. The device must be subsequently closed using VZ_CloseDevice().
* @param[in]     pURI         the uri of the device. See ::VzDeviceInfo for more information.
* @param[out]    pDevice     the handle of the device on which to open.
* @return:       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_OpenDeviceByUri(const char* pURI, VzDeviceHandle* pDevice);

/**
* @brief         Opens the device specified by <code>alias</code>. The device must be subsequently closed using VZ_CloseDevice().
* @param[in]     pAlias       the alias of the device. See ::VzDeviceInfo for more information.
* @param[out]    pDevice     the handle of the device on which to open.
* @return:       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_OpenDeviceByAlias(const char* pAlias, VzDeviceHandle* pDevice);

/**
* @brief         Opens the device specified by <code>uri</code>. The device must be subsequently closed using VZ_CloseDevice().
* @param[in]     pIP          the ip of the device. See ::VzDeviceInfo for more information.
* @param[out]    pDevice     the handle of the device on which to open.
* @return:       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_OpenDeviceByIP(const char* pIP, VzDeviceHandle* pDevice);

/**
* @brief         Closes the device specified by <code>device</code> that was opened using VZ_OpenDevice.
* @param[in]     pDevice       The handle of the device to close.
* @return:       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_CloseDevice(VzDeviceHandle* pDevice);

/**
* @brief         Starts capturing the image stream indicated by <code>device</code>. Invoke VZ_StopStream() to stop capturing the image stream.
* @param[in]     device          The handle of the device on which to start capturing the image stream.                        
* @return        ::VzRetOK if    the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_StartStream(VzDeviceHandle device);

/**
* @brief         Stops capturing the image stream on the device specified by <code>device</code>. that was started using VZ_StartStream.
* @param[in]     device       The handle of the device on which to stop capturing the image stream.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_StopStream(VzDeviceHandle device);

/**
* @brief         Captures the next image frame from the device specified by <code>device</code>. This API must be invoked before capturing frame data using VZ_GetFrame().
* @param[in]     device         The handle of the device on which to read the next frame.
* @param[in]     waitTime       The unit is millisecond, the value is in the range (0,65535).
*                               You can change the value according to the frame rate. For example,the frame rate is 30, so the theoretical waittime interval is 33ms, but if set the time value is 20ms,
*                               it means the max wait time is 20 ms when capturing next frame, so when call the VZ_GetFrameReady, it may return VzRetGetFrameReadyTimeOut(-11).
*                               So the recommended value is 2 * 1000/ FPS.
* @param[out]    pFrameReady    Pointer to a buffer in which to store the signal on which image is ready to be get.
* @return        ::VzRetOK      if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetFrameReady(VzDeviceHandle device, uint16_t waitTime, VzFrameReady* pFrameReady);

/**
* @brief         Returns the image data for the current frame from the device specified by <code>device</code>. Before invoking this API, invoke VZ_GetFrameReady() to capture one image frame from the device.
* @param[in]     device       The handle of the device to capture an image frame from.
* @param[in]     frameType    The image frame type.
* @param[out]    pVzFrame     Pointer to a buffer in which to store the returned image data.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetFrame(VzDeviceHandle device, VzFrameType frameType, VzFrame* pVzFrame);

/**
* @brief        Set the working mode of the camera.
* @param[in]    device      The handle of the device
* @param[in]    mode      The work mode of camera.
* @return       ::VzRetOK   if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetWorkMode(VzDeviceHandle device, VzWorkMode mode);

/**
* @brief        Get the working mode of the camera.
* @param[in]    device      The handle of the device
* @param[in]    pMode       The work mode of camera.
* @return       ::VzRetOK   if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetWorkMode(VzDeviceHandle device, VzWorkMode* pMode);

/**
* @brief        Trigger frame data once in software slave mode using invoke this API.
* @param[in]    device      The handle of the device.
* @return       ::VzRetOK   if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetSoftwareSlaveTrigger(VzDeviceHandle device);

/**
* @brief         Returns the internal intrinsic and distortion coefficient parameters from the device specified by <code>device</code>.
* @param[in]     device                        The handle of the device from which to get the internal parameters. 
* @param[in]     sensorType                    The type of sensor (depth or color) from which to get parameter information. Pass in the applicable value defined by ::VzSensorType.
* @param[out]    pSensorIntrinsicParameters    Pointer to a VzSensorIntrinsicParameters variable in which to store the parameter values.
* @return        ::PsRetOK                     if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetSensorIntrinsicParameters(VzDeviceHandle device, VzSensorType sensorType, VzSensorIntrinsicParameters* pSensorIntrinsicParameters);

/**
* @brief         Returns the camera rotation and translation coefficient parameters from the device specified by <code>device</code>.
* @param[in]     device                        The handle of the device from which to get the extrinsic parameters. 
* @param[out]    pSensorExtrinsicParameters    Pointer to a ::VzSensorExtrinsicParameters variable in which to store the parameters.
* @return        ::PsRetOK                     if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetSensorExtrinsicParameters(VzDeviceHandle device, VzSensorExtrinsicParameters* pSensorExtrinsicParameters);

/**
/**
* @brief         Gets the firmware version number.
* @param[in]     device              The handle of the device on which to set the pulse count.
* @param[in]     pFirmwareVersion    Pointer to a variable in which to store the returned fw value.
* @param[in]     length              The maximum length is 64 bytes.
* @return        ::PsRetOK          if the function succeeded, or one of the error values defined by ::PsReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetFirmwareVersion(VzDeviceHandle device, char* pFirmwareVersion, int length);

/**
* @brief         Gets the MAC from the device specified by <code>device</code>.
* @param[in]     device         The handle of the device.
* @param[out]    pMACAddress    Pointer to a buffer in which to store the device MAC address. the buffer default size is 18, and the last buffer set '\0'.
* @return        ::PsRetOK      if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetDeviceMACAddress(VzDeviceHandle device, char* pMACAddress);

/**
* @brief        Sets the device GMM gain on a device.
* @param[in]    device       The handle of the device on which to set the GMM gain.
* @param[in]    gmmgain      The GMM gain value to set. See ::VzGMMGain for more information.The GMM gain value is in the range [0,4095].
* @return       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetIRGMMGain(VzDeviceHandle device, uint8_t gmmgain);

/**
* @brief        Returns the the device's GMM gain.
* @param[in]    device       The handle of the device from which to get the GMM gain.
* @param[out]   pGmmgain      Pointer to a variable in which to store the returned GMM gain.
* @return       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetIRGMMGain(VzDeviceHandle device, uint8_t* pGmmgain);

/**
* @brief         Sets the tof frame rate.The interface takes a long time, about 500 ms.
* @param[in]     device       The handle of the device on which to set the framerate.
* @param[in]     value        The rate value, in range [1,25].
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetFrameRate(VzDeviceHandle device, uint8_t value);
/**
* @brief         Gets the tof frame rate.
* @param[in]     device       The handle of the device on which to get the framerate.
* @param[in]     pValue       The rate value.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetFrameRate(VzDeviceHandle device, uint8_t* pValue);

/**
* @brief        Set the exposure time of Tofsensor.
* @param[in]    device          The handle of the device on which to set the exposure time(ns).
* @param[in]    exposureTime    the exposure time.
* @return       ::VzRetOK       if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetToFExposureTime(VzDeviceHandle device, uint32_t exposureTime);

/**
* @brief         Get the exposure time of Tofsensor.
* @param[in]     device           The handle of the device on which to get the exposure time(ns).
* @param[out]    pExposureTime    the exposure time.
* @return        ::VzRetOK        if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetToFExposureTime(VzDeviceHandle device, uint32_t* pExposureTime);

/**
* @brief        Enables or disables the Time filter.
* @param[in]    device       The handle of the device
* @param[in]    bEnabled     Set to <code>true</code> to enable the feature or <code>false</code> to disable the feature.
* @return       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/ 
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetTimeFilterEnabled(VzDeviceHandle device, bool bEnabled);

/**
* @brief         Returns the Boolean value of whether the TimeFilter feature is enabled or disabled.
* @param[in]     device       The handle of the device
* @param[out]    pEnabled     Pointer to a variable in which to store the returned Boolean value.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetTimeFilterEnabled(VzDeviceHandle device, bool *pEnabled);

/**
* @brief         Set the parameters of the Confidence filter.
* @param[in]     device       The handle of the device
* @param[out]    params       Pointer to a variable in which to store the parameters.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetConfidenceFilterParams(VzDeviceHandle device, VzConfidenceFilterParams params);

/**
* @brief         Get the parameters of the ConfidenceFilter feature.
* @param[in]     device       The handle of the device
* @param[out]    pParams      Pointer to a variable in which to store the returned value.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetConfidenceFilterParams(VzDeviceHandle device, VzConfidenceFilterParams *pParams);

/**
* @brief        Set the parameters of the FlyingPixel filter.
* @param[in]    device       The handle of the device.
* @param[out]   params       Pointer to a variable in which to store the parameters.
* @return       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetFlyingPixelFilterParams(VzDeviceHandle device, const VzFlyingPixelFilterParams params);

/**
* @brief         Get the parameters of the Confidence filter.
* @param[in]     device       The handle of the device
* @param[out]    pParams      Pointer to a variable in which to store the returned value.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetFlyingPixelFilterParams(VzDeviceHandle device, VzFlyingPixelFilterParams* params);

/**
* @brief        Set the parameters of the FillHole filter.
* @param[in]    device       The handle of the device.
* @param[out]   params       Pointer to a variable in which to store the parameters.
* @return       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetFillHoleFilterParams(VzDeviceHandle device, const VzFillHoleFilterParams params);

/**
* @brief         Get the parameters of the FillHole filter.
* @param[in]     device       The handle of the device
* @param[out]    pParams      Pointer to a variable in which to store the returned value.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetFillHoleFilterParams(VzDeviceHandle device, VzFillHoleFilterParams* params);

/**
* @brief        Set the parameters of the Spatial filter.
* @param[in]    device       The handle of the device.
* @param[out]   params       Pointer to a variable in which to store the parameters.
* @return       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetSpatialFilterParams(VzDeviceHandle device, const VzSpatialFilterParams params);

/**
* @brief         Get the parameters of the Spatial filter.
* @param[in]     device       The handle of the device
* @param[out]    pParams      Pointer to a variable in which to store the returned value.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetSpatialFilterParams(VzDeviceHandle device, VzSpatialFilterParams* params);

/**
* @brief        Set the parameters of the Overexposure filter.
* @param[in]    device       The handle of the device.
* @param[out]   params       Pointer to a variable in which to store the parameters.
* @return       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetOverexposureFilterParams(VzDeviceHandle device, const VzOverexposureFilterParams params);

/**
* @brief         Get the parameters of the Overexposure filter.
* @param[in]     device       The handle of the device
* @param[out]    pParams      Pointer to a variable in which to store the returned value.
* @return        ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_GetOverexposureFilterParams(VzDeviceHandle device, VzOverexposureFilterParams* params);

/**
* @brief         Converts the input points from depth coordinate space to world coordinate space.
* @param[in]     device          The handle of the device on which to perform the operation.
* @param[in]     pDepthVector    Pointer to a buffer containing the x, y, and z values of the depth coordinates to be converted. \n
*                                x and y are measured in pixels, where 0, 0 is located at the top left corner of the image. \n
*                                z is measured in millimeters, based on the ::VzPixelFormat depth frame.
* @param[out]    pWorldVector    Pointer to a buffer in which to output the converted x, y, and z values of the world coordinates, measured in millimeters.
* @param[in]     pointCount      The number of points to convert.
* @param[in]     pSensorParam    The intrinsic parameters for the depth sensor. See ::VzSensorIntrinsicParameters.
* @return        ::VzRetOK       if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_ConvertDepthToPointCloud(VzDeviceHandle device, VzDepthVector3* pDepthVector, VzVector3f* pWorldVector, int32_t pointCount, VzSensorIntrinsicParameters* pSensorParam);

/**
* @brief         Converts the input Depth frame from depth coordinate space to world coordinate space on the device.
* @param[in]     device          The handle of the device on which to perform the operation.
* @param[in]     depthFrame      The depth frame.
* @param[out]    pWorldVector    Pointer to a buffer in which to output the converted x, y, and z values of the world coordinates, measured in millimeters.
* @return        ::VzRetOK       if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_ConvertDepthFrameToPointCloudVector(VzDeviceHandle device, const VzFrame& depthFrame, VzVector3f* pWorldVector);

/**
* @brief        Sets hotplug status callback function
* @param[in]    pCallback    Pointer to the callback function. See ::PtrHotPlugStatusCallback 
* @param[in]    pUserData    Pointer to the user data. See ::PtrHotPlugStatusCallback
* @return       ::VzRetOK    if the function succeeded, or one of the error values defined by ::VzReturnStatus.
*/
VZENSE_C_API_EXPORT VzReturnStatus VZ_SetHotPlugStatusCallback(PtrHotPlugStatusCallback pCallback, const void* pUserData);

#endif /* VZENSEDS_API_H */
