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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=BSP.c Interrupt.c main.c Timer.c em9301.c ../../bluetooth/stack/gatt/accel-service.c ../../bluetooth/stack/gatt/battery-service.c ../../bluetooth/stack/gatt/blood-pressure-service.c ../../bluetooth/stack/gatt/devinfo-service.c ../../bluetooth/stack/gatt/gatt.c ../../bluetooth/stack/gatt/led-service.c ../../bluetooth/stack/hci/hcid.c ../../bluetooth/stack/l2cap/l2cap.c ../../bluetooth/stack/rfcomm/rfcomm.c ../../bluetooth/stack/rfcomm/spp.c ../../bluetooth/stack/sdp/sdp.c ../../bluetooth/stack/vport/vport.c ../../bluetooth/utils/debug.c ../../apps/demo/btdemo.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/BSP.o ${OBJECTDIR}/Interrupt.o ${OBJECTDIR}/main.o ${OBJECTDIR}/Timer.o ${OBJECTDIR}/em9301.o ${OBJECTDIR}/_ext/1614121890/accel-service.o ${OBJECTDIR}/_ext/1614121890/battery-service.o ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o ${OBJECTDIR}/_ext/1614121890/devinfo-service.o ${OBJECTDIR}/_ext/1614121890/gatt.o ${OBJECTDIR}/_ext/1614121890/led-service.o ${OBJECTDIR}/_ext/1853184774/hcid.o ${OBJECTDIR}/_ext/1498628348/l2cap.o ${OBJECTDIR}/_ext/1006972936/rfcomm.o ${OBJECTDIR}/_ext/1006972936/spp.o ${OBJECTDIR}/_ext/1853195383/sdp.o ${OBJECTDIR}/_ext/1487534033/vport.o ${OBJECTDIR}/_ext/762655856/debug.o ${OBJECTDIR}/_ext/235100608/btdemo.o
POSSIBLE_DEPFILES=${OBJECTDIR}/BSP.o.d ${OBJECTDIR}/Interrupt.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/Timer.o.d ${OBJECTDIR}/em9301.o.d ${OBJECTDIR}/_ext/1614121890/accel-service.o.d ${OBJECTDIR}/_ext/1614121890/battery-service.o.d ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o.d ${OBJECTDIR}/_ext/1614121890/devinfo-service.o.d ${OBJECTDIR}/_ext/1614121890/gatt.o.d ${OBJECTDIR}/_ext/1614121890/led-service.o.d ${OBJECTDIR}/_ext/1853184774/hcid.o.d ${OBJECTDIR}/_ext/1498628348/l2cap.o.d ${OBJECTDIR}/_ext/1006972936/rfcomm.o.d ${OBJECTDIR}/_ext/1006972936/spp.o.d ${OBJECTDIR}/_ext/1853195383/sdp.o.d ${OBJECTDIR}/_ext/1487534033/vport.o.d ${OBJECTDIR}/_ext/762655856/debug.o.d ${OBJECTDIR}/_ext/235100608/btdemo.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/BSP.o ${OBJECTDIR}/Interrupt.o ${OBJECTDIR}/main.o ${OBJECTDIR}/Timer.o ${OBJECTDIR}/em9301.o ${OBJECTDIR}/_ext/1614121890/accel-service.o ${OBJECTDIR}/_ext/1614121890/battery-service.o ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o ${OBJECTDIR}/_ext/1614121890/devinfo-service.o ${OBJECTDIR}/_ext/1614121890/gatt.o ${OBJECTDIR}/_ext/1614121890/led-service.o ${OBJECTDIR}/_ext/1853184774/hcid.o ${OBJECTDIR}/_ext/1498628348/l2cap.o ${OBJECTDIR}/_ext/1006972936/rfcomm.o ${OBJECTDIR}/_ext/1006972936/spp.o ${OBJECTDIR}/_ext/1853195383/sdp.o ${OBJECTDIR}/_ext/1487534033/vport.o ${OBJECTDIR}/_ext/762655856/debug.o ${OBJECTDIR}/_ext/235100608/btdemo.o

