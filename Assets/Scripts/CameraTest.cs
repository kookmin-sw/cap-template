using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;
using Cinemachine;

public class CameraTest : MonoBehaviour
{
    public GameObject player;
    public Vector3 offset;

    //public Vector3 offset;

    Vector3 newPosition;

    // Update is called once per frame
    void Start()
    {
        this.gameObject.transform.rotation = Quaternion.Euler(0, 0, 0);
    }
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
