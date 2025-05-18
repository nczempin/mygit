#!/usr/bin/env pwsh

# Build, lint, test, and run the artifact

# Run C++ linter if available
if (Get-Command cpplint -ErrorAction SilentlyContinue) {
    Write-Host "Running cpplint..."
    cpplint src/*.cpp src/*.h | Out-Default
} else {
    Write-Host "cpplint not found; skipping lint."
}

# Build the project
Write-Host "Building project..."
try {
    make
} catch {
    Write-Error "Build failed."
    exit 1
}

# Run tests if a test directory exists
if (Test-Path tests) {
    Write-Host "Running tests..."
    if (Get-Command pytest -ErrorAction SilentlyContinue) {
        try {
            pytest | Out-Default
        } catch {
            Write-Warning "Tests failed."
        }
    } else {
        Write-Host "pytest not found; skipping tests."
    }
} else {
    Write-Host "No tests to run."
}

# Execute the resulting binary if it exists
if (Test-Path ./mygit) {
    Write-Host "Running artifact..."
    ./mygit --help
} elseif (Test-Path ./mygit.exe) {
    Write-Host "Running artifact..."
    ./mygit.exe --help
} else {
    Write-Host "Built artifact not found."
}
