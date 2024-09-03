// Fill out your copyright notice in the Description page of Project Settings.


#include "MySoundManager.h"

#include "MyCharacter.h"
#include "MyPlayer.h"
#include "MyMonsters.h"

#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"


// Sets default values
AMySoundManager::AMySoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CreateSound("PlayerDamageCue", "/Script/Engine.SoundCue'/Game/Sounds/PlayerDamageCue.PlayerDamageCue'");
	CreateSound("MonsterDamageCue", "/Script/Engine.SoundCue'/Game/Sounds/MonsterDamageCue.MonsterDamageCue'");

}

// Called when the game starts or when spawned
void AMySoundManager::BeginPlay()
{
	Super::BeginPlay();

	

}

// Called every frame
void AMySoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMySoundManager::CreateSound(FString name, FString path)
{
	
	if (SoundTable.Contains(name))
	{
		UE_LOG(LogTemp, Warning, TEXT("FFFFFFFFFFFFFFFFFFFFFind : %s"), *name);
		return;
	}
	//

	static ConstructorHelpers::FObjectFinder<USoundBase> soundFinder(*path);
	if (soundFinder.Succeeded())
	{
		USoundBase* LoadedSound = soundFinder.Object;
		SoundTable.Add(name, LoadedSound);
	}

}

void AMySoundManager::PlaySound(FString name, FVector location)
{
	//if (SoundTable.Contains(name) /*== false*/)
	//{	//return; 
	//	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundTable[name], location);
	//	
	//}

	/*if (!character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is null"));
		return;
	}*/

	//FString SoundKey = name;

	
	//if (character->IsA(AMyPlayer::StaticClass())) // Player 
	//{
	//	SoundKey = "PlayerDamageSound";
	//}
	//else if (character->IsA(AMyMonsters::StaticClass())) // Monster
	//{
	//	SoundKey = "MonsterDamageSound";
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Unknown character type: %s"), *character->GetName());
	//	return;
	//}




	

	//if (SoundTable.Contains(name) == false)
	//{	return; 
	//	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundTable[name], location);
	//}

	if (USoundBase** Sound = SoundTable.Find(name))
	{
		UE_LOG(LogTemp, Log, TEXT("Sound found: %s, playing at location: %s"), *name, *location.ToString());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), *Sound, location);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound not found: %s"), *name);
	}


}

