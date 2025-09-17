#!/bin/bash

# Simple script to create a comprehensive document from all Java solutions
# This creates a text file that can be easily converted to Word format

echo "# DSA Questions - Complete Solutions Collection" > docs/AllSolutions.txt
echo "" >> docs/AllSolutions.txt
echo "Generated on: $(date)" >> docs/AllSolutions.txt
echo "Total Problems: 154 (66 Easy + 78 Medium + 10 Hard)" >> docs/AllSolutions.txt
echo "" >> docs/AllSolutions.txt
echo "===============================================" >> docs/AllSolutions.txt
echo "" >> docs/AllSolutions.txt

# Function to process Java files and extract content
process_directory() {
    local dir=$1
    local title=$2
    
    echo "" >> docs/AllSolutions.txt
    echo "## $title" >> docs/AllSolutions.txt
    echo "" >> docs/AllSolutions.txt
    
    if [ -d "src/$dir" ]; then
        for file in src/$dir/*.java; do
            if [ -f "$file" ]; then
                echo "Processing $file..."
                echo "" >> docs/AllSolutions.txt
                echo "### $(basename "$file" .java)" >> docs/AllSolutions.txt
                echo "" >> docs/AllSolutions.txt
                
                # Extract problem description from comments
                grep -A 5 "Problem.*:" "$file" | head -5 >> docs/AllSolutions.txt
                echo "" >> docs/AllSolutions.txt
                
                # Add full file content
                echo "\`\`\`java" >> docs/AllSolutions.txt
                cat "$file" >> docs/AllSolutions.txt
                echo "\`\`\`" >> docs/AllSolutions.txt
                echo "" >> docs/AllSolutions.txt
                echo "---" >> docs/AllSolutions.txt
                echo "" >> docs/AllSolutions.txt
            fi
        done
    else
        echo "*No problems implemented in $dir yet*" >> docs/AllSolutions.txt
        echo "" >> docs/AllSolutions.txt
    fi
}

# Process each difficulty level
process_directory "easy" "EASY PROBLEMS (66)"
process_directory "medium" "MEDIUM PROBLEMS (78)" 
process_directory "hard" "HARD PROBLEMS (10)"

echo "" >> docs/AllSolutions.txt
echo "===============================================" >> docs/AllSolutions.txt
echo "End of Document" >> docs/AllSolutions.txt
echo "" >> docs/AllSolutions.txt

echo "Document generated: docs/AllSolutions.txt"
echo "You can convert this to Word format using any text-to-Word converter or copy-paste into Word."