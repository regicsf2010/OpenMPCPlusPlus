################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ag/MoonSlow.cpp \
../src/ag/Population.cpp 

OBJS += \
./src/ag/MoonSlow.o \
./src/ag/Population.o 

CPP_DEPS += \
./src/ag/MoonSlow.d \
./src/ag/Population.d 


# Each subdirectory must supply rules for building sources it contributes
src/ag/%.o: ../src/ag/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-4.8 -O0 -g3 -Wall -fopenmp -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


