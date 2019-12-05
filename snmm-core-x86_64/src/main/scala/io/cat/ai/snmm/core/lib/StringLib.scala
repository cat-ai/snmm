package io.cat.ai.snmm.core.lib

import io.cat.ai.snmm.common.CTypeAlias._
import io.cat.ai.snmm.core.jni.SnmmCore
import io.cat.ai.snmm.core.pointer.{Pointer, PointerFactory}
import io.cat.ai.snmm.core.pointer.generic.NativeHeapStringPointer

object StringLib {

  /**
    * Copies n characters from memory area src to memory area dest.
    *
    * @example {{{
    *            val str = "123456"
    *            val len = str.length
    *
    *            val src: *[char] = &(str)
    *
    *            var dest: *[char] = cast[char](10 * malloc(sizeof[char])))
    *            // copying 6 bytes from src to dst
    *
    *            memcpy(dst, src, 6)

    *            // dst = 123456
    * }}}
    *
    * @param dest − pointer to the destination array where the content is to be copied, type-casted to a pointer of type void*.
    *
    * @param src − pointer to the source of data to be copied, type-casted to a pointer of type void*.
    *
    * @param n − number of bytes to be copied.
    *
    * */
  def memcpy[A](dest: Pointer[A], src: Pointer[A], n: size_t): Pointer[Unit] =
    PointerFactory(SnmmCore.SNMM_CORE_JNI.mem_cpy(dest.address, src.address, n))

  def memcpy[A](dest: String, src: Pointer[Char], n: size_t)
            (implicit nString: NativeHeapStringPointer[Char]): Pointer[Unit] = memcpy(nString.addressOf(dest), src, n)

  def memcpy(dest: String, src: String, n: size_t)
            (implicit nString: NativeHeapStringPointer[Char]): Pointer[Unit] = memcpy(nString.addressOf(dest), nString.addressOf(src), n)

  /**
    * Copies n characters from str2 to str1, but for overlapping memory blocks,
    * [[memmove]] is a safer approach than [[memcpy]].
    *
    * @example {{{
    *
    *         val str = "some"
    *
    *         var src = &(str)
    *         val n = strlen(src)
    *         var dest = malloc(n)
    *
    *         // copying 6 bytes from src to dst
    *         memcpy(dst, src, n)

    *         // dst = some
    * }}}
    *
    * @param str1 − pointer to the destination array where the content is to be copied, type-casted to a pointer of type void*
    *
    * @param str2 − pointer to the source of data to be copied, type-casted to a pointer of type void*
    *
    * @param n − number of bytes to be copied
    *
    * @return a pointer to the destination, which is str1
    **/
  def memmove[A](str1: Pointer[A], str2: Pointer[A], n: size_t): Pointer[Unit] =
    PointerFactory(SnmmCore.SNMM_CORE_JNI.mem_move(str1.address, str2.address, n))

  def memmove[A](str1: String, str2: Pointer[A], n: size_t)
             (implicit nString: NativeHeapStringPointer[Char]): Pointer[Unit] =
    PointerFactory(SnmmCore.SNMM_CORE_JNI.mem_move(nString.addressOf(str1).address, str2.address, n))

  /**
    * Searches for the first occurrence of the character c (an unsigned char) in the first n bytes of
    * the string pointed to, by the argument str
    *
    * @example {{{
    *         val str = "[...///++!!_-^]" //9
    *
    *         val chr = '!'
    *
    *         var ptr: *[Char] = _
    *
    *         ptr = cast[Char](memchr(str, chr, strlen(str))

    *         // string after '!' char = !_-^]
    *
    * }}}
    *
    * @param str − pointer to the destination array where the content is to be copied,
    *              type-casted to a pointer of type void*.
    * @param c - value to be passed as an int, but the function performs a byte per byte search using
    *            the unsigned char conversion of this value
    * @param n − number of bytes to be copied.
    *
    * @return a pointer to the matching byte or NULL if the character does not occur in the given memory area
    *
    * */
  def memchr(str: Pointer[Char], c: Int, n: size_t): Pointer[Unit] =
    PointerFactory(SnmmCore.SNMM_CORE_JNI.mem_chr(str.address, c, n))

