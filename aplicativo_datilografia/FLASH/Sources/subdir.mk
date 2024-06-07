################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/GPIO_latch_lcd.c" \
"../Sources/ISR.c" \
"../Sources/SIM.c" \
"../Sources/TPM.c" \
"../Sources/UART.c" \
"../Sources/main.c" \
"../Sources/pilha_LCD.c" \
"../Sources/sa_mtb.c" \
"../Sources/song.c" \
"../Sources/util.c" \

C_SRCS += \
../Sources/GPIO_latch_lcd.c \
../Sources/ISR.c \
../Sources/SIM.c \
../Sources/TPM.c \
../Sources/UART.c \
../Sources/main.c \
../Sources/pilha_LCD.c \
../Sources/sa_mtb.c \
../Sources/song.c \
../Sources/util.c \

OBJS += \
./Sources/GPIO_latch_lcd.o \
./Sources/ISR.o \
./Sources/SIM.o \
./Sources/TPM.o \
./Sources/UART.o \
./Sources/main.o \
./Sources/pilha_LCD.o \
./Sources/sa_mtb.o \
./Sources/song.o \
./Sources/util.o \

C_DEPS += \
./Sources/GPIO_latch_lcd.d \
./Sources/ISR.d \
./Sources/SIM.d \
./Sources/TPM.d \
./Sources/UART.d \
./Sources/main.d \
./Sources/pilha_LCD.d \
./Sources/sa_mtb.d \
./Sources/song.d \
./Sources/util.d \

OBJS_QUOTED += \
"./Sources/GPIO_latch_lcd.o" \
"./Sources/ISR.o" \
"./Sources/SIM.o" \
"./Sources/TPM.o" \
"./Sources/UART.o" \
"./Sources/main.o" \
"./Sources/pilha_LCD.o" \
"./Sources/sa_mtb.o" \
"./Sources/song.o" \
"./Sources/util.o" \

C_DEPS_QUOTED += \
"./Sources/GPIO_latch_lcd.d" \
"./Sources/ISR.d" \
"./Sources/SIM.d" \
"./Sources/TPM.d" \
"./Sources/UART.d" \
"./Sources/main.d" \
"./Sources/pilha_LCD.d" \
"./Sources/sa_mtb.d" \
"./Sources/song.d" \
"./Sources/util.d" \

OBJS_OS_FORMAT += \
./Sources/GPIO_latch_lcd.o \
./Sources/ISR.o \
./Sources/SIM.o \
./Sources/TPM.o \
./Sources/UART.o \
./Sources/main.o \
./Sources/pilha_LCD.o \
./Sources/sa_mtb.o \
./Sources/song.o \
./Sources/util.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/GPIO_latch_lcd.o: ../Sources/GPIO_latch_lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/GPIO_latch_lcd.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/GPIO_latch_lcd.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ISR.o: ../Sources/ISR.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ISR.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ISR.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/SIM.o: ../Sources/SIM.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/SIM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/SIM.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TPM.o: ../Sources/TPM.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TPM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TPM.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/UART.o: ../Sources/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UART.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/pilha_LCD.o: ../Sources/pilha_LCD.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/pilha_LCD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/pilha_LCD.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/song.o: ../Sources/song.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/song.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/song.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/util.o: ../Sources/util.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/util.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/util.o"
	@echo 'Finished building: $<'
	@echo ' '


