package io.cat.ai

import io.cat.ai.snmm.common.CTypeAlias._
import io.cat.ai.snmm.core.lib.{StdLib, StringLib}
import io.cat.ai.snmm.core.pointer.generic._
import io.cat.ai.snmm.core.pointer.struct.AbstractStruct
import io.cat.ai.snmm.core.pointer.{Pointer, PointerFactory}

import scala.annotation.tailrec

package object snmm {

  object Implicits
    extends core.pointer.generic.Implicits
      with core.pointer.Ops.PointerOps

  object StructImplicits
    extends core.pointer.struct.generic.StructMemberValueAssignerImplicit
      with core.pointer.struct.generic.StructMemberPointerImplicit

  object CSyntax {

    import io.cat.ai.snmm.common.CTypeAlias._

    /**
      * Dereference the pointer
      *
      * Provides C-style syntax to access native memory
      *
      * @example {{{
      *
      *         val someValue: double = _
      *
      *         //defining a pointer
      *         var b: *[double] = &(someValue)
      * }}}
      *
      * @param ptr - off-heap pointer
      *
      * @param nativePtr - native pointer typeclass
      *
      * @return the value stored in memory
      **/
    def *[A](ptr: *[A])(implicit nativePtr: NativeHeapPointer[A]): A = nativePtr.deref(ptr)

    def **[A](ptr: **[A])(implicit
                          nativeDoublePtr: NativeHeapPointerToPointer[A],
                          nativePtr: NativeHeapPointer[A]): A = *(nativeDoublePtr.deref(ptr))

    def ***[A](ptr: ***[A])(implicit
                            nativeTriplePtr: NativeHeapPointerToPointer[Pointer[A]],
                            nativeDoublePtr: NativeHeapPointerToPointer[A],
                            nativePtr: NativeHeapPointer[A]): A = **(nativeTriplePtr.deref(ptr))

    def *(ptr: *[char])(implicit nativeStringPtr: NativeHeapStringPointer[Char]): String = nativeStringPtr.deref(ptr)

    def **(ptr: **[char])(implicit
                          nativeDoublePtr: NativeHeapPointerToPointer[Char],
                          nativeStringPtr: NativeHeapStringPointer[Char]): String = *(nativeDoublePtr.deref(ptr))

    def ***(ptr: ***[char])(implicit
                            nativeTriplePtr: NativeHeapPointerToPointer[Pointer[Char]],
                            nativeDoublePtr: NativeHeapPointerToPointer[Char],
                            nativePtr: NativeHeapStringPointer[Char]): String = **(nativeTriplePtr.deref(ptr))

    /**
      * Get address of variable
      *
      * Provides C-style syntax to get the address of variable
      *
      * @example {{{
      *
      *         //defining a variable
      *         val a = 10
      *
      *         //defining a pointer and get address of pointer
      *         var b: *[int] = &(a)
      * }}}
      *
      * @param value     - value stored at native memory
      * @param nativePtr - native pointer typeclass
      *
      *  @return the pointer of value
      **/
    def &[A](value: A)(implicit nativePtr: NativeHeapPointer[A]): *[A] = nativePtr.addressOf(value)

    def &[A](ptr: *[A])(implicit nativeHeapDoublePtr: NativeHeapPointerToPointer[A]): **[A] = nativeHeapDoublePtr.addressOf(ptr)

    def &(value: String)(implicit nativePtr: NativeHeapStringPointer[Char]): *[char] = nativePtr.addressOf(value)

    /**
      * Imperative C-style for loop
      *
      * @example {{{
      *
      *         var i: int32_t = 0
      *
      *         `for`(i, i < 5, i = i + 1) {
      *           printf("Iteration: %i \n", i)
      *         }
      * }}}
      *
      *  @return the pointer of value
      **/

    @tailrec
    def `for`[T](init: => T, condition: => Boolean, op: => T = None)(body: => Unit): Unit =
      if (condition) {
        body
        op
        `for`(init, condition, op)(body)
      }
  }

  object stdlib {

    /**
      * You can store the result of malloc into any pointer variable without a cast, because ISO C automatically converts the type
      * void* to another type of pointer when necessary. But the cast is necessary in contexts other than assignment operators or
      * if you might want your code to run in traditional C.
      *
      * @example {{{
      *         val rawPtr: *[void] = malloc(5 * sizeof[int])
      *         val arr: *[int] = cast[int](rawPtr)
      * }}}
      *
      * @param ptr - off-heap pointer
      *
      * @return type casted native pointer
      **/
    def cast[A](ptr: *[void]): *[A] = PointerFactory.create[A](ptr.address)

    /**
      * Obtain the size (in bytes) of the data type
      *
      * @example {{{
      *         val size = sizeof[long]
      * }}}
      **/
    def sizeof[A](implicit nativeSize: NativeSize[A]): Int = StdLib.sizeof(nativeSize)

    def sizeofStruct[Struct <: AbstractStruct](struct: Struct): AbstractStruct = struct

    /**
      * Memory allocation
      *
      * @see [[StdLib.malloc]]
      * @param size - type size of memory
      * @return pointer to the memory
      **/
    def malloc(size: size_t)
              (implicit allocator: NativeHeapDynamicMemoryAllocator): *[void] = StdLib.malloc(size)

    /**
      * Allocates the memory and also initializes the allocates memory block to zero
      *
      * @see [[StdLib.calloc]]
      * @param nitems - number of items
      * @param size   - size of items
      * @return pointer to the memory
      **/
    def calloc(nitems: Int, size: size_t)
              (implicit allocator: NativeHeapDynamicMemoryAllocator): *[void] = StdLib.calloc(nitems, size)

    /**
      * Deallocates the old object pointed to by ptr and returns a pointer to a new object that has the size specified by size
      * Should only be used for dynamically allocated memory
      *
      * @see [[StdLib.realloc]]
      * @param ptr  - old pointer to deallocation
      * @param size - new size
      * @return pointer to the memory
      **/
    def realloc[A](ptr: *[A], size: size_t)
                  (implicit allocator: NativeHeapDynamicMemoryAllocator): *[void] = StdLib.realloc(ptr, size)

    /**
      * Deallocates the memory
      *
      * @see [[StdLib.free]]
      **/
    def free[A](mem: *[A])
               (implicit allocator: NativeHeapDynamicMemoryAllocator): void = StdLib.free(mem)

  }

  import stdlib._

  object string {

    import Implicits._

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.memcpy]]
      * */
    def memcpy[A](dest: *[A], src: *[A], n: size_t): *[void] = StringLib.memcpy(dest, src, n)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.memmove]]
      * */
    def memmove[A](str1: *[A], str2: *[A], n: size_t): *[void] = StringLib.memmove(str1, str2, n)

    /**
      * Searches for the first occurrence of the character c (an unsigned char) in the first n bytes of
      * the string pointed to, by the argument str
      *
      * * @see [[io.cat.ai.snmm.core.lib.StringLib.memchr]]
      * */
    def memchr(src: *[void], c: Int, n: size_t): *[void] = StringLib.memchr(cast[Char](src), c, n)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.memcmp]]
      * */
    def memcmp[A](str1: *[void], str2: *[void], n: size_t): Int = StringLib.memcmp(str1, str2, n)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.memset]]
      * */
    def memset[A](str: *[A], c: Int, n: size_t): *[void] = StringLib.memset(str, c, n)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strcat]]
      * */
    def strcat(dest: *[char], src: *[char]): *[char] = StringLib.strcat(dest, src)

    def strcat(dest: *[char], src: String): *[char] = StringLib.strcat(dest, src)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strncat]]
      * */
    def strncat(dest: *[char], src: *[char], n: size_t): *[char] = StringLib.strncat(dest, src, n)

    def strncat(dest: *[char], src: String, n: size_t): *[char] = StringLib.strncat(dest, src, n)

    /**
      *
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strchr]]
      * */
    def strchr(str: *[char], c: Int): *[char] = StringLib.strchr(str, c)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strrchr]]
      * */
    def strrchr(str: *[char], c: Int): *[char] = StringLib.strrchr(str, c)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strcmp]]
      * */
    def strcmp(str1: *[char], str2: *[char]): Int =  StringLib.strcmp(str1, str2)

    def strcmp(str1: String, str2: *[char]): Int =  StringLib.strcmp(str1, str2)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strncmp]]
      * */
    def strncmp(str1: *[char], str2: *[char], n: size_t): Int = StringLib.strncmp(str1, str2, n)

    def strncmp(str1: String, str2: *[char], n: size_t): Int = StringLib.strncmp(str1, str2, n)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strcoll]]
      * */
    def strcoll(str1: *[char], str2: *[char]): Int = StringLib.strcoll(str1, str2)

    def strcoll(str1: String, str2: *[char]): Int = StringLib.strcoll(str1, str2)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strcpy]]
      * */
    def strcpy(toHere: *[char], fromHere: *[char]): *[char] = StringLib.strcpy(toHere, fromHere)

    def strcpy(toHere: *[char], fromHere: String): *[char] = StringLib.strcpy(toHere, fromHere)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strlen]]
      * */
    def strlen(str: *[char]): size_t = StringLib.strlen(str)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strspn]]
      * */
    def strspn(s: *[char], reject: *[char]): size_t = StringLib.strspn(s, reject)

    def strspn(s: *[char], reject: String): size_t = StringLib.strspn(s, reject)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strcspn]]
      * */
    def strcspn(s: *[char], reject: *[char]): size_t = StringLib.strcspn(s, reject)

    def strcspn(s: *[char], reject: String): size_t = StringLib.strcspn(s, reject)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strpbrk]]
      * */
    def strpbrk(s: *[char], accept: *[char]): *[char] = StringLib.strpbrk(s, accept)

    def strpbrk(s: *[char], accept: String): *[char] = StringLib.strpbrk(s, accept)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strstr]]
      * */
    def strstr(haystack: *[char], needle: *[char]): *[char] = StringLib.strstr(haystack, needle)

    def strstr(haystack: *[char], needle: String): *[char] = StringLib.strstr(haystack, needle)

    /**
      *
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strtok]]
      * */
    def strtok[A](s: *[char], delim: *[char]): *[char] = StringLib.strtok(s, delim)

    def strtok[A](s: *[char], delim: String): *[char] = StringLib.strtok(s, delim)

    /**
      * @see [[io.cat.ai.snmm.core.lib.StringLib.strxfrm]]
      * */
    def strxfrm(dest: *[char], src: *[char], n: size_t): size_t = StringLib.strxfrm(dest, src, n)

    def strxfrm(dest: *[char], src: String, n: size_t): size_t = StringLib.strxfrm(dest, src, n)
  }
}