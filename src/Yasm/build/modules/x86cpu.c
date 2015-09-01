/* ANSI-C code produced by genperf */
/* Command-line: genperf /home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf /home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86cpu.c */
#line 26 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"

#include <util.h>

#include <ctype.h>
#include <libyasm.h>
#include <libyasm/phash.h>

#include "modules/arch/x86/x86arch.h"

#define PROC_8086	0
#define PROC_186	1
#define PROC_286	2
#define PROC_386	3
#define PROC_486	4
#define PROC_586	5
#define PROC_686	6
#define PROC_p2		7
#define PROC_p3		8
#define PROC_p4		9
#define PROC_prescott	10
#define PROC_conroe	11
#define PROC_penryn	12
#define PROC_nehalem	13
#define PROC_westmere   14
#define PROC_sandybridge 15

static void
x86_cpu_intel(wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data)
{
    BitVector_Empty(cpu);

    BitVector_Bit_On(cpu, CPU_Priv);
    if (data >= PROC_286)
        BitVector_Bit_On(cpu, CPU_Prot);
    if (data >= PROC_386)
        BitVector_Bit_On(cpu, CPU_SMM);
    if (data >= PROC_sandybridge)
        BitVector_Bit_On(cpu, CPU_AVX);
    if (data >= PROC_westmere) {
        BitVector_Bit_On(cpu, CPU_AES);
        BitVector_Bit_On(cpu, CPU_CLMUL);
    }
    if (data >= PROC_nehalem) {
        BitVector_Bit_On(cpu, CPU_SSE42);
        BitVector_Bit_On(cpu, CPU_XSAVE);
    }
    if (data >= PROC_penryn)
        BitVector_Bit_On(cpu, CPU_SSE41);
    if (data >= PROC_conroe)
        BitVector_Bit_On(cpu, CPU_SSSE3);
    if (data >= PROC_prescott)
        BitVector_Bit_On(cpu, CPU_SSE3);
    if (data >= PROC_p4)
        BitVector_Bit_On(cpu, CPU_SSE2);
    if (data >= PROC_p3)
        BitVector_Bit_On(cpu, CPU_SSE);
    if (data >= PROC_p2)
        BitVector_Bit_On(cpu, CPU_MMX);
    if (data >= PROC_486)
        BitVector_Bit_On(cpu, CPU_FPU);
    if (data >= PROC_prescott)
        BitVector_Bit_On(cpu, CPU_EM64T);

    if (data >= PROC_p4)
        BitVector_Bit_On(cpu, CPU_P4);
    if (data >= PROC_p3)
        BitVector_Bit_On(cpu, CPU_P3);
    if (data >= PROC_686)
        BitVector_Bit_On(cpu, CPU_686);
    if (data >= PROC_586)
        BitVector_Bit_On(cpu, CPU_586);
    if (data >= PROC_486)
        BitVector_Bit_On(cpu, CPU_486);
    if (data >= PROC_386)
        BitVector_Bit_On(cpu, CPU_386);
    if (data >= PROC_286)
        BitVector_Bit_On(cpu, CPU_286);
    if (data >= PROC_186)
        BitVector_Bit_On(cpu, CPU_186);
    BitVector_Bit_On(cpu, CPU_086);

    /* Use Intel long NOPs if 686 or better */
    if (data >= PROC_686)
        arch_x86->nop = X86_NOP_INTEL;
    else
        arch_x86->nop = X86_NOP_BASIC;
}

