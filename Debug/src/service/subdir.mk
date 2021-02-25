################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/service/CrawlerJobExecutor.cpp \
../src/service/CrawlerJobManager.cpp \
../src/service/PageCrawler.cpp \
../src/service/UrlEntryQueue.cpp 

OBJS += \
./src/service/CrawlerJobExecutor.o \
./src/service/CrawlerJobManager.o \
./src/service/PageCrawler.o \
./src/service/UrlEntryQueue.o 

CPP_DEPS += \
./src/service/CrawlerJobExecutor.d \
./src/service/CrawlerJobManager.d \
./src/service/PageCrawler.d \
./src/service/UrlEntryQueue.d 


# Each subdirectory must supply rules for building sources it contributes
src/service/%.o: ../src/service/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++17 -I"C:\Users\bruno\Documents\dev\projects\workspaces\cpp\WebCrawler\src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


