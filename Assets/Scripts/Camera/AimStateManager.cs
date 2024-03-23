using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;
using Photon.Pun;
using Unity.VisualScripting;

public class AimStateManager : MonoBehaviourPun
{
    public Cinemachine.AxisState xAxis, yAxis;
    [SerializeField] Transform camFollowPos;

    [SerializeField] UIManager uiManager;

    private PhotonView pv;

    // Start is called before the first frame update
    void Start()
    {
        pv = GetComponent<PhotonView>();
        uiManager = FindObjectOfType<UIManager>();
        if (pv.IsMine)
        {
            var followCam = FindObjectOfType<CinemachineVirtualCamera>();
            followCam.Follow = this.camFollowPos.transform;
            followCam.LookAt = this.camFollowPos.transform;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (pv.IsMine && uiManager.isUIActivate == false)
        {
            xAxis.Update(Time.deltaTime);
            yAxis.Update(Time.deltaTime);
        }
    }

    private void LateUpdate()
    {
        if (pv.IsMine)
        {
            camFollowPos.localEulerAngles = new Vector3(-yAxis.Value, camFollowPos.localEulerAngles.y, camFollowPos.localEulerAngles.z);
            transform.eulerAngles = new Vector3(transform.eulerAngles.x, xAxis.Value, transform.eulerAngles.z);
        }
    }
}
