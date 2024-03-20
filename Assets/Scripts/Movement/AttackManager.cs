// using System.Collections;
// using System.Collections.Generic;
// using UnityEngine;

// public class AttackManager : MonoBehaviour
// {
//     Animator anim;

//     public Transform RightHand;

//     BoxCollider colliderWeapon;
//     private GameObject objWeapon;

//     void Start()
//     {
//         anim = GetComponent<Animator>();

//         objWeapon = RightHand.GetChild(0).gameObject;
//         colliderWeapon.enabled = false;
//     }

//     void Update(){
//         if(Input.GetMouseButtonDown(0)){
//             Attack();
//         }
//     }

//     private void Attack()
//     {
//         anim.SetTrigger("Attack");
//     }

//     public void AttackStart(){
//         colliderWeapon.enabled = true;
//     }

//     public void AttackEnd(){
//         colliderWeapon.enabled = false;
//     }
// }
