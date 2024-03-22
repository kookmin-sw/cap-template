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

    public GameObject[] weapons; // 모든 무기 배열
    public Inventory quickSlot; // 가지고 있는 무기
    GameObject equipWeapon; // 장착 중인 무기
    int equipWeaponIndex = -1; // 장착 중인 무기의 weapons에서의 위치
    bool isSwap; // 스왑 상태
    public bool isAttack; // 공격 상태
    public Transform RightHand;

    MeshCollider colliderWeapon; // 무기들의 collider
    SphereCollider colliderHand; // 주먹 collider
    public GameObject objWeapon; // 장착중인 무기 gameobject(무기 및 주먹)
    public string Armed; // 현재 장착중인 무기 타입

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

        objWeapon = RightHand.GetChild(1).gameObject; // 처음 시작할 때 주먹의 sphereCollider 받아옴
        colliderHand = objWeapon.GetComponent<SphereCollider>();
        colliderHand.enabled = false; // 기본적으로는 collider 꺼둠
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

    public void JumpForce(){
        velocity.y += jumpForce;
    } 

    public void Jumped() => jumped = true;

    // 공격
    public void Attack(){ 
        if (Input.GetMouseButton(0))
            {
                Debug.Log("aTtatack");
                anim.SetBool("Attack", true);
            }
        else anim.SetBool("Attack", false);
    }

    // 무기 장착 시와 비 장착시 공격 시작(collider on)
    public void AttackStart(){
        Debug.Log("Collider On");
        if(Armed != "") {
            Debug.Log("Weaponcoll On");
            colliderWeapon.enabled = true;
        }
        else {
            Debug.Log("Handcoll on");
            colliderHand.enabled = true;
        }
    }

    // 무기 장착 시와 비 장착시 공격 끝(collider off)
    public void AttackEnd(){
        Debug.Log("coll Off");
        if(Armed != "") {
            colliderWeapon.enabled = false;
            Debug.Log("Weaponcoll Off");
        }
        else {
            colliderHand.enabled = false;
            Debug.Log("Handcoll Off");
        }
    }

    // 공격 시작
    public void AttackIn(){
        Debug.Log("bbabsd");
        isAttack = true;
    }

    // 공격 끝
    public void AttackOut(){
        Debug.Log("ASaaaaaa");
        isAttack = false;   
    }   

    // 스왑 끝
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
        if(isAttack) return; // 공격 중에는 스왑 불가

        int weaponIndex = -1;
        if(Input.GetButtonDown("Swap1")) weaponIndex = 0;
        if(Input.GetButtonDown("Swap2")) weaponIndex = 1;
        if(Input.GetButtonDown("Swap3")) weaponIndex = 2;
        if(Input.GetButtonDown("Swap4")) weaponIndex = 3;
        if(Input.GetButtonDown("Swap5")) weaponIndex = 4;

        if(Input.GetKeyDown(KeyCode.G)) { // G는 버리는 키라서 인벤토리에서도 빼기
            weaponIndex = -1;
            equipWeapon.SetActive(false);
            anim.SetTrigger("doSwap");
            anim.SetBool(Armed, false);
            Armed = "";
            return;
        }
        // 버튼을 입력 받으면 
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
                Debug.Log("swap" + 11231);
            objWeapon = weapons[equipWeaponIndex];
            

            // 무기 들었을 때 애니메이션 변경
            if(objWeapon.GetComponent<ItemData>().itemData.ItemType <= 10){
                colliderWeapon = objWeapon.GetComponent<MeshCollider>();
                if(objWeapon.GetComponent<ItemData>().itemData.ItemType <= 3) {
                    anim.SetBool(Armed, false);
                    Debug.Log("OtoT");
                    Armed = "THW";
                    anim.SetBool(Armed, true);
                }
                else {
                    anim.SetBool(Armed, false);
                    Debug.Log("TtoO");
                    Armed = "OHW";
                    anim.SetBool(Armed, true);
                }
            }
            
            equipWeapon = weapons[equipWeaponIndex];
            equipWeapon.SetActive(true);
            
            anim.SetTrigger("doSwap");
            
            isSwap = true;

            //Invoke("SwapOut", 0.4f);  // swap 애니메이션 넣으면 사용
        }
    }

    void OnDamaged(Vector3 targetPos)
    {
        //player  damaged
        gameObject.layer = 1;
        
        // 여기에 HP감소 넣기
        Debug.Log("Hit");

        //animation
        anim.SetTrigger("doDamaged");

        Invoke("OffDamaged", 2);
    }

    void OffDamaged()
    {
        gameObject.layer = 0;
    }

    void OnCollisionEnter(Collision collision)
    {
        //적에게 닿았을때
        if(collision.gameObject.tag == "Weapon") // tag변경 필요
            OnDamaged(collision.transform.position);
    }
    /*
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(spherePos, controller.radius - 0.05f);
    }
    */
}