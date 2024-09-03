// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "MyGameInstance.h"
#include "MyUIManager.h"
#include "MyInvenWidget.h"

#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"

#include "MyItem.h"
#include "Math/UnrealMathUtility.h" // srand�� ���.
#include "Kismet/GameplayStatics.h"
#include "MyStatComponent.h"
#include "MyInvenComponent.h"
#include "Components/WidgetComponent.h"
#include "MyHpBar.h"
#include "Blueprint/UserWidget.h"
#include "MyInvenWidget.h"
#include "MyPlayerController.h"
#include "Components/Button.h"

#include "MyAIController.h"

//Sound
#include "MySoundManager.h" 
#include "MyPlayer.h"
#include "MyMonsters.h"


#include "Engine/DamageEvents.h"
////particle

#include "MyEffectManager.h"
//#include "Particles/ParticleSystem.h"
//#include "Particles/ParticleSystemComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "Engine/World.h"

////Niagara
//#include "NiagaraComponent.h"
//#include "NiagaraFunctionLibrary.h"


#include "MyPtojectile.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// skeletal Mesh�� ����ϱ����� ConstructorHelpers::FObjectFinder
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Gr
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Meshes/Grux.Grux'"));
	
	if (Gr.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Gr.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//�߰��غ�
	RootComponent = GetCapsuleComponent();

	// inven Component
	_invenCom = CreateDefaultSubobject<UMyInvenComponent>(TEXT("Inventory"));
	
	// hp �� widget UI
	_hpbarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpbarWidget->SetupAttachment(GetMesh());
	_hpbarWidget->SetWidgetSpace(EWidgetSpace::Screen); // EWidgetSpace::World�� �ְ� Screen�� �ִµ� �뵵�� ���� �ٸ���.
	
	// hp����ġ
	_hpbarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 238.0f));
	// Stat Component
	_statCom = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));
	
	
	// Widget : HPBar
	static ConstructorHelpers::FClassFinder<UUserWidget> hpBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/MyHpBar_BP.MyHpBar_BP_C'"));
	
	if (hpBar.Succeeded())
	{
		_hpbarWidget->SetWidgetClass(hpBar.Class);
	}
	
	APawn::AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	//// Particle
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> PT(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonGrux/FX/Particles/Abilities/HardKnocks/FX/P_Grux_Knockup.P_Grux_Knockup'"));

	//if (PT.Succeeded())
	//{
	//	_particle = PT.Object;
	//}
	
	/*static ConstructorHelpers::FClassFinder<AMyPtojectile>
	projectileclass(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Object/MyProjectile_BP.MyProjectile_BP_C'"));*/

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Init();

	///////////////////////////////////���� �̱���? ������ �ذ��غ���////////////////////////
	//_soundManager = Cast<UMyGameInstance>(GetGameInstance())->GetSoundManager();
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	// ��Ÿ�ְ� ������ _isAttack �� false��
	if (_animInstance->IsValidLowLevel())
	{
		_animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackEnded);
		_animInstance->_attackDelegate.AddUObject(this, &AMyCharacter::AttackHit);
		_animInstance->_deathDelegate.AddUObject(this, &AMyCharacter::Disable);
	}

	// ���� ����
	_statCom->SetLevelAndInit(1);
	


	//_statCom->_hpChangedDelegate.Add();
	
	_hpbarWidget->InitWidget();
	auto hpBar = Cast<UMyHpBar>(_hpbarWidget->GetUserWidgetObject());
	if (hpBar)
	{
		_statCom->_hpChangedDelegate.AddUObject(hpBar, &UMyHpBar::SetHpBarValue);
	}
	
	//// TODO : InvenWidget
	//auto invenUI = UIManager->GetInvenUI();

	//if (invenUI)
	//{
	//	_invenCom->_itemAddedEvent.AddUObject(invenUI, &UMyInvenWidget::SetItem);
	//	invenUI->DropBtn->OnClicked.AddDynamic(_invenCom, &UMyInvenComponent::DropItem);
	//}

	
	
}


float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	// 1. hp -= Damage

	float damage = -_statCom->AddCurHp(-Damage);

	//UE_LOG(LogTemp, Log, TEXT("Attack : %s, CurHp : %d"), *DamageCauser->GetName(), _curHp);

	
	return damage;
}

void AMyCharacter::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{

	//UE_LOG(LogTemp, Error, TEXT("Attack!! END!!"));
	_isAttacking = false;
	_attackEndedDelegate.Broadcast(); // 

}

