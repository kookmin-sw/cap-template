using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JudgmentZone : MonoBehaviour
{
    private List<Note> notesInLine = new List<Note>();

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            var notesToJudge = new List<Note>(notesInLine);
        
            foreach (var note in notesToJudge)
            {
                note.Hit(); // 노트 판정
            }            
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        Note note = collision.GetComponent<Note>();
        if (note != null)
        {
            notesInLine.Add(note); // 판정선에 들어온 노트를 추가합니다.
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        Note note = collision.GetComponent<Note>();
        if (note != null)
        {
            notesInLine.Remove(note); // 판정선을 벗어난 노트를 제거합니다.
        }
    }
}