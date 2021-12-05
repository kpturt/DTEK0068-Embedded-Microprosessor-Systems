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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
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
SOURCEFILES_QUOTED_IF_SPACED=FreeRTOS/Source/list.c FreeRTOS/Source/queue.c FreeRTOS/Source/tasks.c FreeRTOS/Source/timers.c FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.c FreeRTOS/Source/portable/MemMang/heap_1.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FreeRTOS/Source/list.o ${OBJECTDIR}/FreeRTOS/Source/queue.o ${OBJECTDIR}/FreeRTOS/Source/tasks.o ${OBJECTDIR}/FreeRTOS/Source/timers.o ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FreeRTOS/Source/list.o.d ${OBJECTDIR}/FreeRTOS/Source/queue.o.d ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d ${OBJECTDIR}/FreeRTOS/Source/timers.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FreeRTOS/Source/list.o ${OBJECTDIR}/FreeRTOS/Source/queue.o ${OBJECTDIR}/FreeRTOS/Source/tasks.o ${OBJECTDIR}/FreeRTOS/Source/timers.o ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=FreeRTOS/Source/list.c FreeRTOS/Source/queue.c FreeRTOS/Source/tasks.c FreeRTOS/Source/timers.c FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.c FreeRTOS/Source/portable/MemMang/heap_1.c main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega4809
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FreeRTOS/Source/list.o: FreeRTOS/Source/list.c  .generated_files/flags/default/f18fd7dd4fb6174116045715fbb7e1613c39fd3f .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/list.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/list.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/list.o -o ${OBJECTDIR}/FreeRTOS/Source/list.o FreeRTOS/Source/list.c 
	
${OBJECTDIR}/FreeRTOS/Source/queue.o: FreeRTOS/Source/queue.c  .generated_files/flags/default/4afa29bbdff91d510ab80f2f8af29b0d1550f5ac .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/queue.o -o ${OBJECTDIR}/FreeRTOS/Source/queue.o FreeRTOS/Source/queue.c 
	
${OBJECTDIR}/FreeRTOS/Source/tasks.o: FreeRTOS/Source/tasks.c  .generated_files/flags/default/5bf48954afa4985b25880ce085b438629de783b3 .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/tasks.o -o ${OBJECTDIR}/FreeRTOS/Source/tasks.o FreeRTOS/Source/tasks.c 
	
${OBJECTDIR}/FreeRTOS/Source/timers.o: FreeRTOS/Source/timers.c  .generated_files/flags/default/27c2774a62bcaafdc3cffb0a8b51e5e5ca2cb6e9 .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/timers.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/timers.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/timers.o -o ${OBJECTDIR}/FreeRTOS/Source/timers.o FreeRTOS/Source/timers.c 
	
${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o: FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.c  .generated_files/flags/default/f869f2ea9d9949e52f156e0b73311d4d8e4c302d .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o -o ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.c 
	
${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o: FreeRTOS/Source/portable/MemMang/heap_1.c  .generated_files/flags/default/92a9ae330c60c05c692691ffd253d5d94bb525bf .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o -o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o FreeRTOS/Source/portable/MemMang/heap_1.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/906606240009633c11e6a84dfa3aba3b904bcfd4 .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
else
${OBJECTDIR}/FreeRTOS/Source/list.o: FreeRTOS/Source/list.c  .generated_files/flags/default/b6c92d490a229f158aaee5ab352e8d02746d045f .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/list.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/list.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/list.o -o ${OBJECTDIR}/FreeRTOS/Source/list.o FreeRTOS/Source/list.c 
	
${OBJECTDIR}/FreeRTOS/Source/queue.o: FreeRTOS/Source/queue.c  .generated_files/flags/default/45a746acee4342798c9bc75123f9a2b9cf60a9d4 .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/queue.o -o ${OBJECTDIR}/FreeRTOS/Source/queue.o FreeRTOS/Source/queue.c 
	
${OBJECTDIR}/FreeRTOS/Source/tasks.o: FreeRTOS/Source/tasks.c  .generated_files/flags/default/c6e93881c2b66c34916ec90de662ae4f7ed4d4bc .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/tasks.o -o ${OBJECTDIR}/FreeRTOS/Source/tasks.o FreeRTOS/Source/tasks.c 
	
${OBJECTDIR}/FreeRTOS/Source/timers.o: FreeRTOS/Source/timers.c  .generated_files/flags/default/26621b834430f5bbfb0ad71dc0b2caa86667435c .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/timers.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/timers.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/timers.o -o ${OBJECTDIR}/FreeRTOS/Source/timers.o FreeRTOS/Source/timers.c 
	
${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o: FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.c  .generated_files/flags/default/aefd75511222a7c23b1af16eb774b257ce06bd56 .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o -o ${OBJECTDIR}/FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.o FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/port.c 
	
${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o: FreeRTOS/Source/portable/MemMang/heap_1.c  .generated_files/flags/default/73d7c38aacb1163e3f16429cccf1dcc2a9b8e386 .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d" -MT "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d" -MT ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o -o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o FreeRTOS/Source/portable/MemMang/heap_1.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/32eb05dbd1c8f54edd1e7a2a1b510d22af5c03cf .generated_files/flags/default/9102a0478522241ef752e9370635837b15197514
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -funsigned-char -funsigned-bitfields -I"." -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/ThirdParty/Partner-Supported-Ports/GCC/AVR_Mega0/" -Wall -gdwarf-3     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/W06E01_DigiDisplay.X.${IMAGE_TYPE}.hex"
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
