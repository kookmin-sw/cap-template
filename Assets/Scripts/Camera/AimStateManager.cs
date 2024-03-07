using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;
using Photon.Pun;

public class AimStateManager : MonoBehaviourPun
{
    public Cinemachine.AxisState xAxis, yAxis;
    [SerializeField] Transform camFollowPos;

    // Start is called before the first frame update
    void Start()
    {
        if(this.photonView.IsMine)
        {
            var followCam = FindObjectOfType<CinemachineVirtualCamera>();
            followCam.Follow = this.camFollowPos.transform;
            followCam.LookAt = this.camFollowPos.transform;
        }
    }

    // Update is called once per frame
    void Update()
    {
        xAxis.Update(Time.deltaTime);
        yAxis.Update(Time.deltaTime);
    }

    private void LateUpdate()
    {
        camFollowPos.localEulerAngles = new Vector3(-yAxis.Value, camFollowPos.localEulerAngles.y, camFollowPos.localEulerAngles.z);
        transform.eulerAngles = new Vector3(transform.eulerAngles.x, xAxis.Value, transform.eulerAngles.z);
    }
}
