cd /d %~dp0
mkdir "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include\GL"
copy include\GL "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include\GL"
copy lib "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib"
copy bin %windir%\SysWOW64
copy bin %windir%\system32
PAUSE