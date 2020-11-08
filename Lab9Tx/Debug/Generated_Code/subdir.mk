################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/Blue.c \
../Generated_Code/Cpu.c \
../Generated_Code/FC32.c \
../Generated_Code/Green.c \
../Generated_Code/Inhr1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/RealTimeLdd1.c \
../Generated_Code/Red.c \
../Generated_Code/TU1.c \
../Generated_Code/Term1.c 

OBJS += \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/Blue.o \
./Generated_Code/Cpu.o \
./Generated_Code/FC32.o \
./Generated_Code/Green.o \
./Generated_Code/Inhr1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/RealTimeLdd1.o \
./Generated_Code/Red.o \
./Generated_Code/TU1.o \
./Generated_Code/Term1.o 

C_DEPS += \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/Blue.d \
./Generated_Code/Cpu.d \
./Generated_Code/FC32.d \
./Generated_Code/Green.d \
./Generated_Code/Inhr1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/RealTimeLdd1.d \
./Generated_Code/Red.d \
./Generated_Code/TU1.d \
./Generated_Code/Term1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Static_Code/System" -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Static_Code/PDD" -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Sources" -I"C:/Users/Will/Desktop/Uni/Year 2/SP 2/MA1580/CC2511_Labs/Lab9Tx/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


