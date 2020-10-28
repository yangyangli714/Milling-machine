################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Drawshapes.c \
../Sources/Events.c \
../Sources/GUI.c \
../Sources/Motors.c \
../Sources/main.c 

OBJS += \
./Sources/Drawshapes.o \
./Sources/Events.o \
./Sources/GUI.o \
./Sources/Motors.o \
./Sources/main.o 

C_DEPS += \
./Sources/Drawshapes.d \
./Sources/Events.d \
./Sources/GUI.d \
./Sources/Motors.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/liyan/workspace.kds/Assessment_2/Static_Code/System" -I"C:/Users/liyan/workspace.kds/Assessment_2/Static_Code/PDD" -I"C:/Users/liyan/workspace.kds/Assessment_2/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/liyan/workspace.kds/Assessment_2/Sources" -I"C:/Users/liyan/workspace.kds/Assessment_2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


