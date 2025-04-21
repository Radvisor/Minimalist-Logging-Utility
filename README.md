# Minimalist-Logging-Utility
This is a small debugging utility I wrote to log activities inside of my PoC code.

This can be very useful when you need to monitor what's happpening inside of your code in a context where
you can't use any utilities provided by the user graphical interface or the runtime library (for instance)
when the execution flow is serialized.
This happens when loading a DLL, so the code executing inside of DllMain shouldn't attempt to call any
user32.dll or msvcrxxx.dll export because this would cause a race condition.
However, this code calls only kernel32.dll exports which are fine in this context.

For more informations check:
- https://learn.microsoft.com/fr-fr/windows/win32/dlls/dynamic-link-library-best-practices
