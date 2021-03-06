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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BigRodent.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BigRodent.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Eeprom.c configurationData.c "Flash Operations.s" configuration_payload.c dumb_payload.c dummy_payload.c init_payload.c state_payload.c speed_payload.c mal_comm.c mal_primitives.c mal_buffer.c main.c platform_defs.c dspic_settings.c generic_utils.c encoder_controller.c pwm_controller.c timer_handler.c control_algorithm.c motor_controller.c odometer.c message_buffer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Eeprom.o ${OBJECTDIR}/configurationData.o "${OBJECTDIR}/Flash Operations.o" ${OBJECTDIR}/configuration_payload.o ${OBJECTDIR}/dumb_payload.o ${OBJECTDIR}/dummy_payload.o ${OBJECTDIR}/init_payload.o ${OBJECTDIR}/state_payload.o ${OBJECTDIR}/speed_payload.o ${OBJECTDIR}/mal_comm.o ${OBJECTDIR}/mal_primitives.o ${OBJECTDIR}/mal_buffer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/platform_defs.o ${OBJECTDIR}/dspic_settings.o ${OBJECTDIR}/generic_utils.o ${OBJECTDIR}/encoder_controller.o ${OBJECTDIR}/pwm_controller.o ${OBJECTDIR}/timer_handler.o ${OBJECTDIR}/control_algorithm.o ${OBJECTDIR}/motor_controller.o ${OBJECTDIR}/odometer.o ${OBJECTDIR}/message_buffer.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Eeprom.o.d ${OBJECTDIR}/configurationData.o.d "${OBJECTDIR}/Flash Operations.o.d" ${OBJECTDIR}/configuration_payload.o.d ${OBJECTDIR}/dumb_payload.o.d ${OBJECTDIR}/dummy_payload.o.d ${OBJECTDIR}/init_payload.o.d ${OBJECTDIR}/state_payload.o.d ${OBJECTDIR}/speed_payload.o.d ${OBJECTDIR}/mal_comm.o.d ${OBJECTDIR}/mal_primitives.o.d ${OBJECTDIR}/mal_buffer.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/platform_defs.o.d ${OBJECTDIR}/dspic_settings.o.d ${OBJECTDIR}/generic_utils.o.d ${OBJECTDIR}/encoder_controller.o.d ${OBJECTDIR}/pwm_controller.o.d ${OBJECTDIR}/timer_handler.o.d ${OBJECTDIR}/control_algorithm.o.d ${OBJECTDIR}/motor_controller.o.d ${OBJECTDIR}/odometer.o.d ${OBJECTDIR}/message_buffer.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Eeprom.o ${OBJECTDIR}/configurationData.o ${OBJECTDIR}/Flash\ Operations.o ${OBJECTDIR}/configuration_payload.o ${OBJECTDIR}/dumb_payload.o ${OBJECTDIR}/dummy_payload.o ${OBJECTDIR}/init_payload.o ${OBJECTDIR}/state_payload.o ${OBJECTDIR}/speed_payload.o ${OBJECTDIR}/mal_comm.o ${OBJECTDIR}/mal_primitives.o ${OBJECTDIR}/mal_buffer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/platform_defs.o ${OBJECTDIR}/dspic_settings.o ${OBJECTDIR}/generic_utils.o ${OBJECTDIR}/encoder_controller.o ${OBJECTDIR}/pwm_controller.o ${OBJECTDIR}/timer_handler.o ${OBJECTDIR}/control_algorithm.o ${OBJECTDIR}/motor_controller.o ${OBJECTDIR}/odometer.o ${OBJECTDIR}/message_buffer.o

