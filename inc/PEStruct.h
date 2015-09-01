#ifndef DATATYPE_H
#define DATATYPE_H
#include "datatype.h"
#endif



//Image Format --------PE文件格式结构体定义
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//PE文件格式结构体定义DOS头。
typedef struct _IMAGE_DOS_HEADER {    // DOS .EXE header
	WORD   e_magic;                     // Magic number
	WORD   e_cblp;                      // Bytes on last page of file
	WORD   e_cp;                        // Pages in file
	WORD   e_crlc;                      // Relocations
	WORD   e_cparhdr;                   // Size of header in paragraphs
	WORD   e_minalloc;                  // Minimum extra paragraphs needed
	WORD   e_maxalloc;                  // Maximum extra paragraphs needed
	WORD   e_ss;                        // Initial (relative) SS value
	WORD   e_sp;                        // Initial SP value
	WORD   e_csum;                      // Checksum
	WORD   e_ip;                        // Initial IP value
	WORD   e_cs;                        // Initial (relative) CS value
	WORD   e_lfarlc;                    // File address of relocation table
	WORD   e_ovno;                      // Overlay number
	WORD   e_res[4];                    // Reserved words
	WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
	WORD   e_oeminfo;                   // OEM information; e_oemid specific
	WORD   e_res2[10];                  // Reserved words
	LONG   e_lfanew;                    // File address of new exe header
}IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

//PE文件头DOS后面的部分
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
// File header format.//COFF 文件格式结构体，说明COFF格式结构。
typedef struct _IMAGE_FILE_HEADER {
	WORD    Machine;
	WORD    NumberOfSections;
	DWORD   TimeDateStamp;
	DWORD   PointerToSymbolTable;
	DWORD   NumberOfSymbols;
	WORD    SizeOfOptionalHeader;
	WORD    Characteristics;
}IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
//Characteristics;的取值常量组合
#define IMAGE_SIZEOF_FILE_HEADER             20 //20字节
#define IMAGE_FILE_RELOCS_STRIPPED           0x0001 // Relocation info stripped from file.
#define IMAGE_FILE_EXECUTABLE_IMAGE          0x0002 // File is executable (i.e. no unresolved externel references).
#define IMAGE_FILE_LINE_NUMS_STRIPPED        0x0004 // Line nunbers stripped from file.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED       0x0008 // Local symbols stripped from file.
#define IMAGE_FILE_AGGRESIVE_WS_TRIM         0x0010 // Agressively trim working set
#define IMAGE_FILE_LARGE_ADDRESS_AWARE       0x0020 // App can handle >2gb addresses
#define IMAGE_FILE_BYTES_REVERSED_LO         0x0080 // Bytes of machine word are reversed.
#define IMAGE_FILE_32BIT_MACHINE             0x0100 // 32 bit word machine.
#define IMAGE_FILE_DEBUG_STRIPPED            0x0200 // Debugging info stripped from file in .DBG file
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP   0x0400 // If Image is on removable media, copy and run from the swap file.
#define IMAGE_FILE_NET_RUN_FROM_SWAP         0x0800 // If Image is on Net, copy and run from the swap file.
#define IMAGE_FILE_SYSTEM                    0x1000 // System File.
#define IMAGE_FILE_DLL                       0x2000 // File is a DLL.
#define IMAGE_FILE_UP_SYSTEM_ONLY            0x4000 // File should only be run on a UP machine
#define IMAGE_FILE_BYTES_REVERSED_HI         0x8000 // Bytes of machine word are reversed.
#define IMAGE_FILE_MACHINE_UNKNOWN           0
#define IMAGE_FILE_MACHINE_I386              0x014c // Intel 386.
#define IMAGE_FILE_MACHINE_R3000             0x0162 // MIPS little-endian, 0x160 big-endian
#define IMAGE_FILE_MACHINE_R4000             0x0166 // MIPS little-endian
#define IMAGE_FILE_MACHINE_R10000            0x0168 // MIPS little-endian
#define IMAGE_FILE_MACHINE_WCEMIPSV2         0x0169 // MIPS little-endian WCE v2
#define IMAGE_FILE_MACHINE_ALPHA             0x0184 // Alpha_AXP
#define IMAGE_FILE_MACHINE_POWERPC           0x01F0 // IBM PowerPC Little-Endian
#define IMAGE_FILE_MACHINE_SH3               0x01a2 // SH3 little-endian
#define IMAGE_FILE_MACHINE_SH3E              0x01a4 // SH3E little-endian
#define IMAGE_FILE_MACHINE_SH4               0x01a6 // SH4 little-endian
#define IMAGE_FILE_MACHINE_ARM               0x01c0 // ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB             0x01c2
#define IMAGE_FILE_MACHINE_IA64              0x0200 // Intel 64
#define IMAGE_FILE_MACHINE_MIPS16            0x0266 // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU           0x0366 // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU16         0x0466 // MIPS
#define IMAGE_FILE_MACHINE_ALPHA64           0x0284 // ALPHA64
#define IMAGE_FILE_MACHINE_AXP64             IMAGE_FILE_MACHINE_ALPHA64


