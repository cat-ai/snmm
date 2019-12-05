package io.cat.ai.snmm.core.lib

import io.cat.ai.snmm.common.CTypeAlias._
import io.cat.ai.snmm.core.pointer.Pointer
import io.cat.ai.snmm.core.pointer.generic.{NativeHeapDynamicMemoryAllocator, NativeSize, NativeStruct}

object StdLib {

  /**
    * Allocates a block of memory
    *
    * @example {{{
    *         val buffer: *[void] = malloc(10 * sizeof[double])
    * }}}
    *
    * @param size - size (in bytes) of the data type
    *
    * @return a pointer to a newly allocated block size bytes long, or [[io.cat.ai.snmm.core.pointer.NULL]] pointer
    *         if the block could not be allocated
    *
    * */
  def malloc(size: size_t)
            (implicit allocator: NativeHeapDynamicMemoryAllocator): Pointer[Unit] = allocator.allocateMemBlock(size)

  /**
    * Allocates the requested memory and returns a pointer to it
    *
    * @example {{{
    *
    *         val n = 5
    *         val ptr: *[short] = cast[short](calloc(n * sizeof[short]))
    *
    *         // ptr = [0 1 2 3 4 5]
    * }}}
    *
    * @param nitems − the number of elements to be allocated
    *
    * @param size − the size of elements
    *
    * @return pointer to the allocated memory, or [[io.cat.ai.snmm.core.pointer.NULL]] if the request fails
    *
    * */
  def calloc(nitems: Int, size: size_t)
            (implicit allocator: NativeHeapDynamicMemoryAllocator): Pointer[Unit] = allocator.allocateMemBlockWithInit(nitems, size)

  /**
    * Attempts to resize the memory block pointed to by ptr that was previously allocated with a call to
    * [[malloc]] or [[calloc]]
    *
    * @example {{{
    *
    *         val five = 5
    *         var ptr: *[int] = cast[int](malloc(five * sizeof[int]))
    *
    *         for (i <- 0 to five)
    *           ptr(i) = i + 1
    *
    *         // 1 2 3 4 5
    *
    *         val ten = 10
    *         ptr = realloc(ptr, ten * sizeof[int])
    *
    *         // ptr = [1 2 3 4 5 6 7 8 9 10]
    * }}}
    *
    * @param ptr - the pointer to a memory block previously allocated with [[malloc]], [[calloc]], [[realloc]] to be reallocated.
    *              If this is NULL, a new block is allocated and a pointer to it is returned by the function
    *
    * @param size - the new size for the memory block in bytes. If it is 0 and ptr points to an existing block of memory,
    *               the memory block pointed by ptr is deallocated and a NULL pointer is returned
    *
    * @return a pointer to the newly allocated memory, or [[io.cat.ai.snmm.core.pointer.NULL]] if the request fails
    *
    * */
  def realloc[A](ptr: Pointer[A], size: size_t)
                (implicit allocator: NativeHeapDynamicMemoryAllocator): Pointer[Unit] = allocator.reallocateMemBlock(ptr, size)

  /**
    * Deallocates the memory previously allocated by a call to [[calloc]], [[malloc]], or [[realloc]].
    *
    * @example {{{
    *         val arr: *[void] = malloc(10 * sizeof[double])
    *
    *         free(arr)
    * }}}
    *
    * @param ptr - the pointer to a memory block previously allocated to be deallocated
    *
    * */
  def free[A](ptr: Pointer[A])
             (implicit allocator: NativeHeapDynamicMemoryAllocator): Unit = allocator.deallocateMemBlock(ptr)

  /**
    * Obtain the size (in bytes) of the data type
    * */
  def sizeof[A](nativeSize: NativeSize[A]): Int = nativeSize.size

  def sizeofStruct[A](nativeStruct: NativeStruct): Int = nativeStruct.hashCode
}