static void
x86_cpu_ia64(wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data)
{
    BitVector_Empty(cpu);
    BitVector_Bit_On(cpu, CPU_Priv);
    BitVector_Bit_On(cpu, CPU_Prot);
    BitVector_Bit_On(cpu, CPU_SMM);
    BitVector_Bit_On(cpu, CPU_SSE2);
    BitVector_Bit_On(cpu, CPU_SSE);
    BitVector_Bit_On(cpu, CPU_MMX);
    BitVector_Bit_On(cpu, CPU_FPU);
    BitVector_Bit_On(cpu, CPU_IA64);
    BitVector_Bit_On(cpu, CPU_P4);
    BitVector_Bit_On(cpu, CPU_P3);
    BitVector_Bit_On(cpu, CPU_686);
    BitVector_Bit_On(cpu, CPU_586);
    BitVector_Bit_On(cpu, CPU_486);
    BitVector_Bit_On(cpu, CPU_386);
    BitVector_Bit_On(cpu, CPU_286);
    BitVector_Bit_On(cpu, CPU_186);
    BitVector_Bit_On(cpu, CPU_086);
}

#define PROC_bulldozer	11
#define PROC_k10    10
#define PROC_venice 9
#define PROC_hammer 8
#define PROC_k7     7
#define PROC_k6     6

static void
x86_cpu_amd(wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data)
{
    BitVector_Empty(cpu);

    BitVector_Bit_On(cpu, CPU_Priv);
    BitVector_Bit_On(cpu, CPU_Prot);
    BitVector_Bit_On(cpu, CPU_SMM);
    BitVector_Bit_On(cpu, CPU_3DNow);
    if (data >= PROC_bulldozer) {
        BitVector_Bit_On(cpu, CPU_XOP);
        BitVector_Bit_On(cpu, CPU_FMA4);
    }
    if (data >= PROC_k10)
        BitVector_Bit_On(cpu, CPU_SSE4a);
    if (data >= PROC_venice)
        BitVector_Bit_On(cpu, CPU_SSE3);
    if (data >= PROC_hammer)
        BitVector_Bit_On(cpu, CPU_SSE2);
    if (data >= PROC_k7)
        BitVector_Bit_On(cpu, CPU_SSE);
    if (data >= PROC_k6)
        BitVector_Bit_On(cpu, CPU_MMX);
    BitVector_Bit_On(cpu, CPU_FPU);

    if (data >= PROC_hammer)
        BitVector_Bit_On(cpu, CPU_Hammer);
    if (data >= PROC_k7)
        BitVector_Bit_On(cpu, CPU_Athlon);
    if (data >= PROC_k6)
        BitVector_Bit_On(cpu, CPU_K6);
    BitVector_Bit_On(cpu, CPU_686);
    BitVector_Bit_On(cpu, CPU_586);
    BitVector_Bit_On(cpu, CPU_486);
    BitVector_Bit_On(cpu, CPU_386);
    BitVector_Bit_On(cpu, CPU_286);
    BitVector_Bit_On(cpu, CPU_186);
    BitVector_Bit_On(cpu, CPU_086);

    /* Use AMD long NOPs if k6 or better */
    if (data >= PROC_k6)
        arch_x86->nop = X86_NOP_AMD;
    else
        arch_x86->nop = X86_NOP_BASIC;
}

static void
x86_cpu_set(wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data)
{
    BitVector_Bit_On(cpu, data);
}

static void
x86_cpu_clear(wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data)
{
    BitVector_Bit_Off(cpu, data);
}

static void
x86_cpu_set_sse4(wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data)
{
    BitVector_Bit_On(cpu, CPU_SSE41);
    BitVector_Bit_On(cpu, CPU_SSE42);
}

static void
x86_cpu_clear_sse4(wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data)
{
    BitVector_Bit_Off(cpu, CPU_SSE41);
    BitVector_Bit_Off(cpu, CPU_SSE42);
}

static void
x86_nop(wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data)
{
    arch_x86->nop = data;
}

