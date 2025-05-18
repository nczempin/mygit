#!/usr/bin/env bash

# Build, lint, test, and run the artifact

# Run C++ linter if available
if command -v cpplint >/dev/null 2>&1; then
  echo "Running cpplint..."
  cpplint src/*.cpp src/*.h || true
else
  echo "cpplint not found; skipping lint."
fi

# Build the project
echo "Building project..."
if ! make; then
  echo "Build failed." >&2
  exit 1
fi

# Run tests if a test directory exists
if [ -d tests ]; then
  echo "Running tests..."
  if command -v pytest >/dev/null 2>&1; then
    pytest || echo "Tests failed." >&2
  else
    echo "pytest not found; skipping tests." >&2
  fi
else
  echo "No tests to run."
fi

# Execute the resulting binary if it exists
if [ -x ./mygit ]; then
  echo "Running artifact..."
  ./mygit --help || true
elif [ -f ./mygit.exe ]; then
  echo "Running artifact..."
  ./mygit.exe --help || true
else
  echo "Built artifact not found."
fi
