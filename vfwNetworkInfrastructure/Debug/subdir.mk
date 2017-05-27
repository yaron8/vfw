################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CIpAddress.cpp \
../CPacketDetails.cpp \
../SIpLayer.cpp \
../main.cpp 

OBJS += \
./CIpAddress.o \
./CPacketDetails.o \
./SIpLayer.o \
./main.o 

CPP_DEPS += \
./CIpAddress.d \
./CPacketDetails.d \
./SIpLayer.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/builds/vFirewallV1/vfwInfrastructure" -O0 -g3 -Wall -c -fmessage-length=0  -std=c++14 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


