src = ./src
inc = ./inc
src_files = ${notdir ${wildcard ${src}/*.c}}
inc_files = ${notdir ${wildcard ${inc}/*.h}}

cspec = ./cspec
cspec_src = ${cspec}/src
cspec_inc = ${cspec}/inc
cspec_src_files = ${notdir ${wildcard ${cspec_src}/*.c}}
cspec_inc_files = ${notdir ${wildcard ${cspec_inc}/*.h}}

test = ./test
test_src = ${test}/src
test_inc = ${test}/inc
test_src_files = ${notdir ${wildcard ${test_src}/*.c}}
test_inc_files = ${notdir ${wildcard ${test_inc}/*.h}}

INCLUDES = -I. -I${SIMAVR_HOME}/simavr/sim/avr -I${inc} -I${cspec_inc} -I${test_inc}
VPATH = . ${src} ${inc} ${cspec_src} ${cspec_inc} ${test_src} ${test_inc}

.PHONY: all

all: main.hex

main.axf: ${src_files} ${inc_files} ${cspec_src_files} ${cspec_inc_files} ${test_src_files} ${test_inc_files}

# The code is compiled "optimized" to the max.
# 
# The weird "-Wl,--undefined=_mmcu,--section-start=.mmcu=0x910000"
# is used to tell the linker not to discard the .mmcu section,
# otherwise the --gc-sections will delete it.

%.hex: %.axf
	@avr-objcopy -j .text -j .data -j .eeprom -O ihex ${<} ${@}

%.s: %.axf
	@avr-objdump -j .text -j .data -j .bss -d  ${<} > ${@}

# --mcall-prologues can be used here, but messes up debugging a little
%.axf: %.c 
	@echo AVR-CC ${<}
	@avr-gcc -Wall -gdwarf-2 -Os -std=gnu99 \
			-mmcu=atmega328p \
			-DF_CPU=8000000 \
			-fno-inline-small-functions \
			-ffunction-sections -fdata-sections \
			-Wl,--relax,--gc-sections \
			-Wl,--undefined=_mmcu,--section-start=.mmcu=0x910000 \
			${INCLUDES}\
			${^} -o ${@}
	@avr-size ${@}|sed '1d'
