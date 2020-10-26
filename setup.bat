@echo off

@REM clone submodules
git submodule update --init --recursive

@REM build thirdparty
cd .\thirdparty\fake_unity_shader

.\setup.bat

pause