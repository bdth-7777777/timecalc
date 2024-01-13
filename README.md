# timecalc
Calc the exact time in the command line\在命令行当中计算精确的时间（毫秒）
for example:

bat 

@echo off
set starttime=%time%

rem your_command

set endtime=%time%

timecalc -start %starttime% -end %endtime%

即可输出 13:45:67.89 格式的时间
