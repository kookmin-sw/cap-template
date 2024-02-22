using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraTest : MonoBehaviour
{
    public GameObject player;

    public Vector3 offset;

    // Update is called once per frame
    void Update()
    {
    }
    private void LateUpdate()
    {
        Vector3 newPosition = player.gameObject.transform.position + offset;
        this.gameObject.transform.position = newPosition;
    }
}
