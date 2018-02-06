CALL "%VS120COMNTOOLS%vsvars32.bat"

pushd "%~dp0"

SET PATH=D:\Qt\Qt5.6.2\5.6\msvc2013\bin;%PATH%
SET QTDIR=D:\Qt\Qt5.6.2\5.6\msvc2013
SET QMAKESPEC=D:\Qt\Qt5.6.2\5.6\msvc2013\mkspecs\win32-msvc2013

qmake -tp vc -r QtLogUtil.pro


popd