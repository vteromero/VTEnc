# VTEnc encoding data format

This document briefly describes the encoding data format produced and consumed by VTEnc.

It's assumed that you know the algorithm and you're familiar with concepts like "Bit Cluster" or "Bit Cluster Tree". If not, you can learn about them in this [article](https://vteromero.github.io/2019/07/28/vtenc.html).

## Introduction

This is a **non-portable** format. An encoded stream with this format won't bear enough information to be decoded on its own. The user must know some extra context beforehand when encoding and decoding. Specifically, they must know:
* The sequence's data type. There are 4 supported data types: `uint8_t`, `uint16_t`, `uint32_t` and `uint64_t`.
* The sequence's size.
* The encoding parameters.

## Encoding parameters

* `allow_repeated_values`: This flag tells whether the sequence can or cannot have repeated values.

* `skip_full_subtrees`: When enabled, if a full subtree is found, all the clusters in that subtree will be skipped from being encoded. On the decoding side, if a full subtree appears, this will be completely reconstructed without having to decode it from the input stream of bytes. `skip_full_subtrees` is ignored if `allow_repeated_values` is true.

## Maximum sequence size

The maximum allowed sequence size depends on the bitwidth of the sequence's data type and whether the sequence has repeated values or not.

Here are the maximum sizes on all the possible input sequences:

|                           |8 bits|16 bits|32 bits|64 bits|
|:-------------------------:|:----:|:-----:|:-----:|:-----:|
|`allow_repeated_values` = 1| 2^57 |  2^57 |  2^57 |  2^57 |
|`allow_repeated_values` = 0|  2^8 |  2^16 |  2^32 |  2^57 |

## Encoding data format

The encoding data format is the result of serialising the Bit Cluster Tree following a **pre-order traversal** order, which is a Depth-First Search (DFS) method. Therefore, cluster lengths are serialised in depth from level `W-1` through level `0`; where `W` is the size (or width) of the sequence's data type.

When a cluster of length 1 is seen, the DFS serialisation for that cluster ends. The rest of clusters from there to the leaf node are **not** serialised in the same fashion. Instead, corresponding lower bits of the value that belongs to those clusters are encoded.

The number of serialisation levels depends on the width of the sequence's data type. Thus, a 8-bit sequence has 8 levels, a 16-bit sequence has 16 levels, and so on.

All the fields/values are encoded in **little-endian** format.
