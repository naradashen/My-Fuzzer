# My-Fuzzer
### My-Fuzzer is a tool for web directory and file enumeration, designed to help identify existing directories and files on a target website.

## Overview
My-Fuzzer is a tool for performing comprehensive web directory and file enumeration on target websites. It is designed to discover hidden directories, files, and sensitive information that may be exposed on web servers.

## Features
- Directory and file enumeration using a predefined list of common names.
- Parallelized requests for faster enumeration.
- Handling of redirects to detect moved or renamed directories/files.
- Output to an easily readable text file for analysis.

## Installation
### Prerequisites
- C++ compiler (g++)
- cURL library

### Instructions
1. Clone the repository:
```bash
git clone https://github.com/naradashen/My-Fuzzer.git
```
2. Navigate to the project directory:
```bash
cd My-Fuzzer
```
3. Compile the code using your C++ compiler (replace 'main.cpp' with your actual C++ file name):
```bash
g++ main.cpp -o fuzzer
```

## Usage
1. Run the compiled executable:
```bash
./fuzzer
```
2. Enter the target website URL when prompted.
3. Wait for the enumeration process to complete.
4. Check the enumeration_results.txt file for the enumeration results.

- For more details make sure to watch this video tutorial 😎
```bash
https://www.youtube.com/watch?v=ttDrYujX4z0
```
🖖
