#ifndef _ROS_SERVICE_LoadController_h
#define _ROS_SERVICE_LoadController_h
#include <Rosserial_STM32_Inc/ros/msg.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

namespace controller_manager_msgs
{

static const char LOADCONTROLLER[] = "controller_manager_msgs/LoadController";

  class LoadControllerRequest : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;

    LoadControllerRequest():
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return LOADCONTROLLER; };
    const char * getMD5(){ return "c1f3d28f1b044c871e6eff2e9fc3c667"; };

  };

  class LoadControllerResponse : public ros::Msg
  {
    public:
      typedef bool _ok_type;
      _ok_type ok;

    LoadControllerResponse():
      ok(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ok;
      u_ok.real = this->ok;
      *(outbuffer + offset + 0) = (u_ok.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ok);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ok;
      u_ok.base = 0;
      u_ok.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ok = u_ok.real;
      offset += sizeof(this->ok);
     return offset;
    }

    const char * getType(){ return LOADCONTROLLER; };
    const char * getMD5(){ return "6f6da3883749771fac40d6deb24a8c02"; };

  };

  class LoadController {
    public:
    typedef LoadControllerRequest Request;
    typedef LoadControllerResponse Response;
  };

}
#endif
