using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Note : MonoBehaviour
{
    public float hitTime;
    void OnUserHit()
    {
        // 사용자가 노트를 타격했을 때의 로직
        GameManager.instance.JudgeNoteTiming(hitTime, Time.time);
    }
}
