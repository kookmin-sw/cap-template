using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class interact : MonoBehaviour
{
    public GameObject image_F;

    private void OnTriggerEnter(Collider other)
    {

        if (other.gameObject.layer == LayerMask.NameToLayer("Interact"))
        {
            Debug.Log("onTriggerEnter is activated for " + other.name);
            image_F.GetComponent<UIpressF>().show_image();
        }
    }

    //트리거로 상호작용 
    private void OnTriggerStay(Collider other)
    {
        if (Input.GetKeyDown(KeyCode.F))
        {
            if (other.CompareTag("door"))
            {
                Debug.Log("문 상호작용 ");
                other.GetComponent<Door>().ChangeDoorState();
            }

            if (other.CompareTag("betteryspawner"))
            {
                Debug.Log("betterySpawner 와 상호작용");
                other.GetComponent<betteryspawner>().Spawn_bettery();
            }

            if (other.CompareTag("battery"))
            {
                Debug.Log("bettery 와 상호작용");
                other.GetComponent<battery>().Destroy_battery();
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.layer == LayerMask.NameToLayer("Interact"))
        {
            Debug.Log("onTriggerExit is activated for " + other.name);
            image_F.GetComponent<UIpressF>().remove_image();
        }
    }

    void Update()
    {
    }
}

