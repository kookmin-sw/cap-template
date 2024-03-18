using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NoteSpawner : MonoBehaviour
{
    public GameObject notePrefab; // 노트 프리팹
    public float[] noteTimings; // 노트가 생성되어야 하는 타이밍 배열
    public AudioSource music; // 음악 AudioSource

    private int nextNoteIndex = 0; // 다음에 생성될 노트의 인덱스

    void Update()
    {
        while (nextNoteIndex < noteTimings.Length && music.isPlaying)
        {
            if (music.time >= noteTimings[nextNoteIndex])
            {
                SpawnNote();
                nextNoteIndex++;
            }
        }
    }

    void SpawnNote()
    {
        Instantiate(notePrefab, transform.position, Quaternion.identity);
    }
}
