@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

pushd ..

set "NASM_DIR=%cd%\Scripts\nasm"
set "PERL_DIR=%cd%\Scripts\perl\perl\bin"

echo perl:%PERL%\perl.exe
echo nasm:%NASM%\nasm.exe

:: registry
set "PATH=%PATH%;%PERL_DIR%;%NASM_DIR%;"
popd

echo [%time%] Init openssl

pushd ..\Dependencies\openssl
set "OPENSSL_DIR=%cd%"
set "OPENSSL_GENERATEDIR=%OPENSSL_DIR%\generated"
echo openssl reposity path:%OPENSSL_DIR%
popd

:: 验证目录结构
if not exist "%OPENSSL_DIR%\Configure" (
    echo [错误] OpenSSL目录结构不完整
    echo 缺失关键文件：Configure
    exit /b 1
)

if not exist "%OPENSSL_DIR%\crypto" (
    echo [错误] OpenSSL目录结构不完整
    echo 缺失核心目录：crypto
    exit /b 1
)

:: 生成构建环境
pushd "%OPENSSL_DIR%"
perl Configure VC-WIN64A ^
    --prefix="%OPENSSL_GENERATEDIR%" ^
    --openssldir="%ROPENSSL_DIR%" ^
    no-asm no-shared

if %errorlevel% neq 0 (
    echo [错误] OpenSSL配置失败
    exit /b 1
)

perl util\mkdir-p.pl "%OPENSSL_GENERATEDIR%\include\openssl"
perl util\mkdir-p.pl "%OPENSSL_GENERATEDIR%\lib"

echo 预构建环境准备完成
popd


pause