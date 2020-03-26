v0.1.0
------
*Released on March 26th, 2020*
* **BREAKING CHANGE**: Encode lower bits of values in clusters of length 1 #18
* Refactor of `count_zeros_at_bit_pos`* functions to improve encoding performance #16
* Fix bug on wrongly using `memcmp` on some testing programs #17 #14
* Tests for random sequences #15

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
