using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;


public class LoginButton : MonoBehaviour
{
    public TMP_InputField InputId;
    public TMP_InputField InputPassword;

    public void OnClickloginButton()
    {
        GameManager.Instance.UserId = InputId.text;
        SceneManager.LoadScene("InGame");
    }
}
