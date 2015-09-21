If(NOT CRYPTOPP_DIR)
  Set(CRYPTOPP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
EndIf()


Set(CRYPTOPP_SOURCES
3way.cpp
adhoc.cpp.proto
adler32.cpp
algebra.cpp
algparam.cpp
arc4.cpp
asn.cpp
authenc.cpp
base32.cpp
base64.cpp
basecode.cpp
bench2.cpp
bench.cpp
bfinit.cpp
blowfish.cpp
blumshub.cpp
camellia.cpp
cast.cpp
casts.cpp
cbcmac.cpp
ccm.cpp
channels.cpp
cmac.cpp
cpu.cpp
crc.cpp
cryptlib_bds.cpp
cryptlib.cpp
datatest.cpp
default.cpp
des.cpp
dessp.cpp
dh2.cpp
dh.cpp
dll.cpp
dlltest.cpp
dsa.cpp
eax.cpp
ec2n.cpp
eccrypto.cpp
ecp.cpp
elgamal.cpp
emsa2.cpp
eprecomp.cpp
esign.cpp
files.cpp
filters.cpp
fips140.cpp
fipsalgt.cpp
fipstest.cpp
gcm.cpp
gf2_32.cpp
gf256.cpp
gf2n.cpp
gfpcrypt.cpp
gost.cpp
gzip.cpp
hex.cpp
hmac.cpp
hrtimer.cpp
ida.cpp
idea.cpp
integer.cpp
iterhash.cpp
luc.cpp
mars.cpp
marss.cpp
md2.cpp
md4.cpp
md5.cpp
misc.cpp
modes.cpp
mqueue.cpp
mqv.cpp
nbtheory.cpp
network.cpp
oaep.cpp
osrng.cpp
panama.cpp
pch.cpp
pkcspad.cpp
polynomi.cpp
pssr.cpp
pubkey.cpp
queue.cpp
rabin.cpp
randpool.cpp
rc2.cpp
rc5.cpp
rc6.cpp
rdtables.cpp
regtest.cpp
rijndael.cpp
ripemd.cpp
rng.cpp
rsa.cpp
rw.cpp
safer.cpp
salsa.cpp
seal.cpp
seed.cpp
serpent.cpp
sha3.cpp
shacal2.cpp
sha.cpp
sharkbox.cpp
shark.cpp
simple.cpp
skipjack.cpp
socketft.cpp
sosemanuk.cpp
square.cpp
squaretb.cpp
stdcpp.h
strciphr.cpp
tea.cpp
test.cpp
tftables.cpp
tiger.cpp
tigertab.cpp
trdlocal.cpp
ttmac.cpp
twofish.cpp
vmac.cpp
wait.cpp
wake.cpp
whrlpool.cpp
winpipes.cpp
xtr.cpp
xtrcrypt.cpp
zdeflate.cpp
zinflate.cpp
zlib.cpp
 
)

Set(CRYPTOPP_HEADERS
)


Include_Directories(${CRYPTOPP_DIR})

if (LIBRARY_TYPE_SHARED)
add_library(CryptoPP SHARED ${CRYPTOPP_SOURCES})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(CryptoPP_Static STATIC ${CRYPTOPP_SOURCES})
#set_target_properties(CryptoPP_Static PROPERTIES OUTPUT_NAME "CryptoPP")
endif ()            



