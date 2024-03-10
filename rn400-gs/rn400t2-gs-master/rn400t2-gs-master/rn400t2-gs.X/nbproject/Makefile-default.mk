#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=bsp/ads1114.c bsp/eep24AA02.c bsp/flash.c bsp/i2c.c bsp/lmp91000.c bsp/max7323.c bsp/power.c bsp/rs485.c bsp/usart.c lightmodbus/master/mbcoils.c lightmodbus/master/mbregs.c lightmodbus/master/mpcoils.c lightmodbus/master/mpregs.c lightmodbus/slave/scoils.c lightmodbus/slave/sregs.c lightmodbus/lightmodbus.c lightmodbus/slave.c lightmodbus/master.c app_atcommand.c app_modbus.c app_sens_measure.c app_usb_cdc.c main.c nvm.c sensor.c system.c usb_descriptors.c usb_events.c filter.c usb/usb_device.c usb/usb_device_cdc.c usb/usb_device_generic.c util/_atof.c util/_atoi.c util/_ftoa.c util/_itoa.c util/_string.c util/buffer.c util/build_time.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/bsp/ads1114.p1 ${OBJECTDIR}/bsp/eep24AA02.p1 ${OBJECTDIR}/bsp/flash.p1 ${OBJECTDIR}/bsp/i2c.p1 ${OBJECTDIR}/bsp/lmp91000.p1 ${OBJECTDIR}/bsp/max7323.p1 ${OBJECTDIR}/bsp/power.p1 ${OBJECTDIR}/bsp/rs485.p1 ${OBJECTDIR}/bsp/usart.p1 ${OBJECTDIR}/lightmodbus/master/mbcoils.p1 ${OBJECTDIR}/lightmodbus/master/mbregs.p1 ${OBJECTDIR}/lightmodbus/master/mpcoils.p1 ${OBJECTDIR}/lightmodbus/master/mpregs.p1 ${OBJECTDIR}/lightmodbus/slave/scoils.p1 ${OBJECTDIR}/lightmodbus/slave/sregs.p1 ${OBJECTDIR}/lightmodbus/lightmodbus.p1 ${OBJECTDIR}/lightmodbus/slave.p1 ${OBJECTDIR}/lightmodbus/master.p1 ${OBJECTDIR}/app_atcommand.p1 ${OBJECTDIR}/app_modbus.p1 ${OBJECTDIR}/app_sens_measure.p1 ${OBJECTDIR}/app_usb_cdc.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/nvm.p1 ${OBJECTDIR}/sensor.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/usb_descriptors.p1 ${OBJECTDIR}/usb_events.p1 ${OBJECTDIR}/filter.p1 ${OBJECTDIR}/usb/usb_device.p1 ${OBJECTDIR}/usb/usb_device_cdc.p1 ${OBJECTDIR}/usb/usb_device_generic.p1 ${OBJECTDIR}/util/_atof.p1 ${OBJECTDIR}/util/_atoi.p1 ${OBJECTDIR}/util/_ftoa.p1 ${OBJECTDIR}/util/_itoa.p1 ${OBJECTDIR}/util/_string.p1 ${OBJECTDIR}/util/buffer.p1 ${OBJECTDIR}/util/build_time.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/bsp/ads1114.p1.d ${OBJECTDIR}/bsp/eep24AA02.p1.d ${OBJECTDIR}/bsp/flash.p1.d ${OBJECTDIR}/bsp/i2c.p1.d ${OBJECTDIR}/bsp/lmp91000.p1.d ${OBJECTDIR}/bsp/max7323.p1.d ${OBJECTDIR}/bsp/power.p1.d ${OBJECTDIR}/bsp/rs485.p1.d ${OBJECTDIR}/bsp/usart.p1.d ${OBJECTDIR}/lightmodbus/master/mbcoils.p1.d ${OBJECTDIR}/lightmodbus/master/mbregs.p1.d ${OBJECTDIR}/lightmodbus/master/mpcoils.p1.d ${OBJECTDIR}/lightmodbus/master/mpregs.p1.d ${OBJECTDIR}/lightmodbus/slave/scoils.p1.d ${OBJECTDIR}/lightmodbus/slave/sregs.p1.d ${OBJECTDIR}/lightmodbus/lightmodbus.p1.d ${OBJECTDIR}/lightmodbus/slave.p1.d ${OBJECTDIR}/lightmodbus/master.p1.d ${OBJECTDIR}/app_atcommand.p1.d ${OBJECTDIR}/app_modbus.p1.d ${OBJECTDIR}/app_sens_measure.p1.d ${OBJECTDIR}/app_usb_cdc.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/nvm.p1.d ${OBJECTDIR}/sensor.p1.d ${OBJECTDIR}/system.p1.d ${OBJECTDIR}/usb_descriptors.p1.d ${OBJECTDIR}/usb_events.p1.d ${OBJECTDIR}/filter.p1.d ${OBJECTDIR}/usb/usb_device.p1.d ${OBJECTDIR}/usb/usb_device_cdc.p1.d ${OBJECTDIR}/usb/usb_device_generic.p1.d ${OBJECTDIR}/util/_atof.p1.d ${OBJECTDIR}/util/_atoi.p1.d ${OBJECTDIR}/util/_ftoa.p1.d ${OBJECTDIR}/util/_itoa.p1.d ${OBJECTDIR}/util/_string.p1.d ${OBJECTDIR}/util/buffer.p1.d ${OBJECTDIR}/util/build_time.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/bsp/ads1114.p1 ${OBJECTDIR}/bsp/eep24AA02.p1 ${OBJECTDIR}/bsp/flash.p1 ${OBJECTDIR}/bsp/i2c.p1 ${OBJECTDIR}/bsp/lmp91000.p1 ${OBJECTDIR}/bsp/max7323.p1 ${OBJECTDIR}/bsp/power.p1 ${OBJECTDIR}/bsp/rs485.p1 ${OBJECTDIR}/bsp/usart.p1 ${OBJECTDIR}/lightmodbus/master/mbcoils.p1 ${OBJECTDIR}/lightmodbus/master/mbregs.p1 ${OBJECTDIR}/lightmodbus/master/mpcoils.p1 ${OBJECTDIR}/lightmodbus/master/mpregs.p1 ${OBJECTDIR}/lightmodbus/slave/scoils.p1 ${OBJECTDIR}/lightmodbus/slave/sregs.p1 ${OBJECTDIR}/lightmodbus/lightmodbus.p1 ${OBJECTDIR}/lightmodbus/slave.p1 ${OBJECTDIR}/lightmodbus/master.p1 ${OBJECTDIR}/app_atcommand.p1 ${OBJECTDIR}/app_modbus.p1 ${OBJECTDIR}/app_sens_measure.p1 ${OBJECTDIR}/app_usb_cdc.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/nvm.p1 ${OBJECTDIR}/sensor.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/usb_descriptors.p1 ${OBJECTDIR}/usb_events.p1 ${OBJECTDIR}/filter.p1 ${OBJECTDIR}/usb/usb_device.p1 ${OBJECTDIR}/usb/usb_device_cdc.p1 ${OBJECTDIR}/usb/usb_device_generic.p1 ${OBJECTDIR}/util/_atof.p1 ${OBJECTDIR}/util/_atoi.p1 ${OBJECTDIR}/util/_ftoa.p1 ${OBJECTDIR}/util/_itoa.p1 ${OBJECTDIR}/util/_string.p1 ${OBJECTDIR}/util/buffer.p1 ${OBJECTDIR}/util/build_time.p1

