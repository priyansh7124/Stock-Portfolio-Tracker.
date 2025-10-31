@echo off
echo Building Stock Portfolio Tracker for deployment...

:: Clean previous builds
if exist "dist" rmdir /s /q dist
mkdir dist

:: Compile release version
echo Compiling optimized release version...
g++ -std=c++17 -O3 -DNDEBUG -static-libgcc -static-libstdc++ -o dist/portfolio_tracker.exe main.cpp Stock.cpp Transaction.cpp Portfolio.cpp

:: Copy documentation
copy README.md dist\
copy Makefile dist\

:: Create startup script
echo @echo off > dist\run.bat
echo echo Welcome to Stock Portfolio Tracker! >> dist\run.bat
echo echo. >> dist\run.bat
echo portfolio_tracker.exe >> dist\run.bat
echo pause >> dist\run.bat

echo.
echo Deployment package created in 'dist' folder!
echo Ready for distribution.
