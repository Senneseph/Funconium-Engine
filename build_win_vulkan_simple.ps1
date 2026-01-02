<#
Simple Funconium Engine Windows Vulkan Demo Build Script
This PowerShell script builds the Windows demo with Vulkan support
#>

Write-Host "Building Funconium Engine Windows Vulkan Demo..."
Write-Host "================================================"

# Set up build directory
$buildDir = "build_win_vulkan"
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# Check for required tools
try {
    $clPath = (Get-Command cl.exe -ErrorAction Stop).Source
    Write-Host "Found MSVC compiler: $clPath"
} catch {
    Write-Host "Error: Microsoft Visual C++ compiler (cl.exe) not found in PATH" -ForegroundColor Red
    Write-Host "Please ensure you have Visual Studio with C++ development tools installed"
    Write-Host "and run this script from a 'Developer Command Prompt for VS'"
    exit 1
}

# Compile all source files with a single command
Write-Host "Compiling source files..."

# Build the compile command as a single string
$compileCommand = "cl.exe /nologo /W4 /O2 /std:c17 /D_WIN32 /D_WINDOWS /DWIN32_LEAN_AND_MEAN /I`"src/demo/core`" /I`"src/demo/win`" /c src/demo/core/demo_core.c /Fo:`"$buildDir\demo_core.obj`" src/demo/win/demo.c /Fo:`"$buildDir\demo.obj`" src/demo/win/asset_loader.c /Fo:`"$buildDir\asset_loader.obj`" src/demo/win/timing.c /Fo:`"$buildDir\timing.obj`" src/demo/win/logger.c /Fo:`"$buildDir\logger.obj`" src/demo/win/vulkan_wrapper.c /Fo:`"$buildDir\vulkan_wrapper.obj`" src/demo/win/main.c /Fo:`"$buildDir\main.obj`""

# Execute the compile command
$process = Start-Process -FilePath "cmd.exe" -ArgumentList "/c $compileCommand" -NoNewWindow -Wait -PassThru

if ($process.ExitCode -ne 0) {
    Write-Host "Error compiling source files" -ForegroundColor Red
    exit 1
}

# Link all object files
Write-Host "Linking executable..."

$linkCommand = "link.exe /SUBSYSTEM:CONSOLE /MACHINE:x64 /OUT:`"$buildDir\funconium_demo_win_vulkan.exe`" `$buildDir\demo_core.obj` `$buildDir\demo.obj` `$buildDir\asset_loader.obj` `$buildDir\timing.obj` `$buildDir\logger.obj` `$buildDir\vulkan_wrapper.obj` `$buildDir\main.obj` user32.lib gdi32.lib"

$process = Start-Process -FilePath "cmd.exe" -ArgumentList "/c $linkCommand" -NoNewWindow -Wait -PassThru

if ($process.ExitCode -ne 0) {
    Write-Host "Error linking executable" -ForegroundColor Red
    exit 1
}

# Copy resources if they exist
if (Test-Path "resources") {
    Write-Host "Copying resources..."
    Copy-Item -Path "resources" -Destination "$buildDir\resources" -Recurse -Force
}

Write-Host "Build completed successfully!" -ForegroundColor Green
Write-Host "Output: $buildDir\funconium_demo_win_vulkan.exe"

Write-Host "`nBuild summary:"
Write-Host "- Target: Windows Vulkan Demo"
Write-Host "- Output directory: $buildDir"
Write-Host "- Executable: funconium_demo_win_vulkan.exe"
Write-Host "- Build time: $(Get-Date -Format 'HH:mm:ss')"

Write-Host "`nTo run the demo:"
Write-Host "  cd $buildDir"
Write-Host "  .\funconium_demo_win_vulkan.exe"