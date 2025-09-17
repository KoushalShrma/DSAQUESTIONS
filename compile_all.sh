#!/bin/bash

# Compilation script for all DSA solutions
echo "🔨 Compiling all DSA solutions..."
echo "================================="

compile_directory() {
    local dir=$1
    local title=$2
    
    echo ""
    echo "Compiling $title..."
    echo "-------------------"
    
    if [ -d "src/$dir" ]; then
        cd "src/$dir"
        
        for file in *.java; do
            if [ -f "$file" ]; then
                echo "🔨 Compiling $file..."
                if javac "$file"; then
                    echo "✅ Compiled successfully"
                else
                    echo "❌ Compilation failed"
                fi
            fi
        done
        
        cd "../.."
    else
        echo "⚠️  Directory $dir not found"
    fi
}

# Compile each difficulty level
compile_directory "easy" "EASY PROBLEMS"
compile_directory "medium" "MEDIUM PROBLEMS"
compile_directory "hard" "HARD PROBLEMS"
compile_directory "utils" "UTILITIES"

echo ""
echo "================================="
echo "🎯 Compilation completed!"
echo ""
echo "📋 To run a specific solution:"
echo "   cd src/easy && java TwoSum"
echo "   cd src/medium && java MaximumSubarray"
echo "   cd src/hard && java TrappingRainWater"