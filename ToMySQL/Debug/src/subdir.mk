################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BankAccount.cpp \
../src/BankTransaction.cpp \
../src/ToMySQL.cpp 

OBJS += \
./src/BankAccount.o \
./src/BankTransaction.o \
./src/ToMySQL.o 

CPP_DEPS += \
./src/BankAccount.d \
./src/BankTransaction.d \
./src/ToMySQL.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Program Files\MySQL\MySQL Server 5.6\include" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


