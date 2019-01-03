/*
 * copied the source file by CopyLib.exe
 *
 */
void *REAL_memAlloc(int size);
/*
 * copied the source file by CopyLib.exe
 *
 */
void *REAL_memRealloc(void *block, int size);
/*
 * copied the source file by CopyLib.exe
 *
 */
void REAL_memFree(void *block);

/*
 * copied the source file by CopyLib.exe
 *
 */
void memAlloc_INIT(void);

/*
 * copied the source file by CopyLib.exe
 *
 */
void *memAlloc_NC(int size);
/*
 * copied the source file by CopyLib.exe
 *
 */
void *memRealloc(void *block, int size);
/*
 * copied the source file by CopyLib.exe
 *
 */
void memFree(void *block);
/*
 * copied the source file by CopyLib.exe
 *
 */
void *memAlloc(int size);
/*
 * copied the source file by CopyLib.exe
 *
 */
void *memClone(void *block, int size);

#define na(type_t, count) \
	((type_t *)memAlloc(sizeof(type_t) * (count)))

#define nb(type_t) \
	(na(type_t, 1))
