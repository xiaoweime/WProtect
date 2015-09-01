/* ANSI-C code produced by genperf */
/* Command-line: genperf /home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf /home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.c */
#line 10 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
struct insnprefix_parse_data;
static const struct insnprefix_parse_data *
insnprefix_nasm_find(const char *key, size_t len)
{
  static const struct insnprefix_parse_data pd[1442] = {
#line 1372 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsubd",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xFA,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 173 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvttps2pi",	cvt_mm_xmm64_insn,	2,	SUF_Z,	0x2C,	0,	0,	0,	CPU_SSE,	0,	0},
#line 1344 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshaw",	amd_vpshift_insn,	2,	SUF_Z,	0x99,	0,	0,	0,	CPU_XOP,	0,	0},
#line 934 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcomisd",	avx_xmm_xmm64_insn,	2,	SUF_Z,	0x66,	0x2F,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 114 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpltpd",	ssecmp_128_insn,	3,	SUF_Z,	0x01,	0x66,	0,	0,	CPU_SSE,	0,	0},
#line 581 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmvgezb",	cyrixmmx_insn,	1,	SUF_Z,	0x5C,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 84 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovle",	cmovcc_insn,	3,	SUF_Z,	0x0E,	0,	0,	0,	CPU_686,	0,	0},
#line 1439 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xlatb",	onebyte_insn,	1,	SUF_Z,	0xD7,	0x00,	0,	0,	0,	0,	0},
#line 17 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aam",	aadm_insn,	2,	SUF_Z,	0x00,	0,	0,	NOT_64,	0,	0,	0},
#line 1078 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovapd",	movau_insn,	6,	SUF_Z,	0x66,	0x28,	0x01,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 307 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"insw",	onebyte_insn,	1,	SUF_Z,	0x6D,	0x10,	0,	0,	0,	0,	0},
#line 694 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setbe",	setcc_insn,	1,	SUF_Z,	0x06,	0,	0,	0,	CPU_386,	0,	0},
#line 329 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jecxz",	jcxz_insn,	2,	SUF_Z,	0x20,	0,	0,	0,	CPU_386,	0,	0},
#line 644 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pushfd",	onebyte_insn,	1,	SUF_Z,	0x9C,	0x20,	0,	NOT_64,	CPU_386,	0,	0},
#line 1203 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomleuq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x01,	0,	0,	CPU_XOP,	0,	0},
#line 1329 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmulhuw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xE4,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1373 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsubq",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xFB,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 272 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fstpt",	fldstpt_insn,	1,	SUF_Z,	0x07,	0,	0,	0,	CPU_FPU,	0,	0},
#line 19 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"adc",	arith_insn,	22,	SUF_Z,	0x10,	0x02,	0,	0,	0,	0,	0},
#line 1113 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmulss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x59,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 49 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blendvps",	sse4xmm0_insn,	2,	SUF_Z,	0x14,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1419 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vzeroupper",	vzero_insn,	1,	SUF_Z,	0xC0,	0,	0,	0,	CPU_AVX,	0,	0},
#line 344 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnle",	jcc_insn,	9,	SUF_Z,	0x0F,	0,	0,	0,	0,	0,	0},
#line 576 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmulhuw",	mmxsse2_insn,	2,	SUF_Z,	0xE4,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 909 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpord_sss",	ssecmp_32_insn,	4,	SUF_Z,	0x17,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 288 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fxsave",	twobytemem_insn,	1,	SUF_Z,	0x00,	0x0F,	0xAE,	0,	CPU_686,	CPU_FPU,	0},
#line 266 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsincos",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xFB,	0,	0,	CPU_286,	CPU_FPU,	0},
#line 305 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"insertps",	insertps_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 658 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rdtsc",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x31,	0,	0,	CPU_586,	0,	0},
#line 713 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setns",	setcc_insn,	1,	SUF_Z,	0x09,	0,	0,	0,	CPU_386,	0,	0},
#line 918 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmptrue_uspd",	ssecmp_128_insn,	3,	SUF_Z,	0x1F,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1111 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmulps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x59,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 811 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_usps",	ssecmp_128_insn,	3,	SUF_Z,	0x18,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 523 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfrcpit1",	now3d_insn,	1,	SUF_Z,	0xA6,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 915 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpps",	xmm_xmm128_imm_256_insn,	3,	SUF_Z,	0x00,	0xC2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 87 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnb",	cmovcc_insn,	3,	SUF_Z,	0x03,	0,	0,	0,	CPU_686,	0,	0},
#line 1150 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpclmulqdq",	pclmulqdq_insn,	2,	SUF_Z,	0x3A,	0x44,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 75 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmova",	cmovcc_insn,	3,	SUF_Z,	0x07,	0,	0,	0,	CPU_686,	0,	0},
#line 1068 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmaxss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5F,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 537 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pi2fw",	now3d_insn,	1,	SUF_Z,	0x0C,	0,	0,	0,	CPU_3DNow,	CPU_Athlon,	0},
#line 1013 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd132pd",	vfma_pd_insn,	2,	SUF_Z,	0x9C,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 959 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vdpps",	sse4imm_256_insn,	4,	SUF_Z,	0x40,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 203 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcmovnb",	fcmovcc_insn,	1,	SUF_Z,	0xDB,	0xC0,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 993 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub213pd",	vfma_pd_insn,	2,	SUF_Z,	0xAA,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 548 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmaxsw",	mmxsse2_insn,	2,	SUF_Z,	0xEE,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 256 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fpatan",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF3,	0,	0,	CPU_FPU,	0,	0},
#line 1312 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpminud",	ssse3_insn,	5,	SUF_Z,	0x3B,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1240 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomud",	vpcom_imm_insn,	1,	SUF_Z,	0xEE,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1356 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpslld",	vpshift_insn,	8,	SUF_Z,	0xF2,	0x72,	0x06,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 729 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"shufpd",	xmm_xmm128_imm_insn,	1,	SUF_Z,	0x66,	0xC6,	0,	0,	CPU_SSE2,	0,	0},
#line 1194 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgtud",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x02,	0,	0,	CPU_XOP,	0,	0},
#line 947 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtsi2ss",	cvt_xmm_rmx_insn,	6,	SUF_Z,	0xF3,	0x2A,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 827 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpge_oqps",	ssecmp_128_insn,	3,	SUF_Z,	0x1D,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 415 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movmskpd",	movmsk_insn,	4,	SUF_Z,	0x66,	0,	0,	0,	CPU_SSE2,	0,	0},
#line 16 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aad",	aadm_insn,	2,	SUF_Z,	0x01,	0,	0,	NOT_64,	0,	0,	0},
#line 855 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpltps",	ssecmp_128_insn,	3,	SUF_Z,	0x01,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1277 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphsubd",	ssse3_insn,	5,	SUF_Z,	0x06,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 215 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fdiv",	farith_insn,	7,	SUF_Z,	0xF8,	0xF0,	0x06,	0,	CPU_FPU,	0,	0},
#line 268 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fst",	fst_insn,	3,	SUF_Z,	0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 1199 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomled",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x01,	0,	0,	CPU_XOP,	0,	0},
#line 706 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setne",	setcc_insn,	1,	SUF_Z,	0x05,	0,	0,	0,	CPU_386,	0,	0},
#line 724 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"shld",	shlrd_insn,	9,	SUF_Z,	0xA4,	0,	0,	0,	CPU_386,	0,	0},
#line 1333 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmuludq",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xF4,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 59 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"bt",	bittest_insn,	6,	SUF_Z,	0xA3,	0x04,	0,	0,	CPU_386,	0,	0},
#line 848 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmplesd",	ssecmp_64_insn,	4,	SUF_Z,	0x02,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1394 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vroundss",	sse4m32imm_insn,	4,	SUF_Z,	0x0A,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 318 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"iret",	onebyte_insn,	1,	SUF_Z,	0xCF,	0,	0,	0,	0,	0,	0},
#line 181 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"div",	div_insn,	8,	SUF_Z,	0x06,	0,	0,	0,	0,	0,	0},
#line 357 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lar",	larlsl_insn,	6,	SUF_Z,	0x02,	0,	0,	0,	CPU_286,	CPU_Prot,	0},
#line 444 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mulss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x59,	0,	0,	CPU_SSE,	0,	0},
#line 453 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"or",	arith_insn,	22,	SUF_Z,	0x08,	0x01,	0,	0,	0,	0,	0},
#line 145 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpxchg",	cmpxchgxadd_insn,	4,	SUF_Z,	0xB0,	0,	0,	0,	CPU_486,	0,	0},
#line 950 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvttpd2dq",	avx_cvt_xmm128_insn,	2,	SUF_Z,	0x66,	0xE6,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 360 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lds",	ldes_insn,	2,	SUF_Z,	0xC5,	0,	0,	NOT_64,	0,	0,	0},
#line 1268 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddubw",	vphaddsub_insn,	1,	SUF_Z,	0xD1,	0,	0,	0,	CPU_XOP,	0,	0},
#line 294 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"haddps",	xmm_xmm128_insn,	2,	SUF_Z,	0xF2,	0x7C,	0,	0,	CPU_SSE3,	0,	0},
#line 438 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movzx",	movszx_insn,	5,	SUF_Z,	0xB6,	0,	0,	0,	CPU_386,	0,	0},
#line 1290 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacssdqh",	vpma_insn,	1,	SUF_Z,	0x8F,	0,	0,	0,	CPU_XOP,	0,	0},
#line 628 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubw",	mmxsse2_insn,	2,	SUF_Z,	0xF9,	0,	0,	0,	CPU_MMX,	0,	0},
#line 846 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmplepd",	ssecmp_128_insn,	3,	SUF_Z,	0x02,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 782 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaddsubpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0xD0,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 749 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"stosq",	onebyte_insn,	1,	SUF_Z,	0xAB,	0x40,	0,	ONLY_64,	0,	0,	0},
#line 283 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fucompp",	twobyte_insn,	1,	SUF_Z,	0xDA,	0xE9,	0,	0,	CPU_286,	CPU_FPU,	0},
#line 1386 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpunpcklqdq",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x6C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 491 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpeqb",	mmxsse2_insn,	2,	SUF_Z,	0x74,	0,	0,	0,	CPU_MMX,	0,	0},
#line 190 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"extractps",	extractps_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_SSE41,	0},
#line 60 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"btc",	bittest_insn,	6,	SUF_Z,	0xBB,	0x07,	0,	0,	CPU_386,	0,	0},
#line 1345 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshlb",	amd_vpshift_insn,	2,	SUF_Z,	0x94,	0,	0,	0,	CPU_XOP,	0,	0},
#line 669 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ror",	shift_insn,	16,	SUF_Z,	0x01,	0,	0,	0,	0,	0,	0},
#line 1197 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgtw",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x02,	0,	0,	CPU_XOP,	0,	0},
#line 698 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setge",	setcc_insn,	1,	SUF_Z,	0x0D,	0,	0,	0,	CPU_386,	0,	0},
#line 1370 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsrlw",	vpshift_insn,	8,	SUF_Z,	0xD1,	0x71,	0x02,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 984 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsub213ps",	vfma_ps_insn,	2,	SUF_Z,	0xA6,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1201 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomleub",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x01,	0,	0,	CPU_XOP,	0,	0},
#line 131 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpordps",	ssecmp_128_insn,	3,	SUF_Z,	0x07,	0,	0,	0,	CPU_SSE,	0,	0},
#line 94 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnle",	cmovcc_insn,	3,	SUF_Z,	0x0F,	0,	0,	0,	CPU_686,	0,	0},
#line 446 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mwait",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xC9,	0,	CPU_SSE3,	0,	0},
#line 1091 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovmskps",	movmsk_insn,	4,	SUF_Z,	0x00,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1053 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vhaddpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x7C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 642 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pushaw",	onebyte_insn,	1,	SUF_Z,	0x60,	0x10,	0,	NOT_64,	CPU_186,	0,	0},
#line 578 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmulld",	sse4_insn,	2,	SUF_Z,	0x40,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 28 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aesdeclast",	aes_insn,	2,	SUF_Z,	0x38,	0xDF,	0,	0,	CPU_AVX,	0,	0},
#line 180 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"dec",	incdec_insn,	6,	SUF_Z,	0x48,	0x01,	0,	0,	0,	0,	0},
#line 1100 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovss",	movss_insn,	4,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 966 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd132ps",	vfma_ps_insn,	2,	SUF_Z,	0x98,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 309 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"int03",	onebyte_insn,	1,	SUF_Z,	0xCC,	0,	0,	0,	0,	0,	0},
#line 659 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rdtscp",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xF9,	0,	CPU_686,	CPU_AMD,	CPU_Priv},
#line 534 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"phsubsw",	ssse3_insn,	5,	SUF_Z,	0x07,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 753 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"subpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x5C,	0,	0,	CPU_SSE2,	0,	0},
#line 746 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"stmxcsr",	ldstmxcsr_insn,	1,	SUF_Z,	0x03,	0,	0,	0,	CPU_SSE,	0,	0},
#line 83 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovl",	cmovcc_insn,	3,	SUF_Z,	0x0C,	0,	0,	0,	CPU_686,	0,	0},
#line 1226 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneud",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 1442 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xorps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x57,	0,	0,	CPU_SSE,	0,	0},
#line 405 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movddup",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x12,	0,	0,	CPU_SSE3,	0,	0},
#line 884 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngt_uqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x1A,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 773 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"umov",	umov_insn,	6,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_Undoc,	0},
#line 368 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lidt",	twobytemem_insn,	1,	SUF_Z,	0x03,	0x0F,	0x01,	0,	CPU_286,	CPU_Priv,	0},
#line 284 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fwait",	onebyte_insn,	1,	SUF_Z,	0x9B,	0,	0,	0,	CPU_FPU,	0,	0},
#line 57 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"bsr",	bsfr_insn,	3,	SUF_Z,	0xBD,	0,	0,	0,	CPU_386,	0,	0},
#line 1205 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomlew",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x01,	0,	0,	CPU_XOP,	0,	0},
#line 1342 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshad",	amd_vpshift_insn,	2,	SUF_Z,	0x9A,	0,	0,	0,	CPU_XOP,	0,	0},
#line 176 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cwd",	onebyte_insn,	1,	SUF_Z,	0x99,	0x10,	0,	0,	0,	0,	0},
#line 720 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setz",	setcc_insn,	1,	SUF_Z,	0x04,	0,	0,	0,	CPU_386,	0,	0},
#line 825 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpfalsess",	ssecmp_32_insn,	4,	SUF_Z,	0x0B,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 979 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsd",	fma_128_m64_insn,	3,	SUF_Z,	0x6B,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 904 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnltsd",	ssecmp_64_insn,	4,	SUF_Z,	0x05,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1107 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmresume",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xC3,	0,	CPU_P4,	0,	0},
#line 456 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"out",	out_insn,	12,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 956 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vdivsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5E,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1004 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubadd213ps",	vfma_ps_insn,	2,	SUF_Z,	0xA7,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1255 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpextrw",	pextrw_insn,	7,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 331 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jge",	jcc_insn,	9,	SUF_Z,	0x0D,	0,	0,	0,	0,	0,	0},
#line 1141 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpblendw",	sse4imm_256avx2_insn,	4,	SUF_Z,	0x0E,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 123 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpnleps",	ssecmp_128_insn,	3,	SUF_Z,	0x06,	0,	0,	0,	CPU_SSE,	0,	0},
#line 1038 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub231ps",	vfma_ps_insn,	2,	SUF_Z,	0xBE,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 764 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sysret",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x07,	0,	0,	CPU_686,	CPU_AMD,	CPU_Priv},
#line 752 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sub",	arith_insn,	22,	SUF_Z,	0x28,	0x05,	0,	0,	0,	0,	0},
#line 429 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movshdup",	xmm_xmm128_insn,	2,	SUF_Z,	0xF3,	0x16,	0,	0,	CPU_SSE3,	0,	0},
#line 582 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmvlzb",	cyrixmmx_insn,	1,	SUF_Z,	0x5B,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 972 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd213ss",	vfma_ss_insn,	2,	SUF_Z,	0xA9,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1023 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd231sd",	vfma_sd_insn,	2,	SUF_Z,	0xBD,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1341 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshab",	amd_vpshift_insn,	2,	SUF_Z,	0x98,	0,	0,	0,	CPU_XOP,	0,	0},
#line 254 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fnstenv",	onebytemem_insn,	1,	SUF_Z,	0x06,	0xD9,	0,	0,	CPU_FPU,	0,	0},
#line 223 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ficom",	fiarith_insn,	2,	SUF_Z,	0x02,	0xDA,	0,	0,	CPU_FPU,	0,	0},
#line 1316 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovsxbq",	sse4m16_insn,	4,	SUF_Z,	0x22,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 573 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmulhrsw",	ssse3_insn,	5,	SUF_Z,	0x0B,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 738 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sqrtpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x51,	0,	0,	CPU_SSE2,	0,	0},
#line 652 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rdfsbase",	fs_gs_base_insn,	2,	SUF_Z,	0x00,	0,	0,	ONLY_64,	CPU_FSGSBASE,	0,	0},
#line 843 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmple_oqps",	ssecmp_128_insn,	3,	SUF_Z,	0x12,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 431 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movsq",	onebyte_insn,	1,	SUF_Z,	0xA5,	0x40,	0,	ONLY_64,	0,	0,	0},
#line 681 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sahf",	onebyte_insn,	1,	SUF_Z,	0x9E,	0,	0,	0,	0,	0,	0},
#line 1015 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd132sd",	vfma_sd_insn,	2,	SUF_Z,	0x9D,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1029 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub132pd",	vfma_pd_insn,	2,	SUF_Z,	0x9E,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 255 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fnstsw",	fnstsw_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 1395 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vrsqrtps",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x52,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 478 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pandn",	mmxsse2_insn,	2,	SUF_Z,	0xDF,	0,	0,	0,	CPU_MMX,	0,	0},
#line 960 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"verr",	prot286_insn,	1,	SUF_Z,	0x04,	0x00,	0,	0,	CPU_286,	CPU_Prot,	0},
#line 568 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovzxdq",	sse4m64_insn,	4,	SUF_Z,	0x35,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 858 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_oqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x0C,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 692 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setae",	setcc_insn,	1,	SUF_Z,	0x03,	0,	0,	0,	CPU_386,	0,	0},
#line 925 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmptruess",	ssecmp_32_insn,	4,	SUF_Z,	0x0F,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 944 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtsd2si",	cvt_rx_xmm64_insn,	4,	SUF_Z,	0xF2,	0x2D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1034 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub213ps",	vfma_ps_insn,	2,	SUF_Z,	0xAE,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 783 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaddsubps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0xF2,	0xD0,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1426 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xabort",	tsx_xabort_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_TSX,	0,	0},
#line 115 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpltps",	ssecmp_128_insn,	3,	SUF_Z,	0x01,	0,	0,	0,	CPU_SSE,	0,	0},
#line 1309 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpminsd",	ssse3_insn,	5,	SUF_Z,	0x39,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 919 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmptrue_usps",	ssecmp_128_insn,	3,	SUF_Z,	0x1F,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1216 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 292 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"getsec",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x37,	0,	0,	CPU_SMX,	0,	0},
#line 63 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"bzhi",	vex_gpr_reg_rm_nds_0F_insn,	2,	SUF_Z,	0x00,	0x38,	0xF5,	ONLY_AVX,	CPU_BMI2,	0,	0},
#line 164 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtsd2si",	cvt_rx_xmm64_insn,	4,	SUF_Z,	0xF2,	0x2D,	0,	0,	CPU_386,	CPU_SSE2,	0},
#line 1215 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomned",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 231 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fist",	fiarith_insn,	2,	SUF_Z,	0x02,	0xDB,	0,	0,	CPU_FPU,	0,	0},
#line 1390 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vrcpss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x53,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 396 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"minsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5D,	0,	0,	CPU_SSE2,	0,	0},
#line 1061 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vldmxcsr",	ldstmxcsr_insn,	1,	SUF_Z,	0x02,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 859 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_oqps",	ssecmp_128_insn,	3,	SUF_Z,	0x0C,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 563 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovsxwd",	sse4m64_insn,	4,	SUF_Z,	0x23,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1331 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmulld",	ssse3_insn,	5,	SUF_Z,	0x40,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1069 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmcall",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xC1,	0,	CPU_P4,	0,	0},
#line 723 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"shl",	shift_insn,	16,	SUF_Z,	0x04,	0,	0,	0,	0,	0,	0},
#line 96 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnp",	cmovcc_insn,	3,	SUF_Z,	0x0B,	0,	0,	0,	CPU_686,	0,	0},
#line 117 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpltss",	ssecmp_32_insn,	4,	SUF_Z,	0x01,	0xF3,	0,	0,	CPU_SSE,	0,	0},
#line 547 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmaxsd",	sse4_insn,	2,	SUF_Z,	0x3D,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1444 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xrstor",	twobytemem_insn,	1,	SUF_Z,	0x05,	0x0F,	0xAE,	0,	CPU_386,	CPU_XSAVE,	0},
#line 538 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pinsrb",	pinsrb_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 120 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpneqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x04,	0xF2,	0,	0,	CPU_SSE2,	0,	0},
#line 1416 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vxorpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x57,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 933 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpunordss",	ssecmp_32_insn,	4,	SUF_Z,	0x03,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1085 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovhpd",	movhlp_insn,	3,	SUF_Z,	0x66,	0x16,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 222 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fiadd",	fiarith_insn,	2,	SUF_Z,	0x00,	0xDA,	0,	0,	CPU_FPU,	0,	0},
#line 449 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"not",	f6_insn,	4,	SUF_Z,	0x02,	0,	0,	0,	0,	0,	0},
#line 365 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lfs",	lfgss_insn,	3,	SUF_Z,	0xB4,	0,	0,	0,	CPU_386,	0,	0},
#line 762 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sysenter",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x34,	0,	NOT_64,	CPU_686,	0,	0},
#line 166 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtsi2sd",	cvt_xmm_rmx_insn,	6,	SUF_Z,	0xF2,	0x2A,	0,	0,	CPU_SSE2,	0,	0},
#line 230 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"finit",	threebyte_insn,	1,	SUF_Z,	0x9B,	0xDB,	0xE3,	0,	CPU_FPU,	0,	0},
#line 1224 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneqw",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 484 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pblendvb",	sse4xmm0_insn,	2,	SUF_Z,	0x10,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 790 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vandnpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x55,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 21 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"addpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x58,	0,	0,	CPU_SSE2,	0,	0},
#line 81 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovg",	cmovcc_insn,	3,	SUF_Z,	0x0F,	0,	0,	0,	CPU_686,	0,	0},
#line 12 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"a16",	NULL,	X86_ADDRSIZE>>8,	0x10,	0,	0,	0,	0,	0,	0,	0},
#line 781 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaddss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x58,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 502 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpistrm",	sse4pcmpstr_insn,	1,	SUF_Z,	0x62,	0,	0,	0,	CPU_SSE42,	0,	0},
#line 1170 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomequd",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x04,	0,	0,	CPU_XOP,	0,	0},
#line 1424 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"wrmsr",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x30,	0,	0,	CPU_586,	CPU_Priv,	0},
#line 556 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pminud",	sse4_insn,	2,	SUF_Z,	0x3B,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 553 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pminsd",	sse4_insn,	2,	SUF_Z,	0x39,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 278 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ftst",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xE4,	0,	0,	CPU_FPU,	0,	0},
#line 39 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"arpl",	arpl_insn,	1,	SUF_Z,	0,	0,	0,	NOT_64,	CPU_286,	CPU_Prot,	0},
#line 200 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcmovb",	fcmovcc_insn,	1,	SUF_Z,	0xDA,	0xC0,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 1016 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd132ss",	vfma_ss_insn,	2,	SUF_Z,	0x9D,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1355 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsignw",	ssse3_insn,	5,	SUF_Z,	0x09,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1012 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubss",	fma_128_m32_insn,	3,	SUF_Z,	0x6E,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 500 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpgtw",	mmxsse2_insn,	2,	SUF_Z,	0x65,	0,	0,	0,	CPU_MMX,	0,	0},
#line 821 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpfalse_osss",	ssecmp_32_insn,	4,	SUF_Z,	0x1B,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 150 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"comiss",	xmm_xmm32_insn,	4,	SUF_Z,	0x00,	0x2F,	0,	0,	CPU_SSE,	0,	0},
#line 382 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"loopz",	loop_insn,	8,	SUF_Z,	0x01,	0,	0,	0,	0,	0,	0},
#line 122 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpnlepd",	ssecmp_128_insn,	3,	SUF_Z,	0x06,	0x66,	0,	0,	CPU_SSE,	0,	0},
#line 518 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfmin",	now3d_insn,	1,	SUF_Z,	0x94,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1005 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubadd231pd",	vfma_pd_insn,	2,	SUF_Z,	0xB7,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1032 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub132ss",	vfma_ss_insn,	2,	SUF_Z,	0x9F,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 804 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_ossd",	ssecmp_64_insn,	4,	SUF_Z,	0x10,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1354 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsignd",	ssse3_insn,	5,	SUF_Z,	0x0A,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1132 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpaddusw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xDD,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 207 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcmovu",	fcmovcc_insn,	1,	SUF_Z,	0xDA,	0xD8,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 1079 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovaps",	movau_insn,	6,	SUF_Z,	0x00,	0x28,	0x01,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 844 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmple_oqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x12,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 688 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"scasd",	onebyte_insn,	1,	SUF_Z,	0xAF,	0x20,	0,	0,	CPU_386,	0,	0},
#line 127 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpnltps",	ssecmp_128_insn,	3,	SUF_Z,	0x05,	0,	0,	0,	CPU_SSE,	0,	0},
#line 1021 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd231pd",	vfma_pd_insn,	2,	SUF_Z,	0xBC,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 275 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsubp",	farithp_insn,	3,	SUF_Z,	0xE8,	0,	0,	0,	CPU_FPU,	0,	0},
#line 496 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpestrm",	sse4pcmpstr_insn,	1,	SUF_Z,	0x60,	0,	0,	0,	CPU_SSE42,	0,	0},
#line 1014 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd132ps",	vfma_ps_insn,	2,	SUF_Z,	0x9C,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1136 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpandn",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xDF,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1118 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vorps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x56,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1225 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneub",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 1293 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacssww",	vpma_insn,	1,	SUF_Z,	0x85,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1082 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovdqa",	movau_insn,	6,	SUF_Z,	0x66,	0x6F,	0x10,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 332 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jl",	jcc_insn,	9,	SUF_Z,	0x0C,	0,	0,	0,	0,	0,	0},
#line 572 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmulhriw",	cyrixmmx_insn,	1,	SUF_Z,	0x5D,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 1217 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneqb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 1382 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpunpckhqdq",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x6D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 554 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pminsw",	mmxsse2_insn,	2,	SUF_Z,	0xEA,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 1259 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpgatherqq",	gather_64x_64y_insn,	2,	SUF_Z,	0x91,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 967 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd132sd",	vfma_sd_insn,	2,	SUF_Z,	0x99,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 718 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setpo",	setcc_insn,	1,	SUF_Z,	0x0B,	0,	0,	0,	CPU_386,	0,	0},
#line 225 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fidiv",	fiarith_insn,	2,	SUF_Z,	0x06,	0xDA,	0,	0,	CPU_FPU,	0,	0},
#line 73 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"clts",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x06,	0,	0,	CPU_286,	CPU_Priv,	0},
#line 597 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"prefetcht0",	twobytemem_insn,	1,	SUF_Z,	0x01,	0x0F,	0x18,	0,	CPU_P3,	0,	0},
#line 167 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtsi2ss",	cvt_xmm_rmx_insn,	6,	SUF_Z,	0xF3,	0x2A,	0,	0,	CPU_386,	CPU_SSE,	0},
#line 1435 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xcryptecb",	padlock_insn,	1,	SUF_Z,	0xC8,	0xF3,	0xA7,	0,	CPU_PadLock,	0,	0},
#line 1434 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xcryptctr",	padlock_insn,	1,	SUF_Z,	0xD8,	0xF3,	0xA7,	0,	CPU_PadLock,	0,	0},
#line 968 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd132ss",	vfma_ss_insn,	2,	SUF_Z,	0x99,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1162 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpistri",	sse4pcmpstr_insn,	1,	SUF_Z,	0x63,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 593 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"popfw",	onebyte_insn,	1,	SUF_Z,	0x9D,	0x10,	0x40,	0,	0,	0,	0},
#line 1403 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vstmxcsr",	ldstmxcsr_insn,	1,	SUF_Z,	0x03,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1321 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovzxbd",	sse4m32_insn,	4,	SUF_Z,	0x31,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 678 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rsqrtps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x52,	0,	0,	CPU_SSE,	0,	0},
#line 1003 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubadd213pd",	vfma_pd_insn,	2,	SUF_Z,	0xA7,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 598 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"prefetcht1",	twobytemem_insn,	1,	SUF_Z,	0x02,	0x0F,	0x18,	0,	CPU_P3,	0,	0},
#line 1443 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xrelease",	NULL,	X86_ACQREL>>8,	0xF3,	0,	0,	0,	0,	0,	0,	0},
#line 1420 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"wait",	onebyte_insn,	1,	SUF_Z,	0x9B,	0,	0,	0,	0,	0,	0},
#line 29 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aesenc",	aes_insn,	2,	SUF_Z,	0x38,	0xDC,	0,	0,	CPU_AVX,	0,	0},
#line 132 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpordsd",	ssecmp_64_insn,	4,	SUF_Z,	0x07,	0xF2,	0,	0,	CPU_SSE2,	0,	0},
#line 374 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lodsb",	onebyte_insn,	1,	SUF_Z,	0xAC,	0x00,	0,	0,	0,	0,	0},
#line 812 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_ussd",	ssecmp_64_insn,	4,	SUF_Z,	0x18,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 228 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fimul",	fiarith_insn,	2,	SUF_Z,	0x01,	0xDA,	0,	0,	CPU_FPU,	0,	0},
#line 45 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blcs",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x01,	0x03,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 807 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_uqps",	ssecmp_128_insn,	3,	SUF_Z,	0x08,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1020 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd213ss",	vfma_ss_insn,	2,	SUF_Z,	0xAD,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1271 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphadduwq",	vphaddsub_insn,	1,	SUF_Z,	0xD7,	0,	0,	0,	CPU_XOP,	0,	0},
#line 350 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jp",	jcc_insn,	9,	SUF_Z,	0x0A,	0,	0,	0,	0,	0,	0},
#line 1183 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomged",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x03,	0,	0,	CPU_XOP,	0,	0},
#line 786 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaesenc",	aes_insn,	2,	SUF_Z,	0x38,	0xDC,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 251 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fnop",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xD0,	0,	0,	CPU_FPU,	0,	0},
#line 1353 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsignb",	ssse3_insn,	5,	SUF_Z,	0x08,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 766 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"test",	test_insn,	20,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 1072 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vminps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x5D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 154 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtdq2pd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF3,	0xE6,	0,	0,	CPU_SSE2,	0,	0},
#line 544 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmaddwd",	mmxsse2_insn,	2,	SUF_Z,	0xF5,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1245 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vperm2i128",	vperm2i128_avx2_insn,	1,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 905 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnltss",	ssecmp_32_insn,	4,	SUF_Z,	0x05,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 584 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmvzb",	cyrixmmx_insn,	1,	SUF_Z,	0x58,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 899 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnlt_uqps",	ssecmp_128_insn,	3,	SUF_Z,	0x15,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 43 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blcic",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x01,	0x05,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 1031 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub132sd",	vfma_sd_insn,	2,	SUF_Z,	0x9F,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 381 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"loopnz",	loop_insn,	8,	SUF_Z,	0x00,	0,	0,	0,	0,	0,	0},
#line 913 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpordss",	ssecmp_32_insn,	4,	SUF_Z,	0x07,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 423 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movntsd",	movntsd_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_SSE4a,	0,	0},
#line 400 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mov",	mov_insn,	69,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 326 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jc",	jcc_insn,	9,	SUF_Z,	0x02,	0,	0,	0,	0,	0,	0},
#line 1022 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd231ps",	vfma_ps_insn,	2,	SUF_Z,	0xBC,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 955 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vdivps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x5E,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1451 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xstore",	padlock_insn,	1,	SUF_Z,	0xC0,	0x00,	0xA7,	0,	CPU_PadLock,	0,	0},
#line 98 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnz",	cmovcc_insn,	3,	SUF_Z,	0x05,	0,	0,	0,	CPU_686,	0,	0},
#line 1352 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshuflw",	xmm_xmm128_imm_256avx2_insn,	2,	SUF_Z,	0xF2,	0x70,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1324 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovzxdq",	sse4m64_insn,	4,	SUF_Z,	0x35,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 434 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movsx",	movszx_insn,	5,	SUF_Z,	0xBE,	0,	0,	0,	CPU_386,	0,	0},
#line 271 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fstp",	fstp_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 1123 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpacksswb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x63,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 978 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddps",	fma_128_256_insn,	4,	SUF_Z,	0x68,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 922 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmptruepd",	ssecmp_128_insn,	3,	SUF_Z,	0x0F,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 780 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaddsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x58,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1191 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgtd",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x02,	0,	0,	CPU_XOP,	0,	0},
#line 788 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaesimc",	aesimc_insn,	1,	SUF_Z,	0x38,	0xDB,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1421 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"wbinvd",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x09,	0,	0,	CPU_486,	CPU_Priv,	0},
#line 683 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"salc",	onebyte_insn,	1,	SUF_Z,	0xD6,	0,	0,	NOT_64,	CPU_Undoc,	0,	0},
#line 903 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnltps",	ssecmp_128_insn,	3,	SUF_Z,	0x05,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 630 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ptest",	sse4_insn,	2,	SUF_Z,	0x17,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 340 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jne",	jcc_insn,	9,	SUF_Z,	0x05,	0,	0,	0,	0,	0,	0},
#line 1315 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovsxbd",	sse4m32_insn,	4,	SUF_Z,	0x21,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1073 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vminsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 819 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpfalse_osps",	ssecmp_128_insn,	3,	SUF_Z,	0x1B,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1387 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpunpcklwd",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x61,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 273 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fstsw",	fstsw_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 372 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"loadall286",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x05,	0,	0,	CPU_286,	CPU_Undoc,	0},
#line 589 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"popcnt",	cnt_insn,	3,	SUF_Z,	0xB8,	0,	0,	0,	CPU_SSE42,	0,	0},
#line 237 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fld1",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xE8,	0,	0,	CPU_FPU,	0,	0},
#line 1180 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomfalseuw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x06,	0,	0,	CPU_XOP,	0,	0},
#line 257 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fprem",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF8,	0,	0,	CPU_FPU,	0,	0},
#line 942 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtps2pd",	avx_cvt_xmm64_insn,	3,	SUF_Z,	0x00,	0x5A,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1000 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub231ss",	vfma_ss_insn,	2,	SUF_Z,	0xBB,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 226 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fidivr",	fiarith_insn,	2,	SUF_Z,	0x07,	0xDA,	0,	0,	CPU_FPU,	0,	0},
#line 981 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsub132pd",	vfma_pd_insn,	2,	SUF_Z,	0x96,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 261 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"frstor",	onebytemem_insn,	1,	SUF_Z,	0x04,	0xDD,	0,	0,	CPU_FPU,	0,	0},
#line 586 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"popa",	onebyte_insn,	1,	SUF_Z,	0x61,	0x00,	0,	NOT_64,	CPU_186,	0,	0},
#line 85 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovna",	cmovcc_insn,	3,	SUF_Z,	0x06,	0,	0,	0,	CPU_686,	0,	0},
#line 62 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"bts",	bittest_insn,	6,	SUF_Z,	0xAB,	0x05,	0,	0,	CPU_386,	0,	0},
#line 1335 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpperm",	vpperm_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_XOP,	0,	0},
#line 921 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmptrue_usss",	ssecmp_32_insn,	4,	SUF_Z,	0x1F,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 51 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blsi",	vex_gpr_ndd_rm_0F38_regext_insn,	2,	SUF_Z,	0x00,	0xF3,	0x03,	ONLY_AVX,	CPU_BMI1,	0,	0},
#line 461 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pabsd",	ssse3_insn,	5,	SUF_Z,	0x1E,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 837 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgt_oqss",	ssecmp_32_insn,	4,	SUF_Z,	0x1E,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 458 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"outsd",	onebyte_insn,	1,	SUF_Z,	0x6F,	0x20,	0,	0,	CPU_386,	0,	0},
#line 301 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"in",	in_insn,	12,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 667 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"retn",	retnf_insn,	6,	SUF_Z,	0xC2,	0,	0,	0,	0,	0,	0},
#line 137 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpsd",	cmpsd_insn,	5,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 619 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psrlw",	pshift_insn,	4,	SUF_Z,	0xD1,	0x71,	0x02,	0,	CPU_MMX,	0,	0},
#line 1368 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsrlvd",	vpshiftv_vexw0_avx2_insn,	2,	SUF_Z,	0x45,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 428 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movsd",	movsd_insn,	5,	SUF_Z,	0,	0,	0,	0,	CPU_386,	0,	0},
#line 755 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"subsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5C,	0,	0,	CPU_SSE2,	0,	0},
#line 179 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"das",	onebyte_insn,	1,	SUF_Z,	0x2F,	0,	0,	NOT_64,	0,	0,	0},
#line 402 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movaps",	movau_insn,	6,	SUF_Z,	0x00,	0x28,	0x01,	0,	CPU_SSE,	0,	0},
#line 289 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fxtract",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF4,	0,	0,	CPU_FPU,	0,	0},
#line 660 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rep",	NULL,	X86_LOCKREP>>8,	0xF3,	0,	0,	0,	0,	0,	0,	0},
#line 897 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnless",	ssecmp_32_insn,	4,	SUF_Z,	0x06,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 789 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaeskeygenassist",	aes_imm_insn,	1,	SUF_Z,	0x3A,	0xDF,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1129 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpaddsb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xEC,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 477 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pand",	mmxsse2_insn,	2,	SUF_Z,	0xDB,	0,	0,	0,	CPU_MMX,	0,	0},
#line 77 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovb",	cmovcc_insn,	3,	SUF_Z,	0x02,	0,	0,	0,	CPU_686,	0,	0},
#line 1159 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpgtd",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 570 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovzxwq",	sse4m32_insn,	4,	SUF_Z,	0x34,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1002 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubadd132ps",	vfma_ps_insn,	2,	SUF_Z,	0x97,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1318 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovsxdq",	sse4m64_insn,	4,	SUF_Z,	0x25,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1221 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomnequd",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 488 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pclmullqhqdq",	pclmulqdq_fixed_insn,	2,	SUF_Z,	0x10,	0,	0,	0,	CPU_AVX,	0,	0},
#line 224 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ficomp",	fiarith_insn,	2,	SUF_Z,	0x03,	0xDA,	0,	0,	CPU_FPU,	0,	0},
#line 1219 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneqq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 1291 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacssdql",	vpma_insn,	1,	SUF_Z,	0x87,	0,	0,	0,	CPU_XOP,	0,	0},
#line 689 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"scasq",	onebyte_insn,	1,	SUF_Z,	0xAF,	0x40,	0,	ONLY_64,	0,	0,	0},
#line 833 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgess",	ssecmp_32_insn,	4,	SUF_Z,	0x0D,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 923 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmptrueps",	ssecmp_128_insn,	3,	SUF_Z,	0x0F,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 66 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cdq",	onebyte_insn,	1,	SUF_Z,	0x99,	0x20,	0,	0,	CPU_386,	0,	0},
#line 796 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vblendvpd",	avx_sse4xmm0_insn,	2,	SUF_Z,	0x4B,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 893 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnle_uqss",	ssecmp_32_insn,	4,	SUF_Z,	0x16,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 818 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpfalse_ospd",	ssecmp_128_insn,	3,	SUF_Z,	0x1B,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1276 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphsubbw",	vphaddsub_insn,	1,	SUF_Z,	0xE1,	0,	0,	0,	CPU_XOP,	0,	0},
#line 296 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"hsubpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x7D,	0,	0,	CPU_SSE3,	0,	0},
#line 1417 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vxorps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x57,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 286 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fxch",	fxch_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 1362 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsrad",	vpshift_insn,	8,	SUF_Z,	0xE2,	0x72,	0x04,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1196 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgtuw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x02,	0,	0,	CPU_XOP,	0,	0},
#line 690 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"scasw",	onebyte_insn,	1,	SUF_Z,	0xAF,	0x10,	0,	0,	0,	0,	0},
#line 420 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movntpd",	movnt_insn,	2,	SUF_Z,	0x66,	0x2B,	0,	0,	CPU_SSE2,	0,	0},
#line 1383 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpunpckhwd",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x69,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 182 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"divpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x5E,	0,	0,	CPU_SSE2,	0,	0},
#line 1041 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsubpd",	fma_128_256_insn,	4,	SUF_Z,	0x7D,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 613 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psllw",	pshift_insn,	4,	SUF_Z,	0xF1,	0x71,	0x06,	0,	CPU_MMX,	0,	0},
#line 1378 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsubw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xF9,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 209 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcomi",	fcom2_insn,	2,	SUF_Z,	0xDB,	0xF0,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 640 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pusha",	onebyte_insn,	1,	SUF_Z,	0x60,	0x00,	0,	NOT_64,	CPU_186,	0,	0},
#line 882 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngt_uqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x1A,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 414 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movlps",	movhlp_insn,	3,	SUF_Z,	0x00,	0x12,	0,	0,	CPU_SSE,	0,	0},
#line 130 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpordpd",	ssecmp_128_insn,	3,	SUF_Z,	0x07,	0x66,	0,	0,	CPU_SSE,	0,	0},
#line 364 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lfence",	threebyte_insn,	1,	SUF_Z,	0x0F,	0xAE,	0xE8,	0,	CPU_P3,	0,	0},
#line 161 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtps2dq",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x5B,	0,	0,	CPU_SSE2,	0,	0},
#line 1154 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpeqq",	ssse3_insn,	5,	SUF_Z,	0x29,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1270 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphadduwd",	vphaddsub_insn,	1,	SUF_Z,	0xD6,	0,	0,	0,	CPU_XOP,	0,	0},
#line 928 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpunord_ssd",	ssecmp_64_insn,	4,	SUF_Z,	0x13,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 611 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pslldq",	pslrldq_insn,	4,	SUF_Z,	0x07,	0,	0,	0,	CPU_SSE2,	0,	0},
#line 233 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fisttp",	fildstp_insn,	4,	SUF_Z,	0x01,	0x00,	0x01,	0,	CPU_SSE3,	0,	0},
#line 238 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldcw",	fldnstcw_insn,	1,	SUF_Z,	0x05,	0,	0,	0,	CPU_FPU,	0,	0},
#line 842 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmple_oqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x12,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1124 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpackusdw",	ssse3_insn,	5,	SUF_Z,	0x2B,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 79 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovc",	cmovcc_insn,	3,	SUF_Z,	0x02,	0,	0,	0,	CPU_686,	0,	0},
#line 36 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"andnps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x55,	0,	0,	CPU_SSE,	0,	0},
#line 185 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"divss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5E,	0,	0,	CPU_SSE,	0,	0},
#line 878 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngepd",	ssecmp_128_insn,	3,	SUF_Z,	0x09,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1448 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xsetbv",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xD1,	0,	CPU_386,	CPU_Priv,	CPU_XSAVE},
#line 433 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movsw",	onebyte_insn,	1,	SUF_Z,	0xA5,	0x10,	0,	0,	0,	0,	0},
#line 1195 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgtuq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x02,	0,	0,	CPU_XOP,	0,	0},
#line 505 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pext",	vex_gpr_reg_nds_rm_0F_insn,	2,	SUF_Z,	0xF3,	0x38,	0xF5,	ONLY_AVX,	CPU_BMI2,	0,	0},
#line 559 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovsxbd",	sse4m32_insn,	4,	SUF_Z,	0x21,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1450 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xsha256",	padlock_insn,	1,	SUF_Z,	0xD0,	0xF3,	0xA6,	0,	CPU_PadLock,	0,	0},
#line 1011 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubsd",	fma_128_m64_insn,	3,	SUF_Z,	0x6F,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 213 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcos",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xFF,	0,	0,	CPU_286,	CPU_FPU,	0},
#line 448 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"nop",	onebyte_insn,	1,	SUF_Z,	0x90,	0,	0,	0,	0,	0,	0},
#line 888 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngtsd",	ssecmp_64_insn,	4,	SUF_Z,	0x0A,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 276 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsubr",	farith_insn,	7,	SUF_Z,	0xE0,	0xE8,	0x05,	0,	CPU_FPU,	0,	0},
#line 801 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vbroadcastss",	vbroadcastss_insn,	4,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 471 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddsiw",	cyrixmmx_insn,	1,	SUF_Z,	0x51,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 626 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubusb",	mmxsse2_insn,	2,	SUF_Z,	0xD8,	0,	0,	0,	CPU_MMX,	0,	0},
#line 193 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fabs",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xE1,	0,	0,	CPU_FPU,	0,	0},
#line 945 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtsd2ss",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5A,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1182 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgeb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x03,	0,	0,	CPU_XOP,	0,	0},
#line 503 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pdep",	vex_gpr_reg_nds_rm_0F_insn,	2,	SUF_Z,	0xF2,	0x38,	0xF5,	ONLY_AVX,	CPU_BMI2,	0,	0},
#line 1263 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddd",	ssse3_insn,	5,	SUF_Z,	0x02,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 245 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldt",	fldstpt_insn,	1,	SUF_Z,	0x05,	0,	0,	0,	CPU_FPU,	0,	0},
#line 398 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"monitor",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xC8,	0,	CPU_SSE3,	0,	0},
#line 808 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_uqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x08,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 536 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pi2fd",	now3d_insn,	1,	SUF_Z,	0x0D,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1120 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpabsd",	avx2_ssse3_2op_insn,	2,	SUF_Z,	0x1E,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1063 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmaskmovpd",	vmaskmov_insn,	4,	SUF_Z,	0x2D,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 680 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rsts",	cyrixsmm_insn,	1,	SUF_Z,	0x7D,	0,	0,	0,	CPU_486,	CPU_Cyrix,	CPU_SMM},
#line 1007 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubaddpd",	fma_128_256_insn,	4,	SUF_Z,	0x5F,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 244 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldpi",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xEB,	0,	0,	CPU_FPU,	0,	0},
#line 125 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpnless",	ssecmp_32_insn,	4,	SUF_Z,	0x06,	0xF3,	0,	0,	CPU_SSE,	0,	0},
#line 451 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"o32",	NULL,	X86_OPERSIZE>>8,	0x20,	0,	0,	0,	0,	0,	0,	0},
#line 205 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcmovne",	fcmovcc_insn,	1,	SUF_Z,	0xDB,	0xC8,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 863 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_osps",	ssecmp_128_insn,	3,	SUF_Z,	0x1C,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 962 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vextractf128",	vextractif128_insn,	1,	SUF_Z,	0x19,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 577 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmulhw",	mmxsse2_insn,	2,	SUF_Z,	0xE5,	0,	0,	0,	CPU_MMX,	0,	0},
#line 260 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"frndint",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xFC,	0,	0,	CPU_FPU,	0,	0},
#line 1139 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpblendd",	vex_66_0F3A_imm8_avx2_insn,	2,	SUF_Z,	0x02,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 892 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnle_uqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x16,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 97 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovns",	cmovcc_insn,	3,	SUF_Z,	0x09,	0,	0,	0,	CPU_686,	0,	0},
#line 1304 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaxsw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xEE,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1228 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneuw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 543 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmaddubsw",	ssse3_insn,	5,	SUF_Z,	0x04,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 641 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pushad",	onebyte_insn,	1,	SUF_Z,	0x60,	0x20,	0,	NOT_64,	CPU_386,	0,	0},
#line 1218 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneqd",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 1428 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xadd",	cmpxchgxadd_insn,	4,	SUF_Z,	0xC0,	0,	0,	0,	CPU_486,	0,	0},
#line 571 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmuldq",	sse4_insn,	2,	SUF_Z,	0x28,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 714 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnz",	setcc_insn,	1,	SUF_Z,	0x05,	0,	0,	0,	CPU_386,	0,	0},
#line 839 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgtps",	ssecmp_128_insn,	3,	SUF_Z,	0x0E,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 585 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pop",	pop_insn,	23,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 455 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"orps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x56,	0,	0,	CPU_SSE,	0,	0},
#line 741 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sqrtss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x51,	0,	0,	CPU_SSE,	0,	0},
#line 1019 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd213sd",	vfma_sd_insn,	2,	SUF_Z,	0xAD,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1299 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaddwd",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xF5,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 938 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtpd2dq",	avx_cvt_xmm128_insn,	2,	SUF_Z,	0xF2,	0xE6,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 204 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcmovnbe",	fcmovcc_insn,	1,	SUF_Z,	0xDB,	0xD0,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 1092 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovntdq",	movnt_insn,	2,	SUF_Z,	0x66,	0xE7,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 80 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmove",	cmovcc_insn,	3,	SUF_Z,	0x04,	0,	0,	0,	CPU_686,	0,	0},
#line 699 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setl",	setcc_insn,	1,	SUF_Z,	0x0C,	0,	0,	0,	CPU_386,	0,	0},
#line 1223 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomnequw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 815 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeqps",	ssecmp_128_insn,	3,	SUF_Z,	0x00,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1108 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmrun",	svm_rax_insn,	2,	SUF_Z,	0xD8,	0,	0,	0,	CPU_SVM,	0,	0},
#line 629 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pswapd",	now3d_insn,	1,	SUF_Z,	0xBB,	0,	0,	0,	CPU_3DNow,	CPU_Athlon,	0},
#line 854 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpltpd",	ssecmp_128_insn,	3,	SUF_Z,	0x01,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 562 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovsxdq",	sse4m64_insn,	4,	SUF_Z,	0x25,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 954 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vdivpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x5E,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 711 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setno",	setcc_insn,	1,	SUF_Z,	0x01,	0,	0,	0,	CPU_386,	0,	0},
#line 549 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmaxub",	mmxsse2_insn,	2,	SUF_Z,	0xDE,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 359 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ldmxcsr",	ldstmxcsr_insn,	1,	SUF_Z,	0x02,	0,	0,	0,	CPU_SSE,	0,	0},
#line 705 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnc",	setcc_insn,	1,	SUF_Z,	0x03,	0,	0,	0,	CPU_386,	0,	0},
#line 361 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lea",	lea_insn,	3,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 896 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnlesd",	ssecmp_64_insn,	4,	SUF_Z,	0x06,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1357 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpslldq",	pslrldq_insn,	4,	SUF_Z,	0x07,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1278 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphsubdq",	vphaddsub_insn,	1,	SUF_Z,	0xE3,	0,	0,	0,	CPU_XOP,	0,	0},
#line 67 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cdqe",	onebyte_insn,	1,	SUF_Z,	0x98,	0x40,	0,	ONLY_64,	0,	0,	0},
#line 410 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movhpd",	movhlp_insn,	3,	SUF_Z,	0x66,	0x16,	0,	0,	CPU_SSE2,	0,	0},
#line 86 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnae",	cmovcc_insn,	3,	SUF_Z,	0x02,	0,	0,	0,	CPU_686,	0,	0},
#line 61 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"btr",	bittest_insn,	6,	SUF_Z,	0xB3,	0x06,	0,	0,	CPU_386,	0,	0},
#line 249 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fnclex",	twobyte_insn,	1,	SUF_Z,	0xDB,	0xE2,	0,	0,	CPU_FPU,	0,	0},
#line 314 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"invlpg",	twobytemem_insn,	1,	SUF_Z,	0x07,	0x0F,	0x01,	0,	CPU_486,	CPU_Priv,	0},
#line 735 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"smint",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x38,	0,	0,	CPU_686,	CPU_Cyrix,	0},
#line 1375 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsubsw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xE9,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1452 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xstorerng",	padlock_insn,	1,	SUF_Z,	0xC0,	0x00,	0xA7,	0,	CPU_PadLock,	0,	0},
#line 832 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgesd",	ssecmp_64_insn,	4,	SUF_Z,	0x0D,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1351 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshufhw",	xmm_xmm128_imm_256avx2_insn,	2,	SUF_Z,	0xF3,	0x70,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 14 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"a64",	NULL,	X86_ADDRSIZE>>8,	0x40,	0,	0,	0,	ONLY_64,	0,	0,	0},
#line 306 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"insertq",	insertq_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_SSE4a,	0,	0},
#line 891 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnle_uqps",	ssecmp_128_insn,	3,	SUF_Z,	0x16,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 308 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"int",	int_insn,	1,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 847 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpleps",	ssecmp_128_insn,	3,	SUF_Z,	0x02,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1402 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vsqrtss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x51,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1163 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpistrm",	sse4pcmpstr_insn,	1,	SUF_Z,	0x62,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 376 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lodsq",	onebyte_insn,	1,	SUF_Z,	0xAD,	0x40,	0,	ONLY_64,	0,	0,	0},
#line 539 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pinsrd",	pinsrd_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_SSE41,	0},
#line 389 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"maxpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x5F,	0,	0,	CPU_SSE2,	0,	0},
#line 873 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneqss",	ssecmp_32_insn,	4,	SUF_Z,	0x04,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 280 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fucomi",	fcom2_insn,	2,	SUF_Z,	0xDB,	0xE8,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 465 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"packusdw",	sse4_insn,	2,	SUF_Z,	0x2B,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1212 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomltuw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x00,	0,	0,	CPU_XOP,	0,	0},
#line 1134 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpalignr",	sse4imm_256avx2_insn,	4,	SUF_Z,	0x0F,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1314 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovmskb",	pmovmskb_insn,	6,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1057 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vinsertf128",	vinsertif128_insn,	1,	SUF_Z,	0x18,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 30 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aesenclast",	aes_insn,	2,	SUF_Z,	0x38,	0xDD,	0,	0,	CPU_AVX,	0,	0},
#line 583 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmvnzb",	cyrixmmx_insn,	1,	SUF_Z,	0x5A,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 460 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pabsb",	ssse3_insn,	5,	SUF_Z,	0x1C,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 1040 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub231ss",	vfma_ss_insn,	2,	SUF_Z,	0xBF,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 524 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfrcpit2",	now3d_insn,	1,	SUF_Z,	0xB6,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 462 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pabsw",	ssse3_insn,	5,	SUF_Z,	0x1D,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 1101 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovupd",	movau_insn,	6,	SUF_Z,	0x66,	0x10,	0x01,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 940 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtph2ps",	avx_cvtph2ps_insn,	4,	SUF_Z,	0x66,	0x13,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1157 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpestrm",	sse4pcmpstr_insn,	1,	SUF_Z,	0x60,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 369 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lldt",	prot286_insn,	1,	SUF_Z,	0x02,	0x00,	0,	0,	CPU_286,	CPU_Priv,	CPU_Prot},
#line 1232 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomtrued",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x07,	0,	0,	CPU_XOP,	0,	0},
#line 1358 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsllq",	vpshift_insn,	8,	SUF_Z,	0xF3,	0x73,	0x06,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 259 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fptan",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF2,	0,	0,	CPU_FPU,	0,	0},
#line 148 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpxchg8b",	cmpxchg8b_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_586,	0,	0},
#line 982 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsub132ps",	vfma_ps_insn,	2,	SUF_Z,	0x96,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1261 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddbq",	vphaddsub_insn,	1,	SUF_Z,	0xC3,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1135 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpand",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xDB,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 135 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpps",	xmm_xmm128_imm_insn,	1,	SUF_Z,	0x00,	0xC2,	0,	0,	CPU_SSE,	0,	0},
#line 291 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fyl2xp1",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF9,	0,	0,	CPU_FPU,	0,	0},
#line 895 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnleps",	ssecmp_128_insn,	3,	SUF_Z,	0x06,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 654 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rdmsr",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x32,	0,	0,	CPU_586,	CPU_Priv,	0},
#line 733 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sldt",	sldtmsw_insn,	6,	SUF_Z,	0x00,	0x00,	0,	0,	CPU_286,	0,	0},
#line 795 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vblendps",	sse4imm_256_insn,	4,	SUF_Z,	0x0C,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 744 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"stgi",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xDC,	0,	CPU_SVM,	0,	0},
#line 1208 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomltq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x00,	0,	0,	CPU_XOP,	0,	0},
#line 772 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ud2",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x0B,	0,	0,	CPU_286,	0,	0},
#line 56 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"bsf",	bsfr_insn,	3,	SUF_Z,	0xBC,	0,	0,	0,	CPU_386,	0,	0},
#line 416 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movmskps",	movmsk_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_SSE,	0},
#line 1264 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphadddq",	vphaddsub_insn,	1,	SUF_Z,	0xCB,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1400 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vsqrtps",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x51,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 468 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddd",	mmxsse2_insn,	2,	SUF_Z,	0xFE,	0,	0,	0,	CPU_MMX,	0,	0},
#line 54 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blsr",	vex_gpr_ndd_rm_0F38_regext_insn,	2,	SUF_Z,	0x00,	0xF3,	0x01,	ONLY_AVX,	CPU_BMI1,	0,	0},
#line 533 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"phsubd",	ssse3_insn,	5,	SUF_Z,	0x06,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 501 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpistri",	sse4pcmpstr_insn,	1,	SUF_Z,	0x63,	0,	0,	0,	CPU_SSE42,	0,	0},
#line 1343 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshaq",	amd_vpshift_insn,	2,	SUF_Z,	0x9B,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1227 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneuq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 18 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aas",	onebyte_insn,	1,	SUF_Z,	0x3F,	0,	0,	NOT_64,	0,	0,	0},
#line 674 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"roundss",	sse4m32imm_insn,	4,	SUF_Z,	0x0A,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1287 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacsdqh",	vpma_insn,	1,	SUF_Z,	0x9F,	0,	0,	0,	CPU_XOP,	0,	0},
#line 675 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rsdc",	rsdc_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_486,	CPU_Cyrix,	CPU_SMM},
#line 803 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_osps",	ssecmp_128_insn,	3,	SUF_Z,	0x10,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 155 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtdq2ps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x5B,	0,	0,	CPU_SSE2,	0,	0},
#line 1222 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomnequq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 1233 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomtrueq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x07,	0,	0,	CPU_XOP,	0,	0},
#line 23 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"addsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x58,	0,	0,	CPU_SSE2,	0,	0},
#line 776 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"unpcklpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x14,	0,	0,	CPU_SSE2,	0,	0},
#line 113 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpless",	ssecmp_32_insn,	4,	SUF_Z,	0x02,	0xF3,	0,	0,	CPU_SSE,	0,	0},
#line 1305 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaxub",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xDE,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 946 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtsi2sd",	cvt_xmm_rmx_insn,	6,	SUF_Z,	0xF2,	0x2A,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 785 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaesdeclast",	aes_insn,	2,	SUF_Z,	0x38,	0xDF,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 151 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cpuid",	twobyte_insn,	1,	SUF_Z,	0x0F,	0xA2,	0,	0,	CPU_486,	0,	0},
#line 511 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pf2iw",	now3d_insn,	1,	SUF_Z,	0x1C,	0,	0,	0,	CPU_3DNow,	CPU_Athlon,	0},
#line 1377 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsubusw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xD9,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 841 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgtss",	ssecmp_32_insn,	4,	SUF_Z,	0x0E,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1237 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomtrueuw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x07,	0,	0,	CPU_XOP,	0,	0},
#line 951 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvttps2dq",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0xF3,	0x5B,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1273 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddwd",	vphaddsub_insn,	1,	SUF_Z,	0xC6,	0,	0,	0,	CPU_XOP,	0,	0},
#line 481 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pavgb",	mmxsse2_insn,	2,	SUF_Z,	0xE0,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 774 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"unpckhpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x15,	0,	0,	CPU_SSE2,	0,	0},
#line 828 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpge_oqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x1D,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 375 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lodsd",	onebyte_insn,	1,	SUF_Z,	0xAD,	0x20,	0,	0,	CPU_386,	0,	0},
#line 295 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"hlt",	onebyte_insn,	1,	SUF_Z,	0xF4,	0,	0,	0,	CPU_Priv,	0,	0},
#line 175 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvttss2si",	cvt_rx_xmm32_insn,	4,	SUF_Z,	0xF3,	0x2C,	0,	0,	CPU_386,	CPU_SSE,	0},
#line 651 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rcr",	shift_insn,	16,	SUF_Z,	0x03,	0,	0,	0,	0,	0,	0},
#line 520 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfnacc",	now3d_insn,	1,	SUF_Z,	0x8A,	0,	0,	0,	CPU_3DNow,	CPU_Athlon,	0},
#line 1130 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpaddsw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xED,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 974 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd231ps",	vfma_ps_insn,	2,	SUF_Z,	0xB8,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 421 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movntps",	movnt_insn,	2,	SUF_Z,	0x00,	0x2B,	0,	0,	CPU_SSE,	0,	0},
#line 141 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpunordpd",	ssecmp_128_insn,	3,	SUF_Z,	0x03,	0x66,	0,	0,	CPU_SSE,	0,	0},
#line 1028 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmaddss",	fma_128_m32_insn,	3,	SUF_Z,	0x7A,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 408 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movdqu",	movau_insn,	6,	SUF_Z,	0xF3,	0x6F,	0x10,	0,	CPU_SSE2,	0,	0},
#line 871 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneqps",	ssecmp_128_insn,	3,	SUF_Z,	0x04,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 851 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmplt_oqps",	ssecmp_128_insn,	3,	SUF_Z,	0x11,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1106 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmread",	vmxmemrd_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_P4,	0,	0},
#line 1149 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpclmullqlqdq",	pclmulqdq_fixed_insn,	2,	SUF_Z,	0x00,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 636 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"punpckldq",	mmxsse2_insn,	2,	SUF_Z,	0x62,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1137 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpavgb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xE0,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 35 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"andnpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x55,	0,	0,	CPU_SSE2,	0,	0},
#line 436 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movupd",	movau_insn,	6,	SUF_Z,	0x66,	0x10,	0x01,	0,	CPU_SSE2,	0,	0},
#line 512 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfacc",	now3d_insn,	1,	SUF_Z,	0xAE,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 265 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsin",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xFE,	0,	0,	CPU_286,	CPU_FPU,	0},
#line 732 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"skinit",	skinit_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_SVM,	0,	0},
#line 852 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmplt_oqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x11,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1397 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vshufpd",	xmm_xmm128_imm_256_insn,	3,	SUF_Z,	0x66,	0xC6,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 397 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"minss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5D,	0,	0,	CPU_SSE,	0,	0},
#line 1112 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmulsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x59,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 34 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"andn",	vex_gpr_reg_nds_rm_0F_insn,	2,	SUF_Z,	0x00,	0x38,	0xF2,	ONLY_AVX,	CPU_BMI1,	0,	0},
#line 1249 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpermpd",	vperm_imm_avx2_insn,	1,	SUF_Z,	0x01,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 566 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovzxbq",	sse4m16_insn,	4,	SUF_Z,	0x32,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 411 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movhps",	movhlp_insn,	3,	SUF_Z,	0x00,	0x16,	0,	0,	CPU_SSE,	0,	0},
#line 898 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnlt_uqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x15,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 380 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"loopne",	loop_insn,	8,	SUF_Z,	0x00,	0,	0,	0,	0,	0,	0},
#line 1306 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaxud",	ssse3_insn,	5,	SUF_Z,	0x3F,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 277 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsubrp",	farithp_insn,	3,	SUF_Z,	0xE0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 686 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sbb",	arith_insn,	22,	SUF_Z,	0x18,	0x03,	0,	0,	0,	0,	0},
#line 1055 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vhsubpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x7D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 26 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"addsubps",	xmm_xmm128_insn,	2,	SUF_Z,	0xF2,	0xD0,	0,	0,	CPU_SSE3,	0,	0},
#line 551 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmaxuw",	sse4_insn,	2,	SUF_Z,	0x3E,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 328 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"je",	jcc_insn,	9,	SUF_Z,	0x04,	0,	0,	0,	0,	0,	0},
#line 943 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtps2ph",	avx_cvtps2ph_insn,	4,	SUF_Z,	0x66,	0x1D,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 119 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpneqps",	ssecmp_128_insn,	3,	SUF_Z,	0x04,	0,	0,	0,	CPU_SSE,	0,	0},
#line 545 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmagw",	cyrixmmx_insn,	1,	SUF_Z,	0x52,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 1453 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xtest",	tsx_0x0F_0x01_insn,	1,	SUF_Z,	0xD6,	0,	0,	0,	CPU_TSX,	0,	0},
#line 1319 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovsxwd",	sse4m64_insn,	4,	SUF_Z,	0x23,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1280 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphsubw",	ssse3_insn,	5,	SUF_Z,	0x05,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 970 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd213ps",	vfma_ps_insn,	2,	SUF_Z,	0xA8,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 162 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtps2pd",	xmm_xmm64_insn,	4,	SUF_Z,	0x00,	0x5A,	0,	0,	CPU_SSE2,	0,	0},
#line 992 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub132ss",	vfma_ss_insn,	2,	SUF_Z,	0x9B,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 466 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"packuswb",	mmxsse2_insn,	2,	SUF_Z,	0x67,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1396 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vrsqrtss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x52,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 988 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsubps",	fma_128_256_insn,	4,	SUF_Z,	0x5C,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 1242 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomuw",	vpcom_imm_insn,	1,	SUF_Z,	0xED,	0,	0,	0,	CPU_XOP,	0,	0},
#line 758 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"svldt",	cyrixsmm_insn,	1,	SUF_Z,	0x7A,	0,	0,	0,	CPU_486,	CPU_Cyrix,	CPU_SMM},
#line 64 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"call",	call_insn,	30,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 95 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovno",	cmovcc_insn,	3,	SUF_Z,	0x01,	0,	0,	0,	CPU_686,	0,	0},
#line 1404 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vsubpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x5C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1360 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsllvq",	vpshiftv_vexw1_avx2_insn,	2,	SUF_Z,	0x47,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 719 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sets",	setcc_insn,	1,	SUF_Z,	0x08,	0,	0,	0,	CPU_386,	0,	0},
#line 90 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovne",	cmovcc_insn,	3,	SUF_Z,	0x05,	0,	0,	0,	CPU_686,	0,	0},
#line 424 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movntss",	movntss_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_SSE4a,	0,	0},
#line 470 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddsb",	mmxsse2_insn,	2,	SUF_Z,	0xEC,	0,	0,	0,	CPU_MMX,	0,	0},
#line 748 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"stosd",	onebyte_insn,	1,	SUF_Z,	0xAB,	0x20,	0,	0,	CPU_386,	0,	0},
#line 1039 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub231sd",	vfma_sd_insn,	2,	SUF_Z,	0xBF,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 550 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmaxud",	sse4_insn,	2,	SUF_Z,	0x3F,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 100 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovp",	cmovcc_insn,	3,	SUF_Z,	0x0A,	0,	0,	0,	CPU_686,	0,	0},
#line 1253 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpextrd",	pextrd_insn,	1,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 392 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"maxss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5F,	0,	0,	CPU_SSE,	0,	0},
#line 1071 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vminpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x5D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 784 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaesdec",	aes_insn,	2,	SUF_Z,	0x38,	0xDE,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 82 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovge",	cmovcc_insn,	3,	SUF_Z,	0x0D,	0,	0,	0,	CPU_686,	0,	0},
#line 37 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"andpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x54,	0,	0,	CPU_SSE2,	0,	0},
#line 252 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fnsave",	onebytemem_insn,	1,	SUF_Z,	0x06,	0xDD,	0,	0,	CPU_FPU,	0,	0},
#line 109 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpeqss",	ssecmp_32_insn,	4,	SUF_Z,	0x00,	0xF3,	0,	0,	CPU_SSE,	0,	0},
#line 541 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pinsrw",	pinsrw_insn,	9,	SUF_Z,	0,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 464 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"packsswb",	mmxsse2_insn,	2,	SUF_Z,	0x63,	0,	0,	0,	CPU_MMX,	0,	0},
#line 242 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldlg2",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xEC,	0,	0,	CPU_FPU,	0,	0},
#line 1140 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpblendvb",	avx2_sse4xmm0_insn,	2,	SUF_Z,	0x4C,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 160 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtpi2ps",	cvt_xmm_mm_ps_insn,	1,	SUF_Z,	0x2A,	0,	0,	0,	CPU_SSE,	0,	0},
#line 1266 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddubd",	vphaddsub_insn,	1,	SUF_Z,	0xD2,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1376 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsubusb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xD8,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1308 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpminsb",	ssse3_insn,	5,	SUF_Z,	0x38,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 994 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub213ps",	vfma_ps_insn,	2,	SUF_Z,	0xAA,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 700 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setle",	setcc_insn,	1,	SUF_Z,	0x0E,	0,	0,	0,	CPU_386,	0,	0},
#line 1411 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vucomiss",	avx_xmm_xmm32_insn,	2,	SUF_Z,	0x00,	0x2E,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 354 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"js",	jcc_insn,	9,	SUF_Z,	0x08,	0,	0,	0,	0,	0,	0},
#line 1340 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsadbw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xF6,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 731 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sidt",	twobytemem_insn,	1,	SUF_Z,	0x01,	0x0F,	0x01,	0,	CPU_286,	CPU_Priv,	0},
#line 564 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovsxwq",	sse4m32_insn,	4,	SUF_Z,	0x24,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 379 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"loope",	loop_insn,	8,	SUF_Z,	0x01,	0,	0,	0,	0,	0,	0},
#line 1449 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xsha1",	padlock_insn,	1,	SUF_Z,	0xC8,	0xF3,	0xA6,	0,	CPU_PadLock,	0,	0},
#line 1090 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovmskpd",	movmsk_insn,	4,	SUF_Z,	0x66,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1388 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpxor",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xEF,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 89 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnc",	cmovcc_insn,	3,	SUF_Z,	0x03,	0,	0,	0,	CPU_686,	0,	0},
#line 298 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ibts",	ibts_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_Obs,	CPU_Undoc},
#line 836 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgt_oqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x1E,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1060 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vlddqu",	lddqu_insn,	2,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1231 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomtrueb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x07,	0,	0,	CPU_XOP,	0,	0},
#line 760 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"swapgs",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xF8,	ONLY_64,	0,	0,	0},
#line 1167 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomeqd",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x04,	0,	0,	CPU_XOP,	0,	0},
#line 1125 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpackuswb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x67,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1174 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomfalseb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x06,	0,	0,	CPU_XOP,	0,	0},
#line 1127 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpaddd",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xFE,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 646 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pushfw",	onebyte_insn,	1,	SUF_Z,	0x9C,	0x10,	0x40,	0,	0,	0,	0},
#line 1142 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpbroadcastb",	vpbroadcastb_avx2_insn,	4,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 580 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmuludq",	mmxsse2_insn,	2,	SUF_Z,	0xF4,	0,	0,	0,	CPU_SSE2,	0,	0},
#line 211 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcomp",	fcom_insn,	6,	SUF_Z,	0xD8,	0x03,	0,	0,	CPU_FPU,	0,	0},
#line 1438 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xgetbv",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xD0,	0,	CPU_386,	CPU_XSAVE,	0},
#line 1158 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpgtb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x64,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1176 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomfalseq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x06,	0,	0,	CPU_XOP,	0,	0},
#line 838 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgtpd",	ssecmp_128_insn,	3,	SUF_Z,	0x0E,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 194 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fadd",	farith_insn,	7,	SUF_Z,	0xC0,	0xC0,	0x00,	0,	CPU_FPU,	0,	0},
#line 473 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddusb",	mmxsse2_insn,	2,	SUF_Z,	0xDC,	0,	0,	0,	CPU_MMX,	0,	0},
#line 874 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnge_uqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x19,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 643 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pushf",	onebyte_insn,	1,	SUF_Z,	0x9C,	0x00,	0x40,	0,	0,	0,	0},
#line 156 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtpd2dq",	xmm_xmm128_insn,	2,	SUF_Z,	0xF2,	0xE6,	0,	0,	CPU_SSE2,	0,	0},
#line 637 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"punpcklqdq",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x6C,	0,	0,	CPU_SSE2,	0,	0},
#line 418 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movntdqa",	movntdqa_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 105 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmp",	arith_insn,	22,	SUF_Z,	0x38,	0x07,	0,	0,	0,	0,	0},
#line 900 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnlt_uqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x15,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 349 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jo",	jcc_insn,	9,	SUF_Z,	0x00,	0,	0,	0,	0,	0,	0},
#line 1325 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovzxwd",	sse4m64_insn,	4,	SUF_Z,	0x33,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1122 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpackssdw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x6B,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 58 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"bswap",	bswap_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_486,	0,	0},
#line 1027 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmaddsd",	fma_128_m64_insn,	3,	SUF_Z,	0x7B,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 467 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddb",	mmxsse2_insn,	2,	SUF_Z,	0xFC,	0,	0,	0,	CPU_MMX,	0,	0},
#line 472 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddsw",	mmxsse2_insn,	2,	SUF_Z,	0xED,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1365 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsrld",	vpshift_insn,	8,	SUF_Z,	0xD2,	0x72,	0x02,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1181 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomfalsew",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x06,	0,	0,	CPU_XOP,	0,	0},
#line 879 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngeps",	ssecmp_128_insn,	3,	SUF_Z,	0x09,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 202 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcmove",	fcmovcc_insn,	1,	SUF_Z,	0xDA,	0xC8,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 1447 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xsaveopt64",	xsaveopt64_insn,	1,	SUF_Z,	0x06,	0x0F,	0xAE,	ONLY_64,	CPU_XSAVEOPT,	0,	0},
#line 1097 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovsd",	movsd_insn,	5,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1046 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfrczps",	vfrc_pdps_insn,	2,	SUF_Z,	0x00,	0,	0,	0,	CPU_XOP,	0,	0},
#line 163 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtps2pi",	cvt_mm_xmm64_insn,	2,	SUF_Z,	0x2D,	0,	0,	0,	CPU_SSE,	0,	0},
#line 1349 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshufb",	ssse3_insn,	5,	SUF_Z,	0x00,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 635 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"punpcklbw",	mmxsse2_insn,	2,	SUF_Z,	0x60,	0,	0,	0,	CPU_MMX,	0,	0},
#line 769 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ucomisd",	xmm_xmm64_insn,	4,	SUF_Z,	0x66,	0x2E,	0,	0,	CPU_SSE2,	0,	0},
#line 1114 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmwrite",	vmxmemwr_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_P4,	0,	0},
#line 1115 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmxoff",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xC4,	0,	CPU_P4,	0,	0},
#line 542 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmachriw",	pmachriw_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 1189 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgew",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x03,	0,	0,	CPU_XOP,	0,	0},
#line 68 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"clc",	onebyte_insn,	1,	SUF_Z,	0xF8,	0,	0,	0,	0,	0,	0},
#line 604 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pshufhw",	xmm_xmm128_imm_insn,	1,	SUF_Z,	0xF3,	0x70,	0,	0,	CPU_SSE2,	0,	0},
#line 196 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fbld",	fbldstp_insn,	1,	SUF_Z,	0x04,	0,	0,	0,	CPU_FPU,	0,	0},
#line 860 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_oqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x0C,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 609 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psignw",	ssse3_insn,	5,	SUF_Z,	0x09,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 1178 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomfalseud",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x06,	0,	0,	CPU_XOP,	0,	0},
#line 1045 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfrczpd",	vfrc_pdps_insn,	2,	SUF_Z,	0x01,	0,	0,	0,	CPU_XOP,	0,	0},
#line 367 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lgs",	lfgss_insn,	3,	SUF_Z,	0xB5,	0,	0,	0,	CPU_386,	0,	0},
#line 1087 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovlhps",	movhllhps_insn,	2,	SUF_Z,	0x16,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 877 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnge_uqss",	ssecmp_32_insn,	4,	SUF_Z,	0x19,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 395 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"minps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x5D,	0,	0,	CPU_SSE,	0,	0},
#line 1307 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaxuw",	ssse3_insn,	5,	SUF_Z,	0x3E,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 346 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnp",	jcc_insn,	9,	SUF_Z,	0x0B,	0,	0,	0,	0,	0,	0},
#line 1143 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpbroadcastd",	vpbroadcastd_avx2_insn,	4,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 569 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovzxwd",	sse4m64_insn,	4,	SUF_Z,	0x33,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1049 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vgatherdpd",	gather_64x_64x_insn,	2,	SUF_Z,	0x92,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 1077 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmmcall",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xD9,	0,	CPU_SVM,	0,	0},
#line 687 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"scasb",	onebyte_insn,	1,	SUF_Z,	0xAE,	0x00,	0,	0,	0,	0,	0},
#line 212 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcompp",	twobyte_insn,	1,	SUF_Z,	0xDE,	0xD9,	0,	0,	CPU_FPU,	0,	0},
#line 302 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"inc",	incdec_insn,	6,	SUF_Z,	0x40,	0x00,	0,	0,	0,	0,	0},
#line 247 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fmul",	farith_insn,	7,	SUF_Z,	0xC8,	0xC8,	0x01,	0,	CPU_FPU,	0,	0},
#line 485 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pblendw",	sse4imm_insn,	2,	SUF_Z,	0x0E,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 191 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"extrq",	extrq_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_SSE4a,	0,	0},
#line 55 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"bound",	bound_insn,	2,	SUF_Z,	0,	0,	0,	NOT_64,	CPU_186,	0,	0},
#line 743 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"std",	onebyte_insn,	1,	SUF_Z,	0xFD,	0,	0,	0,	0,	0,	0},
#line 1243 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomw",	vpcom_imm_insn,	1,	SUF_Z,	0xCD,	0,	0,	0,	CPU_XOP,	0,	0},
#line 648 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rcl",	shift_insn,	16,	SUF_Z,	0x02,	0,	0,	0,	0,	0,	0},
#line 826 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpge_oqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x1D,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 320 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"iretq",	onebyte_insn,	1,	SUF_Z,	0xCF,	0x40,	0,	ONLY_64,	0,	0,	0},
#line 1230 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomq",	vpcom_imm_insn,	1,	SUF_Z,	0xCF,	0,	0,	0,	CPU_XOP,	0,	0},
#line 142 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpunordps",	ssecmp_128_insn,	3,	SUF_Z,	0x03,	0,	0,	0,	CPU_SSE,	0,	0},
#line 476 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"palignr",	ssse3imm_insn,	2,	SUF_Z,	0x0F,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 352 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jpo",	jcc_insn,	9,	SUF_Z,	0x0B,	0,	0,	0,	0,	0,	0},
#line 750 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"stosw",	onebyte_insn,	1,	SUF_Z,	0xAB,	0x10,	0,	0,	0,	0,	0},
#line 1052 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vgatherqps",	gather_32x_32y_128_insn,	2,	SUF_Z,	0x93,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 525 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfrsqit1",	now3d_insn,	1,	SUF_Z,	0xA7,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1257 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpgatherdq",	gather_64x_64x_insn,	2,	SUF_Z,	0x90,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 1441 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xorpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x57,	0,	0,	CPU_SSE2,	0,	0},
#line 214 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fdecstp",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF6,	0,	0,	CPU_FPU,	0,	0},
#line 430 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movsldup",	xmm_xmm128_insn,	2,	SUF_Z,	0xF3,	0x12,	0,	0,	CPU_SSE3,	0,	0},
#line 263 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fscale",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xFD,	0,	0,	CPU_FPU,	0,	0},
#line 1374 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsubsb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xE8,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1234 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomtrueub",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x07,	0,	0,	CPU_XOP,	0,	0},
#line 1423 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"wrgsbase",	fs_gs_base_insn,	2,	SUF_Z,	0x03,	0,	0,	ONLY_64,	CPU_FSGSBASE,	0,	0},
#line 20 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"add",	arith_insn,	22,	SUF_Z,	0x00,	0x00,	0,	0,	0,	0,	0},
#line 356 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lahf",	onebyte_insn,	1,	SUF_Z,	0x9F,	0,	0,	0,	0,	0,	0},
#line 201 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcmovbe",	fcmovcc_insn,	1,	SUF_Z,	0xDA,	0xD0,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 401 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movapd",	movau_insn,	6,	SUF_Z,	0x66,	0x28,	0x01,	0,	CPU_SSE2,	0,	0},
#line 210 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcomip",	fcom2_insn,	2,	SUF_Z,	0xDF,	0xF0,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 172 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvttps2dq",	xmm_xmm128_insn,	2,	SUF_Z,	0xF3,	0x5B,	0,	0,	CPU_SSE2,	0,	0},
#line 666 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"retf",	retnf_insn,	6,	SUF_Z,	0xCA,	0x40,	0,	0,	0,	0,	0},
#line 427 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movsb",	onebyte_insn,	1,	SUF_Z,	0xA4,	0x00,	0,	0,	0,	0,	0},
#line 40 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"bextr",	bextr_insn,	4,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_386,	CPU_BMI1,	0},
#line 419 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movnti",	movnti_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_P4,	0,	0},
#line 952 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvttsd2si",	cvt_rx_xmm64_insn,	4,	SUF_Z,	0xF2,	0x2C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 106 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpeqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x00,	0x66,	0,	0,	CPU_SSE,	0,	0},
#line 440 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mul",	f6_insn,	4,	SUF_Z,	0x04,	0,	0,	0,	0,	0,	0},
#line 716 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setp",	setcc_insn,	1,	SUF_Z,	0x0A,	0,	0,	0,	CPU_386,	0,	0},
#line 671 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"roundpd",	sse4imm_insn,	2,	SUF_Z,	0x09,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1121 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpabsw",	avx2_ssse3_2op_insn,	2,	SUF_Z,	0x1D,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1445 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xsave",	twobytemem_insn,	1,	SUF_Z,	0x04,	0x0F,	0xAE,	0,	CPU_386,	CPU_XSAVE,	0},
#line 1363 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsravd",	vpshiftv_vexw0_avx2_insn,	2,	SUF_Z,	0x46,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 404 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movd",	movd_insn,	8,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_MMX,	0},
#line 1089 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovlps",	movhlp_insn,	3,	SUF_Z,	0x00,	0x12,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 450 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"o16",	NULL,	X86_OPERSIZE>>8,	0x10,	0,	0,	0,	0,	0,	0,	0},
#line 50 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blsfill",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x01,	0x02,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 1200 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomleq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x01,	0,	0,	CPU_XOP,	0,	0},
#line 887 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngtps",	ssecmp_128_insn,	3,	SUF_Z,	0x0A,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1327 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmuldq",	ssse3_insn,	5,	SUF_Z,	0x28,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 336 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnae",	jcc_insn,	9,	SUF_Z,	0x02,	0,	0,	0,	0,	0,	0},
#line 493 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpeqq",	sse4_insn,	2,	SUF_Z,	0x29,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1193 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgtub",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x02,	0,	0,	CPU_XOP,	0,	0},
#line 1160 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpgtq",	ssse3_insn,	5,	SUF_Z,	0x37,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 650 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rcpss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x53,	0,	0,	CPU_SSE,	0,	0},
#line 290 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fyl2x",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF1,	0,	0,	CPU_FPU,	0,	0},
#line 1294 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacswd",	vpma_insn,	1,	SUF_Z,	0x96,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1322 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovzxbq",	sse4m16_insn,	4,	SUF_Z,	0x32,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 856 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpltsd",	ssecmp_64_insn,	4,	SUF_Z,	0x01,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1425 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"wrshr",	rdwrshr_insn,	1,	SUF_Z,	0x01,	0,	0,	0,	CPU_686,	CPU_Cyrix,	CPU_SMM},
#line 486 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pclmulhqhqdq",	pclmulqdq_fixed_insn,	2,	SUF_Z,	0x11,	0,	0,	0,	CPU_AVX,	0,	0},
#line 1075 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmlaunch",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xC2,	0,	CPU_P4,	0,	0},
#line 875 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnge_uqps",	ssecmp_128_insn,	3,	SUF_Z,	0x19,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 558 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovmskb",	pmovmskb_insn,	6,	SUF_Z,	0,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 1018 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd213ps",	vfma_ps_insn,	2,	SUF_Z,	0xAC,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1406 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vsubsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 670 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rorx",	vex_gpr_reg_rm_0F_imm8_insn,	2,	SUF_Z,	0xF2,	0x3A,	0xF0,	ONLY_AVX,	CPU_BMI2,	0,	0},
#line 1213 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomltw",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x00,	0,	0,	CPU_XOP,	0,	0},
#line 595 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"prefetch",	twobytemem_insn,	1,	SUF_Z,	0x00,	0x0F,	0x0D,	0,	CPU_3DNow,	0,	0},
#line 914 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmppd",	xmm_xmm128_imm_256_insn,	3,	SUF_Z,	0x66,	0xC2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1430 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xbts",	xbts_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_Obs,	CPU_Undoc},
#line 953 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvttss2si",	cvt_rx_xmm32_insn,	4,	SUF_Z,	0xF3,	0x2C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 487 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pclmulhqlqdq",	pclmulqdq_fixed_insn,	2,	SUF_Z,	0x01,	0,	0,	0,	CPU_AVX,	0,	0},
#line 639 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"push",	push_insn,	35,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 1337 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vprotd",	vprot_insn,	3,	SUF_Z,	0x02,	0,	0,	0,	CPU_XOP,	0,	0},
#line 911 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpordps",	ssecmp_128_insn,	3,	SUF_Z,	0x07,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 463 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"packssdw",	mmxsse2_insn,	2,	SUF_Z,	0x6B,	0,	0,	0,	CPU_MMX,	0,	0},
#line 323 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jae",	jcc_insn,	9,	SUF_Z,	0x03,	0,	0,	0,	0,	0,	0},
#line 820 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpfalse_ossd",	ssecmp_64_insn,	4,	SUF_Z,	0x1B,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 989 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub132pd",	vfma_pd_insn,	2,	SUF_Z,	0x9A,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 546 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmaxsb",	sse4_insn,	2,	SUF_Z,	0x3C,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1433 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xcryptcfb",	padlock_insn,	1,	SUF_Z,	0xE0,	0xF3,	0xA7,	0,	CPU_PadLock,	0,	0},
#line 591 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"popfd",	onebyte_insn,	1,	SUF_Z,	0x9D,	0x20,	0,	NOT_64,	CPU_386,	0,	0},
#line 920 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmptrue_ussd",	ssecmp_64_insn,	4,	SUF_Z,	0x1F,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1328 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmulhrsw",	ssse3_insn,	5,	SUF_Z,	0x0B,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 600 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"prefetchw",	twobytemem_insn,	1,	SUF_Z,	0x01,	0x0F,	0x0D,	0,	CPU_3DNow,	0,	0},
#line 358 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lddqu",	lddqu_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_SSE3,	0,	0},
#line 316 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"invpcid",	invpcid_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_INVPCID,	CPU_Priv},
#line 616 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psrld",	pshift_insn,	4,	SUF_Z,	0xD2,	0x72,	0x02,	0,	CPU_MMX,	0,	0},
#line 1298 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaddubsw",	ssse3_insn,	5,	SUF_Z,	0x04,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 737 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"smsw",	sldtmsw_insn,	6,	SUF_Z,	0x04,	0x01,	0,	0,	CPU_286,	0,	0},
#line 1128 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpaddq",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xD4,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 881 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngess",	ssecmp_32_insn,	4,	SUF_Z,	0x09,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 388 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"maskmovq",	maskmovq_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 76 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovae",	cmovcc_insn,	3,	SUF_Z,	0x03,	0,	0,	0,	CPU_686,	0,	0},
#line 91 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovng",	cmovcc_insn,	3,	SUF_Z,	0x0E,	0,	0,	0,	CPU_686,	0,	0},
#line 991 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub132sd",	vfma_sd_insn,	2,	SUF_Z,	0x9B,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 587 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"popad",	onebyte_insn,	1,	SUF_Z,	0x61,	0x20,	0,	NOT_64,	CPU_386,	0,	0},
#line 347 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jns",	jcc_insn,	9,	SUF_Z,	0x09,	0,	0,	0,	0,	0,	0},
#line 1429 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xbegin",	tsx_xbegin_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_TSX,	0},
#line 834 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgt_oqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x1E,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1076 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmload",	svm_rax_insn,	2,	SUF_Z,	0xDA,	0,	0,	0,	CPU_SVM,	0,	0},
#line 1413 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vunpckhps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x15,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 799 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vbroadcasti128",	vbroadcastif128_insn,	1,	SUF_Z,	0x5A,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 69 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cld",	onebyte_insn,	1,	SUF_Z,	0xFC,	0,	0,	0,	0,	0,	0},
#line 771 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ud1",	twobyte_insn,	1,	SUF_Z,	0x0F,	0xB9,	0,	0,	CPU_286,	CPU_Undoc,	0},
#line 138 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpsq",	onebyte_insn,	1,	SUF_Z,	0xA7,	0x40,	0,	ONLY_64,	0,	0,	0},
#line 192 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"f2xm1",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF0,	0,	0,	CPU_FPU,	0,	0},
#line 634 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"punpckhwd",	mmxsse2_insn,	2,	SUF_Z,	0x69,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1024 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd231ss",	vfma_ss_insn,	2,	SUF_Z,	0xBD,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1048 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfrczss",	vfrczss_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1399 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vsqrtpd",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x51,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 592 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"popfq",	onebyte_insn,	1,	SUF_Z,	0x9D,	0x40,	0x40,	ONLY_64,	0,	0,	0},
#line 1035 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub213sd",	vfma_sd_insn,	2,	SUF_Z,	0xAF,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1033 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub213pd",	vfma_pd_insn,	2,	SUF_Z,	0xAE,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1302 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaxsb",	ssse3_insn,	5,	SUF_Z,	0x3C,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 710 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnle",	setcc_insn,	1,	SUF_Z,	0x0F,	0,	0,	0,	CPU_386,	0,	0},
#line 1037 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub231pd",	vfma_pd_insn,	2,	SUF_Z,	0xBE,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 965 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd132pd",	vfma_pd_insn,	2,	SUF_Z,	0x98,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 103 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovs",	cmovcc_insn,	3,	SUF_Z,	0x08,	0,	0,	0,	CPU_686,	0,	0},
#line 413 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movlpd",	movhlp_insn,	3,	SUF_Z,	0x66,	0x12,	0,	0,	CPU_SSE2,	0,	0},
#line 335 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jna",	jcc_insn,	9,	SUF_Z,	0x06,	0,	0,	0,	0,	0,	0},
#line 399 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"montmul",	padlock_insn,	1,	SUF_Z,	0xC0,	0xF3,	0xA6,	0,	CPU_PadLock,	0,	0},
#line 312 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"invd",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x08,	0,	0,	CPU_486,	CPU_Priv,	0},
#line 1054 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vhaddps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0xF2,	0x7C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 338 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnbe",	jcc_insn,	9,	SUF_Z,	0x07,	0,	0,	0,	0,	0,	0},
#line 1084 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovhlps",	movhllhps_insn,	2,	SUF_Z,	0x12,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 806 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_uqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x08,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 390 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"maxps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x5F,	0,	0,	CPU_SSE,	0,	0},
#line 303 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"insb",	onebyte_insn,	1,	SUF_Z,	0x6C,	0x00,	0,	0,	0,	0,	0},
#line 730 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"shufps",	xmm_xmm128_imm_insn,	1,	SUF_Z,	0x00,	0xC6,	0,	0,	CPU_SSE,	0,	0},
#line 560 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovsxbq",	sse4m16_insn,	4,	SUF_Z,	0x22,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1246 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpermd",	vperm_var_avx2_insn,	1,	SUF_Z,	0x36,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 92 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnge",	cmovcc_insn,	3,	SUF_Z,	0x0C,	0,	0,	0,	CPU_686,	0,	0},
#line 775 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"unpckhps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x15,	0,	0,	CPU_SSE,	0,	0},
#line 102 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovpo",	cmovcc_insn,	3,	SUF_Z,	0x0B,	0,	0,	0,	CPU_686,	0,	0},
#line 703 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnb",	setcc_insn,	1,	SUF_Z,	0x03,	0,	0,	0,	CPU_386,	0,	0},
#line 998 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub231ps",	vfma_ps_insn,	2,	SUF_Z,	0xBA,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 830 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgepd",	ssecmp_128_insn,	3,	SUF_Z,	0x0D,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 198 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fchs",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xE0,	0,	0,	CPU_FPU,	0,	0},
#line 304 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"insd",	onebyte_insn,	1,	SUF_Z,	0x6D,	0x20,	0,	0,	CPU_386,	0,	0},
#line 607 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psignb",	ssse3_insn,	5,	SUF_Z,	0x08,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 370 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lmsw",	prot286_insn,	1,	SUF_Z,	0x06,	0x01,	0,	0,	CPU_286,	CPU_Priv,	0},
#line 281 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fucomip",	fcom2_insn,	2,	SUF_Z,	0xDF,	0xE8,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 817 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeqss",	ssecmp_32_insn,	4,	SUF_Z,	0x00,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 927 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpunord_sps",	ssecmp_128_insn,	3,	SUF_Z,	0x13,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1175 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomfalsed",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x06,	0,	0,	CPU_XOP,	0,	0},
#line 831 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgeps",	ssecmp_128_insn,	3,	SUF_Z,	0x0D,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 685 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sarx",	vex_gpr_reg_rm_nds_0F_insn,	2,	SUF_Z,	0xF3,	0x38,	0xF7,	ONLY_AVX,	CPU_BMI2,	0,	0},
#line 809 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_uqss",	ssecmp_32_insn,	4,	SUF_Z,	0x08,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 371 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"loadall",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x07,	0,	0,	CPU_386,	CPU_Undoc,	0},
#line 655 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rdpmc",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x33,	0,	0,	CPU_686,	0,	0},
#line 208 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcom",	fcom_insn,	6,	SUF_Z,	0xD0,	0x02,	0,	0,	CPU_FPU,	0,	0},
#line 1099 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovsldup",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0xF3,	0x12,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 864 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_ossd",	ssecmp_64_insn,	4,	SUF_Z,	0x1C,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 632 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"punpckhdq",	mmxsse2_insn,	2,	SUF_Z,	0x6A,	0,	0,	0,	CPU_MMX,	0,	0},
#line 41 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blcfill",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x01,	0x01,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 475 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddw",	mmxsse2_insn,	2,	SUF_Z,	0xFD,	0,	0,	0,	CPU_MMX,	0,	0},
#line 241 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldl2t",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xE9,	0,	0,	CPU_FPU,	0,	0},
#line 886 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngtpd",	ssecmp_128_insn,	3,	SUF_Z,	0x0A,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 798 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vbroadcastf128",	vbroadcastif128_insn,	1,	SUF_Z,	0x1A,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 740 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sqrtsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x51,	0,	0,	CPU_SSE2,	0,	0},
#line 526 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfrsqrt",	now3d_insn,	1,	SUF_Z,	0x97,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1206 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomltb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x00,	0,	0,	CPU_XOP,	0,	0},
#line 140 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpsw",	onebyte_insn,	1,	SUF_Z,	0xA7,	0x10,	0,	0,	0,	0,	0},
#line 1347 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshlq",	amd_vpshift_insn,	2,	SUF_Z,	0x97,	0,	0,	0,	CPU_XOP,	0,	0},
#line 124 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpnlesd",	ssecmp_64_insn,	4,	SUF_Z,	0x06,	0xF2,	0,	0,	CPU_SSE2,	0,	0},
#line 1088 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovlpd",	movhlp_insn,	3,	SUF_Z,	0x66,	0x12,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1409 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vtestps",	sse4_insn,	2,	SUF_Z,	0x0E,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 157 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtpd2pi",	cvt_mm_xmm_insn,	1,	SUF_Z,	0x66,	0x2D,	0,	0,	CPU_SSE2,	0,	0},
#line 527 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfsub",	now3d_insn,	1,	SUF_Z,	0x9A,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1047 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfrczsd",	vfrczsd_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_XOP,	0,	0},
#line 941 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtps2dq",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x5B,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1285 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpinsrw",	pinsrw_insn,	9,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 665 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ret",	retnf_insn,	6,	SUF_Z,	0xC2,	0,	0,	0,	0,	0,	0},
#line 514 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfcmpeq",	now3d_insn,	1,	SUF_Z,	0xB0,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1422 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"wrfsbase",	fs_gs_base_insn,	2,	SUF_Z,	0x02,	0,	0,	ONLY_64,	CPU_FSGSBASE,	0,	0},
#line 540 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pinsrq",	pinsrq_insn,	2,	SUF_Z,	0,	0,	0,	ONLY_64,	CPU_SSE41,	0,	0},
#line 1110 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmulpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x59,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 313 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"invept",	eptvpid_insn,	2,	SUF_Z,	0x00,	0,	0,	0,	CPU_386,	CPU_EPTVPID,	0},
#line 1171 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomequq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x04,	0,	0,	CPU_XOP,	0,	0},
#line 840 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgtsd",	ssecmp_64_insn,	4,	SUF_Z,	0x0E,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 250 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fninit",	twobyte_insn,	1,	SUF_Z,	0xDB,	0xE3,	0,	0,	CPU_FPU,	0,	0},
#line 42 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blci",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x02,	0x06,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 497 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpgtb",	mmxsse2_insn,	2,	SUF_Z,	0x64,	0,	0,	0,	CPU_MMX,	0,	0},
#line 668 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rol",	shift_insn,	16,	SUF_Z,	0x00,	0,	0,	0,	0,	0,	0},
#line 763 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sysexit",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x35,	0,	NOT_64,	CPU_686,	CPU_Priv,	0},
#line 1050 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vgatherdps",	gather_32x_32y_insn,	2,	SUF_Z,	0x92,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 745 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sti",	onebyte_insn,	1,	SUF_Z,	0xFB,	0,	0,	0,	0,	0,	0},
#line 515 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfcmpge",	now3d_insn,	1,	SUF_Z,	0x90,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 199 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fclex",	threebyte_insn,	1,	SUF_Z,	0x9B,	0xDB,	0xE2,	0,	CPU_FPU,	0,	0},
#line 734 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"smi",	onebyte_insn,	1,	SUF_Z,	0xF1,	0,	0,	0,	CPU_386,	CPU_Undoc,	0},
#line 285 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fxam",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xE5,	0,	0,	CPU_FPU,	0,	0},
#line 495 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpestri",	sse4pcmpstr_insn,	1,	SUF_Z,	0x61,	0,	0,	0,	CPU_SSE42,	0,	0},
#line 865 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_osss",	ssecmp_32_insn,	4,	SUF_Z,	0x1C,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 715 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"seto",	setcc_insn,	1,	SUF_Z,	0x00,	0,	0,	0,	CPU_386,	0,	0},
#line 1094 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovntpd",	movnt_insn,	2,	SUF_Z,	0x66,	0x2B,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1296 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmadcsswd",	vpma_insn,	1,	SUF_Z,	0xA6,	0,	0,	0,	CPU_XOP,	0,	0},
#line 883 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngt_uqps",	ssecmp_128_insn,	3,	SUF_Z,	0x1A,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 757 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"svdc",	svdc_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_486,	CPU_Cyrix,	CPU_SMM},
#line 339 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnc",	jcc_insn,	9,	SUF_Z,	0x03,	0,	0,	0,	0,	0,	0},
#line 1391 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vroundpd",	avx_sse4imm_insn,	3,	SUF_Z,	0x09,	0,	0,	ONLY_AVX,	CPU_SSE41,	0,	0},
#line 1401 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vsqrtsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x51,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1431 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xchg",	xchg_insn,	16,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 236 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fld",	fld_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 997 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub231pd",	vfma_pd_insn,	2,	SUF_Z,	0xBA,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1332 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmullw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xD5,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 552 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pminsb",	sse4_insn,	2,	SUF_Z,	0x38,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 311 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"into",	onebyte_insn,	1,	SUF_Z,	0xCE,	0,	0,	NOT_64,	0,	0,	0},
#line 1281 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphsubwd",	vphaddsub_insn,	1,	SUF_Z,	0xE2,	0,	0,	0,	CPU_XOP,	0,	0},
#line 969 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd213pd",	vfma_pd_insn,	2,	SUF_Z,	0xA8,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 118 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpneqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x04,	0x66,	0,	0,	CPU_SSE,	0,	0},
#line 1188 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgeuw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x03,	0,	0,	CPU_XOP,	0,	0},
#line 1408 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vtestpd",	sse4_insn,	2,	SUF_Z,	0x0F,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 227 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fild",	fildstp_insn,	4,	SUF_Z,	0x00,	0x02,	0x05,	0,	CPU_FPU,	0,	0},
#line 1239 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomub",	vpcom_imm_insn,	1,	SUF_Z,	0xEC,	0,	0,	0,	CPU_XOP,	0,	0},
#line 768 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"tzmsk",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x01,	0x04,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 958 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vdppd",	sse4imm_insn,	2,	SUF_Z,	0x41,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 963 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vextracti128",	vextractif128_insn,	1,	SUF_Z,	0x39,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 158 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtpd2ps",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x5A,	0,	0,	CPU_SSE2,	0,	0},
#line 221 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ffreep",	ffree_insn,	1,	SUF_Z,	0xDF,	0,	0,	0,	CPU_686,	CPU_FPU,	CPU_Undoc},
#line 1098 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovshdup",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0xF3,	0x16,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1105 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmptrst",	vmxtwobytemem_insn,	1,	SUF_Z,	0x07,	0,	0,	0,	CPU_P4,	0,	0},
#line 1384 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpunpcklbw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x60,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 528 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfsubr",	now3d_insn,	1,	SUF_Z,	0xAA,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 129 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpnltss",	ssecmp_32_insn,	4,	SUF_Z,	0x05,	0xF3,	0,	0,	CPU_SSE,	0,	0},
#line 594 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"por",	mmxsse2_insn,	2,	SUF_Z,	0xEB,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1407 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vsubss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1371 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsubb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xF8,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 474 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddusw",	mmxsse2_insn,	2,	SUF_Z,	0xDD,	0,	0,	0,	CPU_MMX,	0,	0},
#line 243 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldln2",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xED,	0,	0,	CPU_FPU,	0,	0},
#line 521 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfpnacc",	now3d_insn,	1,	SUF_Z,	0x8E,	0,	0,	0,	CPU_3DNow,	CPU_Athlon,	0},
#line 1393 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vroundsd",	sse4m64imm_insn,	4,	SUF_Z,	0x0B,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1326 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovzxwq",	sse4m32_insn,	4,	SUF_Z,	0x34,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 990 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub132ps",	vfma_ps_insn,	2,	SUF_Z,	0x9A,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 937 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtdq2ps",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x5B,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 622 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubq",	mmxsse2_insn,	2,	SUF_Z,	0xFB,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1187 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgeuq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x03,	0,	0,	CPU_XOP,	0,	0},
#line 425 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movq",	movq_insn,	9,	SUF_Z,	0,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1184 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgeq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x03,	0,	0,	CPU_XOP,	0,	0},
#line 805 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_osss",	ssecmp_32_insn,	4,	SUF_Z,	0x10,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 849 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpless",	ssecmp_32_insn,	4,	SUF_Z,	0x02,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1067 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmaxsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5F,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 407 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movdqa",	movau_insn,	6,	SUF_Z,	0x66,	0x6F,	0x10,	0,	CPU_SSE2,	0,	0},
#line 507 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pextrd",	pextrd_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_SSE41,	0},
#line 293 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"haddpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x7C,	0,	0,	CPU_SSE3,	0,	0},
#line 1334 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpor",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xEB,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 519 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfmul",	now3d_insn,	1,	SUF_Z,	0xB4,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 618 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psrlq",	pshift_insn,	4,	SUF_Z,	0xD3,	0x73,	0x02,	0,	CPU_MMX,	0,	0},
#line 348 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnz",	jcc_insn,	9,	SUF_Z,	0x05,	0,	0,	0,	0,	0,	0},
#line 25 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"addsubpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0xD0,	0,	0,	CPU_SSE3,	0,	0},
#line 647 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pxor",	mmxsse2_insn,	2,	SUF_Z,	0xEF,	0,	0,	0,	CPU_MMX,	0,	0},
#line 561 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovsxbw",	sse4m64_insn,	4,	SUF_Z,	0x20,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1172 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomequw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x04,	0,	0,	CPU_XOP,	0,	0},
#line 22 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"addps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x58,	0,	0,	CPU_SSE,	0,	0},
#line 274 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsub",	farith_insn,	7,	SUF_Z,	0xE8,	0xE0,	0x04,	0,	CPU_FPU,	0,	0},
#line 111 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpleps",	ssecmp_128_insn,	3,	SUF_Z,	0x02,	0,	0,	0,	CPU_SSE,	0,	0},
#line 814 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x00,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1385 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpunpckldq",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x62,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1009 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubpd",	fma_128_256_insn,	4,	SUF_Z,	0x6D,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 1389 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vrcpps",	avx_xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x53,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 664 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"repz",	NULL,	X86_LOCKREP>>8,	0xF3,	0,	0,	0,	0,	0,	0,	0},
#line 623 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubsb",	mmxsse2_insn,	2,	SUF_Z,	0xE8,	0,	0,	0,	CPU_MMX,	0,	0},
#line 269 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fstcw",	fstcw_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 1146 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpclmulhqhqdq",	pclmulqdq_fixed_insn,	2,	SUF_Z,	0x11,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 65 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cbw",	onebyte_insn,	1,	SUF_Z,	0x98,	0x10,	0,	0,	0,	0,	0},
#line 996 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub213ss",	vfma_ss_insn,	2,	SUF_Z,	0xAB,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 673 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"roundsd",	sse4m64imm_insn,	4,	SUF_Z,	0x0B,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 337 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnb",	jcc_insn,	9,	SUF_Z,	0x03,	0,	0,	0,	0,	0,	0},
#line 742 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"stc",	onebyte_insn,	1,	SUF_Z,	0xF9,	0,	0,	0,	0,	0,	0},
#line 1254 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpextrq",	pextrq_insn,	1,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 627 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubusw",	mmxsse2_insn,	2,	SUF_Z,	0xD9,	0,	0,	0,	CPU_MMX,	0,	0},
#line 445 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mulx",	vex_gpr_reg_nds_rm_0F_insn,	2,	SUF_Z,	0xF2,	0x38,	0xF6,	ONLY_AVX,	CPU_BMI2,	0,	0},
#line 765 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"t1mskc",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x01,	0x07,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 1288 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacsdql",	vpma_insn,	1,	SUF_Z,	0x97,	0,	0,	0,	CPU_XOP,	0,	0},
#line 509 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pextrw",	pextrw_insn,	7,	SUF_Z,	0,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 1064 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmaskmovps",	vmaskmov_insn,	4,	SUF_Z,	0x2C,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 625 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubsw",	mmxsse2_insn,	2,	SUF_Z,	0xE9,	0,	0,	0,	CPU_MMX,	0,	0},
#line 712 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnp",	setcc_insn,	1,	SUF_Z,	0x0B,	0,	0,	0,	CPU_386,	0,	0},
#line 1001 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubadd132pd",	vfma_pd_insn,	2,	SUF_Z,	0x97,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1104 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmptrld",	vmxtwobytemem_insn,	1,	SUF_Z,	0x06,	0,	0,	0,	CPU_P4,	0,	0},
#line 614 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psrad",	pshift_insn,	4,	SUF_Z,	0xE2,	0x72,	0x04,	0,	CPU_MMX,	0,	0},
#line 452 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"o64",	NULL,	X86_OPERSIZE>>8,	0x40,	0,	0,	0,	ONLY_64,	0,	0,	0},
#line 802 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_ospd",	ssecmp_128_insn,	3,	SUF_Z,	0x10,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 126 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpnltpd",	ssecmp_128_insn,	3,	SUF_Z,	0x05,	0x66,	0,	0,	CPU_SSE,	0,	0},
#line 1366 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsrldq",	pslrldq_insn,	4,	SUF_Z,	0x03,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 910 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpordpd",	ssecmp_128_insn,	3,	SUF_Z,	0x07,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 386 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lzcnt",	cnt_insn,	3,	SUF_Z,	0xBD,	0,	0,	0,	CPU_LZCNT,	0,	0},
#line 417 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movntdq",	movnt_insn,	2,	SUF_Z,	0x66,	0xE7,	0,	0,	CPU_SSE2,	0,	0},
#line 702 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnae",	setcc_insn,	1,	SUF_Z,	0x02,	0,	0,	0,	CPU_386,	0,	0},
#line 964 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vextractps",	extractps_insn,	2,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 189 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"enter",	enter_insn,	3,	SUF_Z,	0,	0,	0,	0,	CPU_186,	0,	0},
#line 218 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fdivrp",	farithp_insn,	3,	SUF_Z,	0xF0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 725 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"shlx",	vex_gpr_reg_rm_nds_0F_insn,	2,	SUF_Z,	0x66,	0x38,	0xF7,	ONLY_AVX,	CPU_BMI2,	0,	0},
#line 1126 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpaddb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xFC,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 133 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpordss",	ssecmp_32_insn,	4,	SUF_Z,	0x07,	0xF3,	0,	0,	CPU_SSE,	0,	0},
#line 1166 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomeqb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x04,	0,	0,	CPU_XOP,	0,	0},
#line 1051 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vgatherqpd",	gather_64x_64y_insn,	2,	SUF_Z,	0x93,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 330 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jg",	jcc_insn,	9,	SUF_Z,	0x0F,	0,	0,	0,	0,	0,	0},
#line 494 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpeqw",	mmxsse2_insn,	2,	SUF_Z,	0x75,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1119 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpabsb",	avx2_ssse3_2op_insn,	2,	SUF_Z,	0x1C,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 479 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pause",	onebyte_prefix_insn,	1,	SUF_Z,	0xF3,	0x90,	0,	0,	CPU_P4,	0,	0},
#line 779 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaddps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x58,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 590 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"popf",	onebyte_insn,	1,	SUF_Z,	0x9D,	0x00,	0x40,	0,	0,	0,	0},
#line 1418 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vzeroall",	vzero_insn,	1,	SUF_Z,	0xC4,	0,	0,	0,	CPU_AVX,	0,	0},
#line 1436 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xcryptofb",	padlock_insn,	1,	SUF_Z,	0xE8,	0xF3,	0xA7,	0,	CPU_PadLock,	0,	0},
#line 258 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fprem1",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF5,	0,	0,	CPU_286,	CPU_FPU,	0},
#line 701 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setna",	setcc_insn,	1,	SUF_Z,	0x06,	0,	0,	0,	CPU_386,	0,	0},
#line 1207 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomltd",	vpcom_insn,	1,	SUF_Z,	0xCE,	0x00,	0,	0,	CPU_XOP,	0,	0},
#line 708 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnge",	setcc_insn,	1,	SUF_Z,	0x0C,	0,	0,	0,	CPU_386,	0,	0},
#line 299 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"idiv",	div_insn,	8,	SUF_Z,	0x07,	0,	0,	0,	0,	0,	0},
#line 426 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movq2dq",	movq2dq_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_SSE2,	0,	0},
#line 188 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"emms",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x77,	0,	0,	CPU_MMX,	0,	0},
#line 727 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"shrd",	shlrd_insn,	9,	SUF_Z,	0xAC,	0,	0,	0,	CPU_386,	0,	0},
#line 217 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fdivr",	farith_insn,	7,	SUF_Z,	0xF0,	0xF8,	0x07,	0,	CPU_FPU,	0,	0},
#line 853 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmplt_oqss",	ssecmp_32_insn,	4,	SUF_Z,	0x11,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1437 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xend",	tsx_0x0F_0x01_insn,	1,	SUF_Z,	0xD5,	0,	0,	0,	CPU_TSX,	0,	0},
#line 229 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fincstp",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xF7,	0,	0,	CPU_FPU,	0,	0},
#line 72 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cli",	onebyte_insn,	1,	SUF_Z,	0xFA,	0,	0,	0,	0,	0,	0},
#line 1229 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomnew",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 930 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpunordpd",	ssecmp_128_insn,	3,	SUF_Z,	0x03,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 621 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubd",	mmxsse2_insn,	2,	SUF_Z,	0xFA,	0,	0,	0,	CPU_MMX,	0,	0},
#line 170 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvttpd2dq",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0xE6,	0,	0,	CPU_SSE2,	0,	0},
#line 300 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"imul",	imul_insn,	19,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 1190 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgtb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x02,	0,	0,	CPU_XOP,	0,	0},
#line 957 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vdivss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5E,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1186 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgeud",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x03,	0,	0,	CPU_XOP,	0,	0},
#line 1109 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmsave",	svm_rax_insn,	2,	SUF_Z,	0xDB,	0,	0,	0,	CPU_SVM,	0,	0},
#line 153 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"crc32",	crc32_insn,	5,	SUF_Z,	0,	0,	0,	0,	CPU_386,	CPU_SSE42,	0},
#line 1260 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddbd",	vphaddsub_insn,	1,	SUF_Z,	0xC2,	0,	0,	0,	CPU_XOP,	0,	0},
#line 46 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blendpd",	sse4imm_insn,	2,	SUF_Z,	0x0D,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 633 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"punpckhqdq",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x6D,	0,	0,	CPU_SSE2,	0,	0},
#line 1042 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsubps",	fma_128_256_insn,	4,	SUF_Z,	0x7C,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 1074 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vminss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 187 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"dpps",	sse4imm_insn,	2,	SUF_Z,	0x40,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 645 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pushfq",	onebyte_insn,	1,	SUF_Z,	0x9C,	0x40,	0x40,	ONLY_64,	0,	0,	0},
#line 27 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aesdec",	aes_insn,	2,	SUF_Z,	0x38,	0xDE,	0,	0,	CPU_AVX,	0,	0},
#line 334 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jmp",	jmp_insn,	31,	SUF_Z,	0,	0,	0,	0,	0,	0,	0},
#line 1367 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsrlq",	vpshift_insn,	8,	SUF_Z,	0xD3,	0x73,	0x02,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 906 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpord_spd",	ssecmp_128_insn,	3,	SUF_Z,	0x17,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1192 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgtq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x02,	0,	0,	CPU_XOP,	0,	0},
#line 870 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x04,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1173 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomeqw",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x04,	0,	0,	CPU_XOP,	0,	0},
#line 980 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddss",	fma_128_m32_insn,	3,	SUF_Z,	0x6A,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 197 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fbstp",	fbldstp_insn,	1,	SUF_Z,	0x06,	0,	0,	0,	CPU_FPU,	0,	0},
#line 1006 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubadd231ps",	vfma_ps_insn,	2,	SUF_Z,	0xB7,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 610 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pslld",	pshift_insn,	4,	SUF_Z,	0xF2,	0x72,	0x06,	0,	CPU_MMX,	0,	0},
#line 1336 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vprotb",	vprot_insn,	3,	SUF_Z,	0x00,	0,	0,	0,	CPU_XOP,	0,	0},
#line 116 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpltsd",	ssecmp_64_insn,	4,	SUF_Z,	0x01,	0xF2,	0,	0,	CPU_SSE2,	0,	0},
#line 754 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"subps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x5C,	0,	0,	CPU_SSE,	0,	0},
#line 1262 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddbw",	vphaddsub_insn,	1,	SUF_Z,	0xC1,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1062 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmaskmovdqu",	maskmovdqu_insn,	1,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1056 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vhsubps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0xF2,	0x7D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 195 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"faddp",	farithp_insn,	3,	SUF_Z,	0xC0,	0,	0,	0,	CPU_FPU,	0,	0},
#line 973 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd231pd",	vfma_pd_insn,	2,	SUF_Z,	0xB8,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1026 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmaddps",	fma_128_256_insn,	4,	SUF_Z,	0x78,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 602 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pshufb",	ssse3_insn,	5,	SUF_Z,	0x00,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 1030 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub132ps",	vfma_ps_insn,	2,	SUF_Z,	0x9E,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1168 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomeqq",	vpcom_insn,	1,	SUF_Z,	0xCF,	0x04,	0,	0,	CPU_XOP,	0,	0},
#line 384 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lss",	lfgss_insn,	3,	SUF_Z,	0xB2,	0,	0,	0,	CPU_386,	0,	0},
#line 1235 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomtrueud",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x07,	0,	0,	CPU_XOP,	0,	0},
#line 31 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aesimc",	aesimc_insn,	1,	SUF_Z,	0x38,	0xDB,	0,	0,	CPU_AES,	0,	0},
#line 1147 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpclmulhqlqdq",	pclmulqdq_fixed_insn,	2,	SUF_Z,	0x01,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 792 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vandpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x54,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 615 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psraw",	pshift_insn,	4,	SUF_Z,	0xE1,	0x71,	0x04,	0,	CPU_MMX,	0,	0},
#line 516 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfcmpgt",	now3d_insn,	1,	SUF_Z,	0xA0,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 327 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jcxz",	jcxz_insn,	2,	SUF_Z,	0x10,	0,	0,	0,	0,	0,	0},
#line 1133 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpaddw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xFD,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1361 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsllw",	vpshift_insn,	8,	SUF_Z,	0xF1,	0x71,	0x06,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1210 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomltud",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x00,	0,	0,	CPU_XOP,	0,	0},
#line 341 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jng",	jcc_insn,	9,	SUF_Z,	0x0E,	0,	0,	0,	0,	0,	0},
#line 315 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"invlpga",	invlpga_insn,	2,	SUF_Z,	0,	0,	0,	0,	CPU_SVM,	0,	0},
#line 1148 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpclmullqhqdq",	pclmulqdq_fixed_insn,	2,	SUF_Z,	0x10,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1209 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomltub",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x00,	0,	0,	CPU_XOP,	0,	0},
#line 110 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmplepd",	ssecmp_128_insn,	3,	SUF_Z,	0x02,	0x66,	0,	0,	CPU_SSE,	0,	0},
#line 1177 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomfalseub",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x06,	0,	0,	CPU_XOP,	0,	0},
#line 457 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"outsb",	onebyte_insn,	1,	SUF_Z,	0x6E,	0x00,	0,	0,	0,	0,	0},
#line 1103 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmpsadbw",	sse4imm_256avx2_insn,	4,	SUF_Z,	0x42,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1241 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomuq",	vpcom_imm_insn,	1,	SUF_Z,	0xEF,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1330 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmulhw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xE5,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 684 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sar",	shift_insn,	16,	SUF_Z,	0x07,	0,	0,	0,	0,	0,	0},
#line 168 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtss2sd",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5A,	0,	0,	CPU_SSE2,	0,	0},
#line 662 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"repne",	NULL,	X86_LOCKREP>>8,	0xF2,	0,	0,	0,	0,	0,	0,	0},
#line 1292 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacsswd",	vpma_insn,	1,	SUF_Z,	0x86,	0,	0,	0,	CPU_XOP,	0,	0},
#line 787 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaesenclast",	aes_insn,	2,	SUF_Z,	0x38,	0xDD,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 574 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmulhrw",	now3d_insn,	1,	SUF_Z,	0xB7,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 908 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpord_ssd",	ssecmp_64_insn,	4,	SUF_Z,	0x17,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 333 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jle",	jcc_insn,	9,	SUF_Z,	0x0E,	0,	0,	0,	0,	0,	0},
#line 601 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psadbw",	mmxsse2_insn,	2,	SUF_Z,	0xF6,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 1297 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmadcswd",	vpma_insn,	1,	SUF_Z,	0xB6,	0,	0,	0,	CPU_XOP,	0,	0},
#line 373 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lock",	NULL,	X86_LOCKREP>>8,	0xF0,	0,	0,	0,	0,	0,	0,	0},
#line 912 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpordsd",	ssecmp_64_insn,	4,	SUF_Z,	0x07,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 606 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pshufw",	pshufw_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 948 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtss2sd",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5A,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 383 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lsl",	larlsl_insn,	6,	SUF_Z,	0x03,	0,	0,	0,	CPU_286,	CPU_Prot,	0},
#line 555 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pminub",	mmxsse2_insn,	2,	SUF_Z,	0xDA,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 682 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sal",	shift_insn,	16,	SUF_Z,	0x04,	0,	0,	0,	0,	0,	0},
#line 1313 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpminuw",	ssse3_insn,	5,	SUF_Z,	0x3A,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 447 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"neg",	f6_insn,	4,	SUF_Z,	0x03,	0,	0,	0,	0,	0,	0},
#line 1145 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpbroadcastw",	vpbroadcastw_avx2_insn,	4,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 756 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"subss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x5C,	0,	0,	CPU_SSE,	0,	0},
#line 74 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmc",	onebyte_insn,	1,	SUF_Z,	0xF5,	0,	0,	0,	0,	0,	0},
#line 1204 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomleuw",	vpcom_insn,	1,	SUF_Z,	0xED,	0x01,	0,	0,	CPU_XOP,	0,	0},
#line 557 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pminuw",	sse4_insn,	2,	SUF_Z,	0x3A,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 107 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpeqps",	ssecmp_128_insn,	3,	SUF_Z,	0x00,	0,	0,	0,	CPU_SSE,	0,	0},
#line 624 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubsiw",	cyrixmmx_insn,	1,	SUF_Z,	0x55,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 1179 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomfalseuq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x06,	0,	0,	CPU_XOP,	0,	0},
#line 880 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngesd",	ssecmp_64_insn,	4,	SUF_Z,	0x09,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 522 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfrcp",	now3d_insn,	1,	SUF_Z,	0x96,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1252 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpextrb",	pextrb_insn,	3,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 324 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jb",	jcc_insn,	9,	SUF_Z,	0x02,	0,	0,	0,	0,	0,	0},
#line 24 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"addss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x58,	0,	0,	CPU_SSE,	0,	0},
#line 866 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_uspd",	ssecmp_128_insn,	3,	SUF_Z,	0x14,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1065 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmaxpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x5F,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 297 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"hsubps",	xmm_xmm128_insn,	2,	SUF_Z,	0xF2,	0x7D,	0,	0,	CPU_SSE3,	0,	0},
#line 1151 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmov",	vpcmov_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1095 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovntps",	movnt_insn,	2,	SUF_Z,	0x00,	0x2B,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 800 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vbroadcastsd",	vbroadcastsd_insn,	2,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 861 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_oqss",	ssecmp_32_insn,	4,	SUF_Z,	0x0C,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 529 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"phaddd",	ssse3_insn,	5,	SUF_Z,	0x02,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 1348 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshlw",	amd_vpshift_insn,	2,	SUF_Z,	0x95,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1392 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vroundps",	avx_sse4imm_insn,	3,	SUF_Z,	0x08,	0,	0,	ONLY_AVX,	CPU_SSE41,	0,	0},
#line 1415 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vunpcklps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x14,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 872 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x04,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 868 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_ussd",	ssecmp_64_insn,	4,	SUF_Z,	0x14,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 38 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"andps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x54,	0,	0,	CPU_SSE,	0,	0},
#line 1350 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshufd",	xmm_xmm128_imm_256avx2_insn,	2,	SUF_Z,	0x66,	0x70,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 770 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ucomiss",	xmm_xmm32_insn,	4,	SUF_Z,	0x00,	0x2E,	0,	0,	CPU_SSE,	0,	0},
#line 1248 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpermilps",	vpermil_insn,	4,	SUF_Z,	0x04,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 728 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"shrx",	vex_gpr_reg_rm_nds_0F_insn,	2,	SUF_Z,	0xF2,	0x38,	0xF7,	ONLY_AVX,	CPU_BMI2,	0,	0},
#line 1289 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacssdd",	vpma_insn,	1,	SUF_Z,	0x8E,	0,	0,	0,	CPU_XOP,	0,	0},
#line 696 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sete",	setcc_insn,	1,	SUF_Z,	0x04,	0,	0,	0,	CPU_386,	0,	0},
#line 567 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovzxbw",	sse4m64_insn,	4,	SUF_Z,	0x30,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 480 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paveb",	cyrixmmx_insn,	1,	SUF_Z,	0x50,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 986 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsub231ps",	vfma_ps_insn,	2,	SUF_Z,	0xB6,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1211 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomltuq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x00,	0,	0,	CPU_XOP,	0,	0},
#line 32 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aeskeygenassist",	aes_imm_insn,	1,	SUF_Z,	0x3A,	0xDF,	0,	0,	CPU_AES,	0,	0},
#line 432 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movss",	movss_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_SSE,	0,	0},
#line 605 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pshuflw",	xmm_xmm128_imm_insn,	1,	SUF_Z,	0xF2,	0x70,	0,	0,	CPU_SSE2,	0,	0},
#line 53 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blsmsk",	vex_gpr_ndd_rm_0F38_regext_insn,	2,	SUF_Z,	0x00,	0xF3,	0x02,	ONLY_AVX,	CPU_BMI1,	0,	0},
#line 1275 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphminposuw",	avx_ssse3_2op_insn,	1,	SUF_Z,	0x41,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 363 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"les",	ldes_insn,	2,	SUF_Z,	0xC4,	0,	0,	NOT_64,	0,	0,	0},
#line 409 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movhlps",	movhllhps_insn,	2,	SUF_Z,	0x12,	0,	0,	0,	CPU_SSE,	0,	0},
#line 70 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"clflush",	clflush_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_P3,	0,	0},
#line 270 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fstenv",	twobytemem_insn,	1,	SUF_Z,	0x06,	0x9B,	0xD9,	0,	CPU_FPU,	0,	0},
#line 1251 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpermq",	vperm_imm_avx2_insn,	1,	SUF_Z,	0x00,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 128 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpnltsd",	ssecmp_64_insn,	4,	SUF_Z,	0x05,	0xF2,	0,	0,	CPU_SSE2,	0,	0},
#line 1283 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpinsrd",	pinsrd_insn,	2,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 287 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fxrstor",	twobytemem_insn,	1,	SUF_Z,	0x01,	0x0F,	0xAE,	0,	CPU_686,	CPU_FPU,	0},
#line 1265 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddsw",	ssse3_insn,	5,	SUF_Z,	0x03,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1258 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpgatherqd",	gather_32x_32y_128_insn,	2,	SUF_Z,	0x91,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 1247 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpermilpd",	vpermil_insn,	4,	SUF_Z,	0x05,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 794 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vblendpd",	sse4imm_256_insn,	4,	SUF_Z,	0x0D,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1379 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vptest",	sse4_insn,	2,	SUF_Z,	0x17,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 317 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"invvpid",	eptvpid_insn,	2,	SUF_Z,	0x01,	0,	0,	0,	CPU_386,	CPU_EPTVPID,	0},
#line 983 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsub213pd",	vfma_pd_insn,	2,	SUF_Z,	0xA6,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 603 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pshufd",	xmm_xmm128_imm_insn,	1,	SUF_Z,	0x66,	0x70,	0,	0,	CPU_SSE2,	0,	0},
#line 253 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fnstcw",	fldnstcw_insn,	1,	SUF_Z,	0x07,	0,	0,	0,	CPU_FPU,	0,	0},
#line 657 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rdshr",	rdwrshr_insn,	1,	SUF_Z,	0x00,	0,	0,	0,	CPU_686,	CPU_Cyrix,	CPU_SMM},
#line 617 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psrldq",	pslrldq_insn,	4,	SUF_Z,	0x03,	0,	0,	0,	CPU_SSE2,	0,	0},
#line 489 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pclmullqlqdq",	pclmulqdq_fixed_insn,	2,	SUF_Z,	0x00,	0,	0,	0,	CPU_AVX,	0,	0},
#line 177 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cwde",	onebyte_insn,	1,	SUF_Z,	0x98,	0x20,	0,	0,	CPU_386,	0,	0},
#line 767 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"tzcnt",	cnt_insn,	3,	SUF_Z,	0xBC,	0,	0,	0,	CPU_BMI1,	0,	0},
#line 279 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fucom",	fcom2_insn,	2,	SUF_Z,	0xDD,	0xE0,	0,	0,	CPU_286,	CPU_FPU,	0},
#line 1236 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomtrueuq",	vpcom_insn,	1,	SUF_Z,	0xEF,	0x07,	0,	0,	CPU_XOP,	0,	0},
#line 1369 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsrlvq",	vpshiftv_vexw1_avx2_insn,	2,	SUF_Z,	0x45,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 393 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mfence",	threebyte_insn,	1,	SUF_Z,	0x0F,	0xAE,	0xF0,	0,	CPU_P3,	0,	0},
#line 971 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd213sd",	vfma_sd_insn,	2,	SUF_Z,	0xA9,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1282 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpinsrb",	pinsrb_insn,	4,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 412 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movlhps",	movhllhps_insn,	2,	SUF_Z,	0x16,	0,	0,	0,	CPU_SSE,	0,	0},
#line 149 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"comisd",	xmm_xmm64_insn,	4,	SUF_Z,	0x66,	0x2F,	0,	0,	CPU_SSE2,	0,	0},
#line 504 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pdistib",	cyrixmmx_insn,	1,	SUF_Z,	0x54,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 677 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rsm",	twobyte_insn,	1,	SUF_Z,	0x0F,	0xAA,	0,	0,	CPU_586,	CPU_SMM,	0},
#line 704 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnbe",	setcc_insn,	1,	SUF_Z,	0x07,	0,	0,	0,	CPU_386,	0,	0},
#line 761 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"syscall",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x05,	0,	0,	CPU_686,	CPU_AMD,	0},
#line 1169 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomequb",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x04,	0,	0,	CPU_XOP,	0,	0},
#line 707 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setng",	setcc_insn,	1,	SUF_Z,	0x0E,	0,	0,	0,	CPU_386,	0,	0},
#line 885 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngt_uqss",	ssecmp_32_insn,	4,	SUF_Z,	0x1A,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 325 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jbe",	jcc_insn,	9,	SUF_Z,	0x06,	0,	0,	0,	0,	0,	0},
#line 1153 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpeqd",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x76,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 101 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovpe",	cmovcc_insn,	3,	SUF_Z,	0x0A,	0,	0,	0,	CPU_686,	0,	0},
#line 1364 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsraw",	vpshift_insn,	8,	SUF_Z,	0xE1,	0x71,	0x04,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 935 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcomiss",	avx_xmm_xmm32_insn,	2,	SUF_Z,	0x00,	0x2F,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 78 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovbe",	cmovcc_insn,	3,	SUF_Z,	0x06,	0,	0,	0,	CPU_686,	0,	0},
#line 977 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddpd",	fma_128_256_insn,	4,	SUF_Z,	0x69,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 1010 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubps",	fma_128_256_insn,	4,	SUF_Z,	0x6C,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 219 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"femms",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x0E,	0,	0,	CPU_3DNow,	0,	0},
#line 112 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmplesd",	ssecmp_64_insn,	4,	SUF_Z,	0x02,	0xF2,	0,	0,	CPU_SSE2,	0,	0},
#line 387 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"maskmovdqu",	maskmovdqu_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_SSE2,	0,	0},
#line 596 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"prefetchnta",	twobytemem_insn,	1,	SUF_Z,	0x00,	0x0F,	0x18,	0,	CPU_P3,	0,	0},
#line 441 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mulpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x59,	0,	0,	CPU_SSE2,	0,	0},
#line 143 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpunordsd",	ssecmp_64_insn,	4,	SUF_Z,	0x03,	0xF2,	0,	0,	CPU_SSE2,	0,	0},
#line 890 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnle_uqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x16,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 232 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fistp",	fildstp_insn,	4,	SUF_Z,	0x03,	0x02,	0x07,	0,	CPU_FPU,	0,	0},
#line 656 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rdrand",	rdrand_insn,	3,	SUF_Z,	0,	0,	0,	0,	CPU_RDRAND,	0,	0},
#line 531 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"phaddw",	ssse3_insn,	5,	SUF_Z,	0x01,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 1152 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpeqb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x74,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1043 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsubsd",	fma_128_m64_insn,	3,	SUF_Z,	0x7F,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 144 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpunordss",	ssecmp_32_insn,	4,	SUF_Z,	0x03,	0xF3,	0,	0,	CPU_SSE,	0,	0},
#line 136 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpsb",	onebyte_insn,	1,	SUF_Z,	0xA6,	0x00,	0,	0,	0,	0,	0},
#line 1131 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpaddusb",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xDC,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 649 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rcpps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x53,	0,	0,	CPU_SSE,	0,	0},
#line 490 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pclmulqdq",	pclmulqdq_insn,	2,	SUF_Z,	0x3A,	0x44,	0,	0,	CPU_AVX,	0,	0},
#line 1144 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpbroadcastq",	vpbroadcastq_avx2_insn,	4,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 134 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmppd",	xmm_xmm128_imm_insn,	1,	SUF_Z,	0x66,	0xC2,	0,	0,	CPU_SSE2,	0,	0},
#line 999 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub231sd",	vfma_sd_insn,	2,	SUF_Z,	0xBB,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 1269 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddudq",	vphaddsub_insn,	1,	SUF_Z,	0xDB,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1267 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddubq",	vphaddsub_insn,	1,	SUF_Z,	0xD3,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1220 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomnequb",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 987 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsubpd",	fma_128_256_insn,	4,	SUF_Z,	0x5D,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 579 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmullw",	mmxsse2_insn,	2,	SUF_Z,	0xD5,	0,	0,	0,	CPU_MMX,	0,	0},
#line 691 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"seta",	setcc_insn,	1,	SUF_Z,	0x07,	0,	0,	0,	CPU_386,	0,	0},
#line 575 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmulhrwc",	cyrixmmx_insn,	1,	SUF_Z,	0x59,	0,	0,	0,	CPU_Cyrix,	CPU_MMX,	0},
#line 1093 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovntdqa",	movntdqa_insn,	2,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 824 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpfalsesd",	ssecmp_64_insn,	4,	SUF_Z,	0x0B,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 422 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movntq",	movntq_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_SSE,	0,	0},
#line 532 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"phminposuw",	sse4_insn,	2,	SUF_Z,	0x41,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 813 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_usss",	ssecmp_32_insn,	4,	SUF_Z,	0x18,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 234 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fisub",	fiarith_insn,	2,	SUF_Z,	0x04,	0xDA,	0,	0,	CPU_FPU,	0,	0},
#line 1412 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vunpckhpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x15,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 695 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setc",	setcc_insn,	1,	SUF_Z,	0x02,	0,	0,	0,	CPU_386,	0,	0},
#line 104 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovz",	cmovcc_insn,	3,	SUF_Z,	0x04,	0,	0,	0,	CPU_686,	0,	0},
#line 791 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vandnps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x55,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 262 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsave",	twobytemem_insn,	1,	SUF_Z,	0x06,	0x9B,	0xDD,	0,	CPU_FPU,	0,	0},
#line 693 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setb",	setcc_insn,	1,	SUF_Z,	0x02,	0,	0,	0,	CPU_386,	0,	0},
#line 13 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"a32",	NULL,	X86_ADDRSIZE>>8,	0x20,	0,	0,	0,	0,	0,	0,	0},
#line 1116 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmxon",	vmxthreebytemem_insn,	1,	SUF_Z,	0xF3,	0,	0,	0,	CPU_P4,	0,	0},
#line 506 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pextrb",	pextrb_insn,	3,	SUF_Z,	0,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 901 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnlt_uqss",	ssecmp_32_insn,	4,	SUF_Z,	0x15,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1059 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vinsertps",	insertps_insn,	4,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 178 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"daa",	onebyte_insn,	1,	SUF_Z,	0x27,	0,	0,	NOT_64,	0,	0,	0},
#line 391 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"maxsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5F,	0,	0,	CPU_SSE2,	0,	0},
#line 1295 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacsww",	vpma_insn,	1,	SUF_Z,	0x95,	0,	0,	0,	CPU_XOP,	0,	0},
#line 535 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"phsubw",	ssse3_insn,	5,	SUF_Z,	0x05,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 310 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"int3",	onebyte_insn,	1,	SUF_Z,	0xCC,	0,	0,	0,	0,	0,	0},
#line 936 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtdq2pd",	avx_cvt_xmm64_insn,	3,	SUF_Z,	0xF3,	0xE6,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 235 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fisubr",	fiarith_insn,	2,	SUF_Z,	0x05,	0xDA,	0,	0,	CPU_FPU,	0,	0},
#line 995 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsub213sd",	vfma_sd_insn,	2,	SUF_Z,	0xAB,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 588 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"popaw",	onebyte_insn,	1,	SUF_Z,	0x61,	0x10,	0,	NOT_64,	CPU_186,	0,	0},
#line 876 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnge_uqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x19,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 608 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psignd",	ssse3_insn,	5,	SUF_Z,	0x0A,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 1185 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomgeub",	vpcom_insn,	1,	SUF_Z,	0xEC,	0x03,	0,	0,	CPU_XOP,	0,	0},
#line 139 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpss",	xmm_xmm32_imm_insn,	4,	SUF_Z,	0xF3,	0xC2,	0,	0,	CPU_SSE,	0,	0},
#line 1286 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmacsdd",	vpma_insn,	1,	SUF_Z,	0x9E,	0,	0,	0,	CPU_XOP,	0,	0},
#line 672 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"roundps",	sse4imm_insn,	2,	SUF_Z,	0x08,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1202 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomleud",	vpcom_insn,	1,	SUF_Z,	0xEE,	0x01,	0,	0,	CPU_XOP,	0,	0},
#line 146 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpxchg16b",	cmpxchg16b_insn,	1,	SUF_Z,	0,	0,	0,	ONLY_64,	0,	0,	0},
#line 435 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movsxd",	movsxd_insn,	1,	SUF_Z,	0,	0,	0,	ONLY_64,	0,	0,	0},
#line 1279 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphsubsw",	ssse3_insn,	5,	SUF_Z,	0x07,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1359 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpsllvd",	vpshiftv_vexw0_avx2_insn,	2,	SUF_Z,	0x47,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 342 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnge",	jcc_insn,	9,	SUF_Z,	0x0C,	0,	0,	0,	0,	0,	0},
#line 663 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"repnz",	NULL,	X86_LOCKREP>>8,	0xF2,	0,	0,	0,	0,	0,	0,	0},
#line 612 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psllq",	pshift_insn,	4,	SUF_Z,	0xF3,	0x73,	0x06,	0,	CPU_MMX,	0,	0},
#line 353 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jrcxz",	jcxz_insn,	2,	SUF_Z,	0x40,	0,	0,	ONLY_64,	0,	0,	0},
#line 1320 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovsxwq",	sse4m32_insn,	4,	SUF_Z,	0x24,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 907 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpord_sps",	ssecmp_128_insn,	3,	SUF_Z,	0x17,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1440 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xor",	arith_insn,	22,	SUF_Z,	0x30,	0x06,	0,	0,	0,	0,	0},
#line 1256 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpgatherdd",	gather_32x_32y_insn,	2,	SUF_Z,	0x90,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 93 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnl",	cmovcc_insn,	3,	SUF_Z,	0x0D,	0,	0,	0,	CPU_686,	0,	0},
#line 599 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"prefetcht2",	twobytemem_insn,	1,	SUF_Z,	0x03,	0x0F,	0x18,	0,	CPU_P3,	0,	0},
#line 1058 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vinserti128",	vinsertif128_insn,	1,	SUF_Z,	0x38,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 697 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setg",	setcc_insn,	1,	SUF_Z,	0x0F,	0,	0,	0,	CPU_386,	0,	0},
#line 631 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"punpckhbw",	mmxsse2_insn,	2,	SUF_Z,	0x68,	0,	0,	0,	CPU_MMX,	0,	0},
#line 246 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldz",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xEE,	0,	0,	CPU_FPU,	0,	0},
#line 1323 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovzxbw",	sse4m64_insn,	4,	SUF_Z,	0x30,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1301 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaskmovq",	vmaskmov_vexw1_avx2_insn,	4,	SUF_Z,	0x8C,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 975 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd231sd",	vfma_sd_insn,	2,	SUF_Z,	0xB9,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 48 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blendvpd",	sse4xmm0_insn,	2,	SUF_Z,	0x15,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 829 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpge_oqss",	ssecmp_32_insn,	4,	SUF_Z,	0x1D,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 869 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_usss",	ssecmp_32_insn,	4,	SUF_Z,	0x14,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1017 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmadd213pd",	vfma_pd_insn,	2,	SUF_Z,	0xAC,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 183 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"divps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x5E,	0,	0,	CPU_SSE,	0,	0},
#line 751 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"str",	str_insn,	4,	SUF_Z,	0,	0,	0,	0,	CPU_286,	CPU_Prot,	0},
#line 778 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vaddpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x58,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 777 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"unpcklps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x14,	0,	0,	CPU_SSE,	0,	0},
#line 916 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpsd",	cmpsd_insn,	5,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 931 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpunordps",	ssecmp_128_insn,	3,	SUF_Z,	0x03,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 165 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtsd2ss",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5A,	0,	0,	CPU_SSE2,	0,	0},
#line 121 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpneqss",	ssecmp_32_insn,	4,	SUF_Z,	0x04,	0xF3,	0,	0,	CPU_SSE,	0,	0},
#line 530 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"phaddsw",	ssse3_insn,	5,	SUF_Z,	0x03,	0,	0,	0,	CPU_SSSE3,	0,	0},
#line 1432 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xcryptcbc",	padlock_insn,	1,	SUF_Z,	0xD0,	0xF3,	0xA7,	0,	CPU_PadLock,	0,	0},
#line 1398 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vshufps",	xmm_xmm128_imm_256_insn,	3,	SUF_Z,	0x00,	0xC6,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 889 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpngtss",	ssecmp_32_insn,	4,	SUF_Z,	0x0A,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 33 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"and",	arith_insn,	22,	SUF_Z,	0x20,	0x04,	0,	0,	0,	0,	0},
#line 322 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ja",	jcc_insn,	9,	SUF_Z,	0x07,	0,	0,	0,	0,	0,	0},
#line 454 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"orpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x56,	0,	0,	CPU_SSE2,	0,	0},
#line 319 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"iretd",	onebyte_insn,	1,	SUF_Z,	0xCF,	0x20,	0,	0,	CPU_386,	0,	0},
#line 1311 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpminub",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xDA,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 152 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cqo",	onebyte_insn,	1,	SUF_Z,	0x99,	0x40,	0,	ONLY_64,	0,	0,	0},
#line 240 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldl2e",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xEA,	0,	0,	CPU_FPU,	0,	0},
#line 508 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pextrq",	pextrq_insn,	1,	SUF_Z,	0,	0,	0,	ONLY_64,	CPU_SSE41,	0,	0},
#line 498 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpgtd",	mmxsse2_insn,	2,	SUF_Z,	0x66,	0,	0,	0,	CPU_MMX,	0,	0},
#line 159 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtpi2pd",	cvt_xmm_mm_ss_insn,	1,	SUF_Z,	0x66,	0x2A,	0,	0,	CPU_SSE2,	0,	0},
#line 1303 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaxsd",	ssse3_insn,	5,	SUF_Z,	0x3D,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 797 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vblendvps",	avx_sse4xmm0_insn,	2,	SUF_Z,	0x4A,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 385 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ltr",	prot286_insn,	1,	SUF_Z,	0x03,	0x00,	0,	0,	CPU_286,	CPU_Priv,	CPU_Prot},
#line 1156 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpestri",	sse4pcmpstr_insn,	1,	SUF_Z,	0x61,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1338 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vprotq",	vprot_insn,	3,	SUF_Z,	0x03,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1161 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpgtw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x65,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 736 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"smintold",	twobyte_insn,	1,	SUF_Z,	0x0F,	0x7E,	0,	0,	CPU_486,	CPU_Cyrix,	CPU_Obs},
#line 362 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"leave",	onebyte_insn,	1,	SUF_Z,	0xC9,	0x00,	0x40,	0,	CPU_186,	0,	0},
#line 355 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jz",	jcc_insn,	9,	SUF_Z,	0x04,	0,	0,	0,	0,	0,	0},
#line 186 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"dppd",	sse4imm_insn,	2,	SUF_Z,	0x41,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 343 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jnl",	jcc_insn,	9,	SUF_Z,	0x0D,	0,	0,	0,	0,	0,	0},
#line 661 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"repe",	NULL,	X86_LOCKREP>>8,	0xF3,	0,	0,	0,	0,	0,	0,	0},
#line 1339 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vprotw",	vprot_insn,	3,	SUF_Z,	0x01,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1025 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmaddpd",	fma_128_256_insn,	4,	SUF_Z,	0x79,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 1008 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmsubaddps",	fma_128_256_insn,	4,	SUF_Z,	0x5E,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 147 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpxchg486",	cmpxchgxadd_insn,	4,	SUF_Z,	0xA6,	0,	0,	0,	CPU_486,	CPU_Undoc,	0},
#line 52 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blsic",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x01,	0x06,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 1238 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomtruew",	vpcom_insn,	1,	SUF_Z,	0xCD,	0x07,	0,	0,	CPU_XOP,	0,	0},
#line 517 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfmax",	now3d_insn,	1,	SUF_Z,	0xA4,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1066 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmaxps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x5F,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 929 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpunord_sss",	ssecmp_32_insn,	4,	SUF_Z,	0x13,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 816 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x00,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 482 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pavgusb",	now3d_insn,	1,	SUF_Z,	0xBF,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1310 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpminsw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xEA,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1080 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovd",	vmovd_insn,	2,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_386,	CPU_AVX,	0},
#line 862 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_ospd",	ssecmp_128_insn,	3,	SUF_Z,	0x1C,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 961 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"verw",	prot286_insn,	1,	SUF_Z,	0x05,	0x00,	0,	0,	CPU_286,	CPU_Prot,	0},
#line 1138 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpavgw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0xE3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 867 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpneq_usps",	ssecmp_128_insn,	3,	SUF_Z,	0x14,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 469 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"paddq",	mmxsse2_insn,	2,	SUF_Z,	0xD4,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1405 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vsubps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x5C,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 239 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fldenv",	onebytemem_insn,	1,	SUF_Z,	0x04,	0xD9,	0,	0,	CPU_FPU,	0,	0},
#line 620 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"psubb",	mmxsse2_insn,	2,	SUF_Z,	0xF8,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1284 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpinsrq",	pinsrq_insn,	2,	SUF_Z,	0xC0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 939 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtpd2ps",	avx_cvt_xmm128_insn,	2,	SUF_Z,	0x66,	0x5A,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 88 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovnbe",	cmovcc_insn,	3,	SUF_Z,	0x07,	0,	0,	0,	CPU_686,	0,	0},
#line 1086 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovhps",	movhlp_insn,	3,	SUF_Z,	0x00,	0x16,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 902 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnltpd",	ssecmp_128_insn,	3,	SUF_Z,	0x05,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 459 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"outsw",	onebyte_insn,	1,	SUF_Z,	0x6F,	0x10,	0,	0,	0,	0,	0},
#line 810 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpeq_uspd",	ssecmp_128_insn,	3,	SUF_Z,	0x18,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 679 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rsqrtss",	xmm_xmm32_insn,	4,	SUF_Z,	0xF3,	0x52,	0,	0,	CPU_SSE,	0,	0},
#line 565 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pmovzxbd",	sse4m32_insn,	4,	SUF_Z,	0x31,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 169 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvtss2si",	cvt_rx_xmm32_insn,	4,	SUF_Z,	0xF3,	0x2D,	0,	0,	CPU_386,	CPU_SSE,	0},
#line 1272 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddw",	ssse3_insn,	5,	SUF_Z,	0x01,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 726 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"shr",	shift_insn,	16,	SUF_Z,	0x05,	0,	0,	0,	0,	0,	0},
#line 949 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcvtss2si",	cvt_rx_xmm32_insn,	4,	SUF_Z,	0xF3,	0x2D,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1414 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vunpcklpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x14,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 403 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movbe",	movbe_insn,	6,	SUF_Z,	0,	0,	0,	0,	CPU_MOVBE,	0,	0},
#line 443 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mulsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x59,	0,	0,	CPU_SSE2,	0,	0},
#line 835 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpgt_oqps",	ssecmp_128_insn,	3,	SUF_Z,	0x1E,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 366 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lgdt",	twobytemem_insn,	1,	SUF_Z,	0x02,	0x0F,	0x01,	0,	CPU_286,	CPU_Priv,	0},
#line 1250 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpermps",	vperm_var_avx2_insn,	1,	SUF_Z,	0x16,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 676 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rsldt",	cyrixsmm_insn,	1,	SUF_Z,	0x7B,	0,	0,	0,	CPU_486,	CPU_Cyrix,	CPU_SMM},
#line 822 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpfalsepd",	ssecmp_128_insn,	3,	SUF_Z,	0x0B,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1427 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xacquire",	NULL,	X86_ACQREL>>8,	0xF2,	0,	0,	0,	0,	0,	0,	0},
#line 932 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpunordsd",	ssecmp_64_insn,	4,	SUF_Z,	0x03,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 926 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpunord_spd",	ssecmp_128_insn,	3,	SUF_Z,	0x13,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1155 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcmpeqw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x75,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 171 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvttpd2pi",	cvt_mm_xmm_insn,	1,	SUF_Z,	0x66,	0x2C,	0,	0,	CPU_SSE2,	0,	0},
#line 917 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpss",	xmm_xmm32_imm_insn,	4,	SUF_Z,	0xF3,	0xC2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 638 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"punpcklwd",	mmxsse2_insn,	2,	SUF_Z,	0x61,	0,	0,	0,	CPU_MMX,	0,	0},
#line 823 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpfalseps",	ssecmp_128_insn,	3,	SUF_Z,	0x0B,	0x00,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 747 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"stosb",	onebyte_insn,	1,	SUF_Z,	0xAA,	0x00,	0,	0,	0,	0,	0},
#line 15 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"aaa",	onebyte_insn,	1,	SUF_Z,	0x37,	0,	0,	NOT_64,	0,	0,	0},
#line 709 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setnl",	setcc_insn,	1,	SUF_Z,	0x0D,	0,	0,	0,	CPU_386,	0,	0},
#line 220 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"ffree",	ffree_insn,	1,	SUF_Z,	0xDD,	0,	0,	0,	CPU_FPU,	0,	0},
#line 248 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fmulp",	farithp_insn,	3,	SUF_Z,	0xC8,	0,	0,	0,	CPU_FPU,	0,	0},
#line 282 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fucomp",	fcom2_insn,	2,	SUF_Z,	0xDD,	0xE8,	0,	0,	CPU_286,	CPU_FPU,	0},
#line 47 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blendps",	sse4imm_insn,	2,	SUF_Z,	0x0C,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 321 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"iretw",	onebyte_insn,	1,	SUF_Z,	0xCF,	0x10,	0,	0,	0,	0,	0},
#line 1446 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"xsaveopt",	twobytemem_insn,	1,	SUF_Z,	0x06,	0x0F,	0xAE,	0,	CPU_XSAVEOPT,	0,	0},
#line 377 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"lodsw",	onebyte_insn,	1,	SUF_Z,	0xAD,	0x10,	0,	0,	0,	0,	0},
#line 99 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmovo",	cmovcc_insn,	3,	SUF_Z,	0x00,	0,	0,	0,	CPU_686,	0,	0},
#line 1317 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmovsxbw",	sse4m64_insn,	4,	SUF_Z,	0x20,	0xC0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 71 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"clgi",	threebyte_insn,	1,	SUF_Z,	0x0F,	0x01,	0xDD,	0,	CPU_SVM,	0,	0},
#line 1410 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vucomisd",	avx_xmm_xmm64_insn,	2,	SUF_Z,	0x66,	0x2E,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 845 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmple_oqss",	ssecmp_32_insn,	4,	SUF_Z,	0x12,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 976 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmadd231ss",	vfma_ss_insn,	2,	SUF_Z,	0xB9,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 653 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"rdgsbase",	fs_gs_base_insn,	2,	SUF_Z,	0x01,	0,	0,	ONLY_64,	CPU_FSGSBASE,	0,	0},
#line 1198 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomleb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x01,	0,	0,	CPU_XOP,	0,	0},
#line 924 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmptruesd",	ssecmp_64_insn,	4,	SUF_Z,	0x0F,	0xF2,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1165 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomd",	vpcom_imm_insn,	1,	SUF_Z,	0xCE,	0,	0,	0,	CPU_XOP,	0,	0},
#line 717 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"setpe",	setcc_insn,	1,	SUF_Z,	0x0A,	0,	0,	0,	CPU_386,	0,	0},
#line 483 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pavgw",	mmxsse2_insn,	2,	SUF_Z,	0xE3,	0,	0,	0,	CPU_MMX,	CPU_P3,	0},
#line 722 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sgdt",	twobytemem_insn,	1,	SUF_Z,	0x00,	0x0F,	0x01,	0,	CPU_286,	CPU_Priv,	0},
#line 264 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsetpm",	twobyte_insn,	1,	SUF_Z,	0xDB,	0xE4,	0,	0,	CPU_286,	CPU_FPU,	CPU_Obs},
#line 721 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sfence",	threebyte_insn,	1,	SUF_Z,	0x0F,	0xAE,	0xF8,	0,	CPU_P3,	0,	0},
#line 439 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mpsadbw",	sse4imm_insn,	2,	SUF_Z,	0x42,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1380 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpunpckhbw",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x68,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 894 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpnlepd",	ssecmp_128_insn,	3,	SUF_Z,	0x06,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 793 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vandps",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x00,	0x54,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1164 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomb",	vpcom_imm_insn,	1,	SUF_Z,	0xCC,	0,	0,	0,	CPU_XOP,	0,	0},
#line 267 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fsqrt",	twobyte_insn,	1,	SUF_Z,	0xD9,	0xFA,	0,	0,	CPU_FPU,	0,	0},
#line 1300 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpmaskmovd",	vmaskmov_insn,	4,	SUF_Z,	0x8C,	0,	0,	ONLY_AVX,	CPU_AVX2,	0,	0},
#line 1081 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovddup",	vmovddup_insn,	3,	SUF_Z,	0xF2,	0x12,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 759 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"svts",	cyrixsmm_insn,	1,	SUF_Z,	0x7C,	0,	0,	0,	CPU_486,	CPU_Cyrix,	CPU_SMM},
#line 513 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pfadd",	now3d_insn,	1,	SUF_Z,	0x9E,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 1102 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovups",	movau_insn,	6,	SUF_Z,	0x00,	0x10,	0x01,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1214 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpcomneb",	vpcom_insn,	1,	SUF_Z,	0xCC,	0x05,	0,	0,	CPU_XOP,	0,	0},
#line 1083 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovdqu",	movau_insn,	6,	SUF_Z,	0xF3,	0x6F,	0x10,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 184 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"divsd",	xmm_xmm64_insn,	4,	SUF_Z,	0xF2,	0x5E,	0,	0,	CPU_SSE2,	0,	0},
#line 351 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jpe",	jcc_insn,	9,	SUF_Z,	0x0A,	0,	0,	0,	0,	0,	0},
#line 1381 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpunpckhdq",	xmm_xmm128_256avx2_insn,	4,	SUF_Z,	0x66,	0x6A,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 394 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"minpd",	xmm_xmm128_insn,	2,	SUF_Z,	0x66,	0x5D,	0,	0,	CPU_SSE2,	0,	0},
#line 378 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"loop",	loop_insn,	8,	SUF_Z,	0x02,	0,	0,	0,	0,	0,	0},
#line 492 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpeqd",	mmxsse2_insn,	2,	SUF_Z,	0x76,	0,	0,	0,	CPU_MMX,	0,	0},
#line 1244 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vperm2f128",	vperm2f128_insn,	1,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 499 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pcmpgtq",	sse4_insn,	2,	SUF_Z,	0x37,	0,	0,	0,	CPU_SSE41,	0,	0},
#line 1346 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vpshld",	amd_vpshift_insn,	2,	SUF_Z,	0x96,	0,	0,	0,	CPU_XOP,	0,	0},
#line 437 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movups",	movau_insn,	6,	SUF_Z,	0x00,	0x10,	0x01,	0,	CPU_SSE,	0,	0},
#line 406 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"movdq2q",	movdq2q_insn,	1,	SUF_Z,	0,	0,	0,	0,	CPU_SSE2,	0,	0},
#line 510 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"pf2id",	now3d_insn,	1,	SUF_Z,	0x1D,	0,	0,	0,	CPU_3DNow,	0,	0},
#line 174 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cvttsd2si",	cvt_rx_xmm64_insn,	4,	SUF_Z,	0xF2,	0x2C,	0,	0,	CPU_SSE2,	0,	0},
#line 857 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmpltss",	ssecmp_32_insn,	4,	SUF_Z,	0x01,	0xF3,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 44 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"blcmsk",	xop_gpr_reg_rm_09_insn,	2,	SUF_Z,	0x02,	0x01,	0,	0,	CPU_386,	CPU_TBM,	0},
#line 1117 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vorpd",	xmm_xmm128_256_insn,	4,	SUF_Z,	0x66,	0x56,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 345 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"jno",	jcc_insn,	9,	SUF_Z,	0x01,	0,	0,	0,	0,	0,	0},
#line 1274 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vphaddwq",	vphaddsub_insn,	1,	SUF_Z,	0xC7,	0,	0,	0,	CPU_XOP,	0,	0},
#line 1044 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsubss",	fma_128_m32_insn,	3,	SUF_Z,	0x7E,	0,	0,	ONLY_AVX,	CPU_FMA4,	0,	0},
#line 108 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"cmpeqsd",	ssecmp_64_insn,	4,	SUF_Z,	0x00,	0xF2,	0,	0,	CPU_SSE2,	0,	0},
#line 1070 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmclear",	vmxthreebytemem_insn,	1,	SUF_Z,	0x66,	0,	0,	0,	CPU_P4,	0,	0},
#line 850 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vcmplt_oqpd",	ssecmp_128_insn,	3,	SUF_Z,	0x11,	0x66,	0xC0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 216 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fdivp",	farithp_insn,	3,	SUF_Z,	0xF8,	0,	0,	0,	CPU_FPU,	0,	0},
#line 739 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"sqrtps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x51,	0,	0,	CPU_SSE,	0,	0},
#line 442 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"mulps",	xmm_xmm128_insn,	2,	SUF_Z,	0x00,	0x59,	0,	0,	CPU_SSE,	0,	0},
#line 206 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"fcmovnu",	fcmovcc_insn,	1,	SUF_Z,	0xDB,	0xD8,	0,	0,	CPU_686,	CPU_FPU,	0},
#line 1096 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vmovq",	vmovq_insn,	5,	SUF_Z,	0,	0,	0,	ONLY_AVX,	CPU_AVX,	0,	0},
#line 1036 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfnmsub213ss",	vfma_ss_insn,	2,	SUF_Z,	0xAF,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0},
#line 985 "/home/lovewei/Project/yasm/new yasm/yasm/build/modules/x86insn_nasm.gperf"
    {"vfmaddsub231pd",	vfma_pd_insn,	2,	SUF_Z,	0xB6,	0,	0,	ONLY_AVX,	CPU_FMA,	0,	0}
  };
  static const unsigned short tab[] = {
    333,83,1338,0,733,665,281,1116,11,0,281,1140,1109,1312,864,0,
    0,665,0,1312,764,665,427,323,0,11,11,517,0,0,764,0,
    0,517,1140,665,323,630,323,1044,702,323,517,764,1140,665,0,197,
    1109,764,323,1044,0,702,1042,764,1530,333,508,764,281,823,1212,665,
    0,1312,323,1218,0,159,1109,909,1213,0,0,508,764,1042,0,11,
    1140,11,323,1042,1020,1140,1338,1312,395,823,824,630,1140,1213,83,333,
    864,11,0,1213,83,1295,0,506,1140,1140,764,517,323,0,517,824,
    1529,1189,1312,83,281,11,323,665,1212,281,427,1432,1095,323,1140,1044,
    574,605,605,11,864,0,517,1042,823,281,605,702,605,864,0,179,
    94,0,1432,0,630,323,11,0,1140,764,0,630,281,629,1095,0,
    1044,665,0,0,924,1379,1338,323,281,1213,83,1050,1140,702,528,764,
    864,427,665,924,0,1044,746,665,629,924,517,323,0,0,1095,764,
    629,293,1140,630,94,1399,764,11,1035,1218,0,1116,0,764,239,1044,
    323,1140,11,517,323,399,323,0,988,1432,427,1213,1142,1232,265,1312,
    580,1312,1042,399,0,506,0,1509,1530,702,1140,1020,824,567,1140,11,
    111,517,111,1000,1140,83,399,1140,1312,823,0,0,11,630,665,323,
    0,1140,506,764,83,829,629,1140,764,281,856,1530,145,1453,281,924,
    0,395,665,1383,1074,323,1185,764,528,721,764,665,508,1232,1042,281,
    1312,665,0,83,333,733,323,1020,1044,574,1042,1203,764,83,0,864,
    1165,1415,1236,446,11,688,83,506,427,605,336,1140,0,517,517,1140,
    1528,665,0,764,0,1095,517,0,348,1213,630,605,1312,1312,781,197,
    793,0,83,83,567,83,6,1279,679,83,508,629,1312,630,864,0,
    0,281,736,215,935,1020,351,889,600,1044,1232,1140,897,721,605,94,
    864,83,1432,864,0,1312,11,835,323,159,1481,0,0,665,1432,1165,
    889,517,764,829,764,669,988,525,1312,94,399,605,1007,0,1042,1044,
    1044,1109,1530,281,0,0,793,309,623,0,1213,764,1453,83,1140,935,
    1042,1529,0,684,288,891,358,0,1484,665,1312,897,0,1312,793,1140,
    1000,1203,762,702,1493,629,83,0,0,605,0,1140,846,333,517,0,
    0,1312,580,0,4,0,891,1109,83,702,974,1075,1529,0,199,1493,
    1179,1044,733,1203,814,1295,630,1095,478,1109,749,95,605,892,0,972,
    781,323,635,665,1091,794,753,2,1044,1091,1191,702,1212,988,884,864,
    764,824,874,89,324,0,764,0,1186,1118,1432,807,733,1140,1188,982,
  };

  const struct insnprefix_parse_data *ret;
  unsigned long rsl, val = phash_lookup(key, len, 0xbe1e08bbUL);
  rsl = ((val>>23)^tab[val&0x1ff]);
  if (rsl >= 1442) return NULL;
  ret = &pd[rsl];
  if (strcmp(key, ret->name) != 0) return NULL;
  return ret;
}

