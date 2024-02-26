using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cameraTest_youjin : MonoBehaviour
{
    public GameObject player;

    public Vector3 offset = new Vector3(0,1.5f,0);

    // Update is called once per frame
    void Update()
    {
    }
    private void LateUpdate()
    {
        Vector3 newPosition = player.gameObject.transform.position + offset;
        //Vector3 newPosition = player.gameObject.transform.position;
        this.gameObject.transform.position = newPosition;
    }
}
