#include "AVIDLib_Internal_Util/ItemInitialisation.h"
#include "AVIDLib_Internal_Util/Memory.h"
#include "AVIDLib_Plat/Ptr.h"

void ALU_InitArrayOfItems(void* items,
						  ALP_Size count,
						  ALP_Size itemSize,
						  ALU_ItemInitFunc initCallback,
						  void* initData)
{
	if ( !items || count < 1 || itemSize < 1 || !initCallback )
	{
		return;
	}

	const ALP_Byte* const itemsAsBytes = (const ALP_Byte*)items;

	for ( ALP_Size index = 0; index < count; ++index )
	{
		(*initCallback)((void*)(itemsAsBytes + (itemSize * index)), initData);
	}
}

void ALU_DeinitArrayOfItems(void* items,
							ALP_Size count,
							ALP_Size itemSize,
							ALU_ItemDeinitFunc deinitCallback,
							void* deinitData)
{
	if ( !items || count < 1 || itemSize < 1 || !deinitCallback )
	{
		return;
	}

	const ALP_Byte* const itemsAsBytes = (const ALP_Byte*)items;

	for ( ALP_Size index = 0; index < count; ++index )
	{
		(*deinitCallback)((void*)(itemsAsBytes + (itemSize * index)), deinitData);
	}
}

void* ALU_SetArrayOfItems(void** existingItems,
						  ALP_Size* existingItemCount,
						  ALP_Size newItemCount,
						  ALP_Size itemSize,
						  ALU_ItemInitFunc initCallback,
						  void* initData,
						  ALU_ItemDeinitFunc deinitCallback,
						  void* deinitData)
{
	if ( !existingItems || !existingItemCount || itemSize < 1 )
	{
		// Can't do anything, so no point.
		return ALP_NULL;
	}

	if ( *existingItems )
	{
		// We have existing items to get rid of. Deinit them first.
		ALU_DeinitArrayOfItems(*existingItems, *existingItemCount, itemSize, deinitCallback, deinitData);

		// Then free the memory, and update the output variables to reflect this.
		ALU_FREE(*existingItems);
		*existingItems = ALP_NULL;
		*existingItemCount = 0;
	}

	// Now the items list should be null, and the items count should be 0.

	if ( newItemCount > 0 )
	{
		// We have new items to create. Allocate memory for them.
		*existingItems = ALU_MALLOC(newItemCount * itemSize);

		if ( *existingItems )
		{
			// The allocation succeeded, so update the count.
			*existingItemCount = newItemCount;

			// Now go through and initialise all the items.
			ALU_InitArrayOfItems(*existingItems, *existingItemCount, itemSize, initCallback, initData);
		}
	}

	return *existingItems;
}
