################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c 

OBJS += \
./Project_Settings/Startup_Code/startup.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Static_Code/System" -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Static_Code/PDD" -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Sources" -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


