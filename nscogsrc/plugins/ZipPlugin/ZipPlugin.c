/* Automatically generated by
	VMPluginCodeGenerator VMMaker.oscog-eem.105 uuid: 79234f80-ee6a-404c-9e5c-2134e3b76463
   from
	InflatePlugin VMMaker.oscog-eem.105 uuid: 79234f80-ee6a-404c-9e5c-2134e3b76463
 */
static char __buildInfo[] = "InflatePlugin VMMaker.oscog-eem.105 uuid: 79234f80-ee6a-404c-9e5c-2134e3b76463 " __DATE__ ;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif

#include "sqMemoryAccess.h"


/*** Constants ***/
#define MaxBits 16
#define StateNoMoreData 1


/*** Function Prototypes ***/
static VirtualMachine * getInterpreter(void);
EXPORT(const char*) getModuleName(void);
static sqInt halt(void);
static sqInt msg(char *s);
EXPORT(sqInt) primitiveInflateDecompressBlock(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
static sqInt zipDecodeValueFromsize(unsigned int *table, sqInt tableSize);
static sqInt zipDecompressBlock(void);
static sqInt zipNextBits(sqInt n);


/*** Variables ***/

#ifdef SQUEAK_BUILTIN_PLUGIN
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"ZipPlugin VMMaker.oscog-eem.105 (i)"
#else
	"ZipPlugin VMMaker.oscog-eem.105 (e)"
#endif
;
static sqInt zipBitBuf;
static sqInt zipBitPos;
static unsigned char* zipCollection;
static sqInt zipCollectionSize;
static unsigned int* zipDistTable;
static sqInt zipDistTableSize;
static unsigned int* zipLitTable;
static sqInt zipLitTableSize;
static sqInt zipPosition;
static sqInt zipReadLimit;
static unsigned char* zipSource;
static sqInt zipSourceLimit;
static sqInt zipSourcePos;
static sqInt zipState;



/*	Note: This is coded so that plugins can be run from Squeak. */

static VirtualMachine *
getInterpreter(void)
{
	return interpreterProxy;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}

static sqInt
halt(void)
{
	;
	return 0;
}

static sqInt
msg(char *s)
{
	fprintf(stderr, "\n%s: %s", moduleName, s);
	return 0;
}


/*	Primitive. Inflate a single block. */

EXPORT(sqInt)
primitiveInflateDecompressBlock(void)
{
    sqInt oop;
    sqInt rcvr;

	if (!((interpreterProxy->methodArgumentCount()) == 2)) {
		return interpreterProxy->primitiveFail();
	}
	oop = interpreterProxy->stackObjectValue(0);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(interpreterProxy->isWords(oop))) {
		return interpreterProxy->primitiveFail();
	}
	zipDistTable = interpreterProxy->firstIndexableField(oop);

	/* literal table */

	zipDistTableSize = interpreterProxy->slotSizeOf(oop);
	oop = interpreterProxy->stackObjectValue(1);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(interpreterProxy->isWords(oop))) {
		return interpreterProxy->primitiveFail();
	}
	zipLitTable = interpreterProxy->firstIndexableField(oop);

	/* Receiver (InflateStream) */

	zipLitTableSize = interpreterProxy->slotSizeOf(oop);
	rcvr = interpreterProxy->stackObjectValue(2);
	if (interpreterProxy->failed()) {
		return null;
	}
	if (!(interpreterProxy->isPointers(rcvr))) {
		return interpreterProxy->primitiveFail();
	}
	if ((interpreterProxy->slotSizeOf(rcvr)) < 9) {
		return interpreterProxy->primitiveFail();
	}
	zipReadLimit = interpreterProxy->fetchIntegerofObject(2, rcvr);
	zipState = interpreterProxy->fetchIntegerofObject(3, rcvr);
	zipBitBuf = interpreterProxy->fetchIntegerofObject(4, rcvr);
	zipBitPos = interpreterProxy->fetchIntegerofObject(5, rcvr);
	zipSourcePos = interpreterProxy->fetchIntegerofObject(7, rcvr);
	zipSourceLimit = interpreterProxy->fetchIntegerofObject(8, rcvr);
	if (interpreterProxy->failed()) {
		return null;
	}
	zipReadLimit -= 1;
	zipSourcePos -= 1;

	/* collection */

	zipSourceLimit -= 1;
	oop = interpreterProxy->fetchPointerofObject(0, rcvr);
	if ((oop & 1)) {
		return interpreterProxy->primitiveFail();
	}
	if (!(interpreterProxy->isBytes(oop))) {
		return interpreterProxy->primitiveFail();
	}
	zipCollection = interpreterProxy->firstIndexableField(oop);

	/* source */

	zipCollectionSize = interpreterProxy->byteSizeOf(oop);
	oop = interpreterProxy->fetchPointerofObject(6, rcvr);
	if ((oop & 1)) {
		return interpreterProxy->primitiveFail();
	}
	if (!(interpreterProxy->isBytes(oop))) {
		return interpreterProxy->primitiveFail();
	}

	/* do the primitive */

	zipSource = interpreterProxy->firstIndexableField(oop);
	zipDecompressBlock();
	if (!(interpreterProxy->failed())) {
		interpreterProxy->storeIntegerofObjectwithValue(2, rcvr, zipReadLimit + 1);
		interpreterProxy->storeIntegerofObjectwithValue(3, rcvr, zipState);
		interpreterProxy->storeIntegerofObjectwithValue(4, rcvr, zipBitBuf);
		interpreterProxy->storeIntegerofObjectwithValue(5, rcvr, zipBitPos);
		interpreterProxy->storeIntegerofObjectwithValue(7, rcvr, zipSourcePos + 1);
		interpreterProxy->pop(2);
	}
}


