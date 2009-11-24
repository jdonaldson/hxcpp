#ifndef HX_GC_INTERNAL_H
#define HX_GC_INTERNAL_H


// INTERNAL_GC is defined on the command-line with "-DINTERNAL_GC"


#ifdef INTERNAL_GC
  #define GC_CLEARS_OBJECTS
  #define GC_CLEARS_ALL
#else
  #define GC_CLEARS_OBJECTS
#endif


class hxObject;

typedef void (*finalizer)(hxObject *v);


void *hxInternalNew(int inSize,bool inIsObject);
void *hxInternalRealloc(void *inData,int inSize);
void hxInternalEnableGC(bool inEnable);
void *hxInternalCreateConstBuffer(const void *inData,int inSize);
void hxInternalCollect();
void hxGCSetVTables(struct _VTableMarks inVtableMark[]);

void hxGCMarkNow();

void hxPrologDone();

struct hxInternalFinalizer
{
	hxInternalFinalizer(hxObject *inObj);

	void Mark() { mUsed=true; }
	void Detach();

	bool      mUsed;
	bool      mValid;
	finalizer mFinalizer;
	hxObject  *mObject;
};


bool hxMarkAlloc(void *inPtr);


#endif