// DataDirectory数据目录数组的下标的宏定义。序号表示不同的目录。
//*******************************************************************
#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory
#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory
#define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION       3   // Exception Directory
#define IMAGE_DIRECTORY_ENTRY_SECURITY        4   // Security Directory
#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table
#define IMAGE_DIRECTORY_ENTRY_DEBUG           6   // Debug Directory
//      IMAGE_DIRECTORY_ENTRY_COPYRIGHT       7   // (X86 usage)
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7   // Architecture Specific Data
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8   // RVA of GP
#define IMAGE_DIRECTORY_ENTRY_TLS             9   // TLS Directory
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10   // Load Configuration Directory
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11   // Bound Import Directory in headers
#define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13   // Delay Load Import Descriptors
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14   // COM Runtime descriptor
//Directory format. 数组元素格式，目录数组元素类型。每个元素8个字节，共16*8=128个B。
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
typedef struct _IMAGE_DATA_DIRECTORY {
				DWORD   VirtualAddress; //地址指向某目录。
				DWORD   Size;           // 大小
}IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

//Optional header format. 可选头 
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//pe文件内定义文件头的结构。32位机器PE文件头DOS后面的部分。之二。
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

typedef struct _IMAGE_OPTIONAL_HEADER {
	// Standard fields.
	WORD    Magic;
	BYTE    MajorLinkerVersion;
	BYTE    MinorLinkerVersion;
	DWORD   SizeOfCode;
	DWORD   SizeOfInitializedData;
	DWORD   SizeOfUninitializedData;
	DWORD   AddressOfEntryPoint;
	DWORD   BaseOfCode;
	DWORD   BaseOfData;
	// NT additional fields.
	DWORD   ImageBase;
	DWORD   SectionAlignment;
	DWORD   FileAlignment;
	WORD    MajorOperatingSystemVersion;
	WORD    MinorOperatingSystemVersion;
	WORD    MajorImageVersion;
	WORD    MinorImageVersion;
	WORD    MajorSubsystemVersion;
	WORD    MinorSubsystemVersion;
	DWORD   Win32VersionValue;
	DWORD   SizeOfImage;
	DWORD   SizeOfHeaders;
	DWORD   CheckSum;
	WORD    Subsystem;
	WORD    DllCharacteristics;
	DWORD   SizeOfStackReserve;
	DWORD   SizeOfStackCommit;
	DWORD   SizeOfHeapReserve;
	DWORD   SizeOfHeapCommit;
	DWORD   LoaderFlags;
	DWORD   NumberOfRvaAndSizes;
	//IMAGE_NUMBEROF_DIRECTORY_ENTRIES=16
   IMAGE_DATA_DIRECTORY   DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];    //共有16个元素，每个元素包括相关表的地址和大小。
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32; //定义成一个宏名了。


//PE真正的文件头 //32 bit机器
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
typedef struct _IMAGE_NT_HEADERS {               
	DWORD                      Signature;
	IMAGE_FILE_HEADER          FileHeader;          //第一部分结构
	IMAGE_OPTIONAL_HEADER32    OptionalHeader;      //第二部分结构
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;       
// DLL support.Export Format输出目录结构
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
typedef struct _IMAGE_EXPORT_DIRECTORY {
	DWORD   Characteristics;
	DWORD   TimeDateStamp;
	WORD    MajorVersion;
	WORD    MinorVersion;
	DWORD   Name;
	DWORD   Base;
	DWORD   NumberOfFunctions;
	DWORD   NumberOfNames;
	DWORD   AddressOfFunctions;     // RVA from base of image
	DWORD   AddressOfNames;         // RVA from base of image
	DWORD   AddressOfNameOrdinals; // RVA from base of image
} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;
// Import Format输入目录
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//导入描述符:有几个DLL文件就有几个这样的结构体。其偏移地址保存在前面的OPTIONALHEADER内的目录数组内。
//共有5个字段，20个字节长度。OriginalFirstThunk和FirstThunk分别为不同的地址，但指向的数组Thunk都是一样的内容。
typedef struct _IMAGE_IMPORT_DESCRIPTOR {
union {
		DWORD   Characteristics;             // 0 for terminating null import descriptor
		DWORD   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)指向未绑定的地址表。
	   };                                                      //指向名字表INT。_IMAGE_IMPORT_BY_NAME结构体
DWORD   TimeDateStamp;                    // 0 if not bound,// -1 if bound, and real date\time stamp    in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)   // O.W. date/time stamp of DLL bound to (Old BIND)
DWORD   ForwarderChain;                    // -1 if no forwarders
DWORD   Name;
DWORD   FirstThunk;                           // RVA to IAT (if bound this IAT has actual addresses) 指向地址表
}IMAGE_IMPORT_DESCRIPTOR,*PIMAGE_IMPORT_DESCRIPTOR;