# Source Files
SOURCEFILES=Eeprom.c configurationData.c Flash Operations.s configuration_payload.c dumb_payload.c dummy_payload.c init_payload.c state_payload.c speed_payload.c mal_comm.c mal_primitives.c mal_buffer.c main.c platform_defs.c dspic_settings.c generic_utils.c encoder_controller.c pwm_controller.c timer_handler.c control_algorithm.c motor_controller.c odometer.c message_buffer.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/BigRodent.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Eeprom.o: Eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Eeprom.o.d 
	@${RM} ${OBJECTDIR}/Eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Eeprom.c  -o ${OBJECTDIR}/Eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configurationData.o: configurationData.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configurationData.o.d 
	@${RM} ${OBJECTDIR}/configurationData.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configurationData.c  -o ${OBJECTDIR}/configurationData.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configurationData.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configurationData.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configuration_payload.o: configuration_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_payload.o.d 
	@${RM} ${OBJECTDIR}/configuration_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_payload.c  -o ${OBJECTDIR}/configuration_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_payload.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configuration_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dumb_payload.o: dumb_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dumb_payload.o.d 
	@${RM} ${OBJECTDIR}/dumb_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dumb_payload.c  -o ${OBJECTDIR}/dumb_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dumb_payload.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dumb_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dummy_payload.o: dummy_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dummy_payload.o.d 
	@${RM} ${OBJECTDIR}/dummy_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dummy_payload.c  -o ${OBJECTDIR}/dummy_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dummy_payload.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dummy_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/init_payload.o: init_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/init_payload.o.d 
	@${RM} ${OBJECTDIR}/init_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  init_payload.c  -o ${OBJECTDIR}/init_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/init_payload.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/init_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/state_payload.o: state_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/state_payload.o.d 
	@${RM} ${OBJECTDIR}/state_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  state_payload.c  -o ${OBJECTDIR}/state_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/state_payload.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/state_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/speed_payload.o: speed_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/speed_payload.o.d 
	@${RM} ${OBJECTDIR}/speed_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  speed_payload.c  -o ${OBJECTDIR}/speed_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/speed_payload.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/speed_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mal_comm.o: mal_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mal_comm.o.d 
	@${RM} ${OBJECTDIR}/mal_comm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mal_comm.c  -o ${OBJECTDIR}/mal_comm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mal_comm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/mal_comm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mal_primitives.o: mal_primitives.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mal_primitives.o.d 
	@${RM} ${OBJECTDIR}/mal_primitives.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mal_primitives.c  -o ${OBJECTDIR}/mal_primitives.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mal_primitives.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/mal_primitives.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mal_buffer.o: mal_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mal_buffer.o.d 
	@${RM} ${OBJECTDIR}/mal_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mal_buffer.c  -o ${OBJECTDIR}/mal_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mal_buffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/mal_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/platform_defs.o: platform_defs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform_defs.o.d 
	@${RM} ${OBJECTDIR}/platform_defs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  platform_defs.c  -o ${OBJECTDIR}/platform_defs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/platform_defs.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/platform_defs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dspic_settings.o: dspic_settings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dspic_settings.o.d 
	@${RM} ${OBJECTDIR}/dspic_settings.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic_settings.c  -o ${OBJECTDIR}/dspic_settings.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dspic_settings.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dspic_settings.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/generic_utils.o: generic_utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/generic_utils.o.d 
	@${RM} ${OBJECTDIR}/generic_utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  generic_utils.c  -o ${OBJECTDIR}/generic_utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/generic_utils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/generic_utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/encoder_controller.o: encoder_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/encoder_controller.o.d 
	@${RM} ${OBJECTDIR}/encoder_controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  encoder_controller.c  -o ${OBJECTDIR}/encoder_controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/encoder_controller.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/encoder_controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/pwm_controller.o: pwm_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm_controller.o.d 
	@${RM} ${OBJECTDIR}/pwm_controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm_controller.c  -o ${OBJECTDIR}/pwm_controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/pwm_controller.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/pwm_controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timer_handler.o: timer_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer_handler.o.d 
	@${RM} ${OBJECTDIR}/timer_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer_handler.c  -o ${OBJECTDIR}/timer_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer_handler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/timer_handler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/control_algorithm.o: control_algorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/control_algorithm.o.d 
	@${RM} ${OBJECTDIR}/control_algorithm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  control_algorithm.c  -o ${OBJECTDIR}/control_algorithm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/control_algorithm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/control_algorithm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_controller.o: motor_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motor_controller.o.d 
	@${RM} ${OBJECTDIR}/motor_controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_controller.c  -o ${OBJECTDIR}/motor_controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_controller.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/motor_controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/odometer.o: odometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/odometer.o.d 
	@${RM} ${OBJECTDIR}/odometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  odometer.c  -o ${OBJECTDIR}/odometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/odometer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/odometer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/message_buffer.o: message_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/message_buffer.o.d 
	@${RM} ${OBJECTDIR}/message_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  message_buffer.c  -o ${OBJECTDIR}/message_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/message_buffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/message_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Eeprom.o: Eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Eeprom.o.d 
	@${RM} ${OBJECTDIR}/Eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Eeprom.c  -o ${OBJECTDIR}/Eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Eeprom.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configurationData.o: configurationData.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configurationData.o.d 
	@${RM} ${OBJECTDIR}/configurationData.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configurationData.c  -o ${OBJECTDIR}/configurationData.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configurationData.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configurationData.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configuration_payload.o: configuration_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_payload.o.d 
	@${RM} ${OBJECTDIR}/configuration_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_payload.c  -o ${OBJECTDIR}/configuration_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_payload.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configuration_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dumb_payload.o: dumb_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dumb_payload.o.d 
	@${RM} ${OBJECTDIR}/dumb_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dumb_payload.c  -o ${OBJECTDIR}/dumb_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dumb_payload.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dumb_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dummy_payload.o: dummy_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dummy_payload.o.d 
	@${RM} ${OBJECTDIR}/dummy_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dummy_payload.c  -o ${OBJECTDIR}/dummy_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dummy_payload.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dummy_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/init_payload.o: init_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/init_payload.o.d 
	@${RM} ${OBJECTDIR}/init_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  init_payload.c  -o ${OBJECTDIR}/init_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/init_payload.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/init_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/state_payload.o: state_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/state_payload.o.d 
	@${RM} ${OBJECTDIR}/state_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  state_payload.c  -o ${OBJECTDIR}/state_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/state_payload.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/state_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/speed_payload.o: speed_payload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/speed_payload.o.d 
	@${RM} ${OBJECTDIR}/speed_payload.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  speed_payload.c  -o ${OBJECTDIR}/speed_payload.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/speed_payload.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/speed_payload.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mal_comm.o: mal_comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mal_comm.o.d 
	@${RM} ${OBJECTDIR}/mal_comm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mal_comm.c  -o ${OBJECTDIR}/mal_comm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mal_comm.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/mal_comm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mal_primitives.o: mal_primitives.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mal_primitives.o.d 
	@${RM} ${OBJECTDIR}/mal_primitives.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mal_primitives.c  -o ${OBJECTDIR}/mal_primitives.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mal_primitives.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/mal_primitives.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mal_buffer.o: mal_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mal_buffer.o.d 
	@${RM} ${OBJECTDIR}/mal_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mal_buffer.c  -o ${OBJECTDIR}/mal_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mal_buffer.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/mal_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/platform_defs.o: platform_defs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/platform_defs.o.d 
	@${RM} ${OBJECTDIR}/platform_defs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  platform_defs.c  -o ${OBJECTDIR}/platform_defs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/platform_defs.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/platform_defs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dspic_settings.o: dspic_settings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dspic_settings.o.d 
	@${RM} ${OBJECTDIR}/dspic_settings.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dspic_settings.c  -o ${OBJECTDIR}/dspic_settings.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dspic_settings.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dspic_settings.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/generic_utils.o: generic_utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/generic_utils.o.d 
	@${RM} ${OBJECTDIR}/generic_utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  generic_utils.c  -o ${OBJECTDIR}/generic_utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/generic_utils.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/generic_utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/encoder_controller.o: encoder_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/encoder_controller.o.d 
	@${RM} ${OBJECTDIR}/encoder_controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  encoder_controller.c  -o ${OBJECTDIR}/encoder_controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/encoder_controller.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/encoder_controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/pwm_controller.o: pwm_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pwm_controller.o.d 
	@${RM} ${OBJECTDIR}/pwm_controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm_controller.c  -o ${OBJECTDIR}/pwm_controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/pwm_controller.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/pwm_controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timer_handler.o: timer_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer_handler.o.d 
	@${RM} ${OBJECTDIR}/timer_handler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer_handler.c  -o ${OBJECTDIR}/timer_handler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer_handler.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/timer_handler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/control_algorithm.o: control_algorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/control_algorithm.o.d 
	@${RM} ${OBJECTDIR}/control_algorithm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  control_algorithm.c  -o ${OBJECTDIR}/control_algorithm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/control_algorithm.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/control_algorithm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/motor_controller.o: motor_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motor_controller.o.d 
	@${RM} ${OBJECTDIR}/motor_controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_controller.c  -o ${OBJECTDIR}/motor_controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/motor_controller.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/motor_controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/odometer.o: odometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/odometer.o.d 
	@${RM} ${OBJECTDIR}/odometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  odometer.c  -o ${OBJECTDIR}/odometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/odometer.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/odometer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/message_buffer.o: message_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/message_buffer.o.d 
	@${RM} ${OBJECTDIR}/message_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  message_buffer.c  -o ${OBJECTDIR}/message_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/message_buffer.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/message_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Flash\ Operations.o: Flash\ Operations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} "${OBJECTDIR}/Flash Operations.o".d 
	@${RM} "${OBJECTDIR}/Flash Operations.o" 
	${MP_CC} $(MP_EXTRA_AS_PRE)  "Flash Operations.s"  -o "${OBJECTDIR}/Flash Operations.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/Flash Operations.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/Flash Operations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/Flash\ Operations.o: Flash\ Operations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} "${OBJECTDIR}/Flash Operations.o".d 
	@${RM} "${OBJECTDIR}/Flash Operations.o" 
	${MP_CC} $(MP_EXTRA_AS_PRE)  "Flash Operations.s"  -o "${OBJECTDIR}/Flash Operations.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/Flash Operations.o.d",--defsym=__MPLAB_BUILD=1,-g,--relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/Flash Operations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/BigRodent.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BigRodent.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--heap=200,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/BigRodent.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BigRodent.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=200,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/BigRodent.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
