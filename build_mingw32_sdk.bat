
set VERSION=0.5.0

set BUNDLE_DIR=..\libxmlmm-%VERSION%

rmdir /s /q %BUNDLE_DIR%

mkdir %BUNDLE_DIR%
mkdir %BUNDLE_DIR%\bin
mkdir %BUNDLE_DIR%\include
mkdir %BUNDLE_DIR%\include\libxmlmm
mkdir %BUNDLE_DIR%\apidoc
mkdir %BUNDLE_DIR%\apidoc\html

copy include\libxmlmm\*.h %BUNDLE_DIR%\include\libxmlmm
copy bin\*.dll %BUNDLE_DIR%\bin
xcopy apidoc\html %BUNDLE_DIR%\apidoc\html