typedef IMAGE_IMPORT_DESCRIPTOR UNALIGNED ;//*PIMAGE_IMPORT_DESCRIPTOR;


//按名导入结构体（构成名字表）
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//IMPORT表的Originalfirstthunk指针指向该结构形成的数组，Name是一个可变长度的字符数组，不是指针。这种形式比较少见。
typedef struct _IMAGE_IMPORT_BY_NAME {         
	WORD    Hint;                      //序号
	BYTE    Name[1];                   //函数名
} IMAGE_IMPORT_BY_NAME, *PIMAGE_IMPORT_BY_NAME;

//THUNK 数据结构
//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
//其实下面这个结构里面包含的一个联合体，所以就一个DWORD类型的指针。DLL加载完毕解析完毕后就把所需函数的实际地址填入，这个结构形成一个类似软管连接器的东西，把主调函数和被调函数之间联系起来。其实就是等着加载器把DLL中的函数地址给EXE文件内的这个表进行填空工作，然后EXE就可以调用DLL里面的函数了。多个THUNK对应多个函数从而构成一个数组。一开始是里面的地址是指向函数名表，后来则FirstAdress指向的thunk表改为指向实际函数体入口。originalfirstaddress仍然指向原来的函数名表。以备加载器还需要根据这函数名表查找并加载其他函数。
typedef struct _IMAGE_THUNK_DATA32 {
	union { PBYTE ForwarderString;
			PDWORD Function;
			DWORD Ordinal;
			PIMAGE_IMPORT_BY_NAME AddressOfData;
		  } u1;
} IMAGE_THUNK_DATA32;
typedef IMAGE_THUNK_DATA32 * PIMAGE_THUNK_DATA32;


