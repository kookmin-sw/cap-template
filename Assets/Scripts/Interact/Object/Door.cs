using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Door : MonoBehaviour
{
    public bool open = false;
    public float smoot = 2f;

    public float doorOpenAngle = 90f;
    public float doorCloseAngle = 0f;

    public Vector3 doorOpenVector = new Vector3(0, 90f, 0);
    public Vector3 doorCloseVector = new Vector3(0f, 0f,0f);

    public void ChangeDoorState()
    {
        open = !open;
    }



    void Update()
    {
        Quaternion current_angle = Quaternion.Euler(transform.eulerAngles);
        Vector3 current_vector = transform.eulerAngles;

        if (open)
        {
            //transform.rotation = Quaternion.Euler(current_vector+doorOpenVector);
            //transform.rotation = Quaternion.Slerp(transform.rotation,Quaternion.Euler(), smoot * Time.deltaTime)

            //Quaternion targetRotation = Quaternion.Euler(current_vector+doorOpenAngle);
            //transform.localRotation = Quaternion.Slerp(transform.rotation, targetRotation, smoot * Time.deltaTime);

            //transform.localRotation = Quaternion.Slerp(transform.localRotation, Quaternion.Euler(current + doorOpenAngle), smoot * Time.deltaTime);
        }
        else
        {
            //transform.rotation = Quaternion.Euler(current_vector + doorCloseVector);
            //Quaternion targetRotation2 = Quaternion.Euler(doorCloseAngle);
            //transform.localRotation = Quaternion.Slerp(current_angle, targetRotation2, smoot * Time.deltaTime);

            //transform.localRotation = Quaternion.Slerp(transform.localRotation, Quaternion.Euler(current + doorCloseAngle), smoot * Time.deltaTime);
        }
    }
}
