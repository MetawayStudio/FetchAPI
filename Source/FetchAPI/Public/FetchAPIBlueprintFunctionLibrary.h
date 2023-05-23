// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "Json.h"
#include "Templates/SharedPointer.h"
#include "JsonObjectWrapper.h"
#include "FetchAPIBlueprintFunctionLibrary.generated.h"


// Delegate
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCallbackDelegate, FJsonObjectWrapper, Response, int, HttpStatus, bool, Success);
// Enum
UENUM(BlueprintType)
enum Verb
{
	GET     UMETA(DisplayName = "GET"),
	POST      UMETA(DisplayName = "POST"),
	PUT      UMETA(DisplayName = "PUT"),
};

UCLASS()
class FETCHAPI_API UFetchAPIBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject", Body = "NULL"))
	static void FetchAPI(FString URL, TEnumAsByte<Verb> Verb, FJsonObjectWrapper Body, FCallbackDelegate Callback);
};