# snmm
Scala Native Memory Management

snmm - library allowing to work with off-heap memory using Scala objects

snmm enables programmer to work with native objects, and all of them - is a function calls to JNI methods

Scala -> JVM -> JNI -> C -> OS

## Getting Started

snmm consists of three important components: 
- Pointer
- AbstractStruct 
- OS-specific memory utils

Pointer - is a heart of snmm; is a key wrapper that stores an address. Wrapper for all offheap objects

AbstractStruct - base class for all case classes, that anootated with macro annotations [@struct, @offheap_alloc]

OS-specific memory utils - now it's not tested, but snmm includes POSIX's mman and Windows memoryapi libraries

# snmm C-style syntax

snmm allows you to write code in C-style, you just need to import the key implicit

```
import io.cat.ai.snmm.CSyntax._
import io.cat.ai.snmm.common.CTypeAlias._
import io.cat.ai.snmm.Implicits._

val i: int = 64

// get the address -> pointer to value
val i_ptr: *[int] = &(i)

// dereferences the pointer
printf("*i_ptr: %i \n" *(i_ptr))

free(i_ptr)
```
And yeah, you need to release the memory


## Library usage

Simple operations with off-heap data
```
import io.cat.ai.snmm.CSyntax._
import io.cat.ai.snmm.common.CTypeAlias._
import io.cat.ai.snmm.Implicits._
import io.cat.ai.snmm.core.pointer.{NULL, Pointer}
import io.cat.ai.snmm.stdlib._
import io.cat.ai.snmm.string._

var n: int32_t = 5
var ptr: *[int32_t] = NULL

// allocates off-heap memory for 5 ints and initializes with 0
ptr = cast[int32_t](calloc(n, sizeof[int32_t]))

var i: int32_t = 0

// imperative for loop that assigns value to pointer
`for`(i, i < n, i = i + 1) {
    ptr(i) = i + 1
}

// ptr -> [1, 2, 3, 4, 5]

n = 10

// resizes the memory block pointed to by ptr that was previously allocated
ptr = cast[int32_t](realloc(ptr, n * sizeof[int32_t]))

i = 5

`for`(i, i < n, i = i + 1) {
    ptr(i) = i
}

// ptr -> [1, 2, 3, 4, 5, 5, 6, 7, 8, 9]

free(ptr)
```

C-string via Java/Scala string
```
// copies JVM string to allocated off-heap memory
val chars: *[char] = &("STRING")
```

C-string operations on Java/Scala:

```
var i: int = 0

  var n: int32_t = 6

  val char_ptr: *[uint16_t] = cast[uint16_t](malloc(sizeof[uint16_t] * n))

  `for`(i, i < n, i = i + 1) {
    i match {
      case first  @ 0 => char_ptr(first)  = 'S'
      case second @ 1 => char_ptr(second) = 'T'
      case third  @ 2 => char_ptr(third)  = 'R'
      case fourth @ 3 => char_ptr(fourth) = 'I'
      case fifth  @ 4 => char_ptr(fifth)  = 'N'
      case sixth  @ 5 => char_ptr(sixth)  = 'G'
    }
  }

  i = 0

  `for`(i, i < n, i = i + 1) {
    if (i != 5)
      print(s"${*(char_ptr + i)}, ")
    else
      println(*(char_ptr + i))
  }

  printf("*(char_ptr): %s", *(char_ptr))
  
  free(char_ptr)
```

Off-heap structures

```
object StructTestObj {
  @struct @offheap_alloc
  case class User(number: Int = 1, id: Long = 2L)
}

import StructTestObj._ 

val userStruct = User()

import User._

printf("User number: %i \n", userStruct*->number)
printf("User id: %i \n", userStruct*->id)

// *-> method generated via macros
// number and id - is a methods, that genereated by macro and exists on User companion

free(userStruct)

```