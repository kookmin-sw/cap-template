using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;
using System.Linq.Expressions;

public class MovementStateManager : MonoBehaviour
{
    [HideInInspector] public float xAxis; // 좌, 우
    [HideInInspector] public float zAxis; // 앞, 뒤

    [HideInInspector] public Vector3 moveDir; 
    public float currentMoveSpeed;
    public float walkSpeed = 3, walkBackSpeed = 2; 
    public float runSpeed = 7, runBackSpeed = 5;
    public float crouchSpeed = 1, crouchBackSpeed = 1;
    public float crouchFastSpeed = 2, crouchFastBackSpeed = 2;
    public float jumpPower = 5;
    CharacterController controller;

    [SerializeField] float groundYOffset;
    [SerializeField] LayerMask groundMask;
    Vector3 spherePos;

    [SerializeField] float jumpForce = 5;
    [SerializeField] float gravity = -9.81f;
    [HideInInspector] public bool jumped;
    Vector3 velocity;

    public MovementBaseState previousState;
    public MovementBaseState currentState;
    public IdleState Idle = new IdleState();
    public WalkState Walk = new WalkState();
    public CrouchState Crouch = new CrouchState();
    public RunState Run = new RunState();
    public JumpState Jump = new JumpState();

    [HideInInspector] public Animator anim;
    [HideInInspector] public AnimatorStateInfo stateInfo;
    public int tempLayer;

    void Start()
    {
        anim = GetComponentInChildren<Animator>();
        controller = GetComponent<CharacterController>();
        // anim.SetLayerWeight(tempLayer, 1);
        // stateInfo = anim.GetCurrentAnimatorStateInfo(tempLayer);
        SwitchState(Idle);
    }

    void Update()
    {
        GetDirectionAndMove();
        Gravity();

        anim.SetFloat("xAxis", xAxis);
        anim.SetFloat("zAxis", zAxis);

        currentState.UpdateState(this);

        Attack();
    }

    public void SwitchState(MovementBaseState state)
    {
        currentState = state;
        currentState.EnterState(this);
    }

    void GetDirectionAndMove()
    {
        xAxis = Input.GetAxis("Horizontal");
        zAxis = Input.GetAxis("Vertical");

        moveDir = (transform.forward * zAxis + transform.right * xAxis).normalized;

        controller.Move(moveDir * currentMoveSpeed * Time.deltaTime);
    }
    public bool IsGrounded()
    {
        spherePos = new Vector3(transform.position.x, transform.position.y - groundYOffset, transform.position.z);
        if (Physics.CheckSphere(spherePos, controller.radius - 0.05f, groundMask)) return true;
        return false;
    }

    void Gravity()
    {
        if (!IsGrounded()) velocity.y += gravity * Time.deltaTime;
        else if (velocity.y < 0) velocity.y = -2;

        controller.Move(velocity * Time.deltaTime);
    }

    public void JumpForce() => velocity.y += jumpForce;

    public void Jumped() => jumped = true;

    public void Attack(){
        if (Input.GetMouseButton(0))
            {
                anim.SetBool("Attack", true);
            }
        else anim.SetBool("Attack", false);
    }

    /*
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(spherePos, controller.radius - 0.05f);
    }
    */
}