#line 231 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
struct cpu_parse_data {
    const char *name;
    void (*handler) (wordptr cpu, yasm_arch_x86 *arch_x86, unsigned int data);
    unsigned int data;
};
static const struct cpu_parse_data *
cpu_find(const char *key, size_t len)
{
  static const struct cpu_parse_data pd[165] = {
#line 317 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"3dnow",		x86_cpu_set,	CPU_3DNow},
#line 380 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nof16c",		x86_cpu_clear,	CPU_F16C},
#line 261 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium-2",	x86_cpu_intel,	PROC_p2},
#line 402 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nolzcnt",	x86_cpu_clear,	CPU_LZCNT},
#line 407 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"intelnop",	x86_nop,	X86_NOP_INTEL},
#line 369 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"clmul",		x86_cpu_set,	CPU_CLMUL},
#line 272 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium-4",	x86_cpu_intel,	PROC_p4},
#line 358 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse4a",	x86_cpu_clear,	CPU_SSE4a},
#line 265 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium3",	x86_cpu_intel,	PROC_p3},
#line 359 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse4",		x86_cpu_set_sse4,	0},
#line 367 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"aes",		x86_cpu_set,	CPU_AES},
#line 387 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"eptvpid",	x86_cpu_set,	CPU_EPTVPID},
#line 379 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"f16c",		x86_cpu_set,	CPU_F16C},
#line 394 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"notsx",		x86_cpu_clear,	CPU_TSX},
#line 352 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse41",	x86_cpu_clear,	CPU_SSE41},
#line 306 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nofpu",		x86_cpu_clear,	CPU_FPU},
#line 320 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nocyrix",	x86_cpu_clear,	CPU_Cyrix},
#line 353 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse4.2",		x86_cpu_set,	CPU_SSE42},
#line 340 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noprivileged",	x86_cpu_clear,	CPU_Priv},
#line 305 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"fpu",		x86_cpu_set,	CPU_FPU},
#line 309 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse",		x86_cpu_set,	CPU_SSE},
#line 252 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium",	x86_cpu_intel,	PROC_586},
#line 388 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noeptvpid",	x86_cpu_clear,	CPU_EPTVPID},
#line 377 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"fma4",		x86_cpu_set,	CPU_FMA4},
#line 403 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"tbm",		x86_cpu_set,	CPU_TBM},
#line 262 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentiumii",	x86_cpu_intel,	PROC_p2},
#line 368 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noaes",		x86_cpu_clear,	CPU_AES},
#line 393 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"tsx",		x86_cpu_set,	CPU_TSX},
#line 383 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"rdrand",		x86_cpu_set,	CPU_RDRAND},
#line 318 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"no3dnow",	x86_cpu_clear,	CPU_3DNow},
#line 366 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nofma",		x86_cpu_clear,	CPU_FMA},
#line 242 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"80286",		x86_cpu_intel,	PROC_286},
#line 378 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nofma4",		x86_cpu_clear,	CPU_FMA4},
#line 326 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noprot",		x86_cpu_clear,	CPU_Prot},
#line 355 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse42",		x86_cpu_set,	CPU_SSE42},
#line 345 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"em64t",		x86_cpu_set,	CPU_EM64T},
#line 372 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nopclmulqdq",	x86_cpu_clear,	CPU_CLMUL},
#line 382 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nofsgsbase",	x86_cpu_clear,	CPU_FSGSBASE},
#line 313 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse3",		x86_cpu_set,	CPU_SSE3},
#line 360 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse4",		x86_cpu_clear_sse4,	0},
#line 253 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"p5",		x86_cpu_intel,	PROC_586},
#line 246 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"i386",		x86_cpu_intel,	PROC_386},
#line 347 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"ssse3",		x86_cpu_set,	CPU_SSSE3},
#line 274 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium-iv",	x86_cpu_intel,	PROC_p4},
#line 292 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"bulldozer",	x86_cpu_amd,	PROC_bulldozer},
#line 401 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"lzcnt",		x86_cpu_set,	CPU_LZCNT},
#line 386 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noxsaveopt",	x86_cpu_clear,	CPU_XSAVEOPT},
#line 328 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noprotected",	x86_cpu_clear,	CPU_Prot},
#line 357 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse4a",		x86_cpu_set,	CPU_SSE4a},
#line 408 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"amdnop",		x86_nop,	X86_NOP_AMD},
#line 255 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"i686",		x86_cpu_intel,	PROC_686},
#line 282 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"k8",		x86_cpu_amd,	PROC_hammer},
#line 289 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"k10",		x86_cpu_amd,	PROC_k10},
#line 350 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse4.1",	x86_cpu_clear,	CPU_SSE41},
#line 288 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"venice",		x86_cpu_amd,	PROC_venice},
#line 300 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sandybridge",	x86_cpu_intel,	PROC_sandybridge},
#line 338 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nopriv",		x86_cpu_clear,	CPU_Priv},
#line 312 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse2",		x86_cpu_clear,	CPU_SSE2},
#line 237 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"8086",		x86_cpu_intel,	PROC_8086},
#line 325 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"prot",		x86_cpu_set,	CPU_Prot},
#line 248 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"80486",		x86_cpu_intel,	PROC_486},
#line 251 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"i586",		x86_cpu_intel,	PROC_586},
#line 264 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"p3",		x86_cpu_intel,	PROC_p3},
#line 337 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"priv",		x86_cpu_set,	CPU_Priv},
#line 238 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"186",		x86_cpu_intel,	PROC_186},
#line 330 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noundoc",	x86_cpu_clear,	CPU_Undoc},
#line 276 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"ia64",		x86_cpu_ia64,	0},
#line 283 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"hammer",		x86_cpu_amd,	PROC_hammer},
#line 260 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium2",	x86_cpu_intel,	PROC_p2},
#line 239 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"80186",		x86_cpu_intel,	PROC_186},
#line 273 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentiumiv",	x86_cpu_intel,	PROC_p4},
#line 267 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentiumiii",	x86_cpu_intel,	PROC_p3},
#line 349 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse4.1",		x86_cpu_set,	CPU_SSE41},
#line 299 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"westmere",	x86_cpu_intel,	PROC_westmere},
#line 342 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosvm",		x86_cpu_clear,	CPU_SVM},
#line 391 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"avx2",		x86_cpu_set,	CPU_AVX2},
#line 244 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"386",		x86_cpu_intel,	PROC_386},
#line 294 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"conroe",		x86_cpu_intel,	PROC_conroe},
#line 335 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"obsolete",	x86_cpu_set,	CPU_Obs},
#line 263 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium-ii",	x86_cpu_intel,	PROC_p2},
#line 341 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"svm",		x86_cpu_set,	CPU_SVM},
#line 297 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nehalem",	x86_cpu_intel,	PROC_nehalem},
#line 259 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"p2",		x86_cpu_intel,	PROC_p2},
#line 321 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"amd",		x86_cpu_set,	CPU_AMD},
#line 286 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"athlon64",	x86_cpu_amd,	PROC_hammer},
#line 287 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"athlon-64",	x86_cpu_amd,	PROC_hammer},
#line 365 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"fma",		x86_cpu_set,	CPU_FMA},
#line 390 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosmx",		x86_cpu_clear,	CPU_SMX},
#line 376 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noxop",		x86_cpu_clear,	CPU_XOP},
#line 307 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"mmx",		x86_cpu_set,	CPU_MMX},
#line 281 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"athlon",		x86_cpu_amd,	PROC_k7},
#line 254 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"686",		x86_cpu_intel,	PROC_686},
#line 250 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"586",		x86_cpu_intel,	PROC_586},
#line 323 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"smm",		x86_cpu_set,	CPU_SMM},
#line 361 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"xsave",		x86_cpu_set,	CPU_XSAVE},
#line 275 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"williamette",	x86_cpu_intel,	PROC_p4},
#line 311 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse2",		x86_cpu_set,	CPU_SSE2},
#line 392 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noavx2",		x86_cpu_clear,	CPU_AVX2},
#line 249 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"i486",		x86_cpu_intel,	PROC_486},
#line 334 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noobs",		x86_cpu_clear,	CPU_Obs},
#line 256 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"p6",		x86_cpu_intel,	PROC_686},
#line 284 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"clawhammer",	x86_cpu_amd,	PROC_hammer},
#line 332 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noundocumented",	x86_cpu_clear,	CPU_Undoc},
#line 268 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium-iii",	x86_cpu_intel,	PROC_p3},
#line 348 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nossse3",	x86_cpu_clear,	CPU_SSSE3},
#line 354 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse4.2",	x86_cpu_clear,	CPU_SSE42},
#line 271 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium4",	x86_cpu_intel,	PROC_p4},
#line 364 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noavx",		x86_cpu_clear,	CPU_AVX},
#line 310 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse",		x86_cpu_clear,	CPU_SSE},
#line 329 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"undoc",		x86_cpu_set,	CPU_Undoc},
#line 290 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"phenom",		x86_cpu_amd,	PROC_k10},
#line 346 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noem64t",	x86_cpu_clear,	CPU_EM64T},
#line 370 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noclmul",	x86_cpu_clear,	CPU_CLMUL},
#line 240 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"i186",		x86_cpu_intel,	PROC_186},
#line 247 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"486",		x86_cpu_intel,	PROC_486},
#line 319 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"cyrix",		x86_cpu_set,	CPU_Cyrix},
#line 241 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"286",		x86_cpu_intel,	PROC_286},
#line 397 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"bmi2",		x86_cpu_set,	CPU_BMI2},
#line 266 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentium-3",	x86_cpu_intel,	PROC_p3},
#line 314 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse3",		x86_cpu_clear,	CPU_SSE3},
#line 322 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noamd",		x86_cpu_clear,	CPU_AMD},
#line 404 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"notbm",	x86_cpu_clear,	CPU_TBM},
#line 270 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"p4",		x86_cpu_intel,	PROC_p4},
#line 373 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"movbe",		x86_cpu_set,	CPU_MOVBE},
#line 257 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"ppro",		x86_cpu_intel,	PROC_686},
#line 351 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"sse41",		x86_cpu_set,	CPU_SSE41},
#line 331 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"undocumented",	x86_cpu_set,	CPU_Undoc},
#line 295 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"core2",		x86_cpu_intel,	PROC_conroe},
#line 363 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"avx",		x86_cpu_set,	CPU_AVX},
#line 298 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"corei7",		x86_cpu_intel,	PROC_nehalem},
#line 344 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nopadlock",	x86_cpu_clear,	CPU_PadLock},
#line 269 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"katmai",		x86_cpu_intel,	PROC_p3},
#line 277 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"ia-64",		x86_cpu_ia64,	0},
#line 399 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"invpcid",	x86_cpu_set,	CPU_INVPCID},
#line 398 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nobmi2",		x86_cpu_clear,	CPU_BMI2},
#line 385 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"xsaveopt",	x86_cpu_set,	CPU_XSAVEOPT},
#line 389 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"smx",		x86_cpu_set,	CPU_SMX},
#line 293 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"prescott",	x86_cpu_intel,	PROC_prescott},
#line 285 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"opteron",	x86_cpu_amd,	PROC_hammer},
#line 339 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"privileged",	x86_cpu_set,	CPU_Priv},
#line 406 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"basicnop",	x86_nop,	X86_NOP_BASIC},
#line 395 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"bmi1",		x86_cpu_set,	CPU_BMI1},
#line 400 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noinvpcid",	x86_cpu_clear,	CPU_INVPCID},
#line 291 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"family10h",	x86_cpu_amd,	PROC_k10},
#line 258 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pentiumpro",	x86_cpu_intel,	PROC_686},
#line 245 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"80386",		x86_cpu_intel,	PROC_386},
#line 327 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"protected",	x86_cpu_set,	CPU_Prot},
#line 278 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"itanium",	x86_cpu_ia64,	0},
#line 336 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noobsolete",	x86_cpu_clear,	CPU_Obs},
#line 343 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"padlock",	x86_cpu_set,	CPU_PadLock},
#line 308 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nommx",		x86_cpu_clear,	CPU_MMX},
#line 384 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nordrand",	x86_cpu_clear,	CPU_RDRAND},
#line 356 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosse42",	x86_cpu_clear,	CPU_SSE42},
#line 333 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"obs",		x86_cpu_set,	CPU_Obs},
#line 296 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"penryn",		x86_cpu_intel,	PROC_penryn},
#line 324 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nosmm",		x86_cpu_clear,	CPU_SMM},
#line 362 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"noxsave",	x86_cpu_clear,	CPU_XSAVE},
#line 396 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nobmi1",		x86_cpu_clear,	CPU_BMI1},
#line 381 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"fsgsbase",	x86_cpu_set,	CPU_FSGSBASE},
#line 375 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"xop",		x86_cpu_set,	CPU_XOP},
#line 243 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"i286",		x86_cpu_intel,	PROC_286},
#line 279 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"k6",		x86_cpu_amd,	PROC_k6},
#line 374 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"nomovbe",	x86_cpu_clear,	CPU_MOVBE},
#line 280 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"k7",		x86_cpu_amd,	PROC_k7},
#line 371 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"
    {"pclmulqdq",	x86_cpu_set,	CPU_CLMUL}
  };
  static const unsigned char tab[] = {
    7,125,0,0,125,0,0,0,125,113,0,88,0,125,113,183,
    85,168,146,235,88,82,7,113,85,0,220,0,0,0,0,253,
    0,235,7,0,0,125,131,113,7,7,7,0,0,0,7,0,
    27,0,0,183,0,131,0,0,0,183,183,113,0,0,220,22,
    11,183,0,0,0,32,7,125,131,0,0,0,0,0,0,7,
    168,168,0,214,113,0,40,0,253,235,0,0,120,231,116,177,
    0,214,125,4,32,113,0,0,220,0,135,220,85,88,0,17,
    0,125,124,0,146,22,0,0,165,51,182,139,82,0,0,0,
  };

  const struct cpu_parse_data *ret;
  unsigned long rsl, val = phash_lookup(key, len, 0xdaa66d2bUL);
  rsl = ((val>>25)^tab[val&0x7f]);
  if (rsl >= 165) return NULL;
  ret = &pd[rsl];
  if (strcmp(key, ret->name) != 0) return NULL;
  return ret;
}

