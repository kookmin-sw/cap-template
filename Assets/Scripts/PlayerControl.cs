// using System.Collections;
// using System.Collections.Generic;
// using Unity.VisualScripting;
// using UnityEditor;
// using UnityEngine;

// public class PlayerControl : MonoBehaviour
// {
//     // 스피드 조정 변수
//     [SerializeField]
//     private float walkSpeed;
//     [SerializeField]
//     private float runSpeed;
//     [SerializeField]
//     private float crouchSpeed;
//     private float applySpeed;

//     // 점프 정도
//     [SerializeField]
//     private float jumpForce;

//     // 상태 변수
//     private bool isRun = false;
//     private bool isGround = true;
//     private bool isCrouch = false;

//     // 앉았을 때 얼마나 앉을지 결정하는 변수
//     [SerializeField]
//     private float crouchPosY;
//     private float originPosY;
//     private float applyCrouchPosY;

//     // 민감도
//     [SerializeField]
//     private float lookSensitivity;  

//     // 카메라 한계
//     [SerializeField]
//     private float cameraRotationLimit;  
//     private float currentCameraRotationX; 

//     // 필요한 컴포넌트
//     [SerializeField]
//     private Camera theCamera; 
//     private Rigidbody myRigid;
//     private CapsuleCollider capsuleCollider; 
//     Animator anim;


//     void Start()
//     {
//         // 컴포넌트 할당
//         capsuleCollider = GetComponent<CapsuleCollider>();
//         myRigid = GetComponent<Rigidbody>();
//         anim = GetComponent<Animator>();

//         // 초기화
//         applySpeed = walkSpeed;

//         originPosY = theCamera.transform.localPosition.y;
//         applyCrouchPosY = originPosY;
//     }

//     void Update()  
//     {
//         IsGround();
//         TryJump();
//         TryRun();
//         TryCrouch();
//         Move();
//         CameraRotation();
//         CharacterRotation();
//     }

//     // 지면 체크
//     private void IsGround()
//     {
//         isGround = Physics.Raycast(transform.position, Vector3.down, capsuleCollider.bounds.extents.y + 0.1f);
//     }

//     // 점프 시도
//     private void TryJump()
//     {
//         if (Input.GetKeyDown(KeyCode.Space) && isGround)
//         {
//             Jump();
//         }
//     }

//     // 점프
//     private void Jump()
//     {
//         if (isCrouch)
//             Crouch();

//         myRigid.velocity = transform.up * jumpForce;
//     }

//     // 달리기 시도
//     private void TryRun()
//     {
//         if (Input.GetKey(KeyCode.LeftShift))
//         {
//             Running();
//         }
//         if (Input.GetKeyUp(KeyCode.LeftShift))
//         {
//             RunningCancel();
//         }
//     }

//     // 달리기
//     private void Running()
//     {
//         if (isCrouch)
//             Crouch();

//         isRun = true;
//         applySpeed = runSpeed;
//     }

//     // 달리기 취소
//     private void RunningCancel()
//     {
//         isRun = false;
//         applySpeed = walkSpeed;
//     }

//     // 앉기 시도
//     private void TryCrouch()
//     {
//         if (Input.GetKeyDown(KeyCode.LeftControl))
//         {
//             Crouch();
//         }
//     }

//     // 앉기 동작
//     private void Crouch()
//     {
//         isCrouch = !isCrouch;
//         if (isCrouch)
//         {
//             anim.SetBool("Crouching", true);
//             applySpeed = crouchSpeed;
//             applyCrouchPosY = crouchPosY;
//         }
//         else
//         {
//             anim.SetBool("Crouching", false);
//             applySpeed = walkSpeed;
//             applyCrouchPosY = originPosY;
//         }

//         StartCoroutine(CrouchCoroutine());
//     }

//     // 부드러운 앉기 동작
//     IEnumerator CrouchCoroutine()
//     {
//         float _posY = theCamera.transform.localPosition.y;
//         int count = 0;

//         while(_posY != applyCrouchPosY)
//         {
//             count++;
//             _posY = Mathf.Lerp(_posY, applyCrouchPosY, 0.2f);
//             theCamera.transform.localPosition = new Vector3(0, _posY, 0);
//             if(count > 15)
//                 break;
//             yield return null;
//         }
//         theCamera.transform.localPosition = new Vector3(0, applyCrouchPosY, 0);
//     }

//     private void Move()
//     {
//         float _moveDirX = Input.GetAxisRaw("Horizontal"); 
//         float _moveDirZ = Input.GetAxisRaw("Vertical"); 

//         Vector3 _moveHorizontal = transform.right * _moveDirX;
//         Vector3 _moveVertical = transform.forward * _moveDirZ; 

//         Vector3 _velocity = (_moveHorizontal + _moveVertical).normalized * applySpeed; 
        
//         anim.SetBool("Walking", _velocity != Vector3.zero);
//         myRigid.MovePosition(transform.position + _velocity * Time.deltaTime);
//     }

//     private void CameraRotation() 
//     {
//         float _xRotation = Input.GetAxisRaw("Mouse Y"); 
//         float _cameraRotationX = _xRotation * lookSensitivity;

//         currentCameraRotationX -= _cameraRotationX;
//         currentCameraRotationX = Mathf.Clamp(currentCameraRotationX, -cameraRotationLimit, cameraRotationLimit);

//         theCamera.transform.localEulerAngles = new Vector3(currentCameraRotationX, 0f, 0f);
//     }

//     private void CharacterRotation()
//     {
//         float _yRotation = Input.GetAxisRaw("Mouse X");
//         Vector3 _characterRotationY = new Vector3(0f, _yRotation, 0f) * lookSensitivity;
//         myRigid.MoveRotation(myRigid.rotation * Quaternion.Euler(_characterRotationY)); 
//     }
// }