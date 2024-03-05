using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraRot : MonoBehaviour
{
    [SerializeField] private float mouseSpeed=8f; //회전속도
    private float mouseX=0f; //좌우 회전값을 담을 변수
    private float mouseY=0f; //위아래 회전값을 담을 변수

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        mouseX += Input.GetAxis("Mouse X")*mouseSpeed;
        mouseY += Input.GetAxis("Mouse Y")*mouseSpeed;
        this.transform.localEulerAngles = new Vector3(-mouseY, mouseX, 0);
    }
}