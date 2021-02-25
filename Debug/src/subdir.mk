################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MockWebPortal.cpp \
../src/WebCrawlerApplication.cpp 

OBJS += \
./src/MockWebPortal.o \
./src/WebCrawlerApplication.o 

CPP_DEPS += \
./src/MockWebPortal.d \
./src/WebCrawlerApplication.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++17 -I"C:\Users\bruno\Documents\dev\projects\workspaces\cpp\WebCrawler\src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