/*	Note: This is coded so that is can be run from Squeak. */

EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
    sqInt ok;

	interpreterProxy = anInterpreter;
	ok = interpreterProxy->majorVersion() == VM_PROXY_MAJOR;
	if (ok == 0) {
		return 0;
	}
	ok = interpreterProxy->minorVersion() >= VM_PROXY_MINOR;
	return ok;
}


/*	Decode the next value in the receiver using the given huffman table. */

static sqInt
zipDecodeValueFromsize(unsigned int *table, sqInt tableSize)
{
    sqInt bits;
    sqInt bits1;
    sqInt bitsNeeded;
    sqInt byte;
    sqInt index;
    sqInt tableIndex;
    sqInt value;


	/* Initial bits needed */

	bitsNeeded = ((usqInt) (table[0]) >> 24);
	if (bitsNeeded > MaxBits) {
		interpreterProxy->primitiveFail();
		return 0;
	}

	/* First real table */

	tableIndex = 2;
	while (1) {
		/* begin zipNextBits: */
		while (zipBitPos < bitsNeeded) {
			byte = zipSource[(zipSourcePos += 1)];
			zipBitBuf += byte << zipBitPos;
			zipBitPos += 8;
		}
		bits1 = zipBitBuf & ((1 << bitsNeeded) - 1);
		zipBitBuf = ((usqInt) zipBitBuf) >> bitsNeeded;
		zipBitPos -= bitsNeeded;
		bits = bits1;
		index = (tableIndex + bits) - 1;
		if (index >= tableSize) {
			interpreterProxy->primitiveFail();
			return 0;
		}

		/* Lookup entry in table */

		value = table[index];
		if ((value & 1056964608) == 0) {
			return value;
		}

		/* Table offset in low 16 bit */

		tableIndex = value & 65535;

		/* Additional bits in high 8 bit */

		bitsNeeded = (((usqInt) value >> 24)) & 255;
		if (bitsNeeded > MaxBits) {
			interpreterProxy->primitiveFail();
			return 0;
		}
	}
	return 0;
}

static sqInt
zipDecompressBlock(void)
{
    sqInt distance;
    sqInt dstPos;
    sqInt extra;
    sqInt i;
    sqInt length;
    sqInt max;
    sqInt oldBitPos;
    sqInt oldBits;
    sqInt oldPos;
    sqInt srcPos;
    sqInt value;

	max = zipCollectionSize - 1;
	while ((zipReadLimit < max)
	 && (zipSourcePos <= zipSourceLimit)) {

		/* Back up stuff if we're running out of space */

		oldBits = zipBitBuf;
		oldBitPos = zipBitPos;
		oldPos = zipSourcePos;
		value = zipDecodeValueFromsize(zipLitTable, zipLitTableSize);
		if (value < 256) {
			zipCollection[(zipReadLimit += 1)] = value;
		}
		else {
			if (value == 256) {

				/* length/distance or end of block */
				/* End of block */

				zipState = zipState & StateNoMoreData;
				return 0;
			}
			extra = (((usqInt) value >> 16)) - 1;
			length = value & 65535;
			if (extra > 0) {
				length += zipNextBits(extra);
			}
			value = zipDecodeValueFromsize(zipDistTable, zipDistTableSize);
			extra = ((usqInt) value >> 16);
			distance = value & 65535;
			if (extra > 0) {
				distance += zipNextBits(extra);
			}
			if ((zipReadLimit + length) >= max) {
				zipBitBuf = oldBits;
				zipBitPos = oldBitPos;
				zipSourcePos = oldPos;
				return 0;
			}
			dstPos = zipReadLimit;
			srcPos = zipReadLimit - distance;
			for (i = 1; i <= length; i += 1) {
				zipCollection[dstPos + i] = (zipCollection[srcPos + i]);
			}
			zipReadLimit += length;
		}
	}
}

static sqInt
zipNextBits(sqInt n)
{
    sqInt bits;
    sqInt byte;

	while (zipBitPos < n) {
		byte = zipSource[(zipSourcePos += 1)];
		zipBitBuf += byte << zipBitPos;
		zipBitPos += 8;
	}
	bits = zipBitBuf & ((1 << n) - 1);
	zipBitBuf = ((usqInt) zipBitBuf) >> n;
	zipBitPos -= n;
	return bits;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

void* ZipPlugin_exports[][3] = {
	{"ZipPlugin", "getModuleName", (void*)getModuleName},
	{"ZipPlugin", "primitiveInflateDecompressBlock", (void*)primitiveInflateDecompressBlock},
	{"ZipPlugin", "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#endif /* ifdef SQ_BUILTIN_PLUGIN */
