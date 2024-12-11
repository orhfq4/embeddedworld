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
FINAL_IMAGE=${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=GPIO_Outputs.h LEDS.h Long_Serial_In.h OLED.h SDCard.h SPI.h SPI_CS.h STA013_Config.h TWI.h Temperature_Sensor.h UART.h UART_Print.h board.h peripherals.h print_memory.h Directory_Functions.h Drive_Values.h File_System.h Read_Sector.h Read_Values.h Play_Song.h GPIO_Inputs.h Config_Arrays.c GPIO_Outputs.c LEDS.c Long_Serial_In.c OLED.c board.c OLED_Char_Map.c SDCard.c SPI.c SPI_CS.c STA013_config.c TWI.c Temperature_Sensor.c UART.c UART_Print.c print_memory.c main.c Directory_Functions.c Drive_Values.c File_System.c Read_Sector.c Read_Values.c Play_Song.c GPIO_Inputs.c seos.c seos.h

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/GPIO_Outputs.o ${OBJECTDIR}/LEDS.o ${OBJECTDIR}/Long_Serial_In.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/SDCard.o ${OBJECTDIR}/SPI.o ${OBJECTDIR}/SPI_CS.o ${OBJECTDIR}/STA013_Config.o ${OBJECTDIR}/TWI.o ${OBJECTDIR}/Temperature_Sensor.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/UART_Print.o ${OBJECTDIR}/board.o ${OBJECTDIR}/peripherals.o ${OBJECTDIR}/print_memory.o ${OBJECTDIR}/Directory_Functions.o ${OBJECTDIR}/Drive_Values.o ${OBJECTDIR}/File_System.o ${OBJECTDIR}/Read_Sector.o ${OBJECTDIR}/Read_Values.o ${OBJECTDIR}/Play_Song.o ${OBJECTDIR}/GPIO_Inputs.o ${OBJECTDIR}/Config_Arrays.o ${OBJECTDIR}/GPIO_Outputs.o ${OBJECTDIR}/LEDS.o ${OBJECTDIR}/Long_Serial_In.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/board.o ${OBJECTDIR}/OLED_Char_Map.o ${OBJECTDIR}/SDCard.o ${OBJECTDIR}/SPI.o ${OBJECTDIR}/SPI_CS.o ${OBJECTDIR}/STA013_config.o ${OBJECTDIR}/TWI.o ${OBJECTDIR}/Temperature_Sensor.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/UART_Print.o ${OBJECTDIR}/print_memory.o ${OBJECTDIR}/main.o ${OBJECTDIR}/Directory_Functions.o ${OBJECTDIR}/Drive_Values.o ${OBJECTDIR}/File_System.o ${OBJECTDIR}/Read_Sector.o ${OBJECTDIR}/Read_Values.o ${OBJECTDIR}/Play_Song.o ${OBJECTDIR}/GPIO_Inputs.o ${OBJECTDIR}/seos.o ${OBJECTDIR}/seos.o
POSSIBLE_DEPFILES=${OBJECTDIR}/GPIO_Outputs.o.d ${OBJECTDIR}/LEDS.o.d ${OBJECTDIR}/Long_Serial_In.o.d ${OBJECTDIR}/OLED.o.d ${OBJECTDIR}/SDCard.o.d ${OBJECTDIR}/SPI.o.d ${OBJECTDIR}/SPI_CS.o.d ${OBJECTDIR}/STA013_Config.o.d ${OBJECTDIR}/TWI.o.d ${OBJECTDIR}/Temperature_Sensor.o.d ${OBJECTDIR}/UART.o.d ${OBJECTDIR}/UART_Print.o.d ${OBJECTDIR}/board.o.d ${OBJECTDIR}/peripherals.o.d ${OBJECTDIR}/print_memory.o.d ${OBJECTDIR}/Directory_Functions.o.d ${OBJECTDIR}/Drive_Values.o.d ${OBJECTDIR}/File_System.o.d ${OBJECTDIR}/Read_Sector.o.d ${OBJECTDIR}/Read_Values.o.d ${OBJECTDIR}/Play_Song.o.d ${OBJECTDIR}/GPIO_Inputs.o.d ${OBJECTDIR}/Config_Arrays.o.d ${OBJECTDIR}/GPIO_Outputs.o.d ${OBJECTDIR}/LEDS.o.d ${OBJECTDIR}/Long_Serial_In.o.d ${OBJECTDIR}/OLED.o.d ${OBJECTDIR}/board.o.d ${OBJECTDIR}/OLED_Char_Map.o.d ${OBJECTDIR}/SDCard.o.d ${OBJECTDIR}/SPI.o.d ${OBJECTDIR}/SPI_CS.o.d ${OBJECTDIR}/STA013_config.o.d ${OBJECTDIR}/TWI.o.d ${OBJECTDIR}/Temperature_Sensor.o.d ${OBJECTDIR}/UART.o.d ${OBJECTDIR}/UART_Print.o.d ${OBJECTDIR}/print_memory.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/Directory_Functions.o.d ${OBJECTDIR}/Drive_Values.o.d ${OBJECTDIR}/File_System.o.d ${OBJECTDIR}/Read_Sector.o.d ${OBJECTDIR}/Read_Values.o.d ${OBJECTDIR}/Play_Song.o.d ${OBJECTDIR}/GPIO_Inputs.o.d ${OBJECTDIR}/seos.o.d ${OBJECTDIR}/seos.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/GPIO_Outputs.o ${OBJECTDIR}/LEDS.o ${OBJECTDIR}/Long_Serial_In.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/SDCard.o ${OBJECTDIR}/SPI.o ${OBJECTDIR}/SPI_CS.o ${OBJECTDIR}/STA013_Config.o ${OBJECTDIR}/TWI.o ${OBJECTDIR}/Temperature_Sensor.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/UART_Print.o ${OBJECTDIR}/board.o ${OBJECTDIR}/peripherals.o ${OBJECTDIR}/print_memory.o ${OBJECTDIR}/Directory_Functions.o ${OBJECTDIR}/Drive_Values.o ${OBJECTDIR}/File_System.o ${OBJECTDIR}/Read_Sector.o ${OBJECTDIR}/Read_Values.o ${OBJECTDIR}/Play_Song.o ${OBJECTDIR}/GPIO_Inputs.o ${OBJECTDIR}/Config_Arrays.o ${OBJECTDIR}/GPIO_Outputs.o ${OBJECTDIR}/LEDS.o ${OBJECTDIR}/Long_Serial_In.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/board.o ${OBJECTDIR}/OLED_Char_Map.o ${OBJECTDIR}/SDCard.o ${OBJECTDIR}/SPI.o ${OBJECTDIR}/SPI_CS.o ${OBJECTDIR}/STA013_config.o ${OBJECTDIR}/TWI.o ${OBJECTDIR}/Temperature_Sensor.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/UART_Print.o ${OBJECTDIR}/print_memory.o ${OBJECTDIR}/main.o ${OBJECTDIR}/Directory_Functions.o ${OBJECTDIR}/Drive_Values.o ${OBJECTDIR}/File_System.o ${OBJECTDIR}/Read_Sector.o ${OBJECTDIR}/Read_Values.o ${OBJECTDIR}/Play_Song.o ${OBJECTDIR}/GPIO_Inputs.o ${OBJECTDIR}/seos.o ${OBJECTDIR}/seos.o

# Source Files
SOURCEFILES=GPIO_Outputs.h LEDS.h Long_Serial_In.h OLED.h SDCard.h SPI.h SPI_CS.h STA013_Config.h TWI.h Temperature_Sensor.h UART.h UART_Print.h board.h peripherals.h print_memory.h Directory_Functions.h Drive_Values.h File_System.h Read_Sector.h Read_Values.h Play_Song.h GPIO_Inputs.h Config_Arrays.c GPIO_Outputs.c LEDS.c Long_Serial_In.c OLED.c board.c OLED_Char_Map.c SDCard.c SPI.c SPI_CS.c STA013_config.c TWI.c Temperature_Sensor.c UART.c UART_Print.c print_memory.c main.c Directory_Functions.c Drive_Values.c File_System.c Read_Sector.c Read_Values.c Play_Song.c GPIO_Inputs.c seos.c seos.h



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega324PB
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/GPIO_Outputs.o: GPIO_Outputs.h  .generated_files/flags/default/c04dbe8ed3edfe715009317eea4c6cc7d7906800 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Outputs.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Outputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/GPIO_Outputs.o.d" -MT "${OBJECTDIR}/GPIO_Outputs.o.d" -MT ${OBJECTDIR}/GPIO_Outputs.o -o ${OBJECTDIR}/GPIO_Outputs.o GPIO_Outputs.h 
	
${OBJECTDIR}/LEDS.o: LEDS.h  .generated_files/flags/default/5b2198cde40b9ad50260d690bbd16252d0f3c9cf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LEDS.o.d 
	@${RM} ${OBJECTDIR}/LEDS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/LEDS.o.d" -MT "${OBJECTDIR}/LEDS.o.d" -MT ${OBJECTDIR}/LEDS.o -o ${OBJECTDIR}/LEDS.o LEDS.h 
	
${OBJECTDIR}/Long_Serial_In.o: Long_Serial_In.h  .generated_files/flags/default/70e9913a6f2a9027c980c3967c007b6c5838b8ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Long_Serial_In.o.d 
	@${RM} ${OBJECTDIR}/Long_Serial_In.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Long_Serial_In.o.d" -MT "${OBJECTDIR}/Long_Serial_In.o.d" -MT ${OBJECTDIR}/Long_Serial_In.o -o ${OBJECTDIR}/Long_Serial_In.o Long_Serial_In.h 
	
${OBJECTDIR}/OLED.o: OLED.h  .generated_files/flags/default/a5912519c8a04dcbd866715bb554d5cd18b7722c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/OLED.o.d" -MT "${OBJECTDIR}/OLED.o.d" -MT ${OBJECTDIR}/OLED.o -o ${OBJECTDIR}/OLED.o OLED.h 
	
${OBJECTDIR}/SDCard.o: SDCard.h  .generated_files/flags/default/ff144ac7c26ddd5abf020efbfbf017a41b81ee54 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SDCard.o.d 
	@${RM} ${OBJECTDIR}/SDCard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SDCard.o.d" -MT "${OBJECTDIR}/SDCard.o.d" -MT ${OBJECTDIR}/SDCard.o -o ${OBJECTDIR}/SDCard.o SDCard.h 
	
${OBJECTDIR}/SPI.o: SPI.h  .generated_files/flags/default/2ec5f2c21313bfb440576c24500eed0e0b861220 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI.o.d 
	@${RM} ${OBJECTDIR}/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SPI.o.d" -MT "${OBJECTDIR}/SPI.o.d" -MT ${OBJECTDIR}/SPI.o -o ${OBJECTDIR}/SPI.o SPI.h 
	
${OBJECTDIR}/SPI_CS.o: SPI_CS.h  .generated_files/flags/default/44d2cda71e5e43fe4d7c5564f83a178a1201ee05 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI_CS.o.d 
	@${RM} ${OBJECTDIR}/SPI_CS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SPI_CS.o.d" -MT "${OBJECTDIR}/SPI_CS.o.d" -MT ${OBJECTDIR}/SPI_CS.o -o ${OBJECTDIR}/SPI_CS.o SPI_CS.h 
	
${OBJECTDIR}/STA013_Config.o: STA013_Config.h  .generated_files/flags/default/4cba47885475d33209dc5da1a09fa40dd40bac35 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/STA013_Config.o.d 
	@${RM} ${OBJECTDIR}/STA013_Config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/STA013_Config.o.d" -MT "${OBJECTDIR}/STA013_Config.o.d" -MT ${OBJECTDIR}/STA013_Config.o -o ${OBJECTDIR}/STA013_Config.o STA013_Config.h 
	
${OBJECTDIR}/TWI.o: TWI.h  .generated_files/flags/default/fcfb9fd914cb8eedfe936ea243e13bbd9ec0b280 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TWI.o.d 
	@${RM} ${OBJECTDIR}/TWI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/TWI.o.d" -MT "${OBJECTDIR}/TWI.o.d" -MT ${OBJECTDIR}/TWI.o -o ${OBJECTDIR}/TWI.o TWI.h 
	
${OBJECTDIR}/Temperature_Sensor.o: Temperature_Sensor.h  .generated_files/flags/default/7425a7249b48b29be1ab2e40b220677c151aafbf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Temperature_Sensor.o.d 
	@${RM} ${OBJECTDIR}/Temperature_Sensor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Temperature_Sensor.o.d" -MT "${OBJECTDIR}/Temperature_Sensor.o.d" -MT ${OBJECTDIR}/Temperature_Sensor.o -o ${OBJECTDIR}/Temperature_Sensor.o Temperature_Sensor.h 
	
${OBJECTDIR}/UART.o: UART.h  .generated_files/flags/default/60df6a253bc9b459f26b691c71b6cf1dd3a34156 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/UART.o.d" -MT "${OBJECTDIR}/UART.o.d" -MT ${OBJECTDIR}/UART.o -o ${OBJECTDIR}/UART.o UART.h 
	
${OBJECTDIR}/UART_Print.o: UART_Print.h  .generated_files/flags/default/1bc53e56afaaade05a84996fdd89d1e8b4731703 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_Print.o.d 
	@${RM} ${OBJECTDIR}/UART_Print.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/UART_Print.o.d" -MT "${OBJECTDIR}/UART_Print.o.d" -MT ${OBJECTDIR}/UART_Print.o -o ${OBJECTDIR}/UART_Print.o UART_Print.h 
	
${OBJECTDIR}/board.o: board.h  .generated_files/flags/default/92e7c09643fa580dc375a2776283f7017d6de2e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/board.o.d 
	@${RM} ${OBJECTDIR}/board.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/board.o.d" -MT "${OBJECTDIR}/board.o.d" -MT ${OBJECTDIR}/board.o -o ${OBJECTDIR}/board.o board.h 
	
${OBJECTDIR}/peripherals.o: peripherals.h  .generated_files/flags/default/3b4486cc16fd05a117ab396bb41084937a978fed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/peripherals.o.d 
	@${RM} ${OBJECTDIR}/peripherals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/peripherals.o.d" -MT "${OBJECTDIR}/peripherals.o.d" -MT ${OBJECTDIR}/peripherals.o -o ${OBJECTDIR}/peripherals.o peripherals.h 
	
${OBJECTDIR}/print_memory.o: print_memory.h  .generated_files/flags/default/1736c642cded242b282a67c8e89568c2c1ca3565 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/print_memory.o.d 
	@${RM} ${OBJECTDIR}/print_memory.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/print_memory.o.d" -MT "${OBJECTDIR}/print_memory.o.d" -MT ${OBJECTDIR}/print_memory.o -o ${OBJECTDIR}/print_memory.o print_memory.h 
	
${OBJECTDIR}/Directory_Functions.o: Directory_Functions.h  .generated_files/flags/default/cf1a8acdab4f14c2d1f57474b575422a47d3a629 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Directory_Functions.o.d 
	@${RM} ${OBJECTDIR}/Directory_Functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Directory_Functions.o.d" -MT "${OBJECTDIR}/Directory_Functions.o.d" -MT ${OBJECTDIR}/Directory_Functions.o -o ${OBJECTDIR}/Directory_Functions.o Directory_Functions.h 
	
${OBJECTDIR}/Drive_Values.o: Drive_Values.h  .generated_files/flags/default/516b2299c32afeecb24c871e237a40a8e59a844f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Drive_Values.o.d 
	@${RM} ${OBJECTDIR}/Drive_Values.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Drive_Values.o.d" -MT "${OBJECTDIR}/Drive_Values.o.d" -MT ${OBJECTDIR}/Drive_Values.o -o ${OBJECTDIR}/Drive_Values.o Drive_Values.h 
	
${OBJECTDIR}/File_System.o: File_System.h  .generated_files/flags/default/b11b819be09ca322c77d8c85bb06de053d99e74f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/File_System.o.d 
	@${RM} ${OBJECTDIR}/File_System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/File_System.o.d" -MT "${OBJECTDIR}/File_System.o.d" -MT ${OBJECTDIR}/File_System.o -o ${OBJECTDIR}/File_System.o File_System.h 
	
${OBJECTDIR}/Read_Sector.o: Read_Sector.h  .generated_files/flags/default/69e36aaae2095ed7651b556b9f7c0d98edd9419a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Read_Sector.o.d 
	@${RM} ${OBJECTDIR}/Read_Sector.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Read_Sector.o.d" -MT "${OBJECTDIR}/Read_Sector.o.d" -MT ${OBJECTDIR}/Read_Sector.o -o ${OBJECTDIR}/Read_Sector.o Read_Sector.h 
	
${OBJECTDIR}/Read_Values.o: Read_Values.h  .generated_files/flags/default/15e11a94e109fdc7474bb8f13a69106ea03655ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Read_Values.o.d 
	@${RM} ${OBJECTDIR}/Read_Values.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Read_Values.o.d" -MT "${OBJECTDIR}/Read_Values.o.d" -MT ${OBJECTDIR}/Read_Values.o -o ${OBJECTDIR}/Read_Values.o Read_Values.h 
	
${OBJECTDIR}/Play_Song.o: Play_Song.h  .generated_files/flags/default/75c2fb7c3507fd1d6f45f139599665f5dd1a2d54 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Play_Song.o.d 
	@${RM} ${OBJECTDIR}/Play_Song.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Play_Song.o.d" -MT "${OBJECTDIR}/Play_Song.o.d" -MT ${OBJECTDIR}/Play_Song.o -o ${OBJECTDIR}/Play_Song.o Play_Song.h 
	
${OBJECTDIR}/GPIO_Inputs.o: GPIO_Inputs.h  .generated_files/flags/default/bc8a81fc8631518305dfa4e8bd1c0f9c45165e08 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Inputs.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/GPIO_Inputs.o.d" -MT "${OBJECTDIR}/GPIO_Inputs.o.d" -MT ${OBJECTDIR}/GPIO_Inputs.o -o ${OBJECTDIR}/GPIO_Inputs.o GPIO_Inputs.h 
	
${OBJECTDIR}/Config_Arrays.o: Config_Arrays.c  .generated_files/flags/default/757b63db4e3575ad3ea775e63a670f04a36afa3a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Config_Arrays.o.d 
	@${RM} ${OBJECTDIR}/Config_Arrays.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Config_Arrays.o.d" -MT "${OBJECTDIR}/Config_Arrays.o.d" -MT ${OBJECTDIR}/Config_Arrays.o -o ${OBJECTDIR}/Config_Arrays.o Config_Arrays.c 
	
${OBJECTDIR}/GPIO_Outputs.o: GPIO_Outputs.c  .generated_files/flags/default/71372622c9e20b7dc30099af35496458e1cc78ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Outputs.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Outputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/GPIO_Outputs.o.d" -MT "${OBJECTDIR}/GPIO_Outputs.o.d" -MT ${OBJECTDIR}/GPIO_Outputs.o -o ${OBJECTDIR}/GPIO_Outputs.o GPIO_Outputs.c 
	
${OBJECTDIR}/LEDS.o: LEDS.c  .generated_files/flags/default/b3d4e7f8b48277fd7995b68c3b62ce1fcd2d2065 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LEDS.o.d 
	@${RM} ${OBJECTDIR}/LEDS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/LEDS.o.d" -MT "${OBJECTDIR}/LEDS.o.d" -MT ${OBJECTDIR}/LEDS.o -o ${OBJECTDIR}/LEDS.o LEDS.c 
	
${OBJECTDIR}/Long_Serial_In.o: Long_Serial_In.c  .generated_files/flags/default/30c0a9d1b612778853a2efa1b04278a206e01b62 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Long_Serial_In.o.d 
	@${RM} ${OBJECTDIR}/Long_Serial_In.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Long_Serial_In.o.d" -MT "${OBJECTDIR}/Long_Serial_In.o.d" -MT ${OBJECTDIR}/Long_Serial_In.o -o ${OBJECTDIR}/Long_Serial_In.o Long_Serial_In.c 
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/flags/default/4da05028cfea21a662b81ee3e12786f09c9c1d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/OLED.o.d" -MT "${OBJECTDIR}/OLED.o.d" -MT ${OBJECTDIR}/OLED.o -o ${OBJECTDIR}/OLED.o OLED.c 
	
${OBJECTDIR}/board.o: board.c  .generated_files/flags/default/842cde9b0ef2aba3fb938c1632657d0976069cab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/board.o.d 
	@${RM} ${OBJECTDIR}/board.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/board.o.d" -MT "${OBJECTDIR}/board.o.d" -MT ${OBJECTDIR}/board.o -o ${OBJECTDIR}/board.o board.c 
	
${OBJECTDIR}/OLED_Char_Map.o: OLED_Char_Map.c  .generated_files/flags/default/85c7c2d34faa6c8d135ad7e950171a3fc16fed5e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED_Char_Map.o.d 
	@${RM} ${OBJECTDIR}/OLED_Char_Map.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/OLED_Char_Map.o.d" -MT "${OBJECTDIR}/OLED_Char_Map.o.d" -MT ${OBJECTDIR}/OLED_Char_Map.o -o ${OBJECTDIR}/OLED_Char_Map.o OLED_Char_Map.c 
	
${OBJECTDIR}/SDCard.o: SDCard.c  .generated_files/flags/default/954d5c5c96baaf59d12ee3b22c270c4886c73b51 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SDCard.o.d 
	@${RM} ${OBJECTDIR}/SDCard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SDCard.o.d" -MT "${OBJECTDIR}/SDCard.o.d" -MT ${OBJECTDIR}/SDCard.o -o ${OBJECTDIR}/SDCard.o SDCard.c 
	
${OBJECTDIR}/SPI.o: SPI.c  .generated_files/flags/default/6b1eb89de50796683efdc7deeab5bc05a9e24267 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI.o.d 
	@${RM} ${OBJECTDIR}/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SPI.o.d" -MT "${OBJECTDIR}/SPI.o.d" -MT ${OBJECTDIR}/SPI.o -o ${OBJECTDIR}/SPI.o SPI.c 
	
${OBJECTDIR}/SPI_CS.o: SPI_CS.c  .generated_files/flags/default/493642517c6a08341bbb030b4d99b0d123dcbd68 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI_CS.o.d 
	@${RM} ${OBJECTDIR}/SPI_CS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SPI_CS.o.d" -MT "${OBJECTDIR}/SPI_CS.o.d" -MT ${OBJECTDIR}/SPI_CS.o -o ${OBJECTDIR}/SPI_CS.o SPI_CS.c 
	
${OBJECTDIR}/STA013_config.o: STA013_config.c  .generated_files/flags/default/2de1795fad076b9b38bbd368e533217b06d73e9e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/STA013_config.o.d 
	@${RM} ${OBJECTDIR}/STA013_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/STA013_config.o.d" -MT "${OBJECTDIR}/STA013_config.o.d" -MT ${OBJECTDIR}/STA013_config.o -o ${OBJECTDIR}/STA013_config.o STA013_config.c 
	
${OBJECTDIR}/TWI.o: TWI.c  .generated_files/flags/default/5050af7b528ab41db537bfe19c9ab2d10d52c793 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TWI.o.d 
	@${RM} ${OBJECTDIR}/TWI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/TWI.o.d" -MT "${OBJECTDIR}/TWI.o.d" -MT ${OBJECTDIR}/TWI.o -o ${OBJECTDIR}/TWI.o TWI.c 
	
${OBJECTDIR}/Temperature_Sensor.o: Temperature_Sensor.c  .generated_files/flags/default/803c99a602af37ce404f9d54c5ea328dc659c641 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Temperature_Sensor.o.d 
	@${RM} ${OBJECTDIR}/Temperature_Sensor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Temperature_Sensor.o.d" -MT "${OBJECTDIR}/Temperature_Sensor.o.d" -MT ${OBJECTDIR}/Temperature_Sensor.o -o ${OBJECTDIR}/Temperature_Sensor.o Temperature_Sensor.c 
	
${OBJECTDIR}/UART.o: UART.c  .generated_files/flags/default/62b7e8b31cc06902a1c41d390298c442c778ef6d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/UART.o.d" -MT "${OBJECTDIR}/UART.o.d" -MT ${OBJECTDIR}/UART.o -o ${OBJECTDIR}/UART.o UART.c 
	
${OBJECTDIR}/UART_Print.o: UART_Print.c  .generated_files/flags/default/67db0a7b473a8227b7cf8d8e134232f3b22708ff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_Print.o.d 
	@${RM} ${OBJECTDIR}/UART_Print.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/UART_Print.o.d" -MT "${OBJECTDIR}/UART_Print.o.d" -MT ${OBJECTDIR}/UART_Print.o -o ${OBJECTDIR}/UART_Print.o UART_Print.c 
	
${OBJECTDIR}/print_memory.o: print_memory.c  .generated_files/flags/default/d01e629ea837fb1fd3db40adb6e2d1c26741923b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/print_memory.o.d 
	@${RM} ${OBJECTDIR}/print_memory.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/print_memory.o.d" -MT "${OBJECTDIR}/print_memory.o.d" -MT ${OBJECTDIR}/print_memory.o -o ${OBJECTDIR}/print_memory.o print_memory.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/59fb29f57026affbbcf030c340a9f211140853ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/Directory_Functions.o: Directory_Functions.c  .generated_files/flags/default/cca7de82d6c5f01bb4a7009566ef92ef4f175379 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Directory_Functions.o.d 
	@${RM} ${OBJECTDIR}/Directory_Functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Directory_Functions.o.d" -MT "${OBJECTDIR}/Directory_Functions.o.d" -MT ${OBJECTDIR}/Directory_Functions.o -o ${OBJECTDIR}/Directory_Functions.o Directory_Functions.c 
	
${OBJECTDIR}/Drive_Values.o: Drive_Values.c  .generated_files/flags/default/b9f9b088f26e53283ac39ff357d43dd055c0099b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Drive_Values.o.d 
	@${RM} ${OBJECTDIR}/Drive_Values.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Drive_Values.o.d" -MT "${OBJECTDIR}/Drive_Values.o.d" -MT ${OBJECTDIR}/Drive_Values.o -o ${OBJECTDIR}/Drive_Values.o Drive_Values.c 
	
${OBJECTDIR}/File_System.o: File_System.c  .generated_files/flags/default/9405b820d4bb2de73f2ac7e7e00daddf4399ad29 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/File_System.o.d 
	@${RM} ${OBJECTDIR}/File_System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/File_System.o.d" -MT "${OBJECTDIR}/File_System.o.d" -MT ${OBJECTDIR}/File_System.o -o ${OBJECTDIR}/File_System.o File_System.c 
	
${OBJECTDIR}/Read_Sector.o: Read_Sector.c  .generated_files/flags/default/da8a3b6363bb9b80b140348dd41a00c001a1acbd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Read_Sector.o.d 
	@${RM} ${OBJECTDIR}/Read_Sector.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Read_Sector.o.d" -MT "${OBJECTDIR}/Read_Sector.o.d" -MT ${OBJECTDIR}/Read_Sector.o -o ${OBJECTDIR}/Read_Sector.o Read_Sector.c 
	
${OBJECTDIR}/Read_Values.o: Read_Values.c  .generated_files/flags/default/9ff14ddd7fc6de04b39df844966cfd0b175adac7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Read_Values.o.d 
	@${RM} ${OBJECTDIR}/Read_Values.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Read_Values.o.d" -MT "${OBJECTDIR}/Read_Values.o.d" -MT ${OBJECTDIR}/Read_Values.o -o ${OBJECTDIR}/Read_Values.o Read_Values.c 
	
${OBJECTDIR}/Play_Song.o: Play_Song.c  .generated_files/flags/default/ab9e2d2f0d98735f482e23644dd9a30e140d32ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Play_Song.o.d 
	@${RM} ${OBJECTDIR}/Play_Song.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Play_Song.o.d" -MT "${OBJECTDIR}/Play_Song.o.d" -MT ${OBJECTDIR}/Play_Song.o -o ${OBJECTDIR}/Play_Song.o Play_Song.c 
	
${OBJECTDIR}/GPIO_Inputs.o: GPIO_Inputs.c  .generated_files/flags/default/aab1c476bb9b5afeba6ba4c24e3b888d92ec2af5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Inputs.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/GPIO_Inputs.o.d" -MT "${OBJECTDIR}/GPIO_Inputs.o.d" -MT ${OBJECTDIR}/GPIO_Inputs.o -o ${OBJECTDIR}/GPIO_Inputs.o GPIO_Inputs.c 
	
${OBJECTDIR}/seos.o: seos.c  .generated_files/flags/default/23da736ee6fcbbbc66acbe76c1b0c427a85a9c1b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/seos.o.d 
	@${RM} ${OBJECTDIR}/seos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/seos.o.d" -MT "${OBJECTDIR}/seos.o.d" -MT ${OBJECTDIR}/seos.o -o ${OBJECTDIR}/seos.o seos.c 
	
${OBJECTDIR}/seos.o: seos.h  .generated_files/flags/default/fc3652cedf9fe932cfd76e33a3ca80fbd3bd40c5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/seos.o.d 
	@${RM} ${OBJECTDIR}/seos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/seos.o.d" -MT "${OBJECTDIR}/seos.o.d" -MT ${OBJECTDIR}/seos.o -o ${OBJECTDIR}/seos.o seos.h 
	
else
${OBJECTDIR}/GPIO_Outputs.o: GPIO_Outputs.h  .generated_files/flags/default/b6cdb586fb59af826e3c5274a3d110bc5cbc78dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Outputs.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Outputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/GPIO_Outputs.o.d" -MT "${OBJECTDIR}/GPIO_Outputs.o.d" -MT ${OBJECTDIR}/GPIO_Outputs.o -o ${OBJECTDIR}/GPIO_Outputs.o GPIO_Outputs.h 
	
${OBJECTDIR}/LEDS.o: LEDS.h  .generated_files/flags/default/8a2a5d7e034206102b697d7030a9a79f64ae9ec0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LEDS.o.d 
	@${RM} ${OBJECTDIR}/LEDS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/LEDS.o.d" -MT "${OBJECTDIR}/LEDS.o.d" -MT ${OBJECTDIR}/LEDS.o -o ${OBJECTDIR}/LEDS.o LEDS.h 
	
${OBJECTDIR}/Long_Serial_In.o: Long_Serial_In.h  .generated_files/flags/default/dbf759555a6e1ea8bba358de7ce5513524371d38 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Long_Serial_In.o.d 
	@${RM} ${OBJECTDIR}/Long_Serial_In.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Long_Serial_In.o.d" -MT "${OBJECTDIR}/Long_Serial_In.o.d" -MT ${OBJECTDIR}/Long_Serial_In.o -o ${OBJECTDIR}/Long_Serial_In.o Long_Serial_In.h 
	
${OBJECTDIR}/OLED.o: OLED.h  .generated_files/flags/default/30d31f14a749677f899836c1668f0d0e10465e8c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/OLED.o.d" -MT "${OBJECTDIR}/OLED.o.d" -MT ${OBJECTDIR}/OLED.o -o ${OBJECTDIR}/OLED.o OLED.h 
	
${OBJECTDIR}/SDCard.o: SDCard.h  .generated_files/flags/default/ca3d326c690806af28f4f722f5957a58985b8b95 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SDCard.o.d 
	@${RM} ${OBJECTDIR}/SDCard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SDCard.o.d" -MT "${OBJECTDIR}/SDCard.o.d" -MT ${OBJECTDIR}/SDCard.o -o ${OBJECTDIR}/SDCard.o SDCard.h 
	
${OBJECTDIR}/SPI.o: SPI.h  .generated_files/flags/default/805d526765c0b71b3d16d98d9a8a03ba03cf8308 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI.o.d 
	@${RM} ${OBJECTDIR}/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SPI.o.d" -MT "${OBJECTDIR}/SPI.o.d" -MT ${OBJECTDIR}/SPI.o -o ${OBJECTDIR}/SPI.o SPI.h 
	
${OBJECTDIR}/SPI_CS.o: SPI_CS.h  .generated_files/flags/default/ddffad6c9b3baaee3516fcc2ade5f724b812c7de .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI_CS.o.d 
	@${RM} ${OBJECTDIR}/SPI_CS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SPI_CS.o.d" -MT "${OBJECTDIR}/SPI_CS.o.d" -MT ${OBJECTDIR}/SPI_CS.o -o ${OBJECTDIR}/SPI_CS.o SPI_CS.h 
	
${OBJECTDIR}/STA013_Config.o: STA013_Config.h  .generated_files/flags/default/f2ccd16dbad390985e3be5cdb16365956762d1e5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/STA013_Config.o.d 
	@${RM} ${OBJECTDIR}/STA013_Config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/STA013_Config.o.d" -MT "${OBJECTDIR}/STA013_Config.o.d" -MT ${OBJECTDIR}/STA013_Config.o -o ${OBJECTDIR}/STA013_Config.o STA013_Config.h 
	
${OBJECTDIR}/TWI.o: TWI.h  .generated_files/flags/default/619c1ccf2b396eafb186d63722cbb4dc3a0ceb80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TWI.o.d 
	@${RM} ${OBJECTDIR}/TWI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/TWI.o.d" -MT "${OBJECTDIR}/TWI.o.d" -MT ${OBJECTDIR}/TWI.o -o ${OBJECTDIR}/TWI.o TWI.h 
	
${OBJECTDIR}/Temperature_Sensor.o: Temperature_Sensor.h  .generated_files/flags/default/9af58acdc6b2e1e5c1034c226949c9ab63cf55fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Temperature_Sensor.o.d 
	@${RM} ${OBJECTDIR}/Temperature_Sensor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Temperature_Sensor.o.d" -MT "${OBJECTDIR}/Temperature_Sensor.o.d" -MT ${OBJECTDIR}/Temperature_Sensor.o -o ${OBJECTDIR}/Temperature_Sensor.o Temperature_Sensor.h 
	
${OBJECTDIR}/UART.o: UART.h  .generated_files/flags/default/897e1ed4fc197223944a6a84fa72334c081733a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/UART.o.d" -MT "${OBJECTDIR}/UART.o.d" -MT ${OBJECTDIR}/UART.o -o ${OBJECTDIR}/UART.o UART.h 
	
${OBJECTDIR}/UART_Print.o: UART_Print.h  .generated_files/flags/default/a7315a96c90fd4234ce6f41c840a5de0b171fcb7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_Print.o.d 
	@${RM} ${OBJECTDIR}/UART_Print.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/UART_Print.o.d" -MT "${OBJECTDIR}/UART_Print.o.d" -MT ${OBJECTDIR}/UART_Print.o -o ${OBJECTDIR}/UART_Print.o UART_Print.h 
	
${OBJECTDIR}/board.o: board.h  .generated_files/flags/default/741a356cf5b819e924c31c632f02ba11816e5efb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/board.o.d 
	@${RM} ${OBJECTDIR}/board.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/board.o.d" -MT "${OBJECTDIR}/board.o.d" -MT ${OBJECTDIR}/board.o -o ${OBJECTDIR}/board.o board.h 
	
${OBJECTDIR}/peripherals.o: peripherals.h  .generated_files/flags/default/c8c26281615752d09322837df1fe06f1583c4940 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/peripherals.o.d 
	@${RM} ${OBJECTDIR}/peripherals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/peripherals.o.d" -MT "${OBJECTDIR}/peripherals.o.d" -MT ${OBJECTDIR}/peripherals.o -o ${OBJECTDIR}/peripherals.o peripherals.h 
	
${OBJECTDIR}/print_memory.o: print_memory.h  .generated_files/flags/default/4a111cae75b545c7cd189545a0ecc2c389e1365a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/print_memory.o.d 
	@${RM} ${OBJECTDIR}/print_memory.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/print_memory.o.d" -MT "${OBJECTDIR}/print_memory.o.d" -MT ${OBJECTDIR}/print_memory.o -o ${OBJECTDIR}/print_memory.o print_memory.h 
	
${OBJECTDIR}/Directory_Functions.o: Directory_Functions.h  .generated_files/flags/default/cf516aaa23793802858bc98e8396928977344358 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Directory_Functions.o.d 
	@${RM} ${OBJECTDIR}/Directory_Functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Directory_Functions.o.d" -MT "${OBJECTDIR}/Directory_Functions.o.d" -MT ${OBJECTDIR}/Directory_Functions.o -o ${OBJECTDIR}/Directory_Functions.o Directory_Functions.h 
	
${OBJECTDIR}/Drive_Values.o: Drive_Values.h  .generated_files/flags/default/9a63a9d4847199fd63fd71f3d97ecbd6ed44f1b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Drive_Values.o.d 
	@${RM} ${OBJECTDIR}/Drive_Values.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Drive_Values.o.d" -MT "${OBJECTDIR}/Drive_Values.o.d" -MT ${OBJECTDIR}/Drive_Values.o -o ${OBJECTDIR}/Drive_Values.o Drive_Values.h 
	
${OBJECTDIR}/File_System.o: File_System.h  .generated_files/flags/default/940277f42591166874ec40d3a32101a21918fae5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/File_System.o.d 
	@${RM} ${OBJECTDIR}/File_System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/File_System.o.d" -MT "${OBJECTDIR}/File_System.o.d" -MT ${OBJECTDIR}/File_System.o -o ${OBJECTDIR}/File_System.o File_System.h 
	
${OBJECTDIR}/Read_Sector.o: Read_Sector.h  .generated_files/flags/default/9ca04003fa8c53efb670f60f8380afd0f7f4f47d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Read_Sector.o.d 
	@${RM} ${OBJECTDIR}/Read_Sector.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Read_Sector.o.d" -MT "${OBJECTDIR}/Read_Sector.o.d" -MT ${OBJECTDIR}/Read_Sector.o -o ${OBJECTDIR}/Read_Sector.o Read_Sector.h 
	
${OBJECTDIR}/Read_Values.o: Read_Values.h  .generated_files/flags/default/7677d1c3f516e28f60dc08396ce604272bf865f1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Read_Values.o.d 
	@${RM} ${OBJECTDIR}/Read_Values.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Read_Values.o.d" -MT "${OBJECTDIR}/Read_Values.o.d" -MT ${OBJECTDIR}/Read_Values.o -o ${OBJECTDIR}/Read_Values.o Read_Values.h 
	
${OBJECTDIR}/Play_Song.o: Play_Song.h  .generated_files/flags/default/aaa87338663336bf9fec9aa016ca31658769dce2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Play_Song.o.d 
	@${RM} ${OBJECTDIR}/Play_Song.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Play_Song.o.d" -MT "${OBJECTDIR}/Play_Song.o.d" -MT ${OBJECTDIR}/Play_Song.o -o ${OBJECTDIR}/Play_Song.o Play_Song.h 
	
${OBJECTDIR}/GPIO_Inputs.o: GPIO_Inputs.h  .generated_files/flags/default/c355a2e91bf66f67a819eb901f7a90a5acc29e8a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Inputs.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/GPIO_Inputs.o.d" -MT "${OBJECTDIR}/GPIO_Inputs.o.d" -MT ${OBJECTDIR}/GPIO_Inputs.o -o ${OBJECTDIR}/GPIO_Inputs.o GPIO_Inputs.h 
	
${OBJECTDIR}/Config_Arrays.o: Config_Arrays.c  .generated_files/flags/default/3b9985995e4488f73b210ada79be43248f814b39 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Config_Arrays.o.d 
	@${RM} ${OBJECTDIR}/Config_Arrays.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Config_Arrays.o.d" -MT "${OBJECTDIR}/Config_Arrays.o.d" -MT ${OBJECTDIR}/Config_Arrays.o -o ${OBJECTDIR}/Config_Arrays.o Config_Arrays.c 
	
${OBJECTDIR}/GPIO_Outputs.o: GPIO_Outputs.c  .generated_files/flags/default/a43c3f3a3f4ee928cb1fe05aa3bbbc81f9e71d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Outputs.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Outputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/GPIO_Outputs.o.d" -MT "${OBJECTDIR}/GPIO_Outputs.o.d" -MT ${OBJECTDIR}/GPIO_Outputs.o -o ${OBJECTDIR}/GPIO_Outputs.o GPIO_Outputs.c 
	
${OBJECTDIR}/LEDS.o: LEDS.c  .generated_files/flags/default/5de6bbe092411b82238de91488fbe5cf41058348 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LEDS.o.d 
	@${RM} ${OBJECTDIR}/LEDS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/LEDS.o.d" -MT "${OBJECTDIR}/LEDS.o.d" -MT ${OBJECTDIR}/LEDS.o -o ${OBJECTDIR}/LEDS.o LEDS.c 
	
${OBJECTDIR}/Long_Serial_In.o: Long_Serial_In.c  .generated_files/flags/default/5d19bc0b20e81c19772e9662e7613eedf7ed0e43 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Long_Serial_In.o.d 
	@${RM} ${OBJECTDIR}/Long_Serial_In.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Long_Serial_In.o.d" -MT "${OBJECTDIR}/Long_Serial_In.o.d" -MT ${OBJECTDIR}/Long_Serial_In.o -o ${OBJECTDIR}/Long_Serial_In.o Long_Serial_In.c 
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/flags/default/f2ef27ae98c0040b0cc596bee9262015f2c44b59 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/OLED.o.d" -MT "${OBJECTDIR}/OLED.o.d" -MT ${OBJECTDIR}/OLED.o -o ${OBJECTDIR}/OLED.o OLED.c 
	
${OBJECTDIR}/board.o: board.c  .generated_files/flags/default/ab8e5920450eecf068f300275187f5a39ef01d3b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/board.o.d 
	@${RM} ${OBJECTDIR}/board.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/board.o.d" -MT "${OBJECTDIR}/board.o.d" -MT ${OBJECTDIR}/board.o -o ${OBJECTDIR}/board.o board.c 
	
${OBJECTDIR}/OLED_Char_Map.o: OLED_Char_Map.c  .generated_files/flags/default/998ea296dccf3a08f3973965b72149141ab6b46d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED_Char_Map.o.d 
	@${RM} ${OBJECTDIR}/OLED_Char_Map.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/OLED_Char_Map.o.d" -MT "${OBJECTDIR}/OLED_Char_Map.o.d" -MT ${OBJECTDIR}/OLED_Char_Map.o -o ${OBJECTDIR}/OLED_Char_Map.o OLED_Char_Map.c 
	
${OBJECTDIR}/SDCard.o: SDCard.c  .generated_files/flags/default/84ddb5759db54cc151158008165732d91cc602fa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SDCard.o.d 
	@${RM} ${OBJECTDIR}/SDCard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SDCard.o.d" -MT "${OBJECTDIR}/SDCard.o.d" -MT ${OBJECTDIR}/SDCard.o -o ${OBJECTDIR}/SDCard.o SDCard.c 
	
${OBJECTDIR}/SPI.o: SPI.c  .generated_files/flags/default/bb0047a7d77a94ffe4ee9459e357b1961790e147 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI.o.d 
	@${RM} ${OBJECTDIR}/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SPI.o.d" -MT "${OBJECTDIR}/SPI.o.d" -MT ${OBJECTDIR}/SPI.o -o ${OBJECTDIR}/SPI.o SPI.c 
	
${OBJECTDIR}/SPI_CS.o: SPI_CS.c  .generated_files/flags/default/961b2e27288acbc3a66eaee9c1229f87d0fccdfc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI_CS.o.d 
	@${RM} ${OBJECTDIR}/SPI_CS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/SPI_CS.o.d" -MT "${OBJECTDIR}/SPI_CS.o.d" -MT ${OBJECTDIR}/SPI_CS.o -o ${OBJECTDIR}/SPI_CS.o SPI_CS.c 
	
${OBJECTDIR}/STA013_config.o: STA013_config.c  .generated_files/flags/default/98fd555ddfa82f6d5b8d107cb118f58e15b64a7a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/STA013_config.o.d 
	@${RM} ${OBJECTDIR}/STA013_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/STA013_config.o.d" -MT "${OBJECTDIR}/STA013_config.o.d" -MT ${OBJECTDIR}/STA013_config.o -o ${OBJECTDIR}/STA013_config.o STA013_config.c 
	
${OBJECTDIR}/TWI.o: TWI.c  .generated_files/flags/default/b67d37d1b72318dad561d33196f949a82dcef3f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TWI.o.d 
	@${RM} ${OBJECTDIR}/TWI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/TWI.o.d" -MT "${OBJECTDIR}/TWI.o.d" -MT ${OBJECTDIR}/TWI.o -o ${OBJECTDIR}/TWI.o TWI.c 
	
${OBJECTDIR}/Temperature_Sensor.o: Temperature_Sensor.c  .generated_files/flags/default/52724a062d016ef425754a43058000a21bb20c1e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Temperature_Sensor.o.d 
	@${RM} ${OBJECTDIR}/Temperature_Sensor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Temperature_Sensor.o.d" -MT "${OBJECTDIR}/Temperature_Sensor.o.d" -MT ${OBJECTDIR}/Temperature_Sensor.o -o ${OBJECTDIR}/Temperature_Sensor.o Temperature_Sensor.c 
	
${OBJECTDIR}/UART.o: UART.c  .generated_files/flags/default/befa1a9b9cd6b76919a9b8158544f73d2f6d4495 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/UART.o.d" -MT "${OBJECTDIR}/UART.o.d" -MT ${OBJECTDIR}/UART.o -o ${OBJECTDIR}/UART.o UART.c 
	
${OBJECTDIR}/UART_Print.o: UART_Print.c  .generated_files/flags/default/6c98522e00268ea7c9e7e60a0d7f3e6f7cb254c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_Print.o.d 
	@${RM} ${OBJECTDIR}/UART_Print.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/UART_Print.o.d" -MT "${OBJECTDIR}/UART_Print.o.d" -MT ${OBJECTDIR}/UART_Print.o -o ${OBJECTDIR}/UART_Print.o UART_Print.c 
	
${OBJECTDIR}/print_memory.o: print_memory.c  .generated_files/flags/default/1702a8105b3cdc4c0ff407f40d97701a7d7a250c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/print_memory.o.d 
	@${RM} ${OBJECTDIR}/print_memory.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/print_memory.o.d" -MT "${OBJECTDIR}/print_memory.o.d" -MT ${OBJECTDIR}/print_memory.o -o ${OBJECTDIR}/print_memory.o print_memory.c 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/9d4ad7b4c86629f220eff3da2b6c1bcf0ea93dd1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o -o ${OBJECTDIR}/main.o main.c 
	
${OBJECTDIR}/Directory_Functions.o: Directory_Functions.c  .generated_files/flags/default/ac7b7691f635515e215c1a4e2d82e1c93454e7ff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Directory_Functions.o.d 
	@${RM} ${OBJECTDIR}/Directory_Functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Directory_Functions.o.d" -MT "${OBJECTDIR}/Directory_Functions.o.d" -MT ${OBJECTDIR}/Directory_Functions.o -o ${OBJECTDIR}/Directory_Functions.o Directory_Functions.c 
	
${OBJECTDIR}/Drive_Values.o: Drive_Values.c  .generated_files/flags/default/a9cf40a055310dbc226259b68b895d0401c05d50 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Drive_Values.o.d 
	@${RM} ${OBJECTDIR}/Drive_Values.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Drive_Values.o.d" -MT "${OBJECTDIR}/Drive_Values.o.d" -MT ${OBJECTDIR}/Drive_Values.o -o ${OBJECTDIR}/Drive_Values.o Drive_Values.c 
	
${OBJECTDIR}/File_System.o: File_System.c  .generated_files/flags/default/d369238206219410a0c3d495507add913482e91e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/File_System.o.d 
	@${RM} ${OBJECTDIR}/File_System.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/File_System.o.d" -MT "${OBJECTDIR}/File_System.o.d" -MT ${OBJECTDIR}/File_System.o -o ${OBJECTDIR}/File_System.o File_System.c 
	
${OBJECTDIR}/Read_Sector.o: Read_Sector.c  .generated_files/flags/default/50c15762a693b880d3fb18d8bc07e292f4abea13 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Read_Sector.o.d 
	@${RM} ${OBJECTDIR}/Read_Sector.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Read_Sector.o.d" -MT "${OBJECTDIR}/Read_Sector.o.d" -MT ${OBJECTDIR}/Read_Sector.o -o ${OBJECTDIR}/Read_Sector.o Read_Sector.c 
	
${OBJECTDIR}/Read_Values.o: Read_Values.c  .generated_files/flags/default/54ed75d95acdcd757f58f2896512f8aca363c91d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Read_Values.o.d 
	@${RM} ${OBJECTDIR}/Read_Values.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Read_Values.o.d" -MT "${OBJECTDIR}/Read_Values.o.d" -MT ${OBJECTDIR}/Read_Values.o -o ${OBJECTDIR}/Read_Values.o Read_Values.c 
	
${OBJECTDIR}/Play_Song.o: Play_Song.c  .generated_files/flags/default/fcba0b29f8c0605d9f6724e62611f9835ccf3fc5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Play_Song.o.d 
	@${RM} ${OBJECTDIR}/Play_Song.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/Play_Song.o.d" -MT "${OBJECTDIR}/Play_Song.o.d" -MT ${OBJECTDIR}/Play_Song.o -o ${OBJECTDIR}/Play_Song.o Play_Song.c 
	
${OBJECTDIR}/GPIO_Inputs.o: GPIO_Inputs.c  .generated_files/flags/default/e8bf07bc9695b959500e579ab7e20f57b17ce1e5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPIO_Inputs.o.d 
	@${RM} ${OBJECTDIR}/GPIO_Inputs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/GPIO_Inputs.o.d" -MT "${OBJECTDIR}/GPIO_Inputs.o.d" -MT ${OBJECTDIR}/GPIO_Inputs.o -o ${OBJECTDIR}/GPIO_Inputs.o GPIO_Inputs.c 
	
${OBJECTDIR}/seos.o: seos.c  .generated_files/flags/default/885241e01d3070c8ddfc624651347ac675c8f125 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/seos.o.d 
	@${RM} ${OBJECTDIR}/seos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/seos.o.d" -MT "${OBJECTDIR}/seos.o.d" -MT ${OBJECTDIR}/seos.o -o ${OBJECTDIR}/seos.o seos.c 
	
${OBJECTDIR}/seos.o: seos.h  .generated_files/flags/default/c47ebcbf24411212a931a310c05ab9789f7d1182 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/seos.o.d 
	@${RM} ${OBJECTDIR}/seos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mno-const-data-in-progmem     -MD -MP -MF "${OBJECTDIR}/seos.o.d" -MT "${OBJECTDIR}/seos.o.d" -MT ${OBJECTDIR}/seos.o -o ${OBJECTDIR}/seos.o seos.h 
	
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
${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mno-const-data-in-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/MP3_Player_Example.X.${IMAGE_TYPE}.hex"
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
