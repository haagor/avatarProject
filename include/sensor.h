#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "OpenNI.h"

enum EActiveStream
{
    color_stream,
    depth_stream1
};

class CSensor
{
public:
    openni::Device m_device;

    openni::VideoStream m_colorStream;
    openni::VideoStream m_depthStream;
    EActiveStream active_stream;

public:
    CSensor();
    ~CSensor();
    bool OnInit(bool show_color_stream);
};

#endif
