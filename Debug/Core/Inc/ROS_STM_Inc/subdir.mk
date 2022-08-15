################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/ROS_STM_Inc/duration.cpp \
../Core/Inc/ROS_STM_Inc/time.cpp 

OBJS += \
./Core/Inc/ROS_STM_Inc/duration.o \
./Core/Inc/ROS_STM_Inc/time.o 

CPP_DEPS += \
./Core/Inc/ROS_STM_Inc/duration.d \
./Core/Inc/ROS_STM_Inc/time.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/ROS_STM_Inc/%.o Core/Inc/ROS_STM_Inc/%.su: ../Core/Inc/ROS_STM_Inc/%.cpp Core/Inc/ROS_STM_Inc/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc/ROS_STM_Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-ROS_STM_Inc

clean-Core-2f-Inc-2f-ROS_STM_Inc:
	-$(RM) ./Core/Inc/ROS_STM_Inc/duration.d ./Core/Inc/ROS_STM_Inc/duration.o ./Core/Inc/ROS_STM_Inc/duration.su ./Core/Inc/ROS_STM_Inc/time.d ./Core/Inc/ROS_STM_Inc/time.o ./Core/Inc/ROS_STM_Inc/time.su

.PHONY: clean-Core-2f-Inc-2f-ROS_STM_Inc

