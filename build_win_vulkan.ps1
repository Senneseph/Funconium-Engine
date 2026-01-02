<#
Funconium Engine Windows Vulkan Demo Build Script
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

# Compiler and linker settings
$compilerFlags = "/nologo", "/W4", "/O2", "/std:c17", "/D_WIN32", "/D_WINDOWS", "/DWIN32_LEAN_AND_MEAN"
$includePaths = "/I`"src/demo/core`"", "/I`"src/demo/win`""
$linkerFlags = "/SUBSYSTEM:CONSOLE", "/MACHINE:x64"

# Source files to compile
$sources = @(
    "src/demo/core/demo_core.c",
    "src/demo/win/demo.c",
    "src/demo/win/asset_loader.c",
    "src/demo/win/timing.c",
    "src/demo/win/logger.c",
    "src/demo/win/vulkan_wrapper.c",
    "src/demo/win/main.c"
)

# Object files
$objectFiles = @()

# Compile each source file
Write-Host "Compiling source files..."
foreach ($source in $sources) {
    $sourceName = [System.IO.Path]::GetFileName($source)
    $objectFile = Join-Path -Path $buildDir -ChildPath ($sourceName -replace '\.c$', '.obj')
    
    Write-Host "Compiling $sourceName..."
    
    $compileCommand = @(
        "cl.exe",
        $compilerFlags,
        $includePaths,
        "/c",
        "`"$source`"",
        "/Fo:`"$objectFile`""
    )
    
    $process = Start-Process -FilePath "cl.exe" -ArgumentList ($compileCommand -join " ") -NoNewWindow -Wait -PassThru
    
    if ($process.ExitCode -ne 0) {
        Write-Host "Error compiling $sourceName" -ForegroundColor Red
        exit 1
    }
    
    $objectFiles += "`"$objectFile`""
}

# Link all object files
Write-Host "Linking executable..."
$linkCommand = @(
    "link.exe",
    $linkerFlags,
    "/OUT:`"$buildDir\funconium_demo_win_vulkan.exe`"",
    $objectFiles,
    "user32.lib",
    "gdi32.lib"
)

$process = Start-Process -FilePath "link.exe" -ArgumentList ($linkCommand -join " ") -NoNewWindow -Wait -PassThru

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