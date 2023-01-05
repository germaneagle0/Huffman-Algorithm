# Huffman-Algorithm

```mermaid
flowchart TD
  A[Sort by frequency] --> B{Is there only one element?};
  B -- Yes --> C[Store the result];
  B -- No --> D[Join the smaller two];
  D --> A;
```
