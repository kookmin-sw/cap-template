using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Note : MonoBehaviour
{

    public void Hit()
    {
        GameManager.instance.AddScore(100); // 점수 추가
        Destroy(gameObject); // 노트 제거
    }
}