//节头格式（决定物理存储位置）
//〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓
#define IMAGE_SIZEOF_SHORT_NAME              8   //名字字符个数最多8个
typedef struct _IMAGE_SECTION_HEADER {
	BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
	union {
			DWORD   PhysicalAddress;
			DWORD   VirtualSize;
	} Misc;
	DWORD   VirtualAddress;
	DWORD   SizeOfRawData;
	DWORD   PointerToRawData;
	DWORD   PointerToRelocations;
	DWORD   PointerToLinenumbers;
	WORD    NumberOfRelocations;
	WORD    NumberOfLinenumbers;
	DWORD   Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

//---段表定义结构体类型,有多少个段，就有多少个该类型的数组元素。段表的后面是跟着的实际的各个段了。
// Section characteristics.段的属性
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define IMAGE_SIZEOF_SECTION_HEADER          40
//      IMAGE_SCN_TYPE_REG                   0x00000000 // Reserved.
//      IMAGE_SCN_TYPE_DSECT                 0x00000001 // Reserved.
//      IMAGE_SCN_TYPE_NOLOAD                0x00000002 // Reserved.
//      IMAGE_SCN_TYPE_GROUP                 0x00000004 // Reserved.
#define IMAGE_SCN_TYPE_NO_PAD                0x00000008 // Reserved.
//      IMAGE_SCN_TYPE_COPY                  0x00000010 // Reserved.
#define IMAGE_SCN_CNT_CODE                   0x00000020 // Section contains code.
#define IMAGE_SCN_CNT_INITIALIZED_DATA       0x00000040 // Section contains initialized data.
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA     0x00000080 // Section contains uninitialized data.
#define IMAGE_SCN_LNK_OTHER                  0x00000100 // Reserved.
#define IMAGE_SCN_LNK_INFO                   0x00000200 // Section contains comments or some other type of information.
//      IMAGE_SCN_TYPE_OVER                  0x00000400 // Reserved.
#define IMAGE_SCN_LNK_REMOVE                 0x00000800 // Section contents will not become part of image.
#define IMAGE_SCN_LNK_COMDAT                 0x00001000 // Section contents comdat.
//                                           0x00002000 // Reserved.
//      IMAGE_SCN_MEM_PROTECTED - Obsolete   0x00004000
#define IMAGE_SCN_NO_DEFER_SPEC_EXC          0x00004000 // Reset speculative exceptions handling bits in the TLB entries for this section.
#define IMAGE_SCN_GPREL                      0x00008000 // Section content can be accessed relative to GP
#define IMAGE_SCN_MEM_FARDATA                0x00008000
//      IMAGE_SCN_MEM_SYSHEAP - Obsolete    0x00010000
#define IMAGE_SCN_MEM_PURGEABLE              0x00020000
#define IMAGE_SCN_MEM_16BIT                  0x00020000
#define IMAGE_SCN_MEM_LOCKED                 0x00040000
#define IMAGE_SCN_MEM_PRELOAD                0x00080000
#define IMAGE_SCN_ALIGN_1BYTES               0x00100000 //
#define IMAGE_SCN_ALIGN_2BYTES               0x00200000 //
#define IMAGE_SCN_ALIGN_4BYTES               0x00300000 //
#define IMAGE_SCN_ALIGN_8BYTES               0x00400000 //
#define IMAGE_SCN_ALIGN_16BYTES              0x00500000 // Default alignment if no others are specified.
#define IMAGE_SCN_ALIGN_32BYTES              0x00600000 //
#define IMAGE_SCN_ALIGN_64BYTES              0x00700000 //
#define IMAGE_SCN_ALIGN_128BYTES             0x00800000 //
#define IMAGE_SCN_ALIGN_256BYTES             0x00900000 //
#define IMAGE_SCN_ALIGN_512BYTES             0x00A00000 //
#define IMAGE_SCN_ALIGN_1024BYTES            0x00B00000 //
#define IMAGE_SCN_ALIGN_2048BYTES            0x00C00000 //
#define IMAGE_SCN_ALIGN_4096BYTES            0x00D00000 //
#define IMAGE_SCN_ALIGN_8192BYTES            0x00E00000 //
// Unused                                    0x00F00000
#define IMAGE_SCN_LNK_NRELOC_OVFL            0x01000000 // Section contains extended relocations.
#define IMAGE_SCN_MEM_DISCARDABLE            0x02000000 // Section can be discarded.
#define IMAGE_SCN_MEM_NOT_CACHED             0x04000000 // Section is not cachable.
#define IMAGE_SCN_MEM_NOT_PAGED              0x08000000 // Section is not pageable.
#define IMAGE_SCN_MEM_SHARED                 0x10000000 // Section is shareable.
#define IMAGE_SCN_MEM_EXECUTE                0x20000000 // Section is executable.
#define IMAGE_SCN_MEM_READ                   0x40000000 // Section is readable.
#define IMAGE_SCN_MEM_WRITE                  0x80000000 // Section is writeable.
//Symbol format符号结构体
//======================================================
typedef struct _IMAGE_SYMBOL {
	union {BYTE ShortName[8];        //符号名
		   struct {DWORD   Short;     // if 0, use LongName 
				   DWORD   Long;      // offset into string table
				  }Name;
		   PBYTE LongName[2];
		  }N;
	DWORD   Value;                   //符号值
	SHORT   SectionNumber;           //节号
	WORD    Type;                    //类型
	BYTE    StorageClass;            //存储类
	BYTE    NumberOfAuxSymbols; //辅助符号数目
} IMAGE_SYMBOL,*PIMAGE_SYMBOL;
//typedef IMAGE_SYMBOL UNALIGNED;

#define IMAGE_SIZEOF_SYMBOL                  18

// Section values.变量或者函数在节内的序号。
//***************************************************
// Symbols have a section number of the section in which they are
// defined. Otherwise, section numbers have the following meanings:
//符号有一个节号，在那里定义的。节号的含义如下：
#define IMAGE_SYM_UNDEFINED           (SHORT)0          // Symbol is undefined or is common.
#define IMAGE_SYM_ABSOLUTE            (SHORT)-1         // Symbol is an absolute value.
#define IMAGE_SYM_DEBUG               (SHORT)-2         // Symbol is a special debug item.


#define IMAGE_FIRST_SECTION( ntheader ) ((PIMAGE_SECTION_HEADER)        \
	((ULONG_PTR)(ntheader) +                                            \
	FIELD_OFFSET( IMAGE_NT_HEADERS32, OptionalHeader ) +                 \
	((ntheader))->FileHeader.SizeOfOptionalHeader   \
	))

#define SWAPD(x) (x)
#define SWAPW(x) (x)
#define IMAGE_DOS_SIGNATURE 0x5A4D
#define IMAGE_NT_SIGNATURE 0x00004550



typedef struct _IMAGE_BASE_RELOCATION {
DWORD VirtualAddress;
DWORD SizeOfBlock;
} IMAGE_BASE_RELOCATION,*PIMAGE_BASE_RELOCATION;
