using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro; 

public class GameManager : MonoBehaviour
{
    public static GameManager instance; // 싱글턴 패턴 사용
    public float perfectTiming = 100.0f; // Perfect 판정 기준
    public float greatTiming = 200.0f; // Great 판정 기준
    public float goodTiming = 300.0f; // Good 판정 기준
    public int score = 0; // 현재 점수
    public TextMeshProUGUI scoreText; // 점수 표시용 텍스트

    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    public void AddScore(int amount)
    {
        score += amount;
        scoreText.text = "Score: " + score;
    }
    // 노트가 타격되었을 때 호출되는 함수
    public void JudgeNoteTiming(float noteHitTime, float currentTime)
    {
        // 타격 시간과 현재 시간의 차이를 계산
        float timingDifference = Mathf.Abs(noteHitTime - currentTime);

        // 판정 로직
        if (timingDifference <= perfectTiming)
        {
            Debug.Log("Perfect!");
        }
        else if (timingDifference <= greatTiming)
        {
            Debug.Log("Great!");
        }
        else if (timingDifference <= goodTiming)
        {
            Debug.Log("Good!");
        }
        else
        {
            Debug.Log("Miss");
        }

        // 여기서 노트를 제거하거나 점수를 추가하는 등의 처리를 할 수 있습니다.
    }
    
    void Update()
    {
        // 플레이어가 스페이스바를 누를 때의 로직
        if (Input.GetKeyDown(KeyCode.Space))
        {
            // 노트 판정 로직 호출 (아직 구현 전)
            Debug.Log("Space bar pressed!");
            AddScore(100); // UI 업데이트
        }
    }
}
