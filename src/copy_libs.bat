
set CONFIG=%1

xcopy /Y %ICONV_DIR%\bin\*.dll ..\%CONFIG%
xcopy /Y %LIBXML2_DIR%\bin\*.dll ..\%CONFIG%