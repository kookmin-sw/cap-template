using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NoteMovement : MonoBehaviour
{
    public float speed = 5.0f; // 노트가 움직이는 속도

    void Update()
    {
        // 노트를 매 프레임마다 왼쪽으로 이동시킵니다.
        transform.position += Vector3.left * speed * Time.deltaTime;
    }
}
