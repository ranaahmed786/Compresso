# Compresso

A modern, cross-platform compression utility for folder-based archival using Canonical Huffman Coding algorithms. Built with Qt Widgets and C++, Compresso provides efficient lossless compression while preserving complete directory structures.

## Overview

Compresso is designed as a specialized folder compression tool that addresses the need for efficient, structure-preserving archival solutions. Unlike traditional archive formats, Compresso applies Canonical Huffman Coding to individual files while maintaining the integrity of nested directory hierarchies.

### Key Advantages

- **Individual File Optimization**: Each file is compressed independently using optimized Huffman codes
- **Structure Preservation**: Complete directory trees are maintained with perfect fidelity
- **Minimal Overhead**: Efficient binary storage with compact metadata headers
- **Performance Oriented**: Multithreaded operations with real-time progress tracking
- **User-Centric Design**: Intuitive interface suitable for both technical and non-technical users

## User Interface

The application features a clean, intuitive interface designed for seamless user experience across all platforms.

<div align="center">

| Home Screen | Folder Selection |
|-------------|------------------|
| ![Home Screen](https://github.com/user-attachments/assets/99a0edea-2559-42e3-b025-d50f032f8a89) | ![Folder Select](https://github.com/user-attachments/assets/71d0702d-0b33-4603-85da-ac0ba4a172f4) |

| Compression Progress | Completed Operation |
|---------------------|---------------------|
| ![Compressing](https://github.com/user-attachments/assets/3f988e5d-0d94-4b44-a131-187e7bc1772d) | ![Decompressed](https://github.com/user-attachments/assets/bca60b5f-765a-4771-bc44-efd62065d887) |

</div>

## Features

### Core Functionality
- **Folder-Based Compression**: Processes entire directory structures recursively
- **Canonical Huffman Implementation**: Lexicographically sorted codes for optimal efficiency
- **Lossless Compression**: Perfect reconstruction of original files and folder hierarchy
- **Binary Optimization**: Bit-level encoding for maximum space efficiency

### Performance & Usability
- **Multithreaded Processing**: Background operations using QtConcurrent framework
- **Progress Monitoring**: Real-time feedback during compression/decompression operations
- **Intelligent Naming**: Automatic suffix handling for output directories
- **Error Management**: Comprehensive error handling with user-friendly notifications
- **Cross-Platform Support**: Consistent experience across Windows, Linux, and macOS

## Technical Implementation

### Compression Algorithm
1. **File Analysis**: Tokenization and frequency analysis of input files
2. **Tree Construction**: Building optimal Huffman trees for each file
3. **Canonical Conversion**: Transform to canonical Huffman codes for standardization
4. **Binary Encoding**: Bit-level compression with efficient storage
5. **Metadata Generation**: Minimal header creation for reconstruction data

### Decompression Process
1. **Metadata Parsing**: Reading compression headers and codebook information
2. **Tree Reconstruction**: Rebuilding canonical Huffman trees
3. **Binary Decoding**: Converting compressed bitstreams back to original data
4. **Structure Recreation**: Restoring complete directory hierarchy

## Installation

### Prerequisites
- Qt Framework (5.x or 6.x)
- C++17 compatible compiler
- CMake or qmake build system
- Git version control

### Build Process

#### Using Qt Creator
```bash
git clone https://github.com/yourusername/compresso.git
cd compresso
# Open Compresso.pro in Qt Creator and build
```

#### Command Line Build
```bash
git clone https://github.com/yourusername/compresso.git
cd compresso
qmake Compresso.pro
make
```

#### Alternative CMake Build
```bash
git clone https://github.com/yourusername/compresso.git
cd compresso
mkdir build && cd build
cmake ..
make
```

## Usage

### Compressing Directories

1. Launch the Compresso application
2. Click "Browse Folder" to select the target directory
3. Click "Compress" to begin the compression process
4. Monitor progress through the real-time progress indicator
5. Locate the output in `[DirectoryName] (Compressed)` folder

### Decompressing Archives

1. Select a directory with the "(Compressed)" suffix
2. Click "Decompress" to initiate the restoration process
3. Monitor decompression progress
4. Access restored files in `[DirectoryName] (Decompressed)` folder

### File Format

Compressed files use the `.compresso` extension and contain:
- Canonical Huffman codebook metadata
- Compressed binary data streams
- Directory structure information
- File attribute preservation data

## Architecture

### Core Components

**Compression Engine**
- Huffman tree construction and optimization
- Canonical code generation algorithms
- Binary I/O operations with bitstream handling

**User Interface**
- Qt Widgets-based GUI implementation
- Asynchronous operation handling with QFutureWatcher
- Progress tracking and user feedback systems

**File Management**
- Recursive directory traversal
- Metadata preservation and restoration
- Cross-platform file system compatibility

## Limitations

### Current Constraints
- Folder-only compression (individual files not supported)
- Proprietary format compatibility (only Compresso-generated archives)
- No encryption or password protection capabilities
- Performance considerations for extremely large files due to bit-level operations

### Future Enhancements
- Individual file compression support
- Encryption and security features
- Additional compression algorithms
- Performance optimizations for large datasets

## Technical Learnings

This project provided extensive experience in:

**Algorithm Implementation**
- Huffman tree construction and traversal algorithms
- Canonical Huffman code generation and optimization
- Binary data manipulation and bitstream processing

**Software Engineering**
- Asynchronous programming with Qt's concurrent framework
- Exception-safe multithreaded application design
- Cross-platform GUI development using Qt Widgets

**Systems Programming**
- Low-level binary file I/O operations
- Memory-efficient data structure design
- File system interaction and metadata handling

## Contributing

Contributions are welcome through standard GitHub workflows:

1. Fork the repository
2. Create a feature branch
3. Implement changes with appropriate tests
4. Submit a pull request with detailed description

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for complete terms and conditions.

## Contact

For questions, issues, or feature requests, please use the GitHub issue tracker or contact the development team through the repository.

---

**Compresso** - Efficient folder compression through advanced algorithmic implementation.
