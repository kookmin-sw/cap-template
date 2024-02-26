using System.Collections;
using System.Collections.Generic;
using UnityEditor.Experimental.GraphView;
using UnityEngine;

public class characterMove: MonoBehaviour
{

    [SerializeField] float speed = 5f;
    [SerializeField] float mouseSpeed = 8f;

    private float gravity;
    float yVelocity;
    public float jump_Power;
    private CharacterController controller;
    private Vector3 mov;
    


    private float mouseX;

    Animator anim;

    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
        mov = Vector3.zero;
        gravity = 10f;
        anim = GetComponent<Animator>();
    }   

    // Update is called once per frame
    void PlayerJump(){
        mov.y = jump_Power;
        anim.SetBool("isJump", mov != Vector3.zero);
    }

    // void PlayerMove(){
    //     float h = Input.GetAxisRaw("Horizontal");
    //     float v = Input.GetAxisRaw("Vertical");

    //     mov.x = h;
    //     mov.y = 0;
    //     mov.z = v;

    //     mov = transform.TransformDirection(mov);
    //     mov *= speed * Time.deltaTime;
        
    //     controller.Move(mov);
    // }

    void Update()
    {
        mouseX += Input.GetAxis("Mouse X") * mouseSpeed;
        this.transform.localEulerAngles = new Vector3(0, mouseX, 0);

        if (controller.isGrounded)
        {
            mov = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
            anim.SetBool("isJogForward", mov != Vector3.zero);
            mov = controller.transform.TransformDirection(mov);
            if(Input.GetKeyDown(KeyCode.Space))
                PlayerJump();   
        }
        else
        {
            mov.y -= gravity * Time.deltaTime;
        }

        controller.Move(mov * Time.deltaTime * speed);

    }
}