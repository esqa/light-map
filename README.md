# Light Map (`lmap`)

Single-header, lightweight key/value storage optimized for **32- and 64-bit platforms**. Designed for fast, cache-friendly packed data storage.

---

## Features

-  **Single-header** — drop-in, no dependencies  
-  **Cross-platform** — auto-detects 32/64-bit architectures  
-  **Bit-packed storage** — 64-bit (32-bit platforms) / 128-bit (64-bit platforms)  
-  **Template constructor** — flexible initialization for integers or packed floats  
-  **Zero heap allocations** — extremely cache-friendly

---

## Usage:

```cpp
#include "light_map.h"

int main() {
    lmap::map m(42, 3.14f);

    auto key   = m.upper(); // high bits
    auto value = m.lower(); // low bits
}
```
