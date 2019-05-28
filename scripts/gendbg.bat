@echo off
echo Converting PDBs to MDBs

pushd..
set path=%CD%
popd

cd "%path%\Run\Data\Managed\"

"%path%\scripts\pdb2mdb" ./BlitzEngine.dll
"%path%\scripts\pdb2mdb" ./BlitzGame.dll
"%path%\scripts\pdb2mdb" ./Debug/BlitzEngine.dll
"%path%\scripts\pdb2mdb" ./Debug/BlitzGame.dll
echo Done