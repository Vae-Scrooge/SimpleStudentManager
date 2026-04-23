@echo off
rem SimpleStudentManager Push Script
D:
cd D:\My_code\Github_repository\personal\SimpleStudentManager
git config --global --add safe.directory "D:\My_code\Github_repository\personal\SimpleStudentManager"
D:\Git\bin\git.exe pull origin main --rebase
D:\Git\bin\git.exe push origin main
pause