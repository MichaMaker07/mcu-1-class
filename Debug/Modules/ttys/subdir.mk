################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/ttys/ttys.c 

OBJS += \
./Modules/ttys/ttys.o 

C_DEPS += \
./Modules/ttys/ttys.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/ttys/ttys.o: /home/kepler440b/STM32CubeIDE/workspace_1.10.1/mcu-1-class_diy/modules/ttys/ttys.c Modules/ttys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F446xx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/kepler440b/STM32CubeIDE/workspace_1.10.1/mcu-1-class_diy/modules/include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-ttys

clean-Modules-2f-ttys:
	-$(RM) ./Modules/ttys/ttys.d ./Modules/ttys/ttys.o ./Modules/ttys/ttys.su

.PHONY: clean-Modules-2f-ttys

