# LZ78 Multimedia Compressor

Implementation of the LZ78 compression algorithm using a **Hash Table** for efficient dictionary lookups ($O(1)$ average complexity).

## 🛠 Features
- **Fast Search:** Uses a prime-sized hash table (131,071) to minimize collisions.
- **Visual Debug:** Real-time tracing of dictionary "Hits" and "Misses".
- **Silesia Corpus Support:** Automated testing for standard compression datasets.

## 📂 Module Documentation

### Compression (`compress.h`)
| Function | Description |
| :--- | :--- |
| `hash_func` | Generates a hash key from a prefix index and character. |
| `lz78_compress_logic` | The core loop that converts input bytes into (index, char) tokens. |
| `lz78_visual_debug` | Step-by-step console trace of the compression process. |

### Decompression (`decompress.h`)
| Function | Description |
| :--- | :--- |
| `lz78_decompress_logic` | Reconstructs data using a stack-based dictionary walk. |
| `decompress_and_save` | Handles binary file reading and output restoration. |

## 🚀 How to Run
Compile using `gcc` or `cc`:
```bash
cc main.c compress.c decompress.c TestesCode.c -o lz78_tool
./lz78_tool