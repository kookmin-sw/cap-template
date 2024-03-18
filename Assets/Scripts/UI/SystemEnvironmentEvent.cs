using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
public class SystemEnvironmentEvent : MonoBehaviour
{
    [SerializeField] private GameObject systemEnvironment;

    //시스템 환경 버튼
    [SerializeField] private Button settingButton;
    [SerializeField] private Button lobbyButton;
    [SerializeField] private Button desktopButton;
    [SerializeField] private Button backButton;

    // 시스템 환경 버튼
    public void OnClickedSettingButton()
    {
        return;
    }

    public void OnClickedLobbyButton()
    {
        SceneManager.LoadScene("Lobby");
    }

    public void OnClickedDesktopButton()
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#else
        Application.Quit();
#endif
    }

    public void OnClickedBackButton()
    {
        systemEnvironment.SetActive(false);
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;
    }

}
