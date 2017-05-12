################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fmi2_api_impl.c \
../src/test_fmi2_um_threads.c 

OBJS += \
./src/fmi2_api_impl.o \
./src/test_fmi2_um_threads.o 

C_DEPS += \
./src/fmi2_api_impl.d \
./src/test_fmi2_um_threads.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DFMU_SLAVE=1 -I/home/jmgauthier/Work/git_samares/FMI/fmusdk2/fmu20/src/shared -I/home/jmgauthier/Work/git_samares/FMI/fmusdk2/fmu20/src/shared/include -I/home/jmgauthier/Work/git_samares/FMI/fmusdk2/fmu20/src/shared/parser -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


