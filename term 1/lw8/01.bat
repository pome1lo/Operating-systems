@echo off
chcp 65001
echo Получение информации об оперативной памяти с помощью WMIC
wmic MEMORYCHIP get BankLabel, DeviceLocator, MemoryType, TypeDetail, Capacity, Speed
echo.
echo Получение информации об оперативной памяти с помощью PowerShell
powershell -Command "Get-CimInstance -ClassName Win32_PhysicalMemory | Format-Table Tag, Capacity, MemoryType, FormFactor, Manufacturer, PartNumber, SerialNumber -AutoSize"
echo.
echo Получение информации об оперативной памяти с помощью Systeminfo
systeminfo | findstr /C:"Total Physical Memory"
echo.
echo Получение информации об оперативной памяти с помощью Performance Monitor
echo На данный момент нет прямого способа получить информацию об оперативной памяти с помощью Performance Monitor через командную строку.
echo.

perfmon

pause