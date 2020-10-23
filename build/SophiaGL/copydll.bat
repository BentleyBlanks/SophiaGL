@echo off

set dllPath=..\..\SophiaGL\thirdparty\fake_unity_shader\fake_unity_shader\ShaderConductor\Build\vs2019-win-vc142-x64\Bin\

@REM Copy ShaderConductor dll
set debug_dll0=%dllPath%Debug\dxcompiler.dll
set debug_dll1=%dllPath%Debug\ShaderConductor.dll
set debug_dll2=%dllPath%Debug\ShaderConductorWrapper.dll

set release_dll0=%dllPath%Release\dxcompiler.dll
set release_dll1=%dllPath%Release\ShaderConductor.dll
set release_dll2=%dllPath%Release\ShaderConductorWrapper.dll

copy %debug_dll0% ..\..\bin\debug\
copy %debug_dll1% ..\..\bin\debug\
copy %debug_dll2% ..\..\bin\debug\

copy %release_dll0% ..\..\bin\release\
copy %release_dll1% ..\..\bin\release\
copy %release_dll2% ..\..\bin\release\

pause