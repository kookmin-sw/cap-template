using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;

public class characterMove: MonoBehaviour
{

    [SerializeField] float speed = 5f;
    [SerializeField] float mouseSpeed = 8f;

    private float gravity;
    private CharacterController controller;
    private Vector3 mov;

    private PhotonView pv;
    private cameraTest_youjin camera;


    private float mouseX;


    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
        pv = GetComponent<PhotonView>();
        mov = Vector3.zero;
        gravity = 10f;

        camera = GameObject.FindObjectOfType<cameraTest_youjin>();

        if (pv.IsMine)
        {
            camera.player = this.gameObject;
        }
    }

    // Update is called once per frame
    void Update()
    {
        mouseX += Input.GetAxis("Mouse X") * mouseSpeed;
        this.transform.localEulerAngles = new Vector3(0, mouseX, 0);

        if (controller.isGrounded)
        {
            mov = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
            mov = controller.transform.TransformDirection(mov);
        }
        else
        {
            mov.y -= gravity * Time.deltaTime;
        }

        controller.Move(mov * Time.deltaTime * speed);

    }
}