#line 409 "/home/lovewei/Project/yasm/new yasm/yasm/modules/arch/x86/x86cpu.gperf"


void
yasm_x86__parse_cpu(yasm_arch_x86 *arch_x86, const char *cpuid,
                    size_t cpuid_len)
{
    /*@null@*/ const struct cpu_parse_data *pdata;
    wordptr new_cpu;
    size_t i;
    static char lcaseid[16];

    if (cpuid_len > 15)
        return;
    for (i=0; i<cpuid_len; i++)
        lcaseid[i] = tolower(cpuid[i]);
    lcaseid[cpuid_len] = '\0';

    pdata = cpu_find(lcaseid, cpuid_len);
    if (!pdata) {
        yasm_warn_set(YASM_WARN_GENERAL,
                      N_("unrecognized CPU identifier `%s'"), cpuid);
        return;
    }

    new_cpu = BitVector_Clone(arch_x86->cpu_enables[arch_x86->active_cpu]);
    pdata->handler(new_cpu, arch_x86, pdata->data);

    /* try to find an existing match in the CPU table first */
    for (i=0; i<arch_x86->cpu_enables_size; i++) {
        if (BitVector_equal(arch_x86->cpu_enables[i], new_cpu)) {
            arch_x86->active_cpu = i;
            BitVector_Destroy(new_cpu);
            return;
        }
    }

    /* not found, need to add a new entry */
    arch_x86->active_cpu = arch_x86->cpu_enables_size++;
    arch_x86->cpu_enables =
        yasm_xrealloc(arch_x86->cpu_enables,
                      arch_x86->cpu_enables_size*sizeof(wordptr));
    arch_x86->cpu_enables[arch_x86->active_cpu] = new_cpu;
}
