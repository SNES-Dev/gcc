#ifndef GCC_W65_H
#define GCC_W65_H

/* The GNU C++ standard library requires that these macros be defined.  */
#undef CPLUSPLUS_CPP_SPEC
#define CPLUSPLUS_CPP_SPEC "-D_GNU_SOURCE %(cpp)"

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC "crt1.o%s crti.o%s crtbegin.o%s"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"

#ifndef TARGET_CPU_CPP_BUILTINS
#define TARGET_CPU_CPP_BUILTINS() \
        do{ \
            builtin_define("__w65__");\
            builtin_define("__65816__");\
            builtin_define("__WDC65C816__");\
        }while(0)
#endif

/* Force the generation of dwarf .debug_frame sections even if not
   compiling -g.  This guarantees that we can unwind the stack.  */
#define DWARF2_FRAME_INFO 1

#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG

/* Generate .file/.loc directives, so that the assembler generates the
   line table.  */
#define DWARF2_ASM_LINE_DEBUG_INFO 1

/* Storage layout.  */
#define BITS_BIG_ENDIAN     0

#define BYTES_BIG_ENDIAN    0

#define WORDS_BIG_ENDIAN    0

#define UNITS_PER_WORD      2

#define POINTER_SIZE        32

#define PARM_BOUNDARY       16

#define STACK_BOUNDARY      (MAX (BIGGEST_ALIGNMENT, PARM_BOUNDARY))

#define FUNCTION_BOUNDARY   1

#define BIGGEST_ALIGNMENT 32

#define INT_TYPE_SIZE 2

#define SHORT_TYPE_SIZE     16

#define LONG_TYPE_SIZE      32

#define LONG_LONG_TYPE_SIZE 64

#define FLOAT_TYPE_SIZE     32

#define DOUBLE_TYPE_SIZE    64

#define LONG_DOUBLE_TYPE_SIZE 64

#define DEFAULT_SIGNED_CHAR 1

#define SIZE_TYPE           "long unsigned int"

#define PTRDIFF_TYPE        "long int"

#define WCHAR_TYPE          "short unsigned int"

#define WCHAR_TYPE_SIZE     16

/* By default, the C++ compiler will use the lowest bit of the pointer
   to function to indicate a pointer-to-member-function points to a
   virtual member function.  However, in CR architecture FUNCTION_BOUNDARY
   indicates function addresses are always even, but function pointers can be
   odd (after right-shifting them when loading them into a register), and the
   default doesn't work.  In that case, the lowest bit of the delta
   field will be used (the remainder of the field is shifted to the left).  */
#define TARGET_PTRMEMFUNC_VBIT_LOCATION     ptrmemfunc_vbit_in_delta

/* Define DEFAULT_PCC_STRUCT_RETURN to 1 if all structure and union return
   values must be in memory.  */
#define DEFAULT_PCC_STRUCT_RETURN 0

#define FIRST_PSEUDO_REGISTER       7

/* 1 for registers that have pervasive standard uses
   and are not available for the register allocator.
   On the CR16, only the stack pointer (r15) is such.  */
#define FIXED_REGISTERS                               \
  {                                                   \
  /* A, X, Y, D, B, K, S*/                            \
     0, 0, 0, 0, 1, 1, 1,                             \
     0, 0, 0, 0, 0, 0, 0, 0                           \
  }   

#define CALL_USED_REGISTERS                           \
  {                                                   \
    /* A, X, Y, D, B, K, S*/                          \
       1, 1, 1, 0, 1, 0, 0,                           \
       1, 1, 1, 1, 1, 0, 0, 0,                        \
  }

#define LONG_REG_P(REGNO)                                                    \
    ((REGNO)>6)

/*To ensure correct dwarf unwinding.  */
#define LIBGCC2_UNWIND_ATTRIBUTE __attribute__((optimize ("no-gcse","no-dse")))

#endif /* GCC_W65_H */