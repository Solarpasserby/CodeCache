@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

:: 设置工作目录
set "inputDir=D:\IT\Source\CodeCache\src\sduoj\Data Structures\Course Design\A01\P01-testset"
set "outputDir=D:\IT\Source\CodeCache\src\sduoj\Data Structures\Course Design\A01\P01-output"
set "programPath=D:\IT\Source\CodeCache\build\P01-skiplist.exe"

:: 确保输出目录存在
if not exist "%outputDir%" mkdir "%outputDir%"

:: 切换到输入文件目录
cd /d "%inputDir%"

:: 遍历输入文件目录中的所有输入文件
for %%i in (input_*.txt) do (
    echo 正在处理文件: %%i

    :: 提取文件名（不包括扩展名）
    set "filename=%%~ni"
    set "outputFile=%outputDir%\!filename!.out"

    :: 运行程序并生成输出文件
    "%programPath%" < "%%i" > "!outputFile!"

    :: 提取对应的比较文件名
    set "compareFile=!filename:input_=output_!.txt"

    :: 比较生成的输出文件与对应的比较文件
    fc "!outputFile!" "!compareFile!" > "%outputDir%\!filename!.diff"

    :: 检查比较结果
    if errorlevel 1 (
        echo 文件 %%i 的输出与已有文件 !compareFile! 不同，差异已保存到 !filename!.diff
    ) else (
        echo 文件 %%i 的输出与已有文件 !compareFile! 相同
    )
)

echo 所有文件处理完成。
pause
endlocal