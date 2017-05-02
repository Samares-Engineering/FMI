################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/debug.c \
../src/fifo.c \
../src/fmi2_api_impl.c \
../src/mutex.c \
../src/rr.c \
../src/semaphore.c \
../src/test_fmi2_um_threads.c \
../src/timer_interrupt.c \
../src/um_threads.c \
../src/user_code.c \
../src/workload.c 

OBJS += \
./src/debug.o \
./src/fifo.o \
./src/fmi2_api_impl.o \
./src/mutex.o \
./src/rr.o \
./src/semaphore.o \
./src/test_fmi2_um_threads.o \
./src/timer_interrupt.o \
./src/um_threads.o \
./src/user_code.o \
./src/workload.o 

C_DEPS += \
./src/debug.d \
./src/fifo.d \
./src/fmi2_api_impl.d \
./src/mutex.d \
./src/rr.d \
./src/semaphore.d \
./src/test_fmi2_um_threads.d \
./src/timer_interrupt.d \
./src/um_threads.d \
./src/user_code.d \
./src/workload.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


