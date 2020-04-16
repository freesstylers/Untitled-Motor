SET ogreMediaTarget="%~1\assets\ogre\Media"
SET ogreTestsMediaTarget="%~1\assets\ogre\Tests\Media"

xcopy ..\dependencies\ogre-1.12.4\Media %ogreMediaTarget% /s /e /y /i
xcopy ..\dependencies\ogre-1.12.4\Tests\Media %ogreTestsMediaTarget% /s /e /y /i

for /r ..\dependencies\ogre-1.12.4\Build\bin\debug\ %%f in (*.dll) do @copy "%%f" %1%
for /r ..\dependencies\ogre-1.12.4\Build\bin\release\ %%f in (*.dll) do @copy "%%f" %1%
for /r ..\dependencies\SDL2-2.0.10\lib\x64 %%f in (*.dll) do @copy "%%f" %1%
for /r ..\dependencies\fmod-2.00.07\ %%f in (*.dll) do @copy "%%f" %1%
for /r ..\dependencies\bullet3-2.89\build\lib %%f in (*.dll) do @copy "%%f" %1%
for /r ..\dependencies\cegui-0.8.7\build\bin\ %%f in (*.dll) do @copy "%%f" %1%
for /r ..\dependencies\cegui-0.8.7\dependencies\bin %%f in (*.dll) do @copy "%%f" %1%