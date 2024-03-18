using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JudgmentZone : MonoBehaviour
{
    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.tag == "Note")
        {
            // 점수 증가 로직 호출
            GameManager.instance.AddScore(100);
            Destroy(other.gameObject); // 노트 제거
        }
    }
}