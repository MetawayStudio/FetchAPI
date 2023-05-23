// Fill out your copyright notice in the Description page of Project Settings.


#include "FetchAPIBlueprintFunctionLibrary.h"
#include "JsonObjectConverter.h"
#include "Engine/GameEngine.h"

void UFetchAPIBlueprintFunctionLibrary::FetchAPI(FString URL, TEnumAsByte<Verb> Verb, FJsonObjectWrapper Body, FCallbackDelegate Callback)
{
    FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(URL);
    FString OutJsonBody;
    switch (Verb)
    {
    case POST:
        Request->SetVerb("POST");
        Request->SetHeader("Content-Type", "application/json");
        if(Body){
            Body.JsonObjectToString(OutJsonBody);
            Request->SetContentAsString(OutJsonBody);
        }
        break;
    case GET:
        Request->SetVerb("GET");
        break;
    case PUT:
        Request->SetVerb("PUT");
        break;
    }
    Request->OnProcessRequestComplete().BindLambda([Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
        FString JsonString = Response->GetContentAsString();
        FJsonObjectWrapper JsonResponse;
        JsonResponse.JsonObjectFromString(JsonString);
		Callback.ExecuteIfBound(JsonResponse , Response->GetResponseCode(), bWasSuccessful);
	});
    Request->ProcessRequest();
}
