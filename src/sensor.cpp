#include <iostream>
#include "../include/OpenNI.h"
#include "../include/sensor.h"
#include <OpenNI.h>




bool CSensor::OnInit(bool show_color_stream) {
    openni::OpenNI::initialize();
    m_device.open(openni::ANY_DEVICE);

    if (!(m_colorStream.create(m_device, openni::SENSOR_COLOR) == openni::STATUS_OK)) {
        std::cout << openni::OpenNI::getExtendedError();
        return false;
    }
    if (!(m_colorStream.start() == openni::STATUS_OK)) {
        std::cout << openni::OpenNI::getExtendedError();
        return false;
    }

    if (!(m_depthStream.create(m_device, openni::SENSOR_COLOR) == openni::STATUS_OK)) {
        std::cout << openni::OpenNI::getExtendedError();
        return false;
    }
    if (!(m_depthStream.start() == openni::STATUS_OK)) {
        std::cout << openni::OpenNI::getExtendedError();
        return false;
    }

    if (!(m_colorStream.isValid())) {
        return false;
    }
    if (!(m_depthStream.isValid())) {
        return false;
    }

    if (m_device.isImageRegistrationModeSupported(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR)) {
        if (m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR) != openni::STATUS_OK) {
            std::cerr<<openni::OpenNI::getExtendedError();
            return false;
        }
    } else {
        std::cout<<"STREAM NO SUPPORTED"<<std::endl;
    }
    if (m_depthStream.isValid()) {
        m_device.setDepthColorSyncEnabled(false);
    }

    //active_stream = show_color_stream;
}
