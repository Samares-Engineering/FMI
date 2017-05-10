################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/simulator/debug.c \
../src/simulator/external_clock.c \
../src/simulator/fifo.c \
../src/simulator/mutex.c \
../src/simulator/rr.c \
../src/simulator/semaphore.c \
../src/simulator/timer_interrupt.c \
../src/simulator/um_threads.c \
../src/simulator/user_code.c \
../src/simulator/user_code_fmi.c \
../src/simulator/workload.c 

OBJS += \
./src/simulator/debug.o \
./src/simulator/external_clock.o \
./src/simulator/fifo.o \
./src/simulator/mutex.o \
./src/simulator/rr.o \
./src/simulator/semaphore.o \
./src/simulator/timer_interrupt.o \
./src/simulator/um_threads.o \
./src/simulator/user_code.o \
./src/simulator/user_code_fmi.o \
./src/simulator/workload.o 

C_DEPS += \
./src/simulator/debug.d \
./src/simulator/external_clock.d \
./src/simulator/fifo.d \
./src/simulator/mutex.d \
./src/simulator/rr.d \
./src/simulator/semaphore.d \
./src/simulator/timer_interrupt.d \
./src/simulator/um_threads.d \
./src/simulator/user_code.d \
./src/simulator/user_code_fmi.d \
./src/simulator/workload.d 


# Each subdirectory must supply rules for building sources it contributes
src/simulator/%.o: ../src/simulator/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/jmgauthier/Work/git_samares/FMI/fmusdk2/fmu20/src/shared -I/home/jmgauthier/Work/git_samares/FMI/fmusdk2/fmu20/src/shared/include -I/home/jmgauthier/Work/git_samares/FMI/fmusdk2/fmu20/src/shared/parser -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


