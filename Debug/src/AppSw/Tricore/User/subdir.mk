################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AppSw/Tricore/User/AD_sample.c \
../src/AppSw/Tricore/User/ANO_DT.c \
../src/AppSw/Tricore/User/Camera.c \
../src/AppSw/Tricore/User/debug.c \
../src/AppSw/Tricore/User/event.c \
../src/AppSw/Tricore/User/garage.c \
../src/AppSw/Tricore/User/motor.c \
../src/AppSw/Tricore/User/servo.c 

OBJS += \
./src/AppSw/Tricore/User/AD_sample.o \
./src/AppSw/Tricore/User/ANO_DT.o \
./src/AppSw/Tricore/User/Camera.o \
./src/AppSw/Tricore/User/debug.o \
./src/AppSw/Tricore/User/event.o \
./src/AppSw/Tricore/User/garage.o \
./src/AppSw/Tricore/User/motor.o \
./src/AppSw/Tricore/User/servo.o 

COMPILED_SRCS += \
./src/AppSw/Tricore/User/AD_sample.src \
./src/AppSw/Tricore/User/ANO_DT.src \
./src/AppSw/Tricore/User/Camera.src \
./src/AppSw/Tricore/User/debug.src \
./src/AppSw/Tricore/User/event.src \
./src/AppSw/Tricore/User/garage.src \
./src/AppSw/Tricore/User/motor.src \
./src/AppSw/Tricore/User/servo.src 

C_DEPS += \
./src/AppSw/Tricore/User/AD_sample.d \
./src/AppSw/Tricore/User/ANO_DT.d \
./src/AppSw/Tricore/User/Camera.d \
./src/AppSw/Tricore/User/debug.d \
./src/AppSw/Tricore/User/event.d \
./src/AppSw/Tricore/User/garage.d \
./src/AppSw/Tricore/User/motor.d \
./src/AppSw/Tricore/User/servo.d 


# Each subdirectory must supply rules for building sources it contributes
src/AppSw/Tricore/User/%.src: ../src/AppSw/Tricore/User/%.c src/AppSw/Tricore/User/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/ads_workspace/zwh111/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

src/AppSw/Tricore/User/%.o: ./src/AppSw/Tricore/User/%.src src/AppSw/Tricore/User/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


