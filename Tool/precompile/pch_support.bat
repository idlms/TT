@echo off

@where python >NUL 2>&1
@if %ERRORLEVEL% EQU 0 (
    @where pch51.py >NUL 2>&1
    @if %ERRORLEVEL% EQU 0 (
        python -m build_tool.precompile.pch51 --support "ON" --user_option "ON" --target %1 --uv_file %2 --scaler_type %3 --keil_root %4
        exit 0
    )
)

@if exist ".\Tool\precompile\pch_support.exe" (
    .\Tool\precompile\pch_support.exe --support "OFF" --target %1 --uv_file %2 --scaler_type %3 --keil_root %4
    exit 0
)
