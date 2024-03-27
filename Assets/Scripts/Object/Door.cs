using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;


public class Door : MonoBehaviour
{
    public bool open = false;
    public float smoot = 2f;

    public Vector3 doorOpenVector = new Vector3(0, -90f, 0);

    Quaternion ToDoorAngle;

    public PhotonView pv;

    private void Start()
    {
        pv = gameObject.AddComponent<PhotonView>();
        pv.ViewID = PhotonNetwork.AllocateViewID(0);
    }

    private void Update()
    {
        transform.rotation = Quaternion.Slerp(transform.rotation, ToDoorAngle, smoot * Time.deltaTime);
    }

    [PunRPC]
    public void ChangeDoorStateRPC()
    {
        open = !open;
        ChangeDoorAngle(open);
    }

    public void ChangeDoorState()
    {
        pv.RPC("ChangeDoorStateRPC", RpcTarget.All);
    }

    void ChangeDoorAngle(bool open)
    {
        if (open)
        {
            ToDoorAngle = Quaternion.Euler(transform.eulerAngles + doorOpenVector);

        }
        else
        {
            ToDoorAngle = Quaternion.Euler(transform.eulerAngles - doorOpenVector);
        }

    }

}

