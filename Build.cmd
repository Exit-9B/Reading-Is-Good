@echo off

md "package\SkyrimSE"
md "package\SkyrimVR"

cmake --preset vs2019-windows --check-stamp-file "build/CMakeFiles/generate.stamp" || goto :error
cmake --build build --config Release || goto :error
cmake --install build --prefix "package/SkyrimSE" || goto :error

cmake --preset vs2019-windows-vr --check-stamp-file "buildVR/CMakeFiles/generate.stamp" || goto :error
cmake --build buildVR --config Release || goto :error
cmake --install buildVR --prefix "package/SkyrimVR" || goto :error

pushd package
pushd SkyrimSE
7z a -r -t7Z "..\Reading.Is.Good.7z"
popd
pushd SkyrimVR
7z a -r -t7Z "..\Reading.Is.Good.VR.7z"
popd
popd

goto :EOF

:error
exit /b %errorlevel%
