using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameOverBoradEvent : MonoBehaviour
{
    //게임 스코어보드 버튼
    [SerializeField] private Button scoreLobbyButton;
    [SerializeField] private Button deathcamButton;
    public void OnClickedScoreLobbyButton()
    {
        SceneManager.LoadScene("Lobby");
    }

    public void OnClickedDeathcamButton()
    {
        return;
    }
}
