using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Door : MonoBehaviour
{
    public bool open = false;
    public float smoot = 2f;

    public Vector3 doorOpenVector = new Vector3(0, -90f, 0);

    Quaternion ToDoorAngle;

    private void Update()
    {
        transform.rotation = Quaternion.Slerp(transform.rotation, ToDoorAngle, smoot * Time.deltaTime);
    }

    public void ChangeDoorState()
    {
        open = !open;
        ChangeDoorAngle(open);
    }

    void ChangeDoorAngle(bool open)
    {
        if (open)
        {
            ToDoorAngle = Quaternion.Euler(transform.eulerAngles + doorOpenVector);

        }
        else
        {
            ToDoorAngle = Quaternion.Euler(transform.eulerAngles - doorOpenVector);
        }

    }

}