# Source Files
SOURCEFILES=BSP.c Interrupt.c main.c Timer.c em9301.c ../../bluetooth/stack/gatt/accel-service.c ../../bluetooth/stack/gatt/battery-service.c ../../bluetooth/stack/gatt/blood-pressure-service.c ../../bluetooth/stack/gatt/devinfo-service.c ../../bluetooth/stack/gatt/gatt.c ../../bluetooth/stack/gatt/led-service.c ../../bluetooth/stack/hci/hcid.c ../../bluetooth/stack/l2cap/l2cap.c ../../bluetooth/stack/rfcomm/rfcomm.c ../../bluetooth/stack/rfcomm/spp.c ../../bluetooth/stack/sdp/sdp.c ../../bluetooth/stack/vport/vport.c ../../bluetooth/utils/debug.c ../../apps/demo/btdemo.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA104
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA104.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/BSP.o: BSP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/BSP.o.d 
	@${RM} ${OBJECTDIR}/BSP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP.c  -o ${OBJECTDIR}/BSP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Interrupt.o: Interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Interrupt.o.d 
	@${RM} ${OBJECTDIR}/Interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Interrupt.c  -o ${OBJECTDIR}/Interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Interrupt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Interrupt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Timer.o: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Timer.o.d 
	@${RM} ${OBJECTDIR}/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timer.c  -o ${OBJECTDIR}/Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/em9301.o: em9301.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/em9301.o.d 
	@${RM} ${OBJECTDIR}/em9301.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  em9301.c  -o ${OBJECTDIR}/em9301.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/em9301.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/em9301.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/accel-service.o: ../../bluetooth/stack/gatt/accel-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/accel-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/accel-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/accel-service.c  -o ${OBJECTDIR}/_ext/1614121890/accel-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/accel-service.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/accel-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/battery-service.o: ../../bluetooth/stack/gatt/battery-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/battery-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/battery-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/battery-service.c  -o ${OBJECTDIR}/_ext/1614121890/battery-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/battery-service.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/battery-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o: ../../bluetooth/stack/gatt/blood-pressure-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/blood-pressure-service.c  -o ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/devinfo-service.o: ../../bluetooth/stack/gatt/devinfo-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/devinfo-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/devinfo-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/devinfo-service.c  -o ${OBJECTDIR}/_ext/1614121890/devinfo-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/devinfo-service.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/devinfo-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/gatt.o: ../../bluetooth/stack/gatt/gatt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/gatt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/gatt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/gatt.c  -o ${OBJECTDIR}/_ext/1614121890/gatt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/gatt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/gatt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/led-service.o: ../../bluetooth/stack/gatt/led-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/led-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/led-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/led-service.c  -o ${OBJECTDIR}/_ext/1614121890/led-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/led-service.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/led-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1853184774/hcid.o: ../../bluetooth/stack/hci/hcid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1853184774 
	@${RM} ${OBJECTDIR}/_ext/1853184774/hcid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853184774/hcid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/hci/hcid.c  -o ${OBJECTDIR}/_ext/1853184774/hcid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1853184774/hcid.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853184774/hcid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1498628348/l2cap.o: ../../bluetooth/stack/l2cap/l2cap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1498628348 
	@${RM} ${OBJECTDIR}/_ext/1498628348/l2cap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498628348/l2cap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/l2cap/l2cap.c  -o ${OBJECTDIR}/_ext/1498628348/l2cap.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1498628348/l2cap.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1498628348/l2cap.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1006972936/rfcomm.o: ../../bluetooth/stack/rfcomm/rfcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1006972936 
	@${RM} ${OBJECTDIR}/_ext/1006972936/rfcomm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1006972936/rfcomm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/rfcomm/rfcomm.c  -o ${OBJECTDIR}/_ext/1006972936/rfcomm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1006972936/rfcomm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1006972936/rfcomm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1006972936/spp.o: ../../bluetooth/stack/rfcomm/spp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1006972936 
	@${RM} ${OBJECTDIR}/_ext/1006972936/spp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1006972936/spp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/rfcomm/spp.c  -o ${OBJECTDIR}/_ext/1006972936/spp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1006972936/spp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1006972936/spp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1853195383/sdp.o: ../../bluetooth/stack/sdp/sdp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1853195383 
	@${RM} ${OBJECTDIR}/_ext/1853195383/sdp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853195383/sdp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/sdp/sdp.c  -o ${OBJECTDIR}/_ext/1853195383/sdp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1853195383/sdp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853195383/sdp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1487534033/vport.o: ../../bluetooth/stack/vport/vport.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487534033 
	@${RM} ${OBJECTDIR}/_ext/1487534033/vport.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487534033/vport.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/vport/vport.c  -o ${OBJECTDIR}/_ext/1487534033/vport.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1487534033/vport.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487534033/vport.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/762655856/debug.o: ../../bluetooth/utils/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/762655856 
	@${RM} ${OBJECTDIR}/_ext/762655856/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/762655856/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/utils/debug.c  -o ${OBJECTDIR}/_ext/762655856/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/762655856/debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/762655856/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/235100608/btdemo.o: ../../apps/demo/btdemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/235100608 
	@${RM} ${OBJECTDIR}/_ext/235100608/btdemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/235100608/btdemo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../apps/demo/btdemo.c  -o ${OBJECTDIR}/_ext/235100608/btdemo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/235100608/btdemo.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/235100608/btdemo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/BSP.o: BSP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/BSP.o.d 
	@${RM} ${OBJECTDIR}/BSP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BSP.c  -o ${OBJECTDIR}/BSP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/BSP.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/BSP.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Interrupt.o: Interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Interrupt.o.d 
	@${RM} ${OBJECTDIR}/Interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Interrupt.c  -o ${OBJECTDIR}/Interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Interrupt.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Interrupt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Timer.o: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Timer.o.d 
	@${RM} ${OBJECTDIR}/Timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timer.c  -o ${OBJECTDIR}/Timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Timer.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/em9301.o: em9301.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/em9301.o.d 
	@${RM} ${OBJECTDIR}/em9301.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  em9301.c  -o ${OBJECTDIR}/em9301.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/em9301.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/em9301.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/accel-service.o: ../../bluetooth/stack/gatt/accel-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/accel-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/accel-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/accel-service.c  -o ${OBJECTDIR}/_ext/1614121890/accel-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/accel-service.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/accel-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/battery-service.o: ../../bluetooth/stack/gatt/battery-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/battery-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/battery-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/battery-service.c  -o ${OBJECTDIR}/_ext/1614121890/battery-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/battery-service.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/battery-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o: ../../bluetooth/stack/gatt/blood-pressure-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/blood-pressure-service.c  -o ${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/blood-pressure-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/devinfo-service.o: ../../bluetooth/stack/gatt/devinfo-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/devinfo-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/devinfo-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/devinfo-service.c  -o ${OBJECTDIR}/_ext/1614121890/devinfo-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/devinfo-service.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/devinfo-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/gatt.o: ../../bluetooth/stack/gatt/gatt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/gatt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/gatt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/gatt.c  -o ${OBJECTDIR}/_ext/1614121890/gatt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/gatt.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/gatt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1614121890/led-service.o: ../../bluetooth/stack/gatt/led-service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1614121890 
	@${RM} ${OBJECTDIR}/_ext/1614121890/led-service.o.d 
	@${RM} ${OBJECTDIR}/_ext/1614121890/led-service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/gatt/led-service.c  -o ${OBJECTDIR}/_ext/1614121890/led-service.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1614121890/led-service.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1614121890/led-service.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1853184774/hcid.o: ../../bluetooth/stack/hci/hcid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1853184774 
	@${RM} ${OBJECTDIR}/_ext/1853184774/hcid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853184774/hcid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/hci/hcid.c  -o ${OBJECTDIR}/_ext/1853184774/hcid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1853184774/hcid.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853184774/hcid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1498628348/l2cap.o: ../../bluetooth/stack/l2cap/l2cap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1498628348 
	@${RM} ${OBJECTDIR}/_ext/1498628348/l2cap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1498628348/l2cap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/l2cap/l2cap.c  -o ${OBJECTDIR}/_ext/1498628348/l2cap.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1498628348/l2cap.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1498628348/l2cap.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1006972936/rfcomm.o: ../../bluetooth/stack/rfcomm/rfcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1006972936 
	@${RM} ${OBJECTDIR}/_ext/1006972936/rfcomm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1006972936/rfcomm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/rfcomm/rfcomm.c  -o ${OBJECTDIR}/_ext/1006972936/rfcomm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1006972936/rfcomm.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1006972936/rfcomm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1006972936/spp.o: ../../bluetooth/stack/rfcomm/spp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1006972936 
	@${RM} ${OBJECTDIR}/_ext/1006972936/spp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1006972936/spp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/rfcomm/spp.c  -o ${OBJECTDIR}/_ext/1006972936/spp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1006972936/spp.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1006972936/spp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1853195383/sdp.o: ../../bluetooth/stack/sdp/sdp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1853195383 
	@${RM} ${OBJECTDIR}/_ext/1853195383/sdp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1853195383/sdp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/sdp/sdp.c  -o ${OBJECTDIR}/_ext/1853195383/sdp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1853195383/sdp.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1853195383/sdp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1487534033/vport.o: ../../bluetooth/stack/vport/vport.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487534033 
	@${RM} ${OBJECTDIR}/_ext/1487534033/vport.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487534033/vport.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/stack/vport/vport.c  -o ${OBJECTDIR}/_ext/1487534033/vport.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1487534033/vport.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487534033/vport.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/762655856/debug.o: ../../bluetooth/utils/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/762655856 
	@${RM} ${OBJECTDIR}/_ext/762655856/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/762655856/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../bluetooth/utils/debug.c  -o ${OBJECTDIR}/_ext/762655856/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/762655856/debug.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/762655856/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/235100608/btdemo.o: ../../apps/demo/btdemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/235100608 
	@${RM} ${OBJECTDIR}/_ext/235100608/btdemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/235100608/btdemo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../apps/demo/btdemo.c  -o ${OBJECTDIR}/_ext/235100608/btdemo.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/235100608/btdemo.o.d"        -g -omf=elf -O0 -I"../../bluetooth/include" -DINIT_CMD_NUM=1 -DEM9301=1 -DDISABLE_BT_CLASSICAL=1 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/235100608/btdemo.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic24.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic24.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pic24.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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
