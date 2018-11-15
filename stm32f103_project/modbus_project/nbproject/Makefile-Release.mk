#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=arm-none-eabi-gcc
CCC=arm-none-eabi-g++
CXX=arm-none-eabi-g++
FC=gfortran
AS=arm-none-eabi-as

# Macros
CND_PLATFORM=GNU-ARM-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_cortex.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_dma.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_flash.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_flash_ex.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_gpio.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_gpio_ex.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_pwr.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_rcc.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_rcc_ex.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_tim.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_tim_ex.o \
	${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_uart.o \
	${OBJECTDIR}/_ext/511dc8f5/dma.o \
	${OBJECTDIR}/_ext/511dc8f5/gpio.o \
	${OBJECTDIR}/_ext/511dc8f5/main.o \
	${OBJECTDIR}/_ext/511dc8f5/stm32f1xx_hal_msp.o \
	${OBJECTDIR}/_ext/511dc8f5/stm32f1xx_it.o \
	${OBJECTDIR}/_ext/511dc8f5/system_stm32f1xx.o \
	${OBJECTDIR}/_ext/511dc8f5/tim.o \
	${OBJECTDIR}/_ext/511dc8f5/usart.o \
	${OBJECTDIR}/_ext/2ac0c52e/startup_stm32f103xb.o \
	${OBJECTDIR}/crc.o \
	${OBJECTDIR}/driver/Src/CRC16ANSI.o \
	${OBJECTDIR}/driver/Src/handlerModbus.o \
	${OBJECTDIR}/driver/Src/parserMODICON.o \
	${OBJECTDIR}/driver/Src/slaveMODBUStrasact.o \
	${OBJECTDIR}/transer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/modbus_project.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/modbus_project.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/modbus_project ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_cortex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_cortex.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_dma.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_dma.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_flash.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_flash.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_flash_ex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_flash_ex.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_gpio.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_gpio.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_gpio_ex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_gpio_ex.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_pwr.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_pwr.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_rcc.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_rcc.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_rcc_ex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_rcc_ex.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_tim.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_tim.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_tim_ex.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_tim_ex.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c

${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_uart.o: ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/3ee57e25
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3ee57e25/stm32f1xx_hal_uart.o ../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c

${OBJECTDIR}/_ext/511dc8f5/dma.o: ../Src/dma.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc8f5
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dc8f5/dma.o ../Src/dma.c

${OBJECTDIR}/_ext/511dc8f5/gpio.o: ../Src/gpio.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc8f5
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dc8f5/gpio.o ../Src/gpio.c

${OBJECTDIR}/_ext/511dc8f5/main.o: ../Src/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc8f5
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dc8f5/main.o ../Src/main.c

${OBJECTDIR}/_ext/511dc8f5/stm32f1xx_hal_msp.o: ../Src/stm32f1xx_hal_msp.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc8f5
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dc8f5/stm32f1xx_hal_msp.o ../Src/stm32f1xx_hal_msp.c

${OBJECTDIR}/_ext/511dc8f5/stm32f1xx_it.o: ../Src/stm32f1xx_it.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc8f5
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dc8f5/stm32f1xx_it.o ../Src/stm32f1xx_it.c

${OBJECTDIR}/_ext/511dc8f5/system_stm32f1xx.o: ../Src/system_stm32f1xx.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc8f5
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dc8f5/system_stm32f1xx.o ../Src/system_stm32f1xx.c

${OBJECTDIR}/_ext/511dc8f5/tim.o: ../Src/tim.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc8f5
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dc8f5/tim.o ../Src/tim.c

${OBJECTDIR}/_ext/511dc8f5/usart.o: ../Src/usart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc8f5
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dc8f5/usart.o ../Src/usart.c

${OBJECTDIR}/_ext/2ac0c52e/startup_stm32f103xb.o: ../startup/startup_stm32f103xb.s
	${MKDIR} -p ${OBJECTDIR}/_ext/2ac0c52e
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/_ext/2ac0c52e/startup_stm32f103xb.o ../startup/startup_stm32f103xb.s

${OBJECTDIR}/crc.o: crc.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/crc.o crc.c

${OBJECTDIR}/driver/Src/CRC16ANSI.o: driver/Src/CRC16ANSI.c
	${MKDIR} -p ${OBJECTDIR}/driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/driver/Src/CRC16ANSI.o driver/Src/CRC16ANSI.c

${OBJECTDIR}/driver/Src/handlerModbus.o: driver/Src/handlerModbus.c
	${MKDIR} -p ${OBJECTDIR}/driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/driver/Src/handlerModbus.o driver/Src/handlerModbus.c

${OBJECTDIR}/driver/Src/parserMODICON.o: driver/Src/parserMODICON.c
	${MKDIR} -p ${OBJECTDIR}/driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/driver/Src/parserMODICON.o driver/Src/parserMODICON.c

${OBJECTDIR}/driver/Src/slaveMODBUStrasact.o: driver/Src/slaveMODBUStrasact.c
	${MKDIR} -p ${OBJECTDIR}/driver/Src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/driver/Src/slaveMODBUStrasact.o driver/Src/slaveMODBUStrasact.c

${OBJECTDIR}/transer.o: transer.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/transer.o transer.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
