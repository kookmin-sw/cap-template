using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIpressF : MonoBehaviour
{
    public GameObject text_pressF;

    // Start is called before the first frame update
    void Start()
    {
        text_pressF.SetActive(false);
    }

    private void OnTriggerEnter(Collider other)
    {
        Debug.Log("onTriggerEnter is activated");
        text_pressF.SetActive(true);
    }

    private void OnTriggerExit(Collider other)
    {
            
        Debug.Log("onTriggerExit is activated");
        text_pressF.SetActive(false);
        
    }

    // Update is called once per frame
    void Update()
    {
     
        
    }
}
