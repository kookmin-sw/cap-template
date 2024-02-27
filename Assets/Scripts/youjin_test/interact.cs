using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class interact : MonoBehaviour
{
    public float interactDiastance = 3f;

    private void OnTriggerEnter(Collider other)
    {
        Debug.Log("onTriggerEnter is activated");

    }

    private void OnTriggerExit(Collider other)
    {
        Debug.Log("onTriggerExit is activated");
    }

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

                if (hit.collider.CompareTag("betteryspawner"))
                {
                    Debug.Log("betterySpawner 와 상호작용");
                    hit.collider.GetComponent<betteryspawner>().create_bettery();
                }
            }


        }


    }
}

