package io.cat.ai.snmm.core.pointer.generic

import io.cat.ai.snmm.core.pointer.Pointer

/**
  * Typeclass for memory allocation during program execution, provides features to manual management of memory,
  * by using this feature we can manage memory, whenever we require memory allocation or reallocation at runtime.
  *
  * Functions allows to create amount of required memory, before exiting the program we will release the memory allocated at runtime
  * by using #deallocateMemBlock function
  * */
trait NativeHeapDynamicMemoryAllocator {

  /**
    * Allocates specified number of bytes (memory blocks)
    * */
  def allocateMemBlock(size: Int): Pointer[Unit]

  /**
    * Allocates specified number of bytes (memory blocks) and initialize all memory with 0
    * */
  def allocateMemBlockWithInit(nitems: Int, size: Int): Pointer[Unit]

  /**
    * Reallocates the dynamically allocated memory to increase or decrease amount of the memory
    * */
  def reallocateMemBlock[A](ptr: Pointer[A], newSize: Int): Pointer[Unit]

  /**
    * Releases dynamically allocated memory
    * */
  def deallocateMemBlock(ptr: Pointer[_]): Unit
}