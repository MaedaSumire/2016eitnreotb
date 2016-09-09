################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../app.cpp 

C_SRCS += \
../balancer.c \
../balancer_param.c 

OBJS += \
./app.o \
./balancer.o \
./balancer_param.o 

CPP_DEPS += \
./app.d 

C_DEPS += \
./balancer.d \
./balancer_param.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\cygwin64\home\hrp2\sdk\OBJ_dummy" -I"C:\cygwin64\home\hrp2\sdk\common\ev3api\include" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"C:\cygwin64\home\hrp2\sdk\OBJ_dummy" -I"C:\cygwin64\home\hrp2\sdk\common\ev3api\include" -IC:/cygwin64/home/hrp2/sdk/common/library/libcpp-ev3/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


