################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../unit/DeviceInterface.cpp \
../unit/WrBalancer.cpp 

OBJS += \
./unit/DeviceInterface.o \
./unit/WrBalancer.o 

CPP_DEPS += \
./unit/DeviceInterface.d \
./unit/WrBalancer.d 


# Each subdirectory must supply rules for building sources it contributes
unit/%.o: ../unit/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\cygwin64\home\hrp2\sdk\OBJ_dummy" -I"C:\cygwin64\home\hrp2\sdk\common\ev3api\include" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


