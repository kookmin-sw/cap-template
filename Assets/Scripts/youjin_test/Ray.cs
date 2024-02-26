using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ray : MonoBehaviour
{
    RaycastHit hit;
    float maxDistance = 15f;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

        //if (Input.GetKeyDown(KeyCode.Space))
        //{
            Debug.DrawRay(transform.position, transform.forward * maxDistance, Color.blue, 0.3f);

            if(Physics.Raycast(transform.position,transform.forward, out hit, maxDistance))
            {
                hit.transform.GetComponent<MeshRenderer>().material.color= Color.red;
            }
            else
            {
                hit.transform.GetComponent<MeshRenderer>().material.color = Color.blue;
            }
        //}


    }
}
