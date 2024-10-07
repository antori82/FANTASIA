// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TTSThreadInterface.generated.h"

UINTERFACE(MinimalAPI)
class UTTSThreadInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class FANTASIA_API ITTSThreadInterface
{
	GENERATED_BODY()

public:

	/**
	* To manage the request to the synthesis API
	*
	*
	**/
	virtual void Synthesize() = 0;


	/**
	* To register to the delegate
	*
	* @param UseDelegate - delegate to receive synthesis notifications
	*
	**/
	virtual FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate) = 0;


	/**
	* To un-register to the delegate
	*
	* @param FTTSResultAvailableDelegate -  registered delegate handle
	*
	**/
	virtual void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) = 0;

};