#ifndef AVIDLIB_INTERNAL_UTIL_ITEMINITIALISATION_H
#define AVIDLIB_INTERNAL_UTIL_ITEMINITIALISATION_H

#include "AVIDLib_Plat/Int.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ALU_ItemInitFunc)(void* item, void* data);
typedef void (*ALU_ItemDeinitFunc)(void* item, void* data);

// Initialises an array of uninitialised items, calling the specified callback on each of them.
void ALU_InitArrayOfItems(void* items,
						  ALP_Size count,
						  ALP_Size itemSize,
						  ALU_ItemInitFunc initCallback,
						  void* initData);

// Deinitialises an array of initialised items, calling the specified callback on each of them.
void ALU_DeinitArrayOfItems(void* items,
							ALP_Size count,
							ALP_Size itemSize,
							ALU_ItemDeinitFunc deinitCallback,
							void* deinitData);

// Given a pointer to an array of items, and a pointer to the number of items in the array,
// deinits any items that are currently in the array, deallocates any memory used by the array,
// and then allocates the amount of memory for the requested number of new items and inits each item.
// The init and deinit callbacks can be left null, in which case the respective init or deinit
// step will not be performed.
// Returns the item list pointer pointed to by existingItems, or null if existingItems is not valid.
void* ALU_SetArrayOfItems(void** existingItems,
						  ALP_Size* existingItemCount,
						  ALP_Size newItemCount,
						  ALP_Size itemSize,
						  ALU_ItemInitFunc initCallback,
						  void* initData,
						  ALU_ItemDeinitFunc deinitCallback,
						  void* deinitData);

#ifdef __cplusplus
} // exter "C"
#endif

#endif // AVIDLIB_INTERNAL_UTIL_ITEMINITIALISATION_H
