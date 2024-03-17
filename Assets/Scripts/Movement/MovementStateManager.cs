using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;

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

    public ItemData[] weapons;
    public bool[] hasWeapons;
    public Inventory quickSlot;
    public Item item;
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

   /// <summary>
   /// ///////////////////////////////////////////
   /// 
   /// </summary>
   /// 
    // void SwapOut(){
    //     isSwap = false;
    // }
    // void Swap(){
    //     if(sDown1 && (!hasWeapons[0] || equipWeaponIndex == 0))
    //         return;
    //     if(sDown2 && (!hasWeapons[1] || equipWeaponIndex == 1))
    //         return;
    //     if(sDown3 && (!hasWeapons[2] || equipWeaponIndex == 2))
    //         return;

    //     int weaponIndex = -1;
    //     if(sDown1) weaponIndex = 0;
    //     if(sDown2) weaponIndex = 1;
    //     if(sDown3) weaponIndex = 2;

    //     if((sDown1 || sDown2 || sDown3)){
    //         if(equipWeapon != null)
    //             equipWeapon.SetActive(false);

    //         equipWeaponIndex = weaponIndex;
    //         equipWeapon = weapons[weaponIndex];
    //         equipWeapon.SetActive(true);

    //         anim.Settrigger("doSwap");
            
    //         isSwap = true;

    //         Invoke("SwapOut", 0.4f);
    //     }

    // }
    // 버튼에 따른 아이템 슬롯 선택
//    public void ChangeInventory()
//     {
//         if (Input.GetKeyDown(KeyCode.Alpha1))
//         {
//             UseItemFromSlot(0);
//         }
//         else if (Input.GetKeyDown(KeyCode.Alpha2))
//         {
//             UseItemFromSlot(1);
//         }
//         else if (Input.GetKeyDown(KeyCode.Alpha3))
//         {
//             UseItemFromSlot(2);
//         }
//         else if (Input.GetKeyDown(KeyCode.Alpha4))
//         {
//             UseItemFromSlot(3);
//         }
//         else if (Input.GetKeyDown(KeyCode.Alpha5))
//         {
//             UseItemFromSlot(4);
//         }
//     }
    
//     private void UseItemFromSlot(int slotIndex)
//     {
//         Slot slot = quickSlot.GetSlot(slotIndex);

//         // 해당 슬롯에 아이템이 존재하는지 확인
//         if (slot != null && slot.item != null)
//         {
//             Item item = slot.item;

//             EquipItem(item); // 장비(무기) 아이템일 경우 장착

//             // 아이템 사용 코드 작성 (예: 아이템 사용, 장착 등)
//             // 아이템 사용에 따른 추가 동작을 수행할 수 있음

//             // 아이템 사용 후에는 인벤토리 UI 갱신 등이 필요할 수 있음
//         }
//     }   

//     private void EquipItem(Item item)
//     {
//         // 아이템의 타입을 확인하여 해당하는 처리를 수행
//         switch (item.ItemType)
//         {
//             case 0:
//                 // 무기를 장착하는 코드 작성
//                 break;
//             case 2:
//                 // 갑옷을 장착하는 코드 작성
//                 break;
//             // 필요에 따라 다른 아이템 타입에 대한 처리 추가
//             default:
//                 // 아이템 타입이 지원되지 않을 때의 처리 작성
//                 break;
//         }

//         // 장착된 아이템에 대한 가시화나 다른 UI 업데이트 작업 수행
//         // 예를 들어, 가리고 있던 UI를 다시 표시하는 등의 작업을 수행할 수 있음
//     }

    /*
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(spherePos, controller.radius - 0.05f);
    }
    */
}