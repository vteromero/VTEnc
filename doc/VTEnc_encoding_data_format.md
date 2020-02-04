# VTEnc encoding data format

This document briefly describes the encoding data format produced and consumed when using VTEnc.

It's assumed that you know the algorithm and you're familiar with concepts like "Bit Cluster" or "Bit Cluster Tree". If not, you can learn about them in this [article](https://vteromero.github.io/2019/07/28/vtenc.html).

## Introduction

There are 8 different variations (2 types of sequences x 4 supported data types) of the encoding data format which differ slightly to one another. Yet, all of them share the same general structure.

This encoding data format doesn't include information about neither the type of sequence nor the sequence's data type. It's up to the user to know that context when decoding a encoded stream.

All the fields are encoded in **little-endian** format.

## General data format

This is the general structure of an encoded stream:

|`Sequence_Size`|[`Cluster_Stream`]|
|:-------------:|:-----------------:|

#### `Sequence_Size`

Size of the encoded list or set.

#### `Cluster_Stream`

Sequence of cluster lengths. This is the result of serialising the Bit Cluster Tree following a **level order**, which means that clusters closer to the root are serialised first and, therefore, appear first in this sequence.

|`cl_W-1_0`|`cl_W-1_1`|`cl_W-1_2`|...|`cl_W-2_0`|`cl_W-2_1`|`cl_W-2_2`|...|`cl_0_0`|`cl_0_1`|`cl_0_2`|
|:--------:|:--------:|:--------:|:-:|:--------:|:--------:|:--------:|:-:|:------:|:------:|:------:|

`cl_LVL_SEQ`: cluster number `SEQ` in level `LVL` (or column, or bit position).

The number of levels depends on the width of the sequence's data type. Thus, a 8-bit sequence has 8 levels, a 16-bit sequence has 16 levels, and so on.

## Lists

Lists use 57 bits to encode `Sequence_Size`.

## Sets

| Type size     | 8 bits | 16 bits | 32 bits | 64 bits |
|:-------------:|:------:|:-------:|:-------:|:-------:|
|`Sequence_Size`| 8 bits | 16 bits | 32 bits | 57 bits |

Empty sets are not supported and the actual set size's value is `Sequence_Size` + 1.
