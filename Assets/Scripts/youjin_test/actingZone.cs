using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class actingZone : MonoBehaviour
{
    public GameObject ob_;
    Vector3 ob_position;

    // Start is called before the first frame update
    void Start()
    {
        ob_position = ob_.transform.position;//실제 오브젝트의 위치를 가져와서 
        gameObject.transform.position = ob_position;//액션존의 위치로 설정해줌

    }

    private void OnTriggerEnter(Collider other)
    {
        Debug.Log("onTriggerEnter is activated");
    }

    private void OnTriggerExit(Collider other)
    {
        Debug.Log("onTriggerExit is activated");
    }


    // Update is called once per frame
    void Update()
    {
        
    }
}
