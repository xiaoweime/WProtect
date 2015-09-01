/* Standard ELF types.  */

#include <stdint.h>

/* Type for a 16-bit quantity.  */
typedef uint16_t Elf32_Half;
typedef uint16_t Elf64_Half;

/* Types for signed and unsigned 32-bit quantities.  */
typedef uint32_t Elf32_Word;
typedef int32_t  Elf32_Sword;
typedef uint32_t Elf64_Word;
typedef int32_t  Elf64_Sword;

/* Types for signed and unsigned 64-bit quantities.  */
typedef uint64_t Elf32_Xword;
typedef int64_t  Elf32_Sxword;
typedef uint64_t Elf64_Xword;
typedef int64_t  Elf64_Sxword;

/* Type of addresses.  */
typedef uint32_t Elf32_Addr;
typedef uint64_t Elf64_Addr;

/* Type of file offsets.  */
typedef uint32_t Elf32_Off;
typedef uint64_t Elf64_Off;

/* Type for section indices, which are 16-bit quantities.  */
typedef uint16_t Elf32_Section;
typedef uint16_t Elf64_Section;

/* Type for version symbol information.  */
typedef Elf32_Half Elf32_Versym;
typedef Elf64_Half Elf64_Versym;

/* The ELF file header.  This appears at the start of every ELF file.  */

#define EI_NIDENT (16)

typedef struct
{
    unsigned char e_ident[EI_NIDENT]; /* Magic number and other info */  // 1-4  为elf  5 尾
/*
struct e_ident
{
    char magic[4]; //elf
    char EI_CLASS;  //1为32位 2为64位
    char EI_DATA ;  // EI_DATA這個byte是用來判斷ELF檔是LSB(Little-endian)還是MSB(Big-endian)
    char EI_VERSION; //EI_VERSION這個byte是指出這個ELF檔的ELF header的版本是多少？目前這個值必須是EV_CURRENT
    char EI_OSABI;   //EI_OSABI這個byte是指出這個ELF檔會在那個OS上運行。 
    char EI_ABIVERSION;  //EI_ABIVERSION這個byte是指出這個ELF檔會在那個API版本上運行。一個OS上可能有多個ABI的版本在運行的版本在運行，如SYSV至少就有SVR、Solaris、SCO等ABI。0代表不指定(unspecified)
    char EI_PAD;  //EI_PAD這個byte之後的都是padding
}*/
    Elf32_Half  e_type;         /* Object file type */
    Elf32_Half    e_machine;      /* Architecture */
    Elf32_Word  e_version;      /* Object file version */
    Elf32_Addr    e_entry;        /* Entry point virtual address */
    Elf32_Off   e_phoff;        /* Program header table file offset */
    Elf32_Off e_shoff;        /* Section header table file offset */
    Elf32_Word  e_flags;        /* Processor-specific flags */
    Elf32_Half    e_ehsize;       /* ELF header size in bytes */
    Elf32_Half  e_phentsize;        /* Program header table entry size */
    Elf32_Half    e_phnum;        /* Program header table entry count */
    Elf32_Half  e_shentsize;        /* Section header table entry size */
    Elf32_Half    e_shnum;        /* Section header table entry count */
    Elf32_Half  e_shstrndx;     /* Section header string table index */
} Elf32_Ehdr;

typedef struct
{
    unsigned char e_ident[EI_NIDENT]; /* Magic number and other info */
    Elf64_Half  e_type;         /* Object file type */
    Elf64_Half    e_machine;      /* Architecture */
    Elf64_Word  e_version;      /* Object file version */
    Elf64_Addr    e_entry;        /* Entry point virtual address */
    Elf64_Off   e_phoff;        /* Program header table file offset */
    Elf64_Off e_shoff;        /* Section header table file offset */
    Elf64_Word  e_flags;        /* Processor-specific flags */
    Elf64_Half    e_ehsize;       /* ELF header size in bytes */
    Elf64_Half  e_phentsize;        /* Program header table entry size */
    Elf64_Half    e_phnum;        /* Program header table entry count */
    Elf64_Half  e_shentsize;        /* Section header table entry size */
    Elf64_Half    e_shnum;        /* Section header table entry count */
    Elf64_Half  e_shstrndx;     /* Section header string table index */
} Elf64_Ehdr;

/* Fields in the e_ident array.  The EI_* macros are indices into the
 *    array.  The macros under each EI_* macro are the values the byte
 *       may have.  */

#define EI_MAG0     0       /* File identification byte 0 index */
#define ELFMAG0     0x7f        /* Magic number byte 0 */

#define EI_MAG1     1       /* File identification byte 1 index */
#define ELFMAG1     'E'     /* Magic number byte 1 */

#define EI_MAG2     2       /* File identification byte 2 index */
#define ELFMAG2     'L'     /* Magic number byte 2 */

#define EI_MAG3     3       /* File identification byte 3 index */
#define ELFMAG3     'F'     /* Magic number byte 3 */

/* Conglomeration of the identification bytes, for easy testing as a word.  */
#define ELFMAG      "\177ELF"
#define SELFMAG     4

#define EI_CLASS    4       /* File class byte index */
#define ELFCLASSNONE    0       /* Invalid class */
#define ELFCLASS32  1       /* 32-bit objects */
#define ELFCLASS64  2       /* 64-bit objects */
#define ELFCLASSNUM 3

#define EI_DATA     5       /* Data encoding byte index */
#define ELFDATANONE 0       /* Invalid data encoding */
#define ELFDATA2LSB 1       /* 2's complement, little endian */
#define ELFDATA2MSB 2       /* 2's complement, big endian */
#define ELFDATANUM  3

#define EI_VERSION  6       /* File version byte index */
                    /* Value must be EV_CURRENT */

#define EI_OSABI            7   /* OS ABI identification */
#define ELFOSABI_NONE       0   /* UNIX System V ABI */
#define ELFOSABI_SYSV       0   /* Alias.  */
#define ELFOSABI_HPUX       1   /* HP-UX */
#define ELFOSABI_NETBSD     2   /* NetBSD.  */
#define ELFOSABI_LINUX      3   /* Linux.  */
#define ELFOSABI_SOLARIS    6   /* Sun Solaris.  */
#define ELFOSABI_AIX        7   /* IBM AIX.  */
#define ELFOSABI_IRIX       8   /* SGI Irix.  */
#define ELFOSABI_FREEBSD    9   /* FreeBSD.  */
#define ELFOSABI_TRU64      10  /* Compaq TRU64 UNIX.  */
#define ELFOSABI_MODESTO    11  /* Novell Modesto.  */
#define ELFOSABI_OPENBSD    12  /* OpenBSD.  */
#define ELFOSABI_ARM_AEABI  64  /* ARM EABI */
#define ELFOSABI_ARM        97  /* ARM */
#define ELFOSABI_STANDALONE 255 /* Standalone (embedded) application */

#define EI_ABIVERSION       8   /* ABI version */

#define EI_PAD              9   /* Byte index of padding bytes */