void AMyCharacter::AttackHit()
{

	//projectile Test
	// Skill Arrow
	if (_projectileclass)
	{
		FVector forward = GetActorForwardVector();
		FVector fireLocation = GetActorLocation()  + forward * 150;

		auto projectile = GetWorld()->SpawnActor<AMyPtojectile>(_projectileclass, fireLocation, FRotator::ZeroRotator);

		projectile->FireInDirection(forward);
	}



	//UE_LOG(LogTemp, Warning, TEXT("Attack!!!!!!!!!"));
	//TODO : AttackChanel
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this); //this �ڱ��ڽ��� �����϶�.. ���� ������ ���������ü�����..

	float attackRange = 1000.0f;
	float attackRadius = 20.0f;

	FVector forward = GetActorForwardVector();
	FQuat quat = FQuat::FindBetweenVectors(FVector(0, 0, 1), forward);

	//UE_LOG(LogTemp, Log, TEXT("%s"), *vec.ToString());
	FVector center = GetActorLocation() + forward * attackRange * 0.5f;
	FVector start = GetActorLocation();
	FVector end = start + forward * (attackRange*0.5f);

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		start,
		end,
		quat,
		ECollisionChannel::ECC_GameTraceChannel2,
		//FCollisionShape::MakeSphere(attackRadius),
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),

		params
	);
	
	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitActor : %s"), *hitResult.GetActor()->GetName());
		drawColor = FColor::Red;

		// ������...
		// 1. .... 
		FDamageEvent damageEvent;
		hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamge(), damageEvent, GetController(), this);
		_hitPoint = hitResult.ImpactPoint;

		// ���� 
		//_attackHitEvent.Broadcast();
			
			
		// ��ƼŬ ��Ʈ����Ʈ
		EffectManager->Play("Particle", _hitPoint);
			
		// ����
		
		PlayAttackHitSound("DefaultSound", _hitPoint);



		//// �÷��̽� ���콺Ŀ�� ����������..
		//if (GetController())
		//{
		//	Cast<AMyPlayerController>(GetController())->ShowUI();
		//}
	}

	// ���õ����� �α� ���
	UE_LOG(LogTemp, Warning, TEXT("AttackDamage : %d"), _statCom->GetAttackDamge());
	//UE_LOG(LogTemp, Warning, TEXT("ME : %s AttackDamage : %d"), *GetName(), _attackDamage);
				
	//DEBUG : DrawCapsule
	//DrawDebugSphere(GetWorld(), center, attackRadius, 12, drawColor, false, 2.0f);	
	//DrawDebugCapsule(GetWorld(), center, attackRange * 0.5f, attackRadius, quat, drawColor, false, 2.0f);
}

void AMyCharacter::PlayAttackHitSound(FString SoundName, FVector location)
{
	
	/*if (SoundManager)
	{
		SoundManager->PlaySound(SoundName, location);
	}*/
	FString Sounds = SoundName;

	if (IsA(AMyPlayer::StaticClass()))
	{
		Sounds = "PlayerDamageCue";
	}
	else if (IsA(AMyMonsters::StaticClass()))
	{
		Sounds = "MonsterDamageCue";
	}

	SoundManager->PlaySound(Sounds, location);

}

void AMyCharacter::AddAttackDamage(AActor* actor, int amount)
{
	// actor�� ���� ���ݷ��� �������� ���

	_statCom->AddAttackDamage(amount);
}

void AMyCharacter::AddItemToCharacter(AMyItem* item)
{
	/*if (_invenCom)
	{*/
		_invenCom->AddItem(item);
		//item->Disable(); //��� ��ž
		UE_LOG(LogTemp, Log, TEXT("Added item: %s"), *item->GetName());

	/*}*/
}

void AMyCharacter::DropItemFromCharacter()
{
	_invenCom->DropItem();
		
	////���������ҽõ�
	//if (_invenCom)
	//{
	//	if (_invenCom->HasItems()) // �κ��丮�� �������� �ִ��� Ȯ��
	//	{
	//		_invenCom->DropItem();
	//		UE_LOG(LogTemp, Warning, TEXT("Attack Damage -50"));
	//		_statCom->SubAttackDamage(50); // ���ݷ� ����
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("NO Have ITEM ~____________~"));
	//	}
	//}
}


void AMyCharacter::Init()
{
	_statCom->Reset();
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	PrimaryActorTick.bCanEverTick = true;

	_statCom->_deathDelegate.AddLambda([this]()-> void { this->GetController()->UnPossess(); }); // ���� ����� �κ�

	if (_aiController && GetController() == nullptr) // ��Ʈ�ѷ��� �ٽ� �������ϱ⶧���� ��Ʈ�ѷ��� ����Ҽ��ֵ���... �� ���Ǹ� ����...
	{
		auto ai_Controller = Cast<AMyAIController>(_aiController);
		if(ai_Controller)
			ai_Controller->Possess(this);
	}
}


void AMyCharacter::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;
	
	auto controller = GetController();
	if (controller)
		GetController()->UnPossess();; // ���� ������ ���� Ǯ��
	
}



