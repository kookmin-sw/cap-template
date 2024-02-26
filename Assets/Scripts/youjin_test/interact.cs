using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class interact : MonoBehaviour
{
    public float interactDiastance = 2f;
    RaycastHit hit;

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.F))
        {
            RaycastHit hit;
            Debug.DrawRay(transform.position, transform.forward * interactDiastance, Color.blue, interactDiastance);

            //Physics.Raycast(원점, 방향, 충돌감지, 거리)
            if (Physics.Raycast(transform.position, transform.forward, out hit, interactDiastance))
            {
                if (hit.collider.CompareTag("door"))
                {
                    Debug.Log("문 상호작용 ");
                    hit.collider.GetComponent<Door>().ChangeDoorState();
                }
            }
        }


    }
}

