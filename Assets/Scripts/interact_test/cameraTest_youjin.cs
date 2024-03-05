using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cameraTest_youjin : MonoBehaviour
{
    public GameObject player;

    public Vector3 offset = new Vector3(0,1.5f,0);

    Vector3 newPosition;

    private void LateUpdate()
    {

        if (player != null)
        {
            newPosition = player.gameObject.transform.position + offset;
        }
        else
        {
            newPosition = new Vector3(0f, 0.2f, 0f) + offset;
        }
        this.gameObject.transform.position = newPosition;
    }
}
