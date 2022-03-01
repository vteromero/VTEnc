v0.3.0
------
*Released on March 1st, 2022*

**BREAKING CHANGES**
* New VTEnc API. [#31](https://github.com/vteromero/VTEnc/pull/31)

**FIXES**
* Fix nodes visiting order. [#25](https://github.com/vteromero/VTEnc/pull/25)

**OTHER**
* Improve decoding performance by memoizing higher bits. [#29](https://github.com/vteromero/VTEnc/pull/29)
* Coding style. [#30](https://github.com/vteromero/VTEnc/pull/30)
* Do not use typedef for internal structs. [#27](https://github.com/vteromero/VTEnc/pull/27)
* Re-implement BitClusterStack to use a fixed-size array instead of allocating memory. [#26](https://github.com/vteromero/VTEnc/pull/26)
* Replace BitClusterStack with generic implementation. [#28](https://github.com/vteromero/VTEnc/pull/28)
* Removes -g3 gcc flag for all targets, except debug. [#32](https://github.com/vteromero/VTEnc/pull/32)

v0.2.0
------
*Released on May 20th, 2020*

**BREAKING CHANGES**:
* Simplify API by removing specific functions for lists and sets. [#20](https://github.com/vteromero/VTEnc/pull/20)
* Add `VtencEncoder` and `VtencDecoder` structures to provide encoding parameters and to hold returning state in `vtenc_encode`* and `vtenc_decode`* functions. [#20](https://github.com/vteromero/VTEnc/pull/20)
* Remove sequence size from encoding data format. [#21](https://github.com/vteromero/VTEnc/pull/21)
* Remove `vtenc_decoded_size`* API functions. [#21](https://github.com/vteromero/VTEnc/pull/21)
* Remove "non-empty sequence" restriction when encoding sequences with no repeated values. [#21](https://github.com/vteromero/VTEnc/pull/21)
* Add `allow_repeated_values` encoding parameter. [#20](https://github.com/vteromero/VTEnc/pull/20)
* Add `skip_full_subtrees` encoding parameter. [#20](https://github.com/vteromero/VTEnc/pull/20)
* Add `min_cluster_length` encoding parameter. [#22](https://github.com/vteromero/VTEnc/pull/22)

**FIXES:**
* Fix bug on decoding steps order not matching its encoding counterpart. [#23](https://github.com/vteromero/VTEnc/pull/23)

v0.1.0
------
*Released on March 26th, 2020*
* **BREAKING CHANGE**: Encode lower bits of values in clusters of length 1. [#18](https://github.com/vteromero/VTEnc/pull/18)
* Refactor of `count_zeros_at_bit_pos`* functions to improve encoding performance. [#16](https://github.com/vteromero/VTEnc/pull/16)
* Fix bug on wrongly using `memcmp` on some testing programs. [#17](https://github.com/vteromero/VTEnc/pull/17) [#14](https://github.com/vteromero/VTEnc/pull/14)
* Tests for random sequences. [#15](https://github.com/vteromero/VTEnc/pull/15)

v0.0.3
------
*Released on February 13th, 2020*
* Refactor encoding and decoding to get rid of recursion. Decoding speed has been improved by ~ 30%.
* Added document that describes encoding data format.

v0.0.2
------
*Released on December 16th, 2019*
* Improved encoding and decoding speed.
* Added CI through GitHub Actions.

v0.0.1
------
*Released on October 27th, 2019*
