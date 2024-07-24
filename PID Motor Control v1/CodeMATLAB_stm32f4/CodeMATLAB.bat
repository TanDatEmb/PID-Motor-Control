echo off

REM Always run this script file from the folder where the makefile resides.
REM Do not forget to update "WaijungRoot" to Waijung's root directory.
set WaijungRoot=C:\Users\tanda\OneDrive\Desktop\waijung18_11a\waijung_18.11a
set WaijungGnuArmPath=C:\Users\tanda\OneDrive\Desktop\waijung18_11a\waijung_18.11a\utils\gnu_tools_arm_embedded\bin

echo on
REM Check which toolchain is used
"%WaijungGnuArmPath%\arm-none-eabi-gcc" --version

"%WaijungRoot%\utils\gnumake382-w32\gnumake382-w32" -f CodeMATLAB.mk 
REM "%WaijungRoot%\utils\gnumake382-w32\gnumake382-w32" -f CodeMATLAB.mk clean-obj

