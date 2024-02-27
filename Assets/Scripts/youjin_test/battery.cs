using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class battery : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Destroy(gameObject, 3f); // 3초뒤 오브젝트를 파괴   
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
