# Coding style

The purpose of this document is to define a set of rules that must be followed to keep a consistent coding style, which will make the source code easier to read and maintain.

It is strongly influenced by the [Linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html#linux-kernel-coding-style), but it has some differences.

The rules don't follow any particular order and don't intend to cover every single aspect of creating and maintaining code. Instead, you should take it as a guide that will remove some of the burden of making decisions, specially those with regards to coding aesthetics.

## Rules

1. Use 2-spaced indentation.

2. This is the preferred style for statement braces (`if`, `for`, `switch`, etc.):
    ```c
    if (condition) {
     do_x();
    } else {
     do_y();
    }
    ```

3. Braces can be skipped when there's only one statement:
    ```c
    if (condition)
      do_x();
    ```

4. This is also acceptable when line is not too long:
    ```c
    if (condition) return -1;
    ```

5. Functions are a special case, with opening brace at the beginning of a new line:
    ```c
    int function(int x)
    {
      /* Body goes here */
    }
    ```

6. Put a space after these keywords: `if, switch, case, for, do, while`

7. When declaring pointers, the preferred use of * is adjacent to the data name or function name and not adjacent to the type name:
    ```c
    char *str;
    char *copy_str(const char *str);
    ```

8. Avoid using typedefs as much as possible. Read rationale here: https://www.kernel.org/doc/html/v4.10/process/coding-style.html#typedefs

9. Function names are `snake_case`:
    ```c
    int process_request(const struct *request);
    ```

10. Variable names are `snake_case`:
    ```c
    size_t arr_len;
    char *tmp, *filter_name;
    ```

11. Struct names are `snake_case`:
    ```c
    struct decoding_ctx {
      size_t processed;
      size_t remaining;
    };
    ```

12. Enum names are `snake_case`:
    ```c
    enum response_error {
      BAD_REQUEST_ERROR,
      UNREACHABLE_ERROR
    };
    ```

13. Names of macros defining constants are `CAPITALISED`:
    ```c
    #define MAGIC_NUMBER 42
    ```

14. Labels in enums are `CAPITALISED`:
    ```c
    enum {
      PERSIST,
      CONTINUE,
      ABORT
    };
    ```

15. Macros resembling functions may be named in lower case:
    ```c
    #define list_add(list, element)
    ```

16. The preferred style for multi-line comments is:
    ```c
    /*
     * This is a multi-line comment that doesn't fit in a
     * single line.
     *
     * Leave a blank line between paragraphs within the block
     * comment.
     */
    ```

