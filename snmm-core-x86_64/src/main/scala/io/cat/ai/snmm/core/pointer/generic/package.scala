package io.cat.ai.snmm.core.pointer

import io.cat.ai.snmm.core.jni.SnmmCore

package object generic {

  trait Implicits
    extends NativePointerImplicit
      with NativeSizeImplicit
      with NativeStringImplicit
      with NativeMemoryAllocatorImplicit
      with PointerValueAssignerImplicit

  trait NativeStringImplicit

  trait NativeMemoryAllocatorImplicit {

    implicit def nativeHeapMemoryDynamicAllocator: NativeHeapDynamicMemoryAllocator = new NativeHeapDynamicMemoryAllocator {

      override def allocateMemBlock(size: Int): Pointer[Unit] =
        PointerFactory(SnmmCore.SNMM_CORE_JNI.malloc(size))

      override def allocateMemBlockWithInit(nitems: Int, size: Int): Pointer[Unit] =
        PointerFactory(SnmmCore.SNMM_CORE_JNI.calloc(nitems, size))

      override def reallocateMemBlock[A](ptr: Pointer[A], newSize: Int): Pointer[Unit] =
        PointerFactory(SnmmCore.SNMM_CORE_JNI.realloc(ptr.address, newSize))

      override def deallocateMemBlock(ptr: Pointer[_]): Unit =
        SnmmCore.SNMM_CORE_JNI.free(ptr.address)
    }
  }

  trait NativePointerImplicit {

    implicit def nativeHeapBytePtr: NativeHeapPointer[Byte] = new NativeHeapPointer[Byte] {

      override def deref(ptr: Pointer[Byte]): Byte = SnmmCore.SNMM_CORE_JNI.deref_byte(ptr.address)

      override def addressOf(value: Byte): Pointer[Byte] =
        PointerFactory.create[Byte](SnmmCore.SNMM_CORE_JNI.byte_pointer(value))
    }

    implicit def nativeHeapShortPtr: NativeHeapPointer[Short] = new NativeHeapPointer[Short] {

      override def deref(ptr: Pointer[Short]): Short = SnmmCore.SNMM_CORE_JNI.deref_short(ptr.address)

      override def addressOf(value: Short): Pointer[Short] =
        PointerFactory.create[Short](SnmmCore.SNMM_CORE_JNI.short_pointer(value))
    }

    implicit def nativeHeapIntPtr: NativeHeapPointer[Int] = new NativeHeapPointer[Int] {

      override def deref(ptr: Pointer[Int]): Int = SnmmCore.SNMM_CORE_JNI.deref_int(ptr.address)

      override def addressOf(value: Int): Pointer[Int] =
        PointerFactory.create[Int](SnmmCore.SNMM_CORE_JNI.integer_pointer(value))
    }

    implicit def nativeHeapCharPtr: NativeHeapPointer[Char] = new NativeHeapPointer[Char] {

      override def deref(ptr: Pointer[Char]): Char = SnmmCore.SNMM_CORE_JNI.deref_char(ptr.address)

      override def addressOf(value: Char): Pointer[Char] =
        PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.char_pointer(value))
    }

    implicit def nativeHeapFloatPtr: NativeHeapPointer[Float] = new NativeHeapPointer[Float] {

      override def deref(ptr: Pointer[Float]): Float = SnmmCore.SNMM_CORE_JNI.deref_float(ptr.address)

      override def addressOf(value: Float): Pointer[Float] =
        PointerFactory.create[Float](SnmmCore.SNMM_CORE_JNI.float_pointer(value))
    }

    implicit def nativeHeapLongPtr: NativeHeapPointer[Long] = new NativeHeapPointer[Long] {

      override def deref(ptr: Pointer[Long]): Long = SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address)

      override def addressOf(value: Long): Pointer[Long] =
        PointerFactory.create[Long](SnmmCore.SNMM_CORE_JNI.long_pointer(value))
    }

    implicit def nativeHeapDoublePtr: NativeHeapPointer[Double] = new NativeHeapPointer[Double] {

      override def deref(ptr: Pointer[Double]): Double = SnmmCore.SNMM_CORE_JNI.deref_double(ptr.address)

      override def addressOf(value: Double): Pointer[Double] =
        PointerFactory.create[Double](SnmmCore.SNMM_CORE_JNI.double_pointer(value))
    }

    implicit def nativeHeapBoolDoublePtr: NativeHeapPointerToPointer[Boolean] = new NativeHeapPointerToPointer[Boolean] {

      override def deref(ptr: Pointer[Pointer[Boolean]]): Pointer[Boolean] =
        PointerFactory.create[Boolean](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))

      override def addressOf(value: Pointer[Boolean]): Pointer[Pointer[Boolean]] =
        PointerFactory.create {
          PointerFactory.create[Boolean](SnmmCore.SNMM_CORE_JNI.deref_long(value.address))
        }
    }

    implicit def nativeHeapCharDoublePtr: NativeHeapPointerToPointer[Char] = new NativeHeapPointerToPointer[Char] {

      override def deref(ptr: Pointer[Pointer[Char]]): Pointer[Char] =
        PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))

      override def addressOf(value: Pointer[Char]): Pointer[Pointer[Char]] =
        PointerFactory {
          PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
        }
    }

    implicit def nativeHeapByteDoublePtr: NativeHeapPointerToPointer[Byte] = new NativeHeapPointerToPointer[Byte] {

      override def deref(ptr: Pointer[Pointer[Byte]]): Pointer[Byte] =
        PointerFactory.create[Byte](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))

      override def addressOf(value: Pointer[Byte]): Pointer[Pointer[Byte]] =
        PointerFactory {
          PointerFactory.create[Byte](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
        }
    }

    implicit def nativeHeapShortDoublePtr: NativeHeapPointerToPointer[Short] = new NativeHeapPointerToPointer[Short] {

      override def deref(ptr: Pointer[Pointer[Short]]): Pointer[Short] =
        PointerFactory.create[Short](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))

      override def addressOf(value: Pointer[Short]): Pointer[Pointer[Short]] = ???
    }

    implicit def nativeHeapIntDoublePtr: NativeHeapPointerToPointer[Int] = new NativeHeapPointerToPointer[Int] {

      override def deref(ptr: Pointer[Pointer[Int]]): Pointer[Int] =
        PointerFactory.create[Int](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))

      override def addressOf(value: Pointer[Int]): Pointer[Pointer[Int]] =
        PointerFactory {
          PointerFactory.create[Int](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
        }
    }

    implicit def nativeHeapLongDoublePtr: NativeHeapPointerToPointer[Long] = new NativeHeapPointerToPointer[Long] {

      override def deref(ptr: Pointer[Pointer[Long]]): Pointer[Long] =
        PointerFactory.create[Long](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))

      override def addressOf(value: Pointer[Long]): Pointer[Pointer[Long]] =
        PointerFactory {
          PointerFactory.create[Long](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
        }
    }

    implicit def nativeHeapFloatDoublePtr: NativeHeapPointerToPointer[Float] = new NativeHeapPointerToPointer[Float] {

      override def deref(ptr: Pointer[Pointer[Float]]): Pointer[Float] =
        PointerFactory.create[Float](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))

      override def addressOf(value: Pointer[Float]): Pointer[Pointer[Float]] =
        PointerFactory {
          PointerFactory.create[Float](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
        }
    }

    implicit def nativeHeapDoubleDoublePtr: NativeHeapPointerToPointer[Double] = new NativeHeapPointerToPointer[Double] {

      override def deref(ptr: Pointer[Pointer[Double]]): Pointer[Double] =
        PointerFactory.create[Double](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))

      override def addressOf(value: Pointer[Double]): Pointer[Pointer[Double]] =
        PointerFactory {
          PointerFactory.create[Double](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
        }
    }

    implicit def nativeHeapBoolTriplePtr: NativeHeapPointerToPointer[Pointer[Boolean]] = new NativeHeapPointerToPointer[Pointer[Boolean]] {

      override def deref(ptr: Pointer[Pointer[Pointer[Boolean]]]): Pointer[Pointer[Boolean]] =
        PointerFactory {
          PointerFactory.create[Boolean](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))
        }

      override def addressOf(value: Pointer[Pointer[Boolean]]): Pointer[Pointer[Pointer[Boolean]]] =
        PointerFactory {
          PointerFactory {
            PointerFactory.create[Boolean](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
          }
        }
    }

    implicit def nativeHeapCharTriplePtr: NativeHeapPointerToPointer[Pointer[Char]] = new NativeHeapPointerToPointer[Pointer[Char]] {

      override def deref(ptr: Pointer[Pointer[Pointer[Char]]]): Pointer[Pointer[Char]] =
        PointerFactory {
          PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))
        }

      override def addressOf(value: Pointer[Pointer[Char]]): Pointer[Pointer[Pointer[Char]]] =
        PointerFactory {
          PointerFactory {
            PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
          }
        }
    }

    implicit def nativeHeapByteTriplePtr: NativeHeapPointerToPointer[Pointer[Byte]] = new NativeHeapPointerToPointer[Pointer[Byte]] {

      override def deref(ptr: Pointer[Pointer[Pointer[Byte]]]): Pointer[Pointer[Byte]] =
        PointerFactory {
          PointerFactory.create[Byte](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))
        }

      override def addressOf(value: Pointer[Pointer[Byte]]): Pointer[Pointer[Pointer[Byte]]] =
        PointerFactory {
          PointerFactory {
            PointerFactory.create[Byte](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
          }
        }
    }

    implicit def nativeHeapShortTriplePtr: NativeHeapPointerToPointer[Pointer[Short]] = new NativeHeapPointerToPointer[Pointer[Short]] {

      override def deref(ptr: Pointer[Pointer[Pointer[Short]]]): Pointer[Pointer[Short]] =
        PointerFactory {
          PointerFactory.create[Short](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))
        }

      override def addressOf(value: Pointer[Pointer[Short]]): Pointer[Pointer[Pointer[Short]]] =
        PointerFactory {
          PointerFactory {
            PointerFactory.create[Short](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
          }
        }
    }

    implicit def nativeHeapIntTriplePtr: NativeHeapPointerToPointer[Pointer[Int]] = new NativeHeapPointerToPointer[Pointer[Int]] {

      override def deref(ptr: Pointer[Pointer[Pointer[Int]]]): Pointer[Pointer[Int]] =
        PointerFactory {
          PointerFactory.create[Int](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))
        }

      override def addressOf(value: Pointer[Pointer[Int]]): Pointer[Pointer[Pointer[Int]]] =
        PointerFactory {
          PointerFactory {
            PointerFactory.create[Int](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
          }
        }
    }

    implicit def nativeHeapLongTriplePtr: NativeHeapPointerToPointer[Pointer[Long]] = new NativeHeapPointerToPointer[Pointer[Long]] {

      override def deref(ptr: Pointer[Pointer[Pointer[Long]]]): Pointer[Pointer[Long]] =
        PointerFactory {
          PointerFactory.create[Long](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))
        }

      override def addressOf(value: Pointer[Pointer[Long]]): Pointer[Pointer[Pointer[Long]]] =
        PointerFactory {
          PointerFactory {
            PointerFactory.create[Long](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
          }
        }
    }

    implicit def nativeHeapFloatTriplePtr: NativeHeapPointerToPointer[Pointer[Float]] = new NativeHeapPointerToPointer[Pointer[Float]] {

      override def deref(ptr: Pointer[Pointer[Pointer[Float]]]): Pointer[Pointer[Float]] =
        PointerFactory {
          PointerFactory.create[Float](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))
        }

      override def addressOf(value: Pointer[Pointer[Float]]): Pointer[Pointer[Pointer[Float]]] =
        PointerFactory {
          PointerFactory {
            PointerFactory.create[Float](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
          }
        }
    }

    implicit def nativeHeapDoubleTriplePtr: NativeHeapPointerToPointer[Pointer[Double]] = new NativeHeapPointerToPointer[Pointer[Double]] {

      override def deref(ptr: Pointer[Pointer[Pointer[Double]]]): Pointer[Pointer[Double]] =
        PointerFactory {
          PointerFactory.create[Double](SnmmCore.SNMM_CORE_JNI.deref_long(ptr.address))
        }

      override def addressOf(value: Pointer[Pointer[Double]]): Pointer[Pointer[Pointer[Double]]] =
        PointerFactory {
          PointerFactory {
            PointerFactory.create[Double](SnmmCore.SNMM_CORE_JNI.long_pointer(value.address))
          }
        }
    }
    // *** ptr;

    implicit def nativeHeapStringPtr: NativeHeapStringPointer[Char] = new NativeHeapStringPointer[Char] {

      override def deref(ptr: Pointer[Char]): String = SnmmCore.SNMM_CORE_JNI.deref_string(ptr.address)

      override def addressOf(value: String): Pointer[Char] = PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.string_pointer(value))
    }
  }

  trait NativeSizeImplicit {

    implicit def nativeByteSize: NativeSize[Byte] = new NativeSize[Byte] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.byte_size
    }

    implicit def nativeIntSize: NativeSize[Int] = new NativeSize[Int] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.int_size
    }

    implicit def nativeBooleanSize: NativeSize[Boolean] = new NativeSize[Boolean] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.boolean_size
    }

    implicit def nativeShortSize: NativeSize[Short] = new NativeSize[Short] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.short_size
    }

    implicit def nativeCharSize: NativeSize[Char] = new NativeSize[Char] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.char_size
    }

    implicit def nativeLongSize: NativeSize[Long] = new NativeSize[Long] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.long_size
    }

    implicit def nativeFloatSize: NativeSize[Float] = new NativeSize[Float] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.float_size
    }

    implicit def nativeDoubleSize: NativeSize[Double] = new NativeSize[Double] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.double_size
    }

    implicit def nativeStringSize: NativeSize[String] = new NativeSize[String] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.string_size
    }

    implicit def nativeBytePtrSize: NativeSize[Pointer[Byte]] = new NativeSize[Pointer[Byte]] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.byte_pointer_size
    }

    implicit def nativeCharPtrSize: NativeSize[Pointer[Char]] = new NativeSize[Pointer[Char]] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.char_pointer_size
    }

    implicit def nativeShortPtrSize: NativeSize[Pointer[Short]] = new NativeSize[Pointer[Short]] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.short_pointer_size
    }

    implicit def nativeIntPtrSize: NativeSize[Pointer[Int]] = new NativeSize[Pointer[Int]] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.integer_pointer_size
    }

    implicit def nativeFloatPtrSize: NativeSize[Pointer[Float]] = new NativeSize[Pointer[Float]] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.float_pointer_size
    }

    implicit def nativeLongPtrSize: NativeSize[Pointer[Long]] = new NativeSize[Pointer[Long]] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.long_pointer_size
    }

    implicit def nativeDoublePtrSize: NativeSize[Pointer[Double]] = new NativeSize[Pointer[Double]] {
      override def size: Int = SnmmCore.SNMM_CORE_JNI.double_pointer_size
    }
  }

  trait PointerValueAssignerImplicit extends NativeSizeImplicit {

    private def address[A](addr: Long, idx: Int)
                          (implicit nSize: NativeSize[A]): Long = addr + idx * nSize.size

    implicit def nativeBooleanPtrValueAssigner: PointerValueAssigner[Boolean] =
      (pointer: Long, idx: Int, value: Boolean) => SnmmCore.SNMM_CORE_JNI.assign_boolean(address[Boolean](pointer, idx), value)

    implicit def nativeBytePtrValueAssigner: PointerValueAssigner[Byte] =
      (pointer: Long, idx: Int, value: Byte) => SnmmCore.SNMM_CORE_JNI.assign_byte(address[Byte](pointer, idx), value)

    implicit def nativeCharPtrValueAssigner: PointerValueAssigner[Char] =
      (pointer: Long, idx: Int, value: Char) => SnmmCore.SNMM_CORE_JNI.assign_char(address[Char](pointer, idx), value)

    implicit def nativeShortPtrValueAssigner: PointerValueAssigner[Short] =
      (pointer: Long, idx: Int, value: Short) => SnmmCore.SNMM_CORE_JNI.assign_short(address[Short](pointer, idx), value)

    implicit def nativeIntPtrValueAssigner: PointerValueAssigner[Int] =
      (pointer: Long, idx: Int, value: Int) => SnmmCore.SNMM_CORE_JNI.assign_integer(address[Int](pointer, idx), value)

    implicit def nativeLongPtrValueAssigner: PointerValueAssigner[Long] =
      (pointer: Long, idx: Int, value: Long) => SnmmCore.SNMM_CORE_JNI.assign_long(address[Long](pointer, idx), value)

    implicit def nativeFloatPtrValueAssigner: PointerValueAssigner[Float] =
      (pointer: Long, idx: Int, value: Float) => SnmmCore.SNMM_CORE_JNI.assign_float(address[Float](pointer, idx), value)

    implicit def nativeDoublePtrValueAssigner: PointerValueAssigner[Double] =
      (pointer: Long, idx: Int, value: Double) => SnmmCore.SNMM_CORE_JNI.assign_double(address[Double](pointer, idx), value)
  }
}