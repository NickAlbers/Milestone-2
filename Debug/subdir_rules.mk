################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
altitudeMonitor.obj: ../altitudeMonitor.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="P:/Courses/ENCE361/StellarisWare" --include_path="P:/Courses/ENCE361/StellarisWare/utils" --include_path="P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="altitudeMonitor.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

circBuf.obj: ../circBuf.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="P:/Courses/ENCE361/StellarisWare" --include_path="P:/Courses/ENCE361/StellarisWare/utils" --include_path="P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="circBuf.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="P:/Courses/ENCE361/StellarisWare" --include_path="P:/Courses/ENCE361/StellarisWare/utils" --include_path="P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pwmOutput.obj: ../pwmOutput.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="P:/Courses/ENCE361/StellarisWare" --include_path="P:/Courses/ENCE361/StellarisWare/utils" --include_path="P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="pwmOutput.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

quadDecoder.obj: ../quadDecoder.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="P:/Courses/ENCE361/StellarisWare" --include_path="P:/Courses/ENCE361/StellarisWare/utils" --include_path="P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="quadDecoder.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rit128x96x4.obj: P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968/drivers/rit128x96x4.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="P:/Courses/ENCE361/StellarisWare" --include_path="P:/Courses/ENCE361/StellarisWare/utils" --include_path="P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="rit128x96x4.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="P:/Courses/ENCE361/StellarisWare" --include_path="P:/Courses/ENCE361/StellarisWare/utils" --include_path="P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ustdlib.obj: P:/Courses/ENCE361/StellarisWare/utils/ustdlib.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="D:/Programs/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="P:/Courses/ENCE361/StellarisWare" --include_path="P:/Courses/ENCE361/StellarisWare/utils" --include_path="P:/Courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="ustdlib.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


