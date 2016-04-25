#include <iostream>
#include "../include/OpenNI.h"
#include "../include/sensor.h"
#include <OpenNI.h>

bool CSensor::OnInit(bool show_color_stream) {
    openni::OpenNI::initialize();
    new_frame_listener = NULL;
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

    if(show_color_stream) {
        SetActiveStream(active_stream);
    };
}

bool CSensor::SetActiveStream(EActiveStream requested_stream)

{
    if (active_stream == requested_stream)
        return false;
    active_stream = requested_stream;
    if (m_device.setDepthColorSyncEnabled(active_stream == depth_stream1) !=
            openni::STATUS_OK) {
        std::cerr << "warning: unable to select color/depth sync mode" << std::endl;
        return false;
    }
    if (new_frame_listener) {
        openni::VideoStream::NewFrameListener* current_new_frame_listener =
                new_frame_listener;
        new_frame_listener = NULL;
        if (active_stream == color_stream) {
            m_depthStream.removeNewFrameListener(current_new_frame_listener);
            if (m_colorStream.addNewFrameListener(current_new_frame_listener) !=
                    openni::STATUS_OK) {
                std::cerr << openni::OpenNI::getExtendedError() << std::endl;
                return true;
            }
        }
        else {
            m_colorStream.removeNewFrameListener(current_new_frame_listener);
            if (m_depthStream.addNewFrameListener(current_new_frame_listener) !=
                    openni::STATUS_OK) {
                std::cerr << openni::OpenNI::getExtendedError() << std::endl;
                return true;
            }
        }
        new_frame_listener = current_new_frame_listener;
    }
    return true;
}
