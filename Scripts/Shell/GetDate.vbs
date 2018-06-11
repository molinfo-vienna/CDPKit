Set wmi_service = GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\cimv2")
Set items = wmi_service.ExecQuery("Select * from Win32_UTCTime")

For Each item in items
    Wscript.Echo item.Year & Right("0" & item.Month, 2) & Right("0" & item.Day, 2)
    Exit For
Next
