# VTEnc encoding data format

This document briefly describes the encoding data format produced by VTEnc.

It's assumed that you know the algorithm and you're familiar with concepts like "Bit Cluster" or "Bit Cluster Tree". If not, you can learn about them in this [article](https://vteromero.github.io/2019/07/28/vtenc.html).

## Introduction

This is a **non-portable** format. An encoded stream with this format won't bear enough information to be decoded on its own. The user must know some extra context beforehand when encoding and decoding. Specifically, they must know:
* The sequence's data type. There are 4 supported data types: `uint8_t`, `uint16_t`, `uint32_t` and `uint64_t`.
* The sequence's size.
* The encoding parameters.

## Encoding data format

This is the general structure of VTEnc's encoding data format:

|`clusters_chunk`|[`lower_bits`|[`clusters_chunk`|[`lower_bits`| ... ]]] |
|:--------------:|:-----------:|:--------------:|:------------:|:-------:|

The combination of all the `clusters_chunk` forms what is the result of serialising the Bit Cluster Tree following a **pre-order traversal** order, which is a Depth-First Search (DFS) method. Therefore, clusters are serialised in depth first from level `W-1` through level `0`; where `W` is the bitwidth of the sequence's data type.

Each `clusters_chunk` is made up of a sequence of encoded cluster lengths:

|`cluster_length`|`cluster_length`| ... |
|:--------------:|:--------------:|:---:|

A `cluster_length` represents the length of a bit cluster node. It's encoded using the minimum required bits to represent its parent bit cluster node within the Bit Cluster Tree.

In the Bit Cluster Tree serialisation, for each visited bit cluster node `Cl` of length `Len` at the tree level `Lvl`, a couple of special cases are checked:

* If `Len` is equal to 2<sup>`Lvl`</sup> and the encoding parameter `skip_full_subtrees` is true and applicable (i.e. the encoding parameter `allow_repeated_values` is also false), then the rest of nodes for the subtree in which `Cl` is the root node are skipped from being visited (and hence, encoded).

* If `Len` is less than or equal to the value of the encoding parameter `min_cluster_length`, `Cl` is the last node to be visited for that `clusters_chunk`. The rest of nodes (if there is any) for the subtree in which `Cl` is the root node are **not** serialised in the same fashion. Instead, corresponding `lower_bits` of the values that belong to those clusters are encoded.

 `lower_bits` is a sequence of encoded least significant bits (`lsb`):

 | `lsb` | `lsb` | `lsb` | ... |
 |:-----:|:-----:|:-----:|:---:|

 The size of `lower_bits` sequence is `Len`. Each `lsb` field is encoded with `Lvl` bits.

## Notes

* All the fields are encoded in **little-endian** format.
* An empty stream of bytes is a valid encoding data format.
