sc stop BlueScreenOnce
sc delete BlueScreenOnce
takeown /f C:\Windows\System32\drivers\BlueScreenOnce.sys
icacls C:\Windows\System32\drivers\BlueScreenOnce.sys /grant Administrators:F
del /Q /F C:\Windows\System32\drivers\BlueScreenOnce.sys
