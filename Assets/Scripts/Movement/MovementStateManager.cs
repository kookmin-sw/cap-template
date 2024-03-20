using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;
using Photon.Pun.UtilityScripts;

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

    public GameObject[] weapons;
    public Inventory quickSlot;
    GameObject equipWeapon;
    int equipWeaponIndex = -1;
    bool isSwap;

    public MovementBaseState previousState;
    public MovementBaseState currentState;
    public IdleState Idle = new IdleState();
    public WalkState Walk = new WalkState();
    public CrouchState Crouch = new CrouchState();
    public RunState Run = new RunState();
    public JumpState Jump = new JumpState();

    [HideInInspector] public Animator anim;

    private PhotonView pv;

    void Start()
    {
        pv = GetComponent<PhotonView>();
        anim = GetComponentInChildren<Animator>();
        controller = GetComponent<CharacterController>();
        quickSlot = GameObject.Find("ItemQuickSlots").GetComponent<Inventory>();
        SwitchState(Idle);
    }

    void Update()
    {
        if (pv.IsMine)
        {
            GetDirectionAndMove();
            Gravity();

            anim.SetFloat("xAxis", xAxis);
            anim.SetFloat("zAxis", zAxis);

            currentState.UpdateState(this);

            Attack();   
            Swap();
        }
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

    public void Attack(){ // 추후에 스크립트 따로
        if (Input.GetMouseButton(0))
            {
                anim.SetBool("Attack", true);
            }
        else anim.SetBool("Attack", false);
    }
    void SwapOut(){
        isSwap = false;
    }
    void Swap(){
        // if(sDown1 && (!hasWeapons[0] || equipWeaponIndex == 0))
        //     return;
        // if(sDown2 && (!hasWeapons[1] || equipWeaponIndex == 1))
        //     return;
        // if(sDown3 && (!hasWeapons[2] || equipWeaponIndex == 2))
        //     return;

        int weaponIndex = -1;
        if(Input.GetButtonDown("Swap1")) weaponIndex = 0;
        if(Input.GetButtonDown("Swap2")) weaponIndex = 1;
        if(Input.GetButtonDown("Swap3")) weaponIndex = 2;
        if(Input.GetButtonDown("Swap4")) weaponIndex = 3;
        if(Input.GetButtonDown("Swap5")) weaponIndex = 4;

        if((Input.GetButtonDown("Swap1") || Input.GetButtonDown("Swap2") || Input.GetButtonDown("Swap3")
            || Input.GetButtonDown("Swap4") || Input.GetButtonDown("Swap5"))){
            if(equipWeapon != null)
                equipWeapon.SetActive(false);

            for(int i = 0 ; i< weapons.Length; i++){
                    if(quickSlot.items[weaponIndex].ItemType == weapons[i].GetComponent<ItemData>().itemData.ItemType){
                        equipWeaponIndex= i;        
                        break;
                    }   
                }
            equipWeapon = weapons[equipWeaponIndex];
            equipWeapon.SetActive(true);

            //anim.Settrigger("doSwap");
            
            isSwap = true;

            //Invoke("SwapOut", 0.4f);
        }
    }

    /*
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(spherePos, controller.radius - 0.05f);
    }
    */
}