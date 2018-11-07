set PATH_ST_LINK=C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\
set PATH_ARM_EABI=C:\Program Files (x86)\GNU Tools ARM Embedded\7 2017-q4-major\bin\
set NAME_FILE=modbus_project
set NAME_TOOL=GNU-ARM
set NAME_SETTING=Debug

cd %CD%\dist\%NAME_SETTING%\%NAME_TOOL%-Windows\

set ERROR_SCRIPT=%ERRORLEVEL%

if %ERROR_SCRIPT% neq 0 set NAME_SETTING=Release
if %ERROR_SCRIPT% neq 0 cd %CD%\dist\%NAME_SETTING%\%NAME_TOOL%-Windows\

"%PATH_ARM_EABI%arm-none-eabi-readelf.exe" -S %NAME_FILE%.elf
"%PATH_ARM_EABI%arm-none-eabi-objcopy.exe" -Oihex %NAME_FILE%.elf %NAME_FILE%.hex
"%PATH_ARM_EABI%arm-none-eabi-objcopy.exe" -Obinary %NAME_FILE%.elf %NAME_FILE%.bin

"%PATH_ST_LINK%ST-LINK_CLI.exe" -c SWD UR freq=1000 -P %NAME_FILE%.hex -V -Rst