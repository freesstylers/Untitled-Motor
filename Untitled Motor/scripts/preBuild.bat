for /r ..\dependencies\ogre-1.12.4\Build\bin\ %%f in (*.dll) do @copy "%%f" ..\bin\
for /r ..\dependencies\SDL2-2.0.10\lib\x64 %%f in (*.dll) do @copy "%%f" ..\bin\
