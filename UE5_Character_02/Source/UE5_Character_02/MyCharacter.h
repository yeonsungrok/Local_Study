// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyStatComponent.h"


#include "MyInvenComponent.h" // �κ��丮 �߰�

#include "MyCharacter.generated.h"


class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE(Delegate_AttackEnded);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_AttackHit);

UCLASS()
class UE5_CHARACTER_02_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()


	
public: //ĳ���� �⺻����
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
		
	// ���� �޴°��� TakeDamage , DamageCauser = �����Ѿְ� ��������
	virtual float TakeDamage
	(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnAttackEnded(class UAnimMontage* Montage, bool bInterrupted);

	//�ִ� �������Ʈ ��Ÿ�� ��Ƽ�����߰��ϱ�����
	UFUNCTION()
	virtual void AttackHit();
	
	// state ����
	int GetCurHp() { return _statCom->GetCurHp(); }
	void AddAttackDamage(AActor* actor, int amount);

	//// Item
	void AddItemToCharacter(class AMyItem* item);
	void DropItemFromCharacter();


	Delegate_AttackEnded _attackEndedDelegate;
			
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = Event, meta = (AllowPrivateAccess = "true"))
	FDelegate_AttackHit _attackHitEvent;

	virtual void PlayAttackHitSound(FString SoundName, FVector location);




protected: 
	virtual void Init();

	UFUNCTION()
	virtual void Disable();


public:


	//// Sound ::::::  Player�� Monster�� �������̵��ؼ� �����Ҽ��ֵ���
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	//AMySoundManager* _soundManager;




	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int _curAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _vertical = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _horizontal = 0.0f;

	// AttackHitPoint (�������Ʈ : �¾����� ��ġ ����)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	FVector _hitPoint;


	//�ִϸ��̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UMyAnimInstance* _animInstance;

	
	// State Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyStatComponent* _statCom;

	// Inven Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UMyInvenComponent* _invenCom;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _hpbarWidget;

	// TODO : Monster
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class AAIController* _aiController;
	



	// Particle
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* _particle;*/


	// BP : Master setting
	// Arrow
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMyPtojectile> _projectileclass;

};

