// using System.Collections;
// using System.Collections.Generic;
// using UnityEngine;
// using Photon.Pun;
// using Photon.Realtime;

// public class Scavenger : MonoBehaviour
// {
//     float xAxis;
//     float zAxis;

//     public float speed;

//     Animator anim;

//     Vector3 moveVec;

//     private PhotonView pv;
//     private CameraTest camera;

//     // Start is called before the first frame update
//     void Awake()
//     {
//         anim = GetComponent<Animator>();
//         pv = GetComponent<PhotonView>();
//         camera = GameObject.FindObjectOfType<CameraTest>();

//         if (pv.IsMine)
//         {
//             camera.player = this.gameObject;
//         }
//     }

//     // Update is called once per frame
//     void Update()
//     {
//         if (pv.IsMine)
//         {
//             xAxis = Input.GetAxisRaw("Horizontal");
//             zAxis = Input.GetAxisRaw("Vertical");

//             moveVec = new Vector3(xAxis, 0, zAxis).normalized;

//             transform.position += moveVec * speed * Time.deltaTime;

//             transform.LookAt(transform.position + moveVec);

//             anim.SetBool("isJogForward", moveVec != Vector3.zero);
//         }
//     }
// }