# Source Files
SOURCEFILES=bsp/ads1114.c bsp/eep24AA02.c bsp/flash.c bsp/i2c.c bsp/lmp91000.c bsp/max7323.c bsp/power.c bsp/rs485.c bsp/usart.c lightmodbus/master/mbcoils.c lightmodbus/master/mbregs.c lightmodbus/master/mpcoils.c lightmodbus/master/mpregs.c lightmodbus/slave/scoils.c lightmodbus/slave/sregs.c lightmodbus/lightmodbus.c lightmodbus/slave.c lightmodbus/master.c app_atcommand.c app_modbus.c app_sens_measure.c app_usb_cdc.c main.c nvm.c sensor.c system.c usb_descriptors.c usb_events.c filter.c usb/usb_device.c usb/usb_device_cdc.c usb/usb_device_generic.c util/_atof.c util/_atoi.c util/_ftoa.c util/_itoa.c util/_string.c util/buffer.c util/build_time.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F26J50
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/bsp/ads1114.p1: bsp/ads1114.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/ads1114.p1.d 
	@${RM} ${OBJECTDIR}/bsp/ads1114.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/ads1114.p1 bsp/ads1114.c 
	@-${MV} ${OBJECTDIR}/bsp/ads1114.d ${OBJECTDIR}/bsp/ads1114.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/ads1114.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/eep24AA02.p1: bsp/eep24AA02.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/eep24AA02.p1.d 
	@${RM} ${OBJECTDIR}/bsp/eep24AA02.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/eep24AA02.p1 bsp/eep24AA02.c 
	@-${MV} ${OBJECTDIR}/bsp/eep24AA02.d ${OBJECTDIR}/bsp/eep24AA02.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/eep24AA02.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/flash.p1: bsp/flash.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/flash.p1.d 
	@${RM} ${OBJECTDIR}/bsp/flash.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/flash.p1 bsp/flash.c 
	@-${MV} ${OBJECTDIR}/bsp/flash.d ${OBJECTDIR}/bsp/flash.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/flash.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/i2c.p1: bsp/i2c.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/i2c.p1.d 
	@${RM} ${OBJECTDIR}/bsp/i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/i2c.p1 bsp/i2c.c 
	@-${MV} ${OBJECTDIR}/bsp/i2c.d ${OBJECTDIR}/bsp/i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/lmp91000.p1: bsp/lmp91000.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/lmp91000.p1.d 
	@${RM} ${OBJECTDIR}/bsp/lmp91000.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/lmp91000.p1 bsp/lmp91000.c 
	@-${MV} ${OBJECTDIR}/bsp/lmp91000.d ${OBJECTDIR}/bsp/lmp91000.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/lmp91000.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/max7323.p1: bsp/max7323.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/max7323.p1.d 
	@${RM} ${OBJECTDIR}/bsp/max7323.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/max7323.p1 bsp/max7323.c 
	@-${MV} ${OBJECTDIR}/bsp/max7323.d ${OBJECTDIR}/bsp/max7323.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/max7323.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/power.p1: bsp/power.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/power.p1.d 
	@${RM} ${OBJECTDIR}/bsp/power.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/power.p1 bsp/power.c 
	@-${MV} ${OBJECTDIR}/bsp/power.d ${OBJECTDIR}/bsp/power.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/power.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/rs485.p1: bsp/rs485.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/rs485.p1.d 
	@${RM} ${OBJECTDIR}/bsp/rs485.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/rs485.p1 bsp/rs485.c 
	@-${MV} ${OBJECTDIR}/bsp/rs485.d ${OBJECTDIR}/bsp/rs485.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/rs485.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/usart.p1: bsp/usart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/usart.p1.d 
	@${RM} ${OBJECTDIR}/bsp/usart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/usart.p1 bsp/usart.c 
	@-${MV} ${OBJECTDIR}/bsp/usart.d ${OBJECTDIR}/bsp/usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master/mbcoils.p1: lightmodbus/master/mbcoils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/master" 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mbcoils.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mbcoils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master/mbcoils.p1 lightmodbus/master/mbcoils.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master/mbcoils.d ${OBJECTDIR}/lightmodbus/master/mbcoils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master/mbcoils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master/mbregs.p1: lightmodbus/master/mbregs.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/master" 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mbregs.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mbregs.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master/mbregs.p1 lightmodbus/master/mbregs.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master/mbregs.d ${OBJECTDIR}/lightmodbus/master/mbregs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master/mbregs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master/mpcoils.p1: lightmodbus/master/mpcoils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/master" 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mpcoils.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mpcoils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master/mpcoils.p1 lightmodbus/master/mpcoils.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master/mpcoils.d ${OBJECTDIR}/lightmodbus/master/mpcoils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master/mpcoils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master/mpregs.p1: lightmodbus/master/mpregs.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/master" 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mpregs.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mpregs.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master/mpregs.p1 lightmodbus/master/mpregs.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master/mpregs.d ${OBJECTDIR}/lightmodbus/master/mpregs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master/mpregs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/slave/scoils.p1: lightmodbus/slave/scoils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/slave" 
	@${RM} ${OBJECTDIR}/lightmodbus/slave/scoils.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/slave/scoils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/slave/scoils.p1 lightmodbus/slave/scoils.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/slave/scoils.d ${OBJECTDIR}/lightmodbus/slave/scoils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/slave/scoils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/slave/sregs.p1: lightmodbus/slave/sregs.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/slave" 
	@${RM} ${OBJECTDIR}/lightmodbus/slave/sregs.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/slave/sregs.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/slave/sregs.p1 lightmodbus/slave/sregs.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/slave/sregs.d ${OBJECTDIR}/lightmodbus/slave/sregs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/slave/sregs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/lightmodbus.p1: lightmodbus/lightmodbus.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus" 
	@${RM} ${OBJECTDIR}/lightmodbus/lightmodbus.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/lightmodbus.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/lightmodbus.p1 lightmodbus/lightmodbus.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/lightmodbus.d ${OBJECTDIR}/lightmodbus/lightmodbus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/lightmodbus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/slave.p1: lightmodbus/slave.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus" 
	@${RM} ${OBJECTDIR}/lightmodbus/slave.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/slave.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/slave.p1 lightmodbus/slave.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/slave.d ${OBJECTDIR}/lightmodbus/slave.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/slave.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master.p1: lightmodbus/master.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus" 
	@${RM} ${OBJECTDIR}/lightmodbus/master.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master.p1 lightmodbus/master.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master.d ${OBJECTDIR}/lightmodbus/master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/app_atcommand.p1: app_atcommand.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_atcommand.p1.d 
	@${RM} ${OBJECTDIR}/app_atcommand.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/app_atcommand.p1 app_atcommand.c 
	@-${MV} ${OBJECTDIR}/app_atcommand.d ${OBJECTDIR}/app_atcommand.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/app_atcommand.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/app_modbus.p1: app_modbus.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_modbus.p1.d 
	@${RM} ${OBJECTDIR}/app_modbus.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/app_modbus.p1 app_modbus.c 
	@-${MV} ${OBJECTDIR}/app_modbus.d ${OBJECTDIR}/app_modbus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/app_modbus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/app_sens_measure.p1: app_sens_measure.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_sens_measure.p1.d 
	@${RM} ${OBJECTDIR}/app_sens_measure.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/app_sens_measure.p1 app_sens_measure.c 
	@-${MV} ${OBJECTDIR}/app_sens_measure.d ${OBJECTDIR}/app_sens_measure.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/app_sens_measure.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/app_usb_cdc.p1: app_usb_cdc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_usb_cdc.p1.d 
	@${RM} ${OBJECTDIR}/app_usb_cdc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/app_usb_cdc.p1 app_usb_cdc.c 
	@-${MV} ${OBJECTDIR}/app_usb_cdc.d ${OBJECTDIR}/app_usb_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/app_usb_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nvm.p1: nvm.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/nvm.p1.d 
	@${RM} ${OBJECTDIR}/nvm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/nvm.p1 nvm.c 
	@-${MV} ${OBJECTDIR}/nvm.d ${OBJECTDIR}/nvm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nvm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sensor.p1: sensor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensor.p1.d 
	@${RM} ${OBJECTDIR}/sensor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sensor.p1 sensor.c 
	@-${MV} ${OBJECTDIR}/sensor.d ${OBJECTDIR}/sensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/system.p1 system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb_descriptors.p1: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb_descriptors.p1 usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/usb_descriptors.d ${OBJECTDIR}/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb_events.p1: usb_events.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_events.p1.d 
	@${RM} ${OBJECTDIR}/usb_events.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb_events.p1 usb_events.c 
	@-${MV} ${OBJECTDIR}/usb_events.d ${OBJECTDIR}/usb_events.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb_events.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/filter.p1: filter.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/filter.p1.d 
	@${RM} ${OBJECTDIR}/filter.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/filter.p1 filter.c 
	@-${MV} ${OBJECTDIR}/filter.d ${OBJECTDIR}/filter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/filter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device.p1: usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device.p1 usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device.d ${OBJECTDIR}/usb/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device_cdc.p1: usb/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device_cdc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device_cdc.p1 usb/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device_cdc.d ${OBJECTDIR}/usb/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device_generic.p1: usb/usb_device_generic.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device_generic.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device_generic.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device_generic.p1 usb/usb_device_generic.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device_generic.d ${OBJECTDIR}/usb/usb_device_generic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device_generic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_atof.p1: util/_atof.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_atof.p1.d 
	@${RM} ${OBJECTDIR}/util/_atof.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_atof.p1 util/_atof.c 
	@-${MV} ${OBJECTDIR}/util/_atof.d ${OBJECTDIR}/util/_atof.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_atof.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_atoi.p1: util/_atoi.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_atoi.p1.d 
	@${RM} ${OBJECTDIR}/util/_atoi.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_atoi.p1 util/_atoi.c 
	@-${MV} ${OBJECTDIR}/util/_atoi.d ${OBJECTDIR}/util/_atoi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_atoi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_ftoa.p1: util/_ftoa.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_ftoa.p1.d 
	@${RM} ${OBJECTDIR}/util/_ftoa.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_ftoa.p1 util/_ftoa.c 
	@-${MV} ${OBJECTDIR}/util/_ftoa.d ${OBJECTDIR}/util/_ftoa.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_ftoa.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_itoa.p1: util/_itoa.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_itoa.p1.d 
	@${RM} ${OBJECTDIR}/util/_itoa.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_itoa.p1 util/_itoa.c 
	@-${MV} ${OBJECTDIR}/util/_itoa.d ${OBJECTDIR}/util/_itoa.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_itoa.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_string.p1: util/_string.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_string.p1.d 
	@${RM} ${OBJECTDIR}/util/_string.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_string.p1 util/_string.c 
	@-${MV} ${OBJECTDIR}/util/_string.d ${OBJECTDIR}/util/_string.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_string.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/buffer.p1: util/buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/buffer.p1.d 
	@${RM} ${OBJECTDIR}/util/buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/buffer.p1 util/buffer.c 
	@-${MV} ${OBJECTDIR}/util/buffer.d ${OBJECTDIR}/util/buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/build_time.p1: util/build_time.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/build_time.p1.d 
	@${RM} ${OBJECTDIR}/util/build_time.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/build_time.p1 util/build_time.c 
	@-${MV} ${OBJECTDIR}/util/build_time.d ${OBJECTDIR}/util/build_time.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/build_time.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/bsp/ads1114.p1: bsp/ads1114.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/ads1114.p1.d 
	@${RM} ${OBJECTDIR}/bsp/ads1114.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/ads1114.p1 bsp/ads1114.c 
	@-${MV} ${OBJECTDIR}/bsp/ads1114.d ${OBJECTDIR}/bsp/ads1114.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/ads1114.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/eep24AA02.p1: bsp/eep24AA02.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/eep24AA02.p1.d 
	@${RM} ${OBJECTDIR}/bsp/eep24AA02.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/eep24AA02.p1 bsp/eep24AA02.c 
	@-${MV} ${OBJECTDIR}/bsp/eep24AA02.d ${OBJECTDIR}/bsp/eep24AA02.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/eep24AA02.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/flash.p1: bsp/flash.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/flash.p1.d 
	@${RM} ${OBJECTDIR}/bsp/flash.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/flash.p1 bsp/flash.c 
	@-${MV} ${OBJECTDIR}/bsp/flash.d ${OBJECTDIR}/bsp/flash.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/flash.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/i2c.p1: bsp/i2c.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/i2c.p1.d 
	@${RM} ${OBJECTDIR}/bsp/i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/i2c.p1 bsp/i2c.c 
	@-${MV} ${OBJECTDIR}/bsp/i2c.d ${OBJECTDIR}/bsp/i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/lmp91000.p1: bsp/lmp91000.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/lmp91000.p1.d 
	@${RM} ${OBJECTDIR}/bsp/lmp91000.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/lmp91000.p1 bsp/lmp91000.c 
	@-${MV} ${OBJECTDIR}/bsp/lmp91000.d ${OBJECTDIR}/bsp/lmp91000.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/lmp91000.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/max7323.p1: bsp/max7323.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/max7323.p1.d 
	@${RM} ${OBJECTDIR}/bsp/max7323.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/max7323.p1 bsp/max7323.c 
	@-${MV} ${OBJECTDIR}/bsp/max7323.d ${OBJECTDIR}/bsp/max7323.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/max7323.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/power.p1: bsp/power.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/power.p1.d 
	@${RM} ${OBJECTDIR}/bsp/power.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/power.p1 bsp/power.c 
	@-${MV} ${OBJECTDIR}/bsp/power.d ${OBJECTDIR}/bsp/power.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/power.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/rs485.p1: bsp/rs485.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/rs485.p1.d 
	@${RM} ${OBJECTDIR}/bsp/rs485.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/rs485.p1 bsp/rs485.c 
	@-${MV} ${OBJECTDIR}/bsp/rs485.d ${OBJECTDIR}/bsp/rs485.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/rs485.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/bsp/usart.p1: bsp/usart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/bsp" 
	@${RM} ${OBJECTDIR}/bsp/usart.p1.d 
	@${RM} ${OBJECTDIR}/bsp/usart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/bsp/usart.p1 bsp/usart.c 
	@-${MV} ${OBJECTDIR}/bsp/usart.d ${OBJECTDIR}/bsp/usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/bsp/usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master/mbcoils.p1: lightmodbus/master/mbcoils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/master" 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mbcoils.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mbcoils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master/mbcoils.p1 lightmodbus/master/mbcoils.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master/mbcoils.d ${OBJECTDIR}/lightmodbus/master/mbcoils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master/mbcoils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master/mbregs.p1: lightmodbus/master/mbregs.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/master" 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mbregs.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mbregs.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master/mbregs.p1 lightmodbus/master/mbregs.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master/mbregs.d ${OBJECTDIR}/lightmodbus/master/mbregs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master/mbregs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master/mpcoils.p1: lightmodbus/master/mpcoils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/master" 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mpcoils.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mpcoils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master/mpcoils.p1 lightmodbus/master/mpcoils.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master/mpcoils.d ${OBJECTDIR}/lightmodbus/master/mpcoils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master/mpcoils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master/mpregs.p1: lightmodbus/master/mpregs.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/master" 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mpregs.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master/mpregs.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master/mpregs.p1 lightmodbus/master/mpregs.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master/mpregs.d ${OBJECTDIR}/lightmodbus/master/mpregs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master/mpregs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/slave/scoils.p1: lightmodbus/slave/scoils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/slave" 
	@${RM} ${OBJECTDIR}/lightmodbus/slave/scoils.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/slave/scoils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/slave/scoils.p1 lightmodbus/slave/scoils.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/slave/scoils.d ${OBJECTDIR}/lightmodbus/slave/scoils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/slave/scoils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/slave/sregs.p1: lightmodbus/slave/sregs.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus/slave" 
	@${RM} ${OBJECTDIR}/lightmodbus/slave/sregs.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/slave/sregs.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/slave/sregs.p1 lightmodbus/slave/sregs.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/slave/sregs.d ${OBJECTDIR}/lightmodbus/slave/sregs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/slave/sregs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/lightmodbus.p1: lightmodbus/lightmodbus.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus" 
	@${RM} ${OBJECTDIR}/lightmodbus/lightmodbus.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/lightmodbus.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/lightmodbus.p1 lightmodbus/lightmodbus.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/lightmodbus.d ${OBJECTDIR}/lightmodbus/lightmodbus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/lightmodbus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/slave.p1: lightmodbus/slave.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus" 
	@${RM} ${OBJECTDIR}/lightmodbus/slave.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/slave.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/slave.p1 lightmodbus/slave.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/slave.d ${OBJECTDIR}/lightmodbus/slave.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/slave.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/lightmodbus/master.p1: lightmodbus/master.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/lightmodbus" 
	@${RM} ${OBJECTDIR}/lightmodbus/master.p1.d 
	@${RM} ${OBJECTDIR}/lightmodbus/master.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/lightmodbus/master.p1 lightmodbus/master.c 
	@-${MV} ${OBJECTDIR}/lightmodbus/master.d ${OBJECTDIR}/lightmodbus/master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/lightmodbus/master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/app_atcommand.p1: app_atcommand.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_atcommand.p1.d 
	@${RM} ${OBJECTDIR}/app_atcommand.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/app_atcommand.p1 app_atcommand.c 
	@-${MV} ${OBJECTDIR}/app_atcommand.d ${OBJECTDIR}/app_atcommand.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/app_atcommand.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/app_modbus.p1: app_modbus.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_modbus.p1.d 
	@${RM} ${OBJECTDIR}/app_modbus.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/app_modbus.p1 app_modbus.c 
	@-${MV} ${OBJECTDIR}/app_modbus.d ${OBJECTDIR}/app_modbus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/app_modbus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/app_sens_measure.p1: app_sens_measure.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_sens_measure.p1.d 
	@${RM} ${OBJECTDIR}/app_sens_measure.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/app_sens_measure.p1 app_sens_measure.c 
	@-${MV} ${OBJECTDIR}/app_sens_measure.d ${OBJECTDIR}/app_sens_measure.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/app_sens_measure.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/app_usb_cdc.p1: app_usb_cdc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_usb_cdc.p1.d 
	@${RM} ${OBJECTDIR}/app_usb_cdc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/app_usb_cdc.p1 app_usb_cdc.c 
	@-${MV} ${OBJECTDIR}/app_usb_cdc.d ${OBJECTDIR}/app_usb_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/app_usb_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nvm.p1: nvm.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/nvm.p1.d 
	@${RM} ${OBJECTDIR}/nvm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/nvm.p1 nvm.c 
	@-${MV} ${OBJECTDIR}/nvm.d ${OBJECTDIR}/nvm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nvm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sensor.p1: sensor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensor.p1.d 
	@${RM} ${OBJECTDIR}/sensor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sensor.p1 sensor.c 
	@-${MV} ${OBJECTDIR}/sensor.d ${OBJECTDIR}/sensor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sensor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/system.p1 system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb_descriptors.p1: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb_descriptors.p1 usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/usb_descriptors.d ${OBJECTDIR}/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb_events.p1: usb_events.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_events.p1.d 
	@${RM} ${OBJECTDIR}/usb_events.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb_events.p1 usb_events.c 
	@-${MV} ${OBJECTDIR}/usb_events.d ${OBJECTDIR}/usb_events.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb_events.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/filter.p1: filter.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/filter.p1.d 
	@${RM} ${OBJECTDIR}/filter.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/filter.p1 filter.c 
	@-${MV} ${OBJECTDIR}/filter.d ${OBJECTDIR}/filter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/filter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device.p1: usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device.p1 usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device.d ${OBJECTDIR}/usb/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device_cdc.p1: usb/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device_cdc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device_cdc.p1 usb/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device_cdc.d ${OBJECTDIR}/usb/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/usb_device_generic.p1: usb/usb_device_generic.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device_generic.p1.d 
	@${RM} ${OBJECTDIR}/usb/usb_device_generic.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/usb/usb_device_generic.p1 usb/usb_device_generic.c 
	@-${MV} ${OBJECTDIR}/usb/usb_device_generic.d ${OBJECTDIR}/usb/usb_device_generic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/usb_device_generic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_atof.p1: util/_atof.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_atof.p1.d 
	@${RM} ${OBJECTDIR}/util/_atof.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_atof.p1 util/_atof.c 
	@-${MV} ${OBJECTDIR}/util/_atof.d ${OBJECTDIR}/util/_atof.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_atof.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_atoi.p1: util/_atoi.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_atoi.p1.d 
	@${RM} ${OBJECTDIR}/util/_atoi.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_atoi.p1 util/_atoi.c 
	@-${MV} ${OBJECTDIR}/util/_atoi.d ${OBJECTDIR}/util/_atoi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_atoi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_ftoa.p1: util/_ftoa.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_ftoa.p1.d 
	@${RM} ${OBJECTDIR}/util/_ftoa.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_ftoa.p1 util/_ftoa.c 
	@-${MV} ${OBJECTDIR}/util/_ftoa.d ${OBJECTDIR}/util/_ftoa.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_ftoa.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_itoa.p1: util/_itoa.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_itoa.p1.d 
	@${RM} ${OBJECTDIR}/util/_itoa.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_itoa.p1 util/_itoa.c 
	@-${MV} ${OBJECTDIR}/util/_itoa.d ${OBJECTDIR}/util/_itoa.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_itoa.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/_string.p1: util/_string.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/_string.p1.d 
	@${RM} ${OBJECTDIR}/util/_string.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/_string.p1 util/_string.c 
	@-${MV} ${OBJECTDIR}/util/_string.d ${OBJECTDIR}/util/_string.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/_string.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/buffer.p1: util/buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/buffer.p1.d 
	@${RM} ${OBJECTDIR}/util/buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/buffer.p1 util/buffer.c 
	@-${MV} ${OBJECTDIR}/util/buffer.d ${OBJECTDIR}/util/buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/util/build_time.p1: util/build_time.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/build_time.p1.d 
	@${RM} ${OBJECTDIR}/util/build_time.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/util/build_time.p1 util/build_time.c 
	@-${MV} ${OBJECTDIR}/util/build_time.d ${OBJECTDIR}/util/build_time.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/util/build_time.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"." -I"./usb" -I"./bsp" -I"./lightmodbus" -I"./lightmodbus/master" -I"./lightmodbus/slave" -I"./util" -mwarn=-3 -Wa,-a -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -mc90lib -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/rn400t2-gs.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
