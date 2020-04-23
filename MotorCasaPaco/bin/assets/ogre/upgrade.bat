@ECHO OFF
set /p folder=Dame la carpeta con los .mesh (dejalo vacio si es esta):

break > UpgradeLog.txt

set files=%folder%*.mesh

echo Buscando %files%...

for %%f in (%files%) do (
	echo %%f
	OgreMeshUpgrader.exe %%f >> UpgradeLog.txt 2>&1
)
PAUSE