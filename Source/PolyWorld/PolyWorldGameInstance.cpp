// Fill out your copyright notice in the Description page of Project Settings.


#include "PolyWorldGameInstance.h"

FPolymonInfo UPolyWorldGameInstance::GetSelectedPolymon(int32 Index)
{
	if (SelectedPolymons.Num() > Index)
	{
		return SelectedPolymons[Index];
	}
	FPolymonInfo empty;
	return empty;
}