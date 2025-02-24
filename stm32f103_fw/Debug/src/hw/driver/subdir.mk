################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/driver/button.c \
../src/hw/driver/flash.c \
../src/hw/driver/led.c \
../src/hw/driver/reset.c \
../src/hw/driver/rtc.c \
../src/hw/driver/uart.c 

OBJS += \
./src/hw/driver/button.o \
./src/hw/driver/flash.o \
./src/hw/driver/led.o \
./src/hw/driver/reset.o \
./src/hw/driver/rtc.o \
./src/hw/driver/uart.o 

C_DEPS += \
./src/hw/driver/button.d \
./src/hw/driver/flash.d \
./src/hw/driver/led.d \
./src/hw/driver/reset.d \
./src/hw/driver/rtc.d \
./src/hw/driver/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/driver/%.o src/hw/driver/%.su src/hw/driver/%.cyclo: ../src/hw/driver/%.c src/hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F103xB -DUSER_VECT_TAB_ADDRESS -c -I"D:/exam_arm/stm32f103_fw/src" -I"D:/exam_arm/stm32f103_fw/src/ap" -I"D:/exam_arm/stm32f103_fw/src/bsp" -I"D:/exam_arm/stm32f103_fw/src/common" -I"D:/exam_arm/stm32f103_fw/src/common/core" -I"D:/exam_arm/stm32f103_fw/src/hw" -I"D:/exam_arm/stm32f103_fw/src/lib" -I"D:/exam_arm/stm32f103_fw/src/lib/cube_f103/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/exam_arm/stm32f103_fw/src/lib/cube_f103/Drivers/CMSIS/Include" -I"D:/exam_arm/stm32f103_fw/src/lib/cube_f103/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/exam_arm/stm32f103_fw/src/common/hw/include" -I"D:/exam_arm/stm32f103_fw/src/lib/cube_f103/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/exam_arm/stm32f103_fw/src/lib/cube_f103/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/exam_arm/stm32f103_fw/src/lib/cube_f103/USB_DEVICE/App" -I"D:/exam_arm/stm32f103_fw/src/lib/cube_f103/USB_DEVICE/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-hw-2f-driver

clean-src-2f-hw-2f-driver:
	-$(RM) ./src/hw/driver/button.cyclo ./src/hw/driver/button.d ./src/hw/driver/button.o ./src/hw/driver/button.su ./src/hw/driver/flash.cyclo ./src/hw/driver/flash.d ./src/hw/driver/flash.o ./src/hw/driver/flash.su ./src/hw/driver/led.cyclo ./src/hw/driver/led.d ./src/hw/driver/led.o ./src/hw/driver/led.su ./src/hw/driver/reset.cyclo ./src/hw/driver/reset.d ./src/hw/driver/reset.o ./src/hw/driver/reset.su ./src/hw/driver/rtc.cyclo ./src/hw/driver/rtc.d ./src/hw/driver/rtc.o ./src/hw/driver/rtc.su ./src/hw/driver/uart.cyclo ./src/hw/driver/uart.d ./src/hw/driver/uart.o ./src/hw/driver/uart.su

.PHONY: clean-src-2f-hw-2f-driver