  def memchr(str: String, c: Int, n: size_t)
            (implicit nString: NativeHeapStringPointer[Char]): Pointer[Unit] = memchr(nString.addressOf(str), c, n)

  /**
    *
    * Compares the first n bytes of memory area src and memory area dest
    *
    * @example {{{
    *
    *      val str1 = "1234567890"
    *      val str2 = getSomeString()
    *
    *      val dest: *[char] = &(str2)
    *
    *      if (memcmp(src, dest, 10) == 0)
    *         println("equal")
    *      else
    *         println("not equal")
    *
    *
    * }}}
    *
    * @param src − pointer to a block of memory.
    *
    * @param dest − pointer to a block of memory.
    *
    * @param n − number of bytes to be compared
    *
    *
    * @return value < 0 when str1 is less than str2.
    *
    * @return value > 0 when str2 is less than str1.
    *
    * @return value = 0 when str1 is equal to str2.
    *
    * */
  def memcmp[A](src: Pointer[A], dest: Pointer[Unit], n: size_t): Int =
    SnmmCore.SNMM_CORE_JNI.mem_cmp(src.address, src.address, n)

  def memcmp(src: String, dest: Pointer[Unit], n: size_t)
            (implicit nString: NativeHeapStringPointer[Char]): Int = memcmp(nString.addressOf(src), dest, n)

  /**
    * Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str
    *
    * @example {{{
    *           val str = "1234567890"
    *
    *           val src = &(str)
    *
    *           val dest = memset(src, 'Z', 5)
    *
    *           // sym = ZZZZZ67890
    * }}}
    *
    * @param dest − pointer to the block of memory to fill
    *
    * @param c − value to be set. The value is passed as an int, but the function fills the block of memory using the unsigned char conversion of this value.
    *
    * @param n − number of bytes to be set to the value.
    *
    * @return pointer to the memory area str
    *
    * */
  def memset[A](dest: Pointer[A], c: Int, n: size_t): Pointer[Unit] =
    PointerFactory(SnmmCore.SNMM_CORE_JNI.mem_set(dest.address, c, n))

