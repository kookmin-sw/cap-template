using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class HpManager : MonoBehaviour
{
    public float maxHp { get; set; } = 100;
    public float hp { get; set; }
    public bool isDead { get; set; } // 죽었는지 확인

    // 죽었을 때 작동할 함수들을 저장하는 변수
    // onDeath += 함수이름; 이렇게 이벤트 등록 가능
    // 함수 이름에 () 안붙여야함
    public event Action onDeath;

    // 캐릭터 생성, 부활 등등 활성화 될 때 실행되는 코드
    void OnEnable()
    {
        hp = maxHp;

        isDead = false;
    }

    // 데미지 처리하는 함수
    public void OnDamage(float damage, Vector3 hitPoint, Vector3 hitNormal)
    {
        hp -= damage;

        // 체력이 0 이하이고 살아있으면 사망
        if (hp <= 0 && !isDead)
        {
            Die();
        }
    }

    // 체력 회복 함수
    public void OnRecovery(float recovery)
    {
        // 죽었으면 회복 x
        if (!isDead)
        {
            hp += recovery;
            if (hp > maxHp)
            {
                hp = maxHp;
            }
        }
    }

    // 사망 함수
    public void Die()
    {
        // 사망 이벤트 있으면 실행
        if (onDeath != null)
        {
            onDeath();
        }
        isDead = true;
    }
}
