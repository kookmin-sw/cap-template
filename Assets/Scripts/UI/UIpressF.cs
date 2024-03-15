using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIpressF : MonoBehaviour
{
    public void show_image()
    {
        gameObject.SetActive(true);
    }

    public void remove_image()
    {
        gameObject.SetActive(false);
    }
}