  /**
    * Appends the string pointed to by src to the end of the string pointed to by dest
    *
    * @example {{{
    *           val str2 = "second str "
    *           val str1 = "first str"
    *
    *           val dst = &(str2)
    *           val app = &(str1)
    *
    *           // concat chars from src to dst
    *           strcat(dst, app)

    *           // dst: first str second str
    *
    * }}}
    *
    * @param dest − pointer to the destination array, which should contain a C string, and should be large enough to contain the concatenated resulting string.
    *
    * @param src − This is the string to be appended. This should not overlap the destination.
    *
    * @return pointer to the resulting string dest
    *
    * */
  def strcat(dest: Pointer[Char], src: Pointer[Char]): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.str_cat(dest.address, src.address))

  def strcat(dest: Pointer[Char], src: String)
            (implicit nativeStr: NativeHeapStringPointer[Char]): Pointer[Char] = strcat(dest, nativeStr.addressOf(src))

  /**
    * Appends the string pointed to by src to the end of the string pointed to by dest up to n characters long.
    *
    * @example {{{
    *
    *           var dest = cast[Char](&("ABCD") )
    *           val src = "EFGHIJKL"
    *
    *           dest = strncat(dest, src, 5)
    *
    *           // dest = ABCDEFGHI
    * }}}
    *
    * @param dest − pointer to the destination array, which should contain a C string, and should be large enough
    *               to contain the concatenated resulting string which includes the additional null-character.
    * @param src − string to be appended.
    *
    * @param n − maximum number of characters to be appended
    *
    * @return pointer to the resulting string dest
    *
    * */
  def strncat(dest: Pointer[Char], src: Pointer[Char], n: size_t): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.strn_cat(dest.address, src.address, n))

  def strncat(dest: Pointer[Char], src: String, n: size_t)
             (implicit nString: NativeHeapStringPointer[Char]): Pointer[Char] = strncat(dest, nString.addressOf(src), n)

  /**
    * Searches for the first occurrence of the character c (an unsigned char) in the string pointed to by the argument str
    *
    * @example {{{
    *
    *         //string for searching
    *         val str = "HTTP"
    *
    *         val ch = 'T'
    *
    *         val src = &("HTTP")
    *
    *         var p: *[char] = _
    *
    *         p = strchr(src, ch)
    *
    *         // p = TTP
    * }}}
    *
    * @param str − string to be scanned
    *
    * @param c − character to be searched in str
    *
    * @return pointer to the first occurrence of the character c in the string str, or NULL if the character is not found
    *
    * */
  def strchr(str: Pointer[Char], c: Int): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.str_chr(str.address, c))

  def strchr(str: String, c: Int)
            (implicit nString: NativeHeapStringPointer[Char]): Pointer[Char] = strchr(nString.addressOf(str), c)

  /**
    * Searches for the last occurrence of the character c (an unsigned char) in the string pointed to, by the argument str
    *
    * @example {{{
    *
    *         //string for searching
    *         val str = "Last occurrence"
    *
    *         val ch = 'r'
    *
    *         val src = &(str)
    *
    *         var ach: *[Char] = _
    *
    *         dest = strrchr(src, ch)
    *         // dest = rrence
    *
    * }}}
    *
    * @param str − string to be scanned
    *
    * @param c − character to be located. It is passed as its int promotion, but it is internally converted back to char
    *
    * @return pointer to the first occurrence of the character c in the string str, or NULL if the character is not found
    *
    * */
  def strrchr(str: Pointer[Char], c: Int): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.strr_chr(str.address, c))

  def strrchr(str: String, c: Int)
             (implicit nString: NativeHeapStringPointer[Char]): Pointer[Char] = strrchr(nString.addressOf(str), c)

  /**
    * Compares the string pointed to, by str1 to the string pointed to by str2
    *
    * @example {{{
    *
    *           val str1 = "abcdef"
    *           val str2 = "ABCDEF"
    *
    *           int ret = strcmp(&(str1), &(str2))
    *
    *           if (ret < 0) {
    *             printf("str1 is less than str2")
    *           } else if (ret > 0) {
    *             printf("str2 is less than str1")
    *           } else {
    *             printf("str1 is equal to str2")
    *           }
    * }}}
    *
    * @param str1 − first string to be compared
    *
    * @param str2 − second string to be compared
    *
    * @return value < 0 when str1 is less than str2.
    *
    * @return value > 0 when str2 is less than str1.
    *
    * @return value = 0 when str1 is equal to str2.
    *
    * */
  def strcmp(str1: Pointer[Char], str2: Pointer[Char]): Int =
    SnmmCore.SNMM_CORE_JNI.str_cmp(str1.address, str2.address)

  def strcmp(str1: String, str2: Pointer[Char])
            (implicit nString: NativeHeapStringPointer[Char]): Int = strcmp(nString.addressOf(str1), str2)

  /**
    * Compares at most the first n bytes of str1 and str2
    *
    * @example {{{
    *
    *           val str1 = "abcdef"
    *           val str2 = "ABCDEF"
    *
    *           int ret = strcmp(&(str1), &(str2), 4)
    *
    *           if (ret < 0) {
    *             printf("str1 is less than str2")
    *           } else if (ret > 0) {
    *             printf("str2 is less than str1")
    *           } else {
    *             printf("str1 is equal to str2")
    *           }
    *
    * }}}
    *
    * @param str1 − first string to be compared
    *
    * @param str2 − second string to be compared
    *
    * @return value < 0 when str1 is less than str2
    *
    * @return value > 0 when str2 is less than str1
    *
    * @return value = 0 when str1 is equal to str2
    *
    * */
  def strncmp(str1: Pointer[Char], str2: Pointer[Char], n: size_t): Int =
    SnmmCore.SNMM_CORE_JNI.strn_cmp(str1.address, str2.address, n)

  def strncmp(str1: String, str2: Pointer[Char], n: size_t)
             (implicit nString: NativeHeapStringPointer[Char]): Int = strncmp(nString.addressOf(str1), str2, n)

  /**
    * Compares string str1 to str2. The result is dependent on the LC_COLLATE setting of the location
    *
    * @example {{{
    *
    *           val str1 = "abcdef"
    *           val str2 = "ABCDEF"
    *
    *           int ret = strcoll(&(str1), &(str2))
    *
    *           if (ret < 0) {
    *             printf("str1 is less than str2")
    *           } else if (ret > 0) {
    *             printf("str2 is less than str1")
    *           } else {
    *             printf("str1 is equal to str2")
    *           }
    *
    * }}}
    *
    * @param str1 − first string to be compared
    * @param str2 − second string to be compared
    *
    * @return value < 0 when str1 is less than str2
    * @return value > 0 when str2 is less than str1
    * @return value = 0 when str1 is equal to str2
    *
    * */
  def strcoll(str1: Pointer[Char], str2: Pointer[Char]): Int =
    SnmmCore.SNMM_CORE_JNI.str_coll(str1.address, str2.address)

  def strcoll(str1: String, str2: Pointer[Char])
             (implicit nString: NativeHeapStringPointer[Char]): Int = strcoll(nString.addressOf(str1), str2)

  /**
    * Copies the string pointed to by fromHere to toHere
    *
    *
    * @example {{{
    *
    *           val fromHere = "simple_string"
    *           val n = fromHere.length
    *           val toHere: *[char] = cast[char](n * malloc(sizeof[char])
    *
    *           strcpy(toHere, fromHere)
    *
    * }}}
    *
    * @param toHere − pointer to the destination array where the content is to be copied
    *
    * @param fromHere − string to be copied
    *
    * @return pointer to the destination string toHere
    *
    * */
  def strcpy(toHere: Pointer[Char], fromHere: Pointer[Char]): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.str_cpy(toHere.address, fromHere.address))

  def strcpy(toHere: Pointer[Char], fromHere: String)
            (implicit nString: NativeHeapStringPointer[Char]): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.str_cpy(toHere.address, nString.addressOf(fromHere).address))

  /**
    * Computes the length of the string str up to but not including the terminating null character
    *
    * @example {{{
    *
    *           val str = "string"
    *           val len = strlen(str)
    *           printf("length of string = %d", len)
    *           // length of string = 6
    *
    * }}}
    *
    * @param str - string whose length is to be found
    *
    * @return length of string
    *
    * */
  def strlen(str: Pointer[Char]): size_t = SnmmCore.SNMM_CORE_JNI.str_len(str.address)

  def strlen(str: String)(implicit nString: NativeHeapStringPointer[Char]): size_t = strlen(nString.addressOf(str))

  /**
    * Calculates the length of the initial segment of s which consists entirely of characters in reject
    *
    * @example {{{
    *
    *           val string = "ABCD1234567890"
    *           val someCharPtr = ...
    *
    *           val len = strspn(string, someCharPtr)
    *
    *           printf("Length of matching = %d", len)
    * }}}
    *
    * @param s − main C string to be scanned
    *
    * @param reject − string containing the list of characters to match in str1
    *
    * @return number of characters in the initial segment of s which consist only of characters from reject
    *
    * */
  def strspn(s: Pointer[Char], reject: Pointer[Char]): size_t = SnmmCore.SNMM_CORE_JNI.str_spn(s.address, reject.address)

  def strspn(s: Pointer[Char], reject: String)
            (implicit nString: NativeHeapStringPointer[Char]): size_t = strspn(s, nString.addressOf(reject))

  /**
    * Calculates the length of the initial segment of c, which consists entirely of characters not in reject
    *
    * @example {{{
    *
    *         val s = &("2faces")
    *
    *         val reject = "last"
    *
    *         val len = strcspn(s, reject)
    *
    *         printf("Num of characters = %d", len)
    *         // Num of characters = 2
    * }}}
    *
    * @param s − C string to be scanned
    *
    * @param reject − string containing a list of characters to match in s
    *
    * @return number of characters in the initial segment of string s which are not in the string reject
    *
    * */
  def strcspn(s: Pointer[Char], reject: Pointer[Char]): size_t = SnmmCore.SNMM_CORE_JNI.str_cspn(s.address, reject.address)

  def strcspn(s: Pointer[Char], reject: String)
             (implicit nStirng: NativeHeapStringPointer[Char]): size_t = strcspn(s, nStirng.addressOf(reject))

  /**
    * Finds the first character in the string c that matches any character specified in accept.
    * This does not include the terminating null-characters.
    *
    * @example {{{
    *
    *         val s = cast[Char]( &("First") )
    *         val accept = "tr"
    *
    *         val ptr = strpbrk(s, accept)
    *
    *         // ptr = rst
    *
    * }}}
    *
    * @param s − C string to be scanned
    *
    * @param accept − C string containing the characters to match
    *
    * @return pointer to the character in s that matches one of the characters in accept, or NULL if no such character is found
    *
    * */
  def strpbrk(s: Pointer[Char], accept: Pointer[Char]): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.str_pbrk(s.address, accept.address))

  def strpbrk(s: Pointer[Char], accept: String)
             (implicit nString: NativeHeapStringPointer[Char]): Pointer[Char] = strpbrk(s, nString.addressOf(accept))

  /**
    * Finds the first occurrence of the substring needle in the string haystack. The terminating '\0' characters are not compared
    *
    * @example {{{
    *           val haystack = &("Dummy string")
    *
    *           val needle = "s"
    *
    *           var stPtr: *[Char] = stPtr = strstr(haystack, needle)
    *           // stPtr = string
    * }}}
    *
    * @param haystack − C string to be scanned
    *
    * @param needle − small string to be searched with-in haystack string
    *
    * pointer to the first occurrence in haystack of any of the entire sequence of characters specified in needle, or a null pointer if the sequence is not present in haystack
    * */
  def strstr(haystack: Pointer[Char], needle: Pointer[Char]): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.str_str(haystack.address, needle.address))

  def strstr(haystack: Pointer[Char], needle: String)
            (implicit nString: NativeHeapStringPointer[Char]): Pointer[Char] = strstr(haystack, nString.addressOf(needle))

  /**
    * Breaks string into a series of tokens using the delimiter
    *
    * @example {{{
    *           val str: *[Char] = _ // char str[30] = {"Some # string # with # sign"}
    *           val delim = "#"
    * }}}
    *
    * @param s − contents of this string are modified and broken into smaller strings (tokens)
    *
    * @param delim − C string containing the delimiters. These may vary from one call to another
    *
    * @return pointer to the first token found in the string. A null pointer is returned if there are no tokens left to retrieve
    * */
  def strtok[A](s: Pointer[Char], delim: Pointer[Char]): Pointer[Char] =
    PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.str_tok(s.address, delim.address))

  def strtok[A](s: Pointer[Char], delim: String)
               (implicit nString: NativeHeapStringPointer[Char]): Pointer[Char] = strtok(s, nString.addressOf(delim))

  /**
    * Transforms the first n characters of the string src into current locale and place them in the string dest.
    *
    * @param dest − first string to be compared
    *
    * @param src − second string to be compared
    *
    * @param n maximum number of characters to be copied to dest
    *
    * @return length of the transformed string, not including the terminating null-character
    *
    * */
  def strxfrm(dest: Pointer[Char], src: Pointer[Char], n: size_t): size_t =
    SnmmCore.SNMM_CORE_JNI.str_xfrm(dest.address, src.address, n)

  def strxfrm(dest: Pointer[Char], src: String, n: size_t)
             (implicit nString: NativeHeapStringPointer[Char]): size_t = strxfrm(dest, nString.addressOf(src), n)
}
