#ifndef _ROS_geometry_msgs_PolygonStamped_h
#define _ROS_geometry_msgs_PolygonStamped_h

#include <Rosserial_STM32_Inc/geometry_msgs/Polygon.h>
#include <Rosserial_STM32_Inc/ros/msg.h>
#include <Rosserial_STM32_Inc/std_msgs/Header.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

namespace geometry_msgs
{

  class PolygonStamped : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Polygon _polygon_type;
      _polygon_type polygon;

    PolygonStamped():
      header(),
      polygon()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->polygon.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->polygon.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "geometry_msgs/PolygonStamped"; };
    const char * getMD5(){ return "c6be8f7dc3bee7fe9e8d296070f53340"; };

  };

}
#endif
