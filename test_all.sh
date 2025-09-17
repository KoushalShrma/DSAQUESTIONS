#!/bin/bash

# Comprehensive test script for all DSA solutions
echo "🚀 Testing all DSA solutions..."
echo "================================="

# Function to test Java files in a directory
test_directory() {
    local dir=$1
    local title=$2
    
    echo ""
    echo "Testing $title..."
    echo "-------------------"
    
    if [ -d "src/$dir" ]; then
        cd "src/$dir"
        
        for file in *.java; do
            if [ -f "$file" ]; then
                echo "📁 Testing $file..."
                
                # Compile
                if javac "$file"; then
                    echo "✅ Compilation successful"
                    
                    # Run (extract class name)
                    class_name=$(basename "$file" .java)
                    if java "$class_name"; then
                        echo "✅ Execution successful"
                    else
                        echo "❌ Execution failed"
                    fi
                else
                    echo "❌ Compilation failed"
                fi
                echo ""
            fi
        done
        
        # Clean up class files
        rm -f *.class
        cd "../.."
    else
        echo "⚠️  Directory $dir not found"
    fi
}

# Test each difficulty level
test_directory "easy" "EASY PROBLEMS"
test_directory "medium" "MEDIUM PROBLEMS" 
test_directory "hard" "HARD PROBLEMS"

echo "================================="
echo "🎯 Testing completed!"
echo ""
echo "📊 Summary:"
echo "- Easy problems: $(ls src/easy/*.java 2>/dev/null | wc -l) files"
echo "- Medium problems: $(ls src/medium/*.java 2>/dev/null | wc -l) files"
echo "- Hard problems: $(ls src/hard/*.java 2>/dev/null | wc -l) files"
echo "- Total: $(($(ls src/easy/*.java 2>/dev/null | wc -l) + $(ls src/medium/*.java 2>/dev/null | wc -l) + $(ls src/hard/*.java 2>/dev/null | wc -l))) Java files"