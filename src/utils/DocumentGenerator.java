import java.io.*;
import java.nio.file.*;
import java.util.*;

/**
 * Utility class to extract content from Java solution files and format them for documentation
 */
public class DocumentGenerator {
    
    public static void main(String[] args) {
        try {
            generateMarkdownDocument();
            System.out.println("Documentation generated successfully!");
        } catch (Exception e) {
            System.err.println("Error generating documentation: " + e.getMessage());
            e.printStackTrace();
        }
    }
    
    /**
     * Generate a comprehensive markdown document from all solution files
     */
    public static void generateMarkdownDocument() throws IOException {
        StringBuilder markdown = new StringBuilder();
        
        // Add header
        markdown.append("# Complete DSA Solutions Collection\n\n");
        markdown.append("This document contains all 154 DSA problems with multiple solution approaches.\n\n");
        markdown.append("## Table of Contents\n");
        markdown.append("- [Easy Problems (66)](#easy-problems)\n");
        markdown.append("- [Medium Problems (78)](#medium-problems)\n");
        markdown.append("- [Hard Problems (10)](#hard-problems)\n\n");
        
        // Process each difficulty level
        processDirectory("easy", "Easy Problems", markdown);
        processDirectory("medium", "Medium Problems", markdown);
        processDirectory("hard", "Hard Problems", markdown);
        
        // Write to file
        Path outputPath = Paths.get("docs/AllSolutions.md");
        Files.createDirectories(outputPath.getParent());
        Files.write(outputPath, markdown.toString().getBytes());
        
        System.out.println("Generated markdown file: " + outputPath.toAbsolutePath());
    }
    
    /**
     * Process all Java files in a directory and extract their content
     */
    private static void processDirectory(String directory, String title, StringBuilder markdown) throws IOException {
        markdown.append("## ").append(title).append("\n\n");
        
        Path dirPath = Paths.get("src/" + directory);
        if (!Files.exists(dirPath)) {
            markdown.append("*No problems implemented yet*\n\n");
            return;
        }
        
        // Get all Java files in directory
        try (var stream = Files.list(dirPath)) {
            stream.filter(path -> path.toString().endsWith(".java"))
                  .sorted()
                  .forEach(path -> {
                      try {
                          processJavaFile(path, markdown);
                      } catch (IOException e) {
                          System.err.println("Error processing file: " + path);
                      }
                  });
        }
    }
    
    /**
     * Extract and format content from a single Java file
     */
    private static void processJavaFile(Path filePath, StringBuilder markdown) throws IOException {
        String content = Files.readString(filePath);
        String fileName = filePath.getFileName().toString().replace(".java", "");
        
        // Extract problem name and description from comments
        String[] lines = content.split("\n");
        String problemName = "";
        String problemDescription = "";
        
        // Find problem info in header comments
        for (int i = 0; i < Math.min(10, lines.length); i++) {
            String line = lines[i].trim();
            if (line.startsWith("* Problem") && line.contains(":")) {
                problemName = line.substring(line.indexOf(":") + 1).trim();
            } else if (line.startsWith("* Given") || line.startsWith("* Determine") || 
                      line.startsWith("* Find") || line.startsWith("* Return")) {
                problemDescription = line.substring(1).trim();
                break;
            }
        }
        
        if (problemName.isEmpty()) {
            problemName = fileName.replaceAll("([A-Z])", " $1").trim();
        }
        
        markdown.append("### ").append(problemName).append("\n\n");
        
        if (!problemDescription.isEmpty()) {
            markdown.append("**Problem:** ").append(problemDescription).append("\n\n");
        }
        
        // Extract and format each approach
        extractApproach(content, "BRUTE FORCE APPROACH", markdown);
        extractApproach(content, "BETTER APPROACH", markdown);
        extractApproach(content, "OPTIMAL APPROACH", markdown);
        
        markdown.append("---\n\n");
    }
    
    /**
     * Extract a specific approach from the Java content
     */
    private static void extractApproach(String content, String approachName, StringBuilder markdown) {
        int startIndex = content.indexOf(approachName);
        if (startIndex == -1) return;
        
        // Find the method that follows this approach
        int methodStart = content.indexOf("public", startIndex);
        if (methodStart == -1) return;
        
        // Find the end of this method
        int braceCount = 0;
        int methodEnd = methodStart;
        boolean inMethod = false;
        
        for (int i = methodStart; i < content.length(); i++) {
            char c = content.charAt(i);
            if (c == '{') {
                braceCount++;
                inMethod = true;
            } else if (c == '}') {
                braceCount--;
                if (inMethod && braceCount == 0) {
                    methodEnd = i + 1;
                    break;
                }
            }
        }
        
        String approachContent = content.substring(startIndex, methodEnd);
        
        // Extract explanation from comments
        String explanation = extractExplanation(approachContent);
        String complexity = extractComplexity(approachContent);
        String code = extractCode(approachContent);
        
        // Format approach section
        markdown.append("#### ").append(formatApproachName(approachName)).append("\n\n");
        
        if (!explanation.isEmpty()) {
            markdown.append("**Explanation:**\n").append(explanation).append("\n\n");
        }
        
        if (!code.isEmpty()) {
            markdown.append("**Java Code:**\n```java\n").append(code).append("\n```\n\n");
        }
        
        if (!complexity.isEmpty()) {
            markdown.append("**Complexity:**\n").append(complexity).append("\n\n");
        }
    }
    
    private static String formatApproachName(String name) {
        return name.replace("APPROACH", "").trim().toLowerCase()
                   .replace("brute force", "1. Brute Force")
                   .replace("better", "2. Better Approach")
                   .replace("optimal", "3. Optimal Approach");
    }
    
    private static String extractExplanation(String content) {
        StringBuilder explanation = new StringBuilder();
        String[] lines = content.split("\n");
        boolean inExplanation = false;
        
        for (String line : lines) {
            line = line.trim();
            if (line.startsWith("* Idea:") || line.startsWith("* How it works:")) {
                inExplanation = true;
                explanation.append(line.substring(1).trim()).append("\n");
            } else if (inExplanation && line.startsWith("*") && !line.startsWith("* Time") && !line.startsWith("* Space")) {
                explanation.append(line.substring(1).trim()).append("\n");
            } else if (line.startsWith("* Time") || line.startsWith("public")) {
                break;
            }
        }
        
        return explanation.toString().trim();
    }
    
    private static String extractComplexity(String content) {
        StringBuilder complexity = new StringBuilder();
        String[] lines = content.split("\n");
        
        for (String line : lines) {
            line = line.trim();
            if (line.startsWith("* Time Complexity:") || line.startsWith("* Space Complexity:")) {
                complexity.append("- ").append(line.substring(1).trim()).append("\n");
            }
        }
        
        return complexity.toString().trim();
    }
    
    private static String extractCode(String content) {
        int methodStart = content.indexOf("public");
        if (methodStart == -1) return "";
        
        int braceCount = 0;
        int codeStart = methodStart;
        int codeEnd = codeStart;
        boolean inMethod = false;
        
        for (int i = codeStart; i < content.length(); i++) {
            char c = content.charAt(i);
            if (c == '{') {
                braceCount++;
                inMethod = true;
            } else if (c == '}') {
                braceCount--;
                if (inMethod && braceCount == 0) {
                    codeEnd = i + 1;
                    break;
                }
            }
        }
        
        return content.substring(codeStart, codeEnd).trim();
    }
}