mkdir deploy
del /S /Q deploy\*
del deploy\gameJam1.exe
copy build-gameJam1-Desktop_Qt_5_15_2_MinGW_64_bit-Release\release\gameJam1.exe deploy
copy build-gameJam1-Desktop_Qt_5_15_2_MinGW_64_bit-Release\release\data deploy\data
C:\Qt\5.15.2\mingw81_64\bin\windeployqt --no-translations  deploy\gameJam1